"""
============================================================================
 시리얼 센서 데이터 AI 분석기 (Google Gemini + DHT11)
============================================================================
 STM32F429I-DISC1 + DHT11에서 UART로 수신한 온습도 데이터를
 Google Gemini API로 분석합니다.
 
 사용법:
   # 시뮬레이터 모드 (하드웨어 없이)
   python serial_ai_analyzer.py --simulate --model gemini-3.1-flash-lite

   # 실제 시리얼 포트 연결
   python serial_ai_analyzer.py --port /dev/ttyACM0 --model gemini-3.1-flash-lite
   python serial_ai_analyzer.py --port COM3 --model gemini-3.1-flash-lite  # Windows

   # 대화형 모드 (분석 후 추가 질문 가능)
   python serial_ai_analyzer.py --simulate --interactive --model gemini-3.1-flash-lite

 환경변수:
   GEMINI_API_KEY  - Google Gemini API 키 (필수)
   
 API 키 발급:
   https://aistudio.google.com/apikey 에서 무료 발급
============================================================================
"""

import os
import sys
import time
import json
import argparse
import re
import urllib.request
import urllib.error
from datetime import datetime


# ============================================================================
#  시스템 프롬프트 (★ 학생들이 수정할 부분 ★)
# ============================================================================
SYSTEM_PROMPT = """당신은 임베디드 시스템의 센서 데이터를 분석하는 AI 전문가입니다.

## 하드웨어 구성
- 보드: STM32F429I-DISC1 (ARM Cortex-M4, FreeRTOS)
- 센서: DHT11 (온습도 센서, PC11 핀)
- 조도 센서는 미연결 (LUX=0은 무시하세요)

## 디폴트 센서 정상 범위 (실내 환경 기준)
- 온도 (TEMP): 18~28°C
- 습도 (HUM): 40~70%

## 스마트 팜 모드 : 토마토 센서 정상 범위
- 온도 (TEMP): 20~25°C
- 습도 (HUM): 60~80%

## 서버실 관리자 모드 : 센서 정상 범위
- 온도 (TEMP): 18~24°C
- 습도 (HUM): 45~55%

## DHT11 센서 특성
- 온도 측정 범위: 0~50°C (정밀도 ±2°C)
- 습도 측정 범위: 20~90% (정밀도 ±5%)
- 측정 주기: 3초

## 디폴트 응답 규칙
- 한국어로 답변합니다. 대신 영어 응답 모드일 경우엔 모두 영어로 답해줍니다.(Respond in English)
- 간결하고 명확하게 분석합니다 (3~5줄 이내).
- 비정상 데이터 발견 시 ⚠️ 이모지를 사용합니다.
- 정상 데이터는 ✅로 표시합니다.
- 가능하면 데이터 트렌드(상승/하락/안정)도 언급합니다.
- 온도와 습도의 상관관계도 고려하여 분석합니다.
  (예: 온도 상승 + 습도 하락 → 건조한 환경)
- LUX 값은 0으로 고정이므로 분석에서 제외합니다.
- 환경 위험도 점수를 1~10 점수로 매겨줍니다.
"""


