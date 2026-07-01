/*
 * dht11.h
 *
 *  Created on: Jun 25, 2025
 *      Author: admin
 */

#ifndef INC_DHT11_H_
#define INC_DHT11_H_

#include "main.h"

/* ── 설정 ────────────────────────────────────────────── */

// 폴링 주기 제한 (너무 빠른 연속 호출 방지)
#define DHT_POLLING_CONTROL       1
#define DHT_POLLING_INTERVAL_DHT11  1200   // DHT11: 최소 1초 간격
#define DHT_POLLING_INTERVAL_DHT22  2200   // DHT22: 최소 2초 간격

// 데이터 수신 중 인터럽트 비활성화 (타이밍 정확도 향상)
#define DHT_IRQ_CONTROL

// 타임아웃 임계값
#define DHT_TIMEOUT  10000

/* ── 타입 정의 ───────────────────────────────────────── */

// 센서 종류
typedef enum {
    DHT11,
    DHT22
} DHT_type;

// 센서 데이터
typedef struct {
    float temp;    // 온도 (°C)
    float hum;     // 습도 (%)
} DHT_data;

// 센서 구조체
typedef struct {
    GPIO_TypeDef *DHT_Port;    // GPIO 포트 (예: GPIOC)
    uint16_t      DHT_Pin;     // GPIO 핀  (예: GPIO_PIN_11)
    DHT_type      type;        // 센서 종류 (DHT11 또는 DHT22)
    uint32_t      pullUp;      // 풀업 설정 (GPIO_NOPULL 또는 GPIO_PULLUP)

#if DHT_POLLING_CONTROL == 1
    uint32_t      lastPollingTime;  // 마지막 측정 시각
    float         lastTemp;         // 마지막 온도값
    float         lastHum;          // 마지막 습도값
#endif
} DHT_sensor;

/* ── 함수 프로토타입 ─────────────────────────────────── */

/**
 * @brief  DHT 센서에서 온습도 데이터를 읽어옴
 * @param  sensor: DHT_sensor 구조체 포인터
 * @retval DHT_data (temp, hum) - 실패 시 -128.0f
 */
DHT_data DHT_getData(DHT_sensor *sensor);

#endif /* INC_DHT11_H_ */
