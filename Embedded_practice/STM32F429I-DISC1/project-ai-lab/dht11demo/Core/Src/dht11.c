/*
 * dht11.c
 *
 *  Created on: Jun 25, 2025
 *      Author: admin
 */
#include "dht11.h"
#include <math.h>

// 핀 제어 매크로
#define lineDown() HAL_GPIO_WritePin(sensor->DHT_Port, sensor->DHT_Pin, GPIO_PIN_RESET)
#define lineUp()   HAL_GPIO_WritePin(sensor->DHT_Port, sensor->DHT_Pin, GPIO_PIN_SET)
#define getLine()  (HAL_GPIO_ReadPin(sensor->DHT_Port, sensor->DHT_Pin) == GPIO_PIN_SET)
#define Delay(d)   HAL_Delay(d)

// 핀을 출력 모드로 설정
static void goToOutput(DHT_sensor *sensor) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    lineUp();

    GPIO_InitStruct.Pin   = sensor->DHT_Pin;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = sensor->pullUp;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(sensor->DHT_Port, &GPIO_InitStruct);
}

// 핀을 입력 모드로 설정
static void goToInput(DHT_sensor *sensor) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin  = sensor->DHT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = sensor->pullUp;
    HAL_GPIO_Init(sensor->DHT_Port, &GPIO_InitStruct);
}

// 센서 데이터 읽기
DHT_data DHT_getData(DHT_sensor *sensor) {
    DHT_data data = {-128.0f, -128.0f};

#if DHT_POLLING_CONTROL == 1
    uint16_t pollingInterval = (sensor->type == DHT11)
                             ? DHT_POLLING_INTERVAL_DHT11
                             : DHT_POLLING_INTERVAL_DHT22;

    if ((HAL_GetTick() - sensor->lastPollingTime < pollingInterval)
        && sensor->lastPollingTime != 0) {
        data.hum  = sensor->lastHum;
        data.temp = sensor->lastTemp;
        return data;
    }
    sensor->lastPollingTime = HAL_GetTick() + 1;
#endif

    // ① 데이터 요청: 18ms LOW → HIGH → 입력 전환
    goToOutput(sensor);
    lineDown();
    Delay(18);
    lineUp();
    goToInput(sensor);

#ifdef DHT_IRQ_CONTROL
    __disable_irq();
#endif

    // ② 센서 응답 대기 (LOW → HIGH → LOW)
    uint16_t timeout = 0;
    while (getLine())  { if (++timeout > DHT_TIMEOUT) goto fail; }
    timeout = 0;
    while (!getLine()) { if (++timeout > DHT_TIMEOUT) goto fail; }
    timeout = 0;
    while (getLine())  { if (++timeout > DHT_TIMEOUT) goto fail; }

    // ③ 데이터 수신 (40비트: 습도16 + 온도16 + 체크섬8)
    uint8_t rawData[5] = {0};
    for (uint8_t a = 0; a < 5; a++) {
        for (uint8_t b = 7; b != 255; b--) {
            uint16_t hT = 0, lT = 0;

            while (!getLine() && lT != 65535) lT++;
            while (getLine()  && hT != 65535) hT++;

            if (hT > lT) rawData[a] |= (1 << b);
        }
    }

#ifdef DHT_IRQ_CONTROL
    __enable_irq();
#endif

    // ④ 체크섬 확인 및 파싱
    if ((uint8_t)(rawData[0] + rawData[1] + rawData[2] + rawData[3]) == rawData[4]) {
        if (sensor->type == DHT22) {
            data.hum = (float)(((uint16_t)rawData[0] << 8) | rawData[1]) * 0.1f;
            if (!(rawData[2] & (1 << 7))) {
                data.temp = (float)(((uint16_t)rawData[2] << 8) | rawData[3]) * 0.1f;
            } else {
                rawData[2] &= ~(1 << 7);
                data.temp = -((float)(((uint16_t)rawData[2] << 8) | rawData[3]) * 0.1f);
            }
        }
        if (sensor->type == DHT11) {
            data.hum  = (float)rawData[0];
            data.temp = (float)rawData[2];
        }
    }

#if DHT_POLLING_CONTROL == 1
    sensor->lastHum  = data.hum;
    sensor->lastTemp = data.temp;
#endif

    return data;

fail:
#ifdef DHT_IRQ_CONTROL
    __enable_irq();
#endif
    sensor->lastHum  = -128.0f;
    sensor->lastTemp = -128.0f;
    return data;
}
