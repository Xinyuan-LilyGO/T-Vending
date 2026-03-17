#ifndef ModbusRTUComm_h
#define ModbusRTUComm_h

#include "Arduino.h"
#include "ModbusADU.h"

enum ModbusRTUCommError : uint8_t {
  MODBUS_RTU_COMM_SUCCESS = 0,
  MODBUS_RTU_COMM_TIMEOUT = 1,
  MODBUS_RTU_COMM_FRAME_ERROR = 2,
  MODBUS_RTU_COMM_CRC_ERROR = 3
};

class ModbusRTUComm {
  public:
    ModbusRTUComm(Stream& serial, int dePin = -1, int rePin = -1);
    void begin(unsigned long baud, uint32_t config = SERIAL_8N1);
    void setTimeout(unsigned long timeout);
    ModbusRTUCommError readAdu(ModbusADU& adu);
    bool writeAdu(ModbusADU& adu);

  private:
    Stream& _serial;
    int _dePin;
    int _rePin;
    unsigned long _charTimeout;
    unsigned long _frameTimeout;
    unsigned long _bytePeriod;
    unsigned long _postDelay;
    unsigned long _readTimeout = 2000;
};

#endif
