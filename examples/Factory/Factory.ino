/**
 * @file      Factory.ino
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @copyright Copyright (c) 2023  Shenzhen Xin Yuan Electronic Technology Co., Ltd
 * @date      2023-06-21
 *
 */

// By default, SIM7600 PCIE is used for testing
#ifndef TINY_GSM_MODEM_SIM7600
#define TINY_GSM_MODEM_SIM7600
#endif

#define SerialMon   Serial
#define SerialAT    Serial1
#define Serial485   Serial2

#define MODEM_PWRKEY_PIN            9
#define MODEM_TX_PIN                3
#define MODEM_RX_PIN                46
#define MODEM_RI_PIN                11
#define MODEM_DTR_PIN               12
#define BOARD_POWER_ON              4
#define BOARD_485_TX                39
#define BOARD_485_RX                38
#define BOARD_485_EN                42
#define GPIO_PUSE                   16



// See all AT commands, if wanted
// #define DUMP_AT_COMMANDS
// Define the serial console for debug prints, if needed
#define TINY_GSM_DEBUG SerialMon

#include <TinyGsmClient.h>
#include <Ticker.h>


#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm        modem(debugger);

#else
TinyGsm        modem(SerialAT);
#endif
Ticker paues;
uint32_t runningMillis = 0;
uint32_t counter = 0;


bool testModem()
{
    int retry = 0;
    while (!modem.testAT(800)) {
        if (retry++ > 5) {
            return false;
        }
    }
    return true;
}

void setup()
{
    // Set console baud rate
    SerialMon.begin(115200);

    delay(3000);


    SerialAT.begin(115200, SERIAL_8N1, MODEM_RX_PIN, MODEM_TX_PIN);

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


    pinMode(MODEM_PWRKEY_PIN, OUTPUT);
    digitalWrite(MODEM_PWRKEY_PIN, LOW);
    delay(100);
    digitalWrite(MODEM_PWRKEY_PIN, HIGH);
    delay(1000);
    digitalWrite(MODEM_PWRKEY_PIN, LOW);


    Serial.println("[INFO]:Wait modem respone .");
    while (!testModem()) {
        Serial.print(".");
    }
    Serial.println();

    String name = modem.getModemName();
    SerialMon.print("[INFO]:Modem Name:"); Serial.println(name);

    while (modem.getSimStatus() != SIM_READY) {
        Serial.println("[ERROR]:SIM Card is not insert!!!");
        delay(500);
    }

    Serial.println("[INFO]:SIM Card is ready!");
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