# ============================================================================
#  Gemini API 클라이언트 (추가 패키지 없이 urllib만 사용)
# ============================================================================
class GeminiClient:
    """
    Google Gemini API 클라이언트
    무료 티어: 분당 15회, 일 1,500회 호출 가능
    """

    BASE_URL = "https://generativelanguage.googleapis.com/v1beta/models"

    def __init__(self, api_key: str, model: str = "gemini-3.1-flash-lite"):
        self.api_key = api_key
        self.model = model

    def generate(self, conversation: list[dict], temperature: float = 0.3,
                 max_tokens: int = 500) -> dict:
        url = f"{self.BASE_URL}/{self.model}:generateContent?key={self.api_key}"

        contents = []
        for msg in conversation:
            contents.append({
                "role": msg["role"],
                "parts": [{"text": msg["text"]}]
            })

        payload = {
            "contents": contents,
            "systemInstruction": {
                "parts": [{"text": SYSTEM_PROMPT}]
            },
            "generationConfig": {
                "temperature": temperature,
                "maxOutputTokens": max_tokens
            }
        }

        data = json.dumps(payload).encode("utf-8")
        req = urllib.request.Request(
            url, data=data,
            headers={"Content-Type": "application/json"},
            method="POST"
        )

        # 자동 재시도 (429 Rate Limit 대응, 최대 3회)
        max_retries = 3
        for attempt in range(max_retries):
            try:
                with urllib.request.urlopen(req, timeout=30) as resp:
                    result = json.loads(resp.read().decode("utf-8"))

                text = result["candidates"][0]["content"]["parts"][0]["text"]
                usage = result.get("usageMetadata", {})

                return {
                    "text": text,
                    "prompt_tokens": usage.get("promptTokenCount", 0),
                    "output_tokens": usage.get("candidatesTokenCount", 0),
                    "total_tokens": usage.get("totalTokenCount", 0)
                }

            except urllib.error.HTTPError as e:
                error_body = e.read().decode("utf-8", errors="ignore")

                if e.code == 429 and attempt < max_retries - 1:
                    wait = (attempt + 1) * 10  # 10초, 20초, 30초
                    print(f"  ⏳ API 호출 한도 초과, {wait}초 후 재시도... "
                          f"({attempt + 1}/{max_retries})")
                    time.sleep(wait)
                    # 재시도를 위해 Request 객체 재생성 (한 번 쓰면 소비됨)
                    req = urllib.request.Request(
                        url, data=data,
                        headers={"Content-Type": "application/json"},
                        method="POST"
                    )
                    continue

                raise RuntimeError(f"Gemini API 오류 ({e.code}): {error_body}")

            except urllib.error.URLError as e:
                raise RuntimeError(f"네트워크 오류: {e.reason}")

        raise RuntimeError("API 호출 재시도 횟수 초과")


# ============================================================================
#  데이터 파서
# ============================================================================
class SensorDataParser:
    """STM32 UART 프로토콜 파싱"""

    PATTERN = re.compile(
        r"SENSOR:TEMP=([-\d.]+),HUM=([-\d.]+),LUX=([-\d.]+)"
    )

    @staticmethod
    def parse(line: str) -> dict | None:
        match = SensorDataParser.PATTERN.search(line)
        if not match:
            return None

        return {
            "temperature": float(match.group(1)),
            "humidity": float(match.group(2)),
            "lux": float(match.group(3)),
            "raw": line.strip(),
            "timestamp": datetime.now().isoformat()
        }


