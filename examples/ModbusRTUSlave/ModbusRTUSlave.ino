/**
 * @file      ModbusRTUSlave.ino
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @copyright Copyright (c) 2026  ShenZhen XinYuan Electronic Technology Co., Ltd
 * @date      2026-03-17
 *
 */

#include <ModbusRTUSlave.h>

#define BOARD_485_TX    39
#define BOARD_485_RX    38
#define BOARD_485_EN    42
#define RS485_EN_LEVEL  LOW
#define BOARD_POWER_ON   4
#define SLAVE_ID        1         // Slave address (same as slave program)


ModbusRTUSlave mb(Serial2, SLAVE_ID);

// Define the coil and register array (size to suit actual needs)
const int NUM_COILS = 8;           // 8 coils
const int NUM_HOLDING_REGS = 10;   // 10 holding registers
bool coilStates[NUM_COILS];
uint16_t holdingRegs[NUM_HOLDING_REGS];

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

    mb.begin(SLAVE_ID, 2400, SERIAL_8N1);
    mb.configureCoils(coilStates, NUM_COILS);
    mb.configureHoldingRegisters(holdingRegs, NUM_HOLDING_REGS);

    holdingRegs[0] = 0;      // Register 0x0000 initial value
    coilStates[2] = false;   // Coil 0x0002 initial state

    Serial.println("The slave station has started and is waiting for a request from the master station...");
}

void loop()
{
    // Must call poll() regularly to process received requests
    mb.poll();
}