# 🔧 임베디드 AI 실습: Gemini API로 DHT11 센서 데이터 분석기 만들기

## 📋 실습 개요

STM32F429I-DISC1 보드에 연결된 **DHT11 센서**에서 온습도 데이터를 UART로 수신하고,
**Google Gemini API (무료)** 를 활용하여 AI가 자연어로 데이터를 분석하는 시스템을 구축합니다.

> 💰 **비용: 완전 무료!** Gemini API Free Tier (분당 15회, 일 1,500회)

<img src="./asset/pic001.png" alt="시스템 구성도" width="480">

## 🏗️ 시스템 구조

```
[STM32F429I-DISC1]     [PC]                    [Cloud]
                                                
  DHT11 센서            Python 분석기            Gemini AI
  (PC11 핀)             serial_ai_analyzer.py    (gemini-2.0-flash)
     │                       │                       │
     │  온도/습도 측정        │                       │
     ▼                       │                       │
  SensorTask ──Queue──► UartTask                     │
                           │                         │
                    SENSOR:TEMP=25.3,                 │
                    HUM=62.1,LUX=0                   │
                           │                         │
                      USART1 (VCP)                   │
                           │                         │
                           ▼                         │
                      시리얼 수신 ──── HTTP API ────► 분석 요청
                           │                         │
                           │         ◄──────────── AI 응답
                           ▼
                      터미널에 분석 결과 출력
```

## 📁 파일 구성

```
embedded-ai-lab/
├── firmware/                      # STM32 펌웨어
│   ├── main.c                     # 메인 코드 (수정된 UartTask 포함)
│   ├── dht11.h                    # DHT11 드라이버 헤더
│   └── dht11.c                    # DHT11 드라이버 소스
├── sensor_simulator.py            # 하드웨어 없이 테스트하는 시뮬레이터
├── serial_ai_analyzer.py          # 메인 프로그램 (시리얼 수신 + AI 분석)
├── requirements.txt               # Python 패키지
└── README.md                      # 이 파일
```

## ⚙️ 사전 준비

### 1. Python 패키지 설치

```bash
pip install pyserial
```

> Gemini API는 Python 내장 `urllib`만 사용하므로 별도 패키지 불필요!

### 2. Gemini API 키 발급 (무료, 2분 소요)

  참고 https://m.blog.naver.com/ryurime88/224153496396

1. **https://aistudio.google.com/apikey** 접속
2. Google 계정으로 로그인
3. **"Create API Key"** 클릭
4. 생성된 키 복사

### 3. 환경변수 설정

```bash
# Linux/Mac
export GEMINI_API_KEY="여기에-복사한-키-붙여넣기"

# Windows CMD
set GEMINI_API_KEY=여기에-복사한-키-붙여넣기

# Windows PowerShell
$env:GEMINI_API_KEY="여기에-복사한-키-붙여넣기"
```

---

## 🚀 실습 진행 순서

### Step 1: 시뮬레이터로 기본 동작 확인 (보드 없이!)

터미널 2개를 열어주세요.

**터미널 1 - 시뮬레이터:**
```bash
python sensor_simulator.py
```

**터미널 2 - AI 분석기:**
```bash
python serial_ai_analyzer.py --simulate
```

약 15초(3초 × 5개) 후 첫 번째 AI 분석 결과가 출력됩니다.

### Step 2: 비정상 데이터 테스트

```bash
# 터미널 1 (15% 확률로 과열/저온/과습/건조 데이터 생성)
python sensor_simulator.py --anomaly

# 터미널 2
python serial_ai_analyzer.py --simulate
```

AI가 이상 데이터를 감지하고 원인/조치를 제안하는 걸 확인해보세요.

### Step 3: 대화형 모드

```bash
python serial_ai_analyzer.py --simulate --interactive
```

분석 후 추가 질문 예시:
- "이 온도에서 식물 키우기 괜찮아?"
- "습도가 더 떨어지면 어떤 문제가 생길 수 있어?"
- "서버실 기준으로 다시 분석해줘"

### Step 4: 프롬프트 커스터마이징 (★ 도전 과제 ★)