# ============================================================================
#  AI 분석기
# ============================================================================
class AIAnalyzer:
    """Google Gemini API를 사용한 센서 데이터 분석기"""

    def __init__(self, model: str = "gemini-3.1-flash-lite"):
        api_key = os.environ.get("GEMINI_API_KEY")
        if not api_key:
            print("=" * 60)
            print("  [오류] GEMINI_API_KEY 환경변수가 설정되지 않았습니다.")
            print()
            print("  ┌─ API 키 발급 방법 (무료, 2분) ──────────────┐")
            print("  │                                              │")
            print("  │  1. https://aistudio.google.com/apikey 접속  │")
            print("  │  2. Google 계정으로 로그인                    │")
            print("  │  3. 'Create API Key' 클릭                    │")
            print("  │  4. 키 복사 후 아래 명령어 실행               │")
            print("  │                                              │")
            print("  └──────────────────────────────────────────────┘")
            print()
            print("  Linux/Mac:")
            print("    export GEMINI_API_KEY='여기에-키-붙여넣기'")
            print()
            print("  Windows CMD:")
            print("    set GEMINI_API_KEY=여기에-키-붙여넣기")
            print()
            print("  Windows PowerShell:")
            print('    $env:GEMINI_API_KEY="여기에-키-붙여넣기"')
            print("=" * 60)
            sys.exit(1)

        self.client = GeminiClient(api_key=api_key, model=model)
        self.model = model
        self.conversation_history = []

    def analyze(self, data_list: list[dict]) -> str:
        """센서 데이터 리스트를 분석하여 자연어 응답 반환"""

        self.conversation_history = []
        data_text = self._format_data(data_list)

        user_message = f"""다음 DHT11 센서 데이터를 분석해주세요:

{data_text}

각 센서값의 정상/비정상 여부와 전체적인 환경 상태를 평가해주세요."""

        self.conversation_history.append({
            "role": "user",
            "text": user_message
        })

        try:
            response = self.client.generate(
                conversation=self.conversation_history,
                temperature=0.3,
                max_tokens=500
            )

            assistant_msg = response["text"]
            self.conversation_history.append({
                "role": "model",
                "text": assistant_msg
            })

            print(f"  [토큰] 입력: {response['prompt_tokens']}, "
                  f"출력: {response['output_tokens']}, "
                  f"합계: {response['total_tokens']}")

            return assistant_msg

        except Exception as e:
            return f"[API 오류] {str(e)}"

    def ask(self, question: str) -> str:
        """자유 질문 (대화형 모드)"""
        self.conversation_history.append({
            "role": "user",
            "text": question
        })

        try:
            response = self.client.generate(
                conversation=self.conversation_history,
                temperature=0.5,
                max_tokens=800
            )

            assistant_msg = response["text"]
            self.conversation_history.append({
                "role": "model",
                "text": assistant_msg
            })
            return assistant_msg

        except Exception as e:
            return f"[API 오류] {str(e)}"

    def _format_data(self, data_list: list[dict]) -> str:
        """데이터를 읽기 쉬운 텍스트로 변환 (LUX 제외)"""
        lines = []
        for i, d in enumerate(data_list, 1):
            ts = d.get("timestamp", "N/A")
            if "T" in ts:
                ts = ts.split("T")[1][:8]
            lines.append(
                f"  [{i}] 시각: {ts} | "
                f"온도: {d['temperature']}°C | "
                f"습도: {d['humidity']}%"
            )
        return "\n".join(lines)


# ============================================================================
#  시리얼 수신기
# ============================================================================
class SerialReceiver:
    """시리얼 포트에서 센서 데이터 수신"""

    def __init__(self, port: str, baudrate: int = 115200):
        try:
            import serial
            self.ser = serial.Serial(port, baudrate, timeout=1)
            print(f"[시리얼] {port} 연결됨 (baud: {baudrate})")
        except ImportError:
            print("[오류] pyserial 패키지가 필요합니다.")
            print("       pip install pyserial")
            sys.exit(1)
        except Exception as e:
            print(f"[오류] 시리얼 포트 연결 실패: {e}")
            sys.exit(1)

    def readline(self) -> str | None:
        try:
            line = self.ser.readline().decode('utf-8', errors='ignore').strip()
            return line if line else None
        except Exception:
            return None

    def close(self):
        self.ser.close()


# ============================================================================
#  시뮬레이터 수신기 (파일 기반)
# ============================================================================
class SimulatorReceiver:
    """sensor_simulator.py가 기록한 파일에서 데이터 읽기"""

    def __init__(self, filepath: str = "sensor_data.txt"):
        self.filepath = filepath
        self.last_pos = 0

        if os.path.exists(filepath):
            self.last_pos = os.path.getsize(filepath)

    def readline(self) -> str | None:
        if not os.path.exists(self.filepath):
            return None

        try:
            with open(self.filepath, "r", encoding="utf-8") as f:
                f.seek(self.last_pos)
                line = f.readline()
                if line:
                    self.last_pos = f.tell()
                    return line.strip()
        except Exception:
            pass
        return None

    def close(self):
        pass


# ============================================================================
#  메인
# ============================================================================
def main():
    parser = argparse.ArgumentParser(
        description="DHT11 센서 데이터 AI 분석기 (Gemini)")
    parser.add_argument("--port", type=str, default=None,
                        help="시리얼 포트 (예: /dev/ttyACM0, COM3)")
    parser.add_argument("--baud", type=int, default=115200,
                        help="보드레이트 (기본: 115200)")
    parser.add_argument("--simulate", action="store_true",
                        help="시뮬레이터 모드 (sensor_data.txt에서 읽기)")
    parser.add_argument("--batch", type=int, default=5,
                        help="한 번에 분석할 데이터 개수 (기본: 5)")
    parser.add_argument("--model", type=str, default="gemini-3.1-flash-lite",
                        help="Gemini 모델 (기본: gemini-3.1-flash-lite)")
    parser.add_argument("--interactive", action="store_true",
                        help="대화형 모드 (분석 후 추가 질문 가능)")
    args = parser.parse_args()

    # 수신기 선택
    if args.simulate:
        receiver = SimulatorReceiver()
        print("[모드] 시뮬레이터 모드 (DHT11)")
        print("[안내] 다른 터미널에서 'python sensor_simulator.py' 실행하세요\n")
    elif args.port:
        receiver = SerialReceiver(args.port, args.baud)
    else:
        print("[오류] --model --port 또는 --simulate 옵션을 지정하세요.")
        print("  예: python serial_ai_analyzer.py --simulate --model gemini-3.1-flash-lite")
        print("  예: python serial_ai_analyzer.py --port /dev/ttyACM0 --model gemini-3.1-flash-lite")
        print("  예: python serial_ai_analyzer.py --port COM3 --model gemini-3.1-flash-lite")
        sys.exit(1)

    # AI 분석기 초기화
    analyzer = AIAnalyzer(model=args.model)

    print("=" * 60)
    print("  🤖 DHT11 센서 데이터 AI 분석기")
    print(f"  보드: STM32F429I-DISC1")
    print(f"  센서: DHT11 (온도 + 습도)")
    print(f"  모델: {args.model}")
    print(f"  분석 단위: {args.batch}개씩")
    print(f"  💰 비용: 무료 (Gemini API Free Tier)")
    print("=" * 60)
    print("  데이터 수신 대기 중... (Ctrl+C로 종료)\n")

    data_buffer = []
    parser_obj = SensorDataParser()
    error_count = 0

    try:
        while True:
            line = receiver.readline()

            if line:
                # 시스템 메시지 표시
                if line.startswith("SYSTEM:") or line.startswith("[Task]"):
                    print(f"  📡 {line}")
                    continue

                # 센서 에러 메시지 처리
                if "ERROR" in line:
                    error_count += 1
                    print(f"  ❌ 센서 읽기 실패 (#{error_count}): {line}")
                    continue

                # 센서 데이터 파싱
                data = parser_obj.parse(line)
                if data:
                    data_buffer.append(data)
                    print(f"  [수신 {len(data_buffer)}/{args.batch}] "
                          f"T={data['temperature']}°C  "
                          f"H={data['humidity']}%")

                    # 배치 단위로 AI 분석
                    if len(data_buffer) >= args.batch:
                        print("\n" + "─" * 60)
                        print("  🤖 AI 분석 중...")
                        print("─" * 60)

                        result = analyzer.analyze(data_buffer)
                        print(f"\n{result}\n")
                        time.sleep(5)

                        # 대화형 모드
                        if args.interactive:
                            print("─" * 60)
                            print("  추가 질문을 입력하세요 (Enter로 건너뛰기)")
                            print("  예: '이 온도에서 식물 키우기 괜찮아?'")
                            print("  예: '에어컨을 켜야 할까?'")
                            print("─" * 60)
                            while True:
                                question = input("  > ").strip()
                                if not question:
                                    break
                                answer = analyzer.ask(question)
                                print(f"\n{answer}\n")

                        data_buffer = []
                        print("\n  다음 데이터 수신 대기 중...\n")
            else:
                time.sleep(0.5)

    except KeyboardInterrupt:
        print(f"\n\n[분석기] 종료됨 (센서 에러: {error_count}회)")
    finally:
        receiver.close()


if __name__ == "__main__":
    main()
