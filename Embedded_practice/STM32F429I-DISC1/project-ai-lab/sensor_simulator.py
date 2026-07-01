"""
============================================================================
 DHT11 센서 데이터 시뮬레이터
============================================================================
 STM32 보드 없이 실습할 수 있도록 DHT11 가상 센서 데이터를 생성합니다.
 
 사용법:
   python sensor_simulator.py                  # 기본 (정상 데이터)
   python sensor_simulator.py --anomaly        # 비정상 데이터 포함
   python sensor_simulator.py --interval 1     # 1초 간격

 동작:
   sensor_data.txt 파일에 데이터를 기록합니다.
   serial_ai_analyzer.py가 이 파일을 읽어 AI 분석을 수행합니다.
============================================================================
"""

import time
import random
import math
import argparse
import os
from datetime import datetime

FILE_NAME = "sensor_data.txt"
with open(FILE_NAME, "w", encoding="utf-8") as f:
    pass # 'w' 모드로 열면 자동으로 내용이 비워집니다.
print(f"[시스템] {FILE_NAME} 파일의 과거 기록을 모두 삭제하고 새로 시작합니다.\n")

class DHT11Simulator:
    """DHT11 센서 시뮬레이터 (온도 + 습도, 조도 없음)"""

    def __init__(self, anomaly_mode=False):
        self.anomaly_mode = anomaly_mode
        self.tick = 0

        # DHT11 스펙 기반 기본값
        # 온도 측정 범위: 0~50°C, 정밀도: ±2°C
        # 습도 측정 범위: 20~90%, 정밀도: ±5%
        self.temp_base = 24.0
        self.hum_base = 55.0

    def generate(self) -> dict:
        """센서 데이터 1회 생성"""
        self.tick += 1

        time_factor = math.sin(self.tick * 0.1)

        # DHT11은 정수 단위 출력 (소수점 1자리까지 확장)
        temp = self.temp_base + time_factor * 2.0 + random.gauss(0, 0.5)
        hum = self.hum_base - time_factor * 5.0 + random.gauss(0, 1.5)

        # 비정상 데이터 주입
        if self.anomaly_mode and random.random() < 0.15:
            anomaly_type = random.choice(["hot", "cold", "humid", "dry"])
            if anomaly_type == "hot":
                temp = random.uniform(35.0, 48.0)
            elif anomaly_type == "cold":
                temp = random.uniform(0.0, 10.0)
            elif anomaly_type == "humid":
                hum = random.uniform(85.0, 95.0)
            elif anomaly_type == "dry":
                hum = random.uniform(15.0, 25.0)

        # DHT11 범위 클리핑
        temp = round(max(0.0, min(50.0, temp)), 1)
        hum = round(max(20.0, min(90.0, hum)), 1)

        return {
            "temperature": temp,
            "humidity": hum,
            "timestamp": datetime.now().isoformat()
        }

    def to_uart_format(self, data: dict) -> str:
        """STM32 UART 프로토콜 형식으로 변환 (LUX=0 고정)"""
        return f"SENSOR:TEMP={data['temperature']},HUM={data['humidity']},LUX=0\n"


def main():
    parser = argparse.ArgumentParser(description="DHT11 센서 데이터 시뮬레이터")
    parser.add_argument("--anomaly", action="store_true",
                        help="비정상 데이터를 간헐적으로 생성")
    parser.add_argument("--interval", type=float, default=5.0,
                        help="데이터 생성 주기 (초, 기본: 3.0)")
    parser.add_argument("--output", type=str, default="sensor_data.txt",
                        help="출력 파일 경로 (기본: sensor_data.txt)")
    args = parser.parse_args()

    sim = DHT11Simulator(anomaly_mode=args.anomaly)

    print("=" * 60)
    print("  DHT11 센서 데이터 시뮬레이터")
    print(f"  모드: {'비정상 데이터 포함' if args.anomaly else '정상 데이터'}")
    print(f"  주기: {args.interval}초")
    print(f"  출력: {args.output}")
    print("=" * 60)
    print("  Ctrl+C로 종료\n")

    count = 0
    try:
        while True:
            count += 1
            data = sim.generate()
            uart_line = sim.to_uart_format(data)

            ts = data['timestamp'].split('T')[1][:8]
            print(f"  [#{count:04d}] T={data['temperature']}°C  "
                  f"H={data['humidity']}%  ({ts})")

            with open(args.output, "a", encoding="utf-8") as f:
                f.write(uart_line)

            time.sleep(args.interval)

    except KeyboardInterrupt:
        print("\n\n[시뮬레이터] 종료됨")


if __name__ == "__main__":
    main()