`serial_ai_analyzer.py`의 **`SYSTEM_PROMPT`** 를 수정해보세요!

| 도전 과제 | 힌트 |
|----------|------|
| 스마트 팜 모드 | 정상 범위를 작물별로 변경 (토마토: 20~25°C, 습도 60~80%) |
| 서버실 관리자 모드 | 온도 18~24°C, 습도 45~55%로 더 엄격하게 |
| 영어 응답 모드 | "Respond in English" 추가 |
| JSON 출력 모드 | 구조화된 데이터로 응답하게 변경 |
| 위험도 점수 모드 | 1~10 점수로 환경 위험도를 매겨달라고 요청 |

### Step 5: 실제 STM32F429I-DISC1 보드 연결

1. `firmware/` 폴더의 파일들을 CubeIDE 프로젝트에 복사
   - `dht11.h` → `Core/Inc/` 폴더
   - `dht11.c` → `Core/Src/` 폴더
   - `main.c` → 기존 `Core/Src/main.c` 교체
2. DHT11 센서 연결:
   ```
   DHT11          STM32F429I-DISC1
   VCC ────────── 3.3V
   DATA ───────── PC11
   GND ────────── GND
   ```
   > 💡 DATA와 VCC 사이에 4.7kΩ 풀업 저항 권장 (없어도 동작할 수 있음)
3. 빌드 & 다운로드
4. 시리얼 포트 확인 후 분석기 연결:

```bash
# Linux
python serial_ai_analyzer.py --port /dev/ttyACM0

# Mac
python serial_ai_analyzer.py --port /dev/cu.usbmodem14101

# Windows
python serial_ai_analyzer.py --port COM3
```

---

## 📊 UART 데이터 프로토콜

### 센서 데이터
```
SENSOR:TEMP=25.0,HUM=62.0,LUX=0\r\n
```

| 필드 | 설명 | 단위 | 정상 범위 |
|------|------|------|-----------|
| TEMP | 온도 | °C | 18~28 |
| HUM | 습도 | % | 40~70 |
| LUX | 조도 (미연결) | lux | 항상 0 |

### 시스템 메시지
```
SYSTEM:READY,BOARD:STM32F429I-DISC1,SENSOR:DHT11\r\n
```

### 에러 메시지
```
SENSOR:ERROR=READ_FAIL\r\n
```

---

## 🔑 Gemini API 참고

| 항목 | 내용 |
|------|------|
| 모델 | gemini-2.0-flash (기본, 무료) |
| 무료 한도 | 분당 15회, 일 1,500회 |
| API 문서 | https://ai.google.dev/gemini-api/docs |
| 키 관리 | https://aistudio.google.com/apikey |

---

## 🏛️ 소프트웨어 아키텍처 (FreeRTOS)

```
┌─────────────┐     ┌──────────────┐     ┌─────────────┐
│ SensorTask  │     │   Queue      │     │  UartTask   │
│             │     │ (10 items)   │     │             │
│ DHT11 읽기  ├────►│ DHT_data     ├────►│ 프로토콜    │
│ 3초 주기    │     │ {temp, hum}  │     │ 포맷 변환   │
│             │     │              │     │ + UART 전송  │
└─────────────┘     └──────────────┘     └─────────────┘
```

- **SensorTask**: DHT11에서 온습도 읽기 → 큐에 전달
- **UartTask**: 큐에서 데이터 수신 → 프로토콜 포맷으로 UART 전송
- **Queue**: 태스크 간 안전한 데이터 전달 (FreeRTOS xQueue)

---

## ❓ 트러블슈팅

| 증상 | 해결 |
|------|------|
| API 키 오류 | `echo $GEMINI_API_KEY`로 설정 확인 |
| 429 에러 (Rate Limit) | `--batch 10`으로 늘려서 호출 빈도 감소 |
| 센서 READ_FAIL | DHT11 배선 확인, 풀업 저항 추가, 3.3V 전원 확인 |
| COM 포트 안 보임 | ST-Link 드라이버 설치, USB 케이블 교체 |
| 데이터 깨짐 | 양쪽 Baud Rate 115200 확인 |
| 온도 -128°C 표시 | DHT11 연결 불량 (체크섬 실패) |
