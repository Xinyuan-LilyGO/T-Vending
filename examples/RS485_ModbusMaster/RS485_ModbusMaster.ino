/**
 * @file      RS485_ModbusMaster.ino
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @copyright Copyright (c) 2026  ShenZhen XinYuan Electronic Technology Co., Ltd
 * @date      2026-03-17
 *
 */
#include <ModbusMaster.h>

#define BOARD_485_TX    39
#define BOARD_485_RX    38
#define BOARD_485_EN    42
#define RS485_EN_LEVEL  LOW
#define BOARD_POWER_ON   4

#define SLAVE_ID        1         // Slave address (same as slave program)

ModbusMaster node;

void setup()
{
    Serial.begin(115200);

    // Peripheral power supply is enabled, the Pin must be set to HIGH to use PCIE, RS485
    pinMode(BOARD_POWER_ON, OUTPUT);
    digitalWrite(BOARD_POWER_ON, HIGH);

    // RS485 Drive LOW to normal operation , HIGH to put the part in shutdown.
    pinMode(BOARD_485_EN, OUTPUT);
    digitalWrite(BOARD_485_EN, RS485_EN_LEVEL);

    Serial2.begin(2400, SERIAL_8N1, BOARD_485_RX, BOARD_485_TX);

    node.begin(SLAVE_ID, Serial2);

    Serial.println("The main site has started and will send requests to the slave sites...");
}

void loop()
{
    uint8_t result;
    static bool coilState = true;

    // -----1. Write a single coil (Function code 0x05) -----
    Serial.print("Write coil 0x0002 to ");
    Serial.println(coilState ? "ON" : "OFF");
    result = node.writeSingleCoil(0x0002, coilState);
    if (result == node.ku8MBSuccess) {
        Serial.println("  Coil write successful");
    } else {
        Serial.print("  Coil write failed, error code: 0x");
        Serial.println(result, HEX);
    }
    coilState = !coilState;
    delay(1000);

    // ----- 2. Write Single Register (Function Code 0x06) -----
    Serial.print("Write holding register 0x0000 to 1234");
    result = node.writeSingleRegister(0x0000, 1234);
    if (result == node.ku8MBSuccess) {
        Serial.println("  Register write successful");
    } else {
        Serial.print("  Register write failed, error code: 0x");
        Serial.println(result, HEX);
    }
    delay(1000);

    // ----- 3. Read Holding Register (Function Code 0x03) -----
    Serial.print("Read holding register 0x0000");
    result = node.readHoldingRegisters(0x0000, 1);
    if (result == node.ku8MBSuccess) {
        uint16_t value = node.getResponseBuffer(0);
        Serial.print("  Read value: ");
        Serial.println(value);
    } else {
        Serial.print("  Read failed, error code: 0x");
        Serial.println(result, HEX);
    }

    Serial.println("--------------------");
    delay(3000);
}