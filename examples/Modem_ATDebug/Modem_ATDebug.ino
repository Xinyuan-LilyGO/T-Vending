/**
 * @file      Modem_ATDebug.ino
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @copyright Copyright (c) 2023  Shenzhen Xin Yuan Electronic Technology Co., Ltd
 * @date      2023-06-21
 *
 */

// #define TINY_GSM_MODEM_SIM800
// #define TINY_GSM_MODEM_SIM868
// #define TINY_GSM_MODEM_SIM7000
// #define TINY_GSM_MODEM_SIM7000SSL
// #define TINY_GSM_MODEM_SIM7080
#define TINY_GSM_MODEM_SIM7600               //SIM7600NA/SA/G/E, A7608/A7670

#define SerialMon   Serial
#define SerialAT    Serial1

#define MODEM_PWRKEY_PIN            9
#define MODEM_TX_PIN                3
#define MODEM_RX_PIN                46
#define MODEM_RI_PIN                11
#define MODEM_DTR_PIN               12
#define BOARD_POWER_ON              4

// See all AT commands, if wanted
// #define DUMP_AT_COMMANDS
// Define the serial console for debug prints, if needed
#define TINY_GSM_DEBUG SerialMon

#include <TinyGsmClient.h>


#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm        modem(debugger);

#else
TinyGsm        modem(SerialAT);
#endif

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

    SerialAT.begin(115200, SERIAL_8N1, MODEM_RX_PIN, MODEM_TX_PIN);

    pinMode(BOARD_POWER_ON, OUTPUT);
    digitalWrite(BOARD_POWER_ON, HIGH);

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
    while (SerialAT.available()) {
        SerialMon.write(SerialAT.read());
    }
    while (SerialMon.available()) {
        SerialAT.write(SerialMon.read());
    }
    delay(1);
}
