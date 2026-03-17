# ModbusSlaveLogic

Modbus is an industrial communication protocol. The full details of the Modbus protocol can be found at [modbus.org](https://modbus.org). A good summary can also be found on [Wikipedia](https://en.wikipedia.org/wiki/Modbus).

This is an Arduino library for processing Modbus requests. It enables an Arduino, or arduino compatible, board to process requests from a Modbus master/client and formulate an appropriate response based on the library instance's configuration.  
This library is able to service the following function codes:  
- 1 (Read Coils)
- 2 (Read Discrete Inputs)
- 3 (Read Holding Registers)
- 4 (Read Input Registers)
- 5 (Write Single Coil)
- 6 (Write Single Holding Register)
- 15 (Write Multiple Coils)
- 16 (Write Multiple Holding Registers).

This library works with `ModbusADU` objects. See [ModbusADU](https://github.com/CMB27/ModbusADU) for details.

This library updates coil, descrete input, holding register, and input register arrays based on the PDU portion of the input ADU.
It will also update the PDU portion of the ADU to be the appropriate response.



## Methods



<details><summary id="modbusslavelogic-1"><strong>ModbusSlaveLogic</strong></summary>
  <blockquote>

### Description
Creates a `ModbusSlaveLogic` object.

### Example
``` C++
# include <ModbusSlaveLogic.h>

ModbusSlaveLogic modbusLogic;
```

  </blockquote>
</details>



<details><summary id="configurecoils"><strong>configureCoils()</strong></summary>
  <blockquote>

### Description
Tells the library where coil data is stored and the number of coils.
If this function is not run, the library will assume there are no coils.

### Syntax
`modbusLogic.configureCoils(coils, numCoils)`

### Parameters
- `modbusLogic`: a `ModbusSlaveLogic` object.
- `coils`: an array of coil values. Allowed data types: array of `bool`.
- `numCoils`: the number of coils. This value must not be larger than the size of the array. Allowed data types: `uint16_t`.

  </blockquote>
</details>



<details><summary id="configurediscreteinputs"><strong>configureDiscreteInputs()</strong></summary>
  <blockquote>

### Description
Tells the library where to read discrete input data and the number of discrete inputs.
If this function is not run, the library will assume there are no discrete inputs.

### Syntax
`modbusLogic.configureDiscreteInputs(discreteInputs, numDiscreteInputs)`

### Parameters
- `modbusLogic`: a `ModbusSlaveLogic` object.
- `discreteInputs`: an array of discrete input values. Allowed data types: array of `bool`.
- `numDiscreteInputs`: the number of discrete inputs. This value must not be larger than the size of the array. Allowed data types: `uint16_t`.

  </blockquote>
</details>



<details><summary id="configureholdingregisters"><strong>configureHoldingRegisters()</strong></summary>
  <blockquote>

### Description
Tells the library where holding register data is stored and the number of holding registers.
If this function is not run, the library will assume there are no holding registers.

### Syntax
`modbusLogic.configureHoldingRegisters(holdingRegisters, numHoldingRegisters)`

### Parameters
- `modbusLogic`: a `ModbusSlaveLogic` object.
- `holdingRegisters`: an array of holding register values. Allowed data types: array of `uint16_t`.
- `numHoldingRegisters`: the number of holding registers. This value must not be larger than the size of the array. Allowed data types: `uint16_t`.

  </blockquote>
</details>



<details><summary id="configureinputregisters"><strong>configureInputRegisters()</strong></summary>
  <blockquote>

### Description
Tells the library where to read input register data and the number of input registers.
If this function is not run, the library will assume there are no input registers.

### Syntax
`modbusLogic.configureInputRegisters(inputRegisters, numInputRegisters)`

### Parameters
- `modbusLogic`: a `ModbusSlaveLogic` object.
- `inputRegisters`: an array of input register values. Allowed data types: array of `uint16_t`.
- `numInputRegisters`: the number of input registers. This value must not be larger than the size of the array. Allowed data types: `uint16_t`.

  </blockquote>
</details>



<details><summary id="processpdu"><strong>processPdu()</strong></summary>
  <blockquote>

### Description
If a valid write request is submitted in the adu, it will update the appropriate data array, and modify the adu to be the correct acknowledgment response.
If a valid read request is submitted, it will modify the adu to be the correct response with the requested data from the appropriate array.
If an invalid request is submitted, it will modify the adu to be an exception response as per the Modbus specification.

### Syntax
`modbusLogic.processPdu(adu)`

### Parameters
- `modbusLogic`: a `ModbusSlaveLogic` object.
- `adu`: a `ModbusADU` object.

  </blockquote>
</details>


