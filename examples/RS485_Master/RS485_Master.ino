/**
 * @file      RS485_Master.ino
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @copyright Copyright (c) 2023  Shenzhen Xin Yuan Electronic Technology Co., Ltd
 * @date      2023-06-21
 *
 */

#define SerialMon   Serial
#define Serial485   Serial2

#define MODEM_PWRKEY_PIN            9
#define MODEM_TX_PIN                3
#define MODEM_RX_PIN                46
#define BOARD_POWER_ON              4
#define BOARD_485_TX                39
#define BOARD_485_RX                38
#define BOARD_485_EN                42
#define GPIO_PUSE                   16


#include <Ticker.h>
#include <Arduino.h>


Ticker paues;
uint32_t runningMillis = 0;
uint32_t counter = 0;

void setup()
{
    // Set console baud rate
    SerialMon.begin(115200);

    delay(3000);


    Serial485.begin(9600, SERIAL_8N1, BOARD_485_RX, BOARD_485_TX);

    pinMode(GPIO_PUSE, OUTPUT);

    paues.attach_ms(1000, []() {
        digitalWrite(GPIO_PUSE, 1 - digitalRead(GPIO_PUSE));
    });

    // Peripheral power supply is enabled, the Pin must be set to HIGH to use PCIE, RS485
    pinMode(BOARD_POWER_ON, OUTPUT);
    digitalWrite(BOARD_POWER_ON, HIGH);

    pinMode(BOARD_485_EN, OUTPUT);
    digitalWrite(BOARD_485_EN, LOW);

}

void loop()
{
    if (runningMillis < millis()) {
        runningMillis = millis() + 2000;
        Serial485.print("[");
        Serial485.print(millis());
        Serial485.print("]");
        Serial485.print(" Counter:");
        Serial485.println(counter++);

        Serial.print("Sender -> [");
        Serial.print(millis());
        Serial.print("]");
        Serial.print(" Millis:");
        Serial.println(counter++);

    }

    while (Serial485.available()) {
        SerialMon.write(Serial485.read());
    }
    while (SerialMon.available()) {
        Serial485.write(SerialMon.read());
    }

}
