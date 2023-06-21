/**
 * @file      RS485_Slave.ino
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @copyright Copyright (c) 2023  Shenzhen Xin Yuan Electronic Technology Co., Ltd
 * @date      2023-06-21
 *
 */
#include <Arduino.h>

#define BOARD_POWER_ON              4
#define BOARD_485_TX                39
#define BOARD_485_RX                38
#define BOARD_485_EN                42

#define Serial485 Serial2

uint32_t runningMillis = 0;
uint32_t counter = 0;

void setup()
{
    // Peripheral power supply is enabled, the Pin must be set to HIGH to use PCIE, RS485
    pinMode(BOARD_POWER_ON, OUTPUT);
    digitalWrite(BOARD_POWER_ON, HIGH);

    pinMode(BOARD_485_EN, OUTPUT);
    digitalWrite(BOARD_485_EN, HIGH);

    Serial.begin(115200);
    Serial485.begin(9600, SERIAL_8N1, BOARD_485_RX, BOARD_485_TX);
}


void loop()
{
    while (Serial.available()) {
        Serial485.write(Serial.read());
    }
    while (Serial485.available()) {
        String  recv = Serial485.readStringUntil('\n');
        Serial.print("<- Recver:");
        Serial.println(recv);
        Serial485.print("<-- Rspone :"); Serial485.println(recv);
    }
}







