#include <ModbusADU.h>
#include <ModbusRTUComm.h>

#define SERIAL_PORT Serial1
#define BAUD_RATE 9600

ModbusADU adu;
ModbusRTUComm rtuComm(SERIAL_PORT, 13);
uint16_t count = 0;

void setup() {
  pinMode(12, OUTPUT);
  SERIAL_PORT.begin(BAUD_RATE);
  rtuComm.begin(BAUD_RATE);
  adu.setUnitId(1);
  adu.setFunctionCode(3);
  adu.data[0] = 2;
  adu.setDataLen(3);
}

void loop() {
  adu.setDataRegister(1, count);
  bool verified = rtuComm.writeAdu(adu);
  if (verified) digitalWrite(12, HIGH);
  else digitalWrite(12, LOW);
  count++;
  delay(100);
}
