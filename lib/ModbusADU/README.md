# ModbusADU

This is a library for managing Modbus RTU and TCP application data units (ADUs).
It is intended to be used with other libraries, but it can be used on its own.

Creating an instance of `ModbusADU` creates a structure with essentially the following form:

| Field                  | Length        | Description                                      |
| :--------------------- | :-----------: | :----------------------------------------------- |
| Transaction Identifier | 2 Bytes       | Identification of a Modbus request               |
| Protocol Identifier    | 2 Bytes       | 0 = Modbus protocol                              |
| Length                 | 2 Bytes       | Number of following bytes, excluding error check |
| Unit Itentifier        | 1 Byte        | Identification of a remote slave/server device   |
| Function Code          | 1 Byte        | Function of message: read, write, other          |
| Data                   | 1 - 252 Bytes | Contents depend on function code                 |
| Error Check            | 2 Bytes       | Cyclic redundancy check (CRC) code               |



## Methods



<details><summary id="modbusadu-1"><strong>ModbusADU</strong></summary>
  <blockquote>

### Description
Creates a ModbusADU object.

### Example
``` C++
# include <ModbusADU.h>

ModbusADU adu;
```

  </blockquote>
</details>



<details><summary id="rtu"><strong>rtu[]</strong></summary>
  <blockquote>

### Description
Allows reading from and writing to a `ModbusADU` object as a byte (`uint8_t`) array, with index `0` corresponding to the unit identifier.

### Syntax
`adu.rtu[index]`

### Parameters
- `adu`: a `ModbusADU` object.
- `index`: the location to read/write from. Allowed data types: `int`.

  </blockquote>
</details>



<details><summary id="tcp"><strong>tcp[]</strong></summary>
  <blockquote>

### Description
Allows reading from and writing to a `ModbusADU` object as a byte (`uint8_t`) array, with index `0` corresponding to the first byte of the transaction identifier.

### Syntax
`adu.tcp[index]`

### Parameters
- `adu`: a `ModbusADU` object.
- `index`: the location to read/write from, starting from 0. Allowed data types: `int`.

  </blockquote>
</details>



<details><summary id="pdu"><strong>pdu[]</strong></summary>
  <blockquote>

### Description
Allows reading from and writing to a `ModbusADU` object as a byte (`uint8_t`) array, with index `0` corresponding to the function code.

### Syntax
`adu.pdu[index]`

### Parameters
- `adu`: a `ModbusADU` object.
- `index`: the location to read/write from. Allowed data types: `int`.

  </blockquote>
</details>



<details><summary id="data"><strong>data[]</strong></summary>
  <blockquote>

### Description
Allows reading from and writing to a `ModbusADU` object as a byte (`uint8_t`) array, with index `0` corresponding to the first byte of the data section.

### Syntax
`adu.data[index]`

### Parameters
- `adu`: a `ModbusADU` object.
- `index`: the location to read/write from. Allowed data types: `int`.

  </blockquote>
</details>



<details><summary id="settransactionid"><strong>setTransactionId()</strong></summary>
  <blockquote>

### Description
Sets the transaction identification number of the `ModbusADU` object.

### Syntax
`adu.setTransactionId(transactionId)`

### Parameters
- `adu`: a `ModbusADU` object.
- `transactionId`: a transaction identifier number for Modbus TCP. Allowed data types: `uint16_t`.

  </blockquote>
</details>



<details><summary id="setprotocolid"><strong>setProtocolId()</strong></summary>
  <blockquote>

### Description
Sets the protocol identification number of the `ModbusADU` object.
For all valid Modbus TCP transactions, this should be set to `0`.

### Syntax
`adu.setProtocolId(protocolId)`

### Parameters
- `adu`: a `ModbusADU` object.
- `protocolId`: a protocol identifier number for Modbus TCP. Allowed data types: `uint16_t`.

  </blockquote>
</details>



<details><summary id="setlength"><strong>setLength()</strong></summary>
  <blockquote>

### Description
Sets the value in the length field.
This value should be the number of bytes in the ADU following the length field, but exluding the error check field.
This includes the unit id, function code, and data fields.

### Syntax
`adu.setLength(length)`

### Parameters
- `adu`: a `ModbusADU` object.
- `length`: the value to place in the length field. Allowed data types: `uint16_t`.

*Note the length field can also be manipulated with `setRtuLen()`, `setTcpLen()`, `setPduLen()`, and `setDataLen()`.*

  </blockquote>
</details>



<details><summary id="setunitid"><strong>setUnitId()</strong></summary>
  <blockquote>

### Description
Sets the unit identification number of the `ModbusADU` object.

### Syntax
`adu.setUnitId(unitId)`

### Parameters
- `adu`: a `ModbusADU` object.
- `unitId`: the unit identifier number. Allowed data types: `uint8_t`.

  </blockquote>
</details>



<details><summary id="setfunctioncode"><strong>setFunctionCode()</strong></summary>
  <blockquote>

### Description
Sets the function code of the `ModbusADU` object.

### Syntax
`adu.setFunctionCode(functionCode)`

### Parameters
- `adu`: a `ModbusADU` object.
- `functionCode`: a Modbus function code. Allowed data types: `uint8_t`.

  </blockquote>
</details>



<details><summary id="setdataregister"><strong>setDataRegister()</strong></summary>
  <blockquote>

### Description
Sets a 16-bit register in the data portion the `ModbusADU` object.

### Syntax
`adu.setDataRegister(index, value)`

### Parameters
- `adu`: a `ModbusADU` object.
- `index`: the data byte at which to start writing the 16-bit value. Allowed data types: `uint8_t`.
- `value`: the 16-bit value to write to the data field of the ADU. Allowed data types: `uint16_t`.

### Example
``` C++
ModbusADU adu;
adu.data[0] = 6;                // sets data byte 0
adu.setDataRegister(1, 38229);  // sets data bytes 1 and 2
adu.setDataRegister(3, 65535);  // sets data bytes 3 and 4
adu.setDataRegister(5, 52428);  // sets data bytes 5 and 6
```

*Note that the index is per byte, not per 16-bit value. This means that if you are writing multiple registers in a row, you will need to skip an index value between them.*

  </blockquote>
</details>



<details><summary id="setrtulen"><strong>setRtuLen()</strong></summary>
  <blockquote>

### Description
Sets the length field assuming that the submitted value is the length of the RTU frame.
The RTU frame includes the unit id, function code, data, and error check fields.

### Syntax
`adu.setRtuLen(length)`

### Parameters
- `adu`: a `ModbusADU` object.
- `length`: the length in bytes of a RTU message frame. Allowed data types: `uint16_t`.

  </blockquote>
</details>



<details><summary id="settcplen"><strong>setTcpLen()</strong></summary>
  <blockquote>

### Description
Sets the length field assuming that the submitted value is the length of the TCP frame.
The TCP frame includes the transaction id, protocol id, length, unit id, function code, and data fields.

### Syntax
`adu.setTcpLen(length)`

### Parameters
- `adu`: a `ModbusADU` object.
- `length`: the length in bytes of the TCP frame. Allowed data types: `uint16_t`.

  </blockquote>
</details>



<details><summary id="setpdulen"><strong>setPduLen()</strong></summary>
  <blockquote>

### Description
Sets the length field assuming that the submitted value is the length of the PDU (Protocol Data Unit).
The PDU includes the function code, and data fields.

### Syntax
`adu.setPduLen(length)`

### Parameters
- `adu`: a `ModbusADU` object.
- `length`: the length in bytes of the PDU. Allowed data types: `uint16_t`.

  </blockquote>
</details>



<details><summary id="setdatalen"><strong>setDataLen()</strong></summary>
  <blockquote>

### Description
Sets the length field assuming that the submitted value is the length of the data field.

### Syntax
`adu.setDataLen(length)`

### Parameters
- `adu`: a `ModbusADU` object.
- `length`: the length in bytes of the data field. Allowed data types: `uint16_t`.

  </blockquote>
</details>



<details><summary id="gettransactionid"><strong>getTransactionId()</strong></summary>
  <blockquote>

### Description
Gets the transaction identification number of the `ModbusADU` object.

### Syntax
`adu.getTransactionId()`

### Parameters
- `adu`: a `ModbusADU` object.

### Returns
Transaction identifier. Data type: `uint16_t`.

  </blockquote>
</details>



<details><summary id="getprotocolid"><strong>getProtocolId()</strong></summary>
  <blockquote>

### Description
Gets the protocol identification number of the `ModbusADU` object.

### Syntax
`adu.getProtocolId()`

### Parameters
- `adu`: a `ModbusADU` object.

### Returns
Protocol identifier. Data type: `uint16_t`.

  </blockquote>
</details>



<details><summary id="getlength"><strong>getLength()</strong></summary>
  <blockquote>

### Description
Gets the value in the length field.
This value should be the number of bytes in the ADU following the length field, but exluding the error check field.
This includes the unit id, function code, and data fields.

### Syntax
`adu.getLength()`

### Parameters
- `adu`: a `ModbusADU` object.

### Returns
The value in the length field. Data type: `uint16_t`.

  </blockquote>
</details>



<details><summary id="getunitid"><strong>getUnitId()</strong></summary>
  <blockquote>

### Description
Gets the unit identification number of the `ModbusADU` object.

### Syntax
`adu.getUnitId()`

### Parameters
- `adu`: a `ModbusADU` object.

### Returns
The unit identifier number. Data type: `uint8_t`.

  </blockquote>
</details>



<details><summary id="getfunctioncode"><strong>getFunctionCode()</strong></summary>
  <blockquote>

### Description
Gets the function code of the `ModbusADU` object.

### Syntax
`adu.getFunctionCode()`

### Parameters
- `adu`: a `ModbusADU` object.

### Returns
The function code. Data type: `uint8_t`.

  </blockquote>
</details>



<details><summary id="getdataregister"><strong>getDataRegister()</strong></summary>
  <blockquote>

### Description
Gets a 16-bit register from the data portion the `ModbusADU` object.

### Syntax
`adu.getDataRegister(index)`

### Parameters
- `adu`: a `ModbusADU` object.
- `index`: the data byte at which to start reading the 16-bit value. Allowed data types: `uint8_t`.

### Returns
The 16-bit value read from the data field of the ADU. Data type: `uint16_t`.

*Note that the index is per byte, not per 16-bit value.*

  </blockquote>
</details>



<details><summary id="getrtulen"><strong>getRtuLen()</strong></summary>
  <blockquote>

### Description
Gets the length of the RTU frame based on the length field.
The RTU frame includes the unit id, function code, data, and error check fields.

### Syntax
`adu.getRtuLen()`

### Parameters
- `adu`: a `ModbusADU` object.

### Returns
The length in bytes of the RTU frame. Data type: `uint16_t`.

  </blockquote>
</details>



<details><summary id="gettcplen"><strong>getTcpLen()</strong></summary>
  <blockquote>

### Description
Gets the length of the TCP frame based on the length field.
The TCP frame includes the transaction id, protocol id, length, unit id, function code, and data fields.

### Syntax
`adu.getTcpLen()`

### Parameters
- `adu`: a `ModbusADU` object.

### Returns
The length in bytes of the TCP frame. Data type: `uint16_t`.

  </blockquote>
</details>



<details><summary id="getpdulen"><strong>getPduLen()</strong></summary>
  <blockquote>

### Description
Gets the length of the PDU (Protocol Data Unit) based on the length field.
The PDU includes the function code, and data fields.

### Syntax
`adu.getPduLen()`

### Parameters
- `adu`: a `ModbusADU` object.

### Returns
The length in bytes of the PDU. Data type: `uint16_t`.

  </blockquote>
</details>



<details><summary id="getdatalen"><strong>getDataLen()</strong></summary>
  <blockquote>

### Description
Gets the length of the data field based on the length field.

### Syntax
`adu.getDataLen()`

### Parameters
- `adu`: a `ModbusADU` object.

### Returns
The length in bytes of the data field. Allowed data types: `uint16_t`.

  </blockquote>
</details>



<details><summary id="updatecrc"><strong>updateCrc()</strong></summary>
  <blockquote>

### Description
Updates the error check field based on the contents of the ADU.

### Syntax
`adu.updateCrc()`

### Parameters
- `adu`: a `ModbusADU` object.

  </blockquote>
</details>



<details><summary id="crcgood"><strong>crcGood()</strong></summary>
  <blockquote>

### Description
Checks if the error check is correct for the contents of the ADU.

### Syntax
`adu.crcGood()`

### Parameters
- `adu`: a `ModbusADU` object.

### Returns
- `true` if the error check is correct for the contents of the ADU.
- `false` if the error check is incorrect for the contents of the ADU.

  </blockquote>
</details>



<details><summary id="prepareexceptionresponse"><strong>prepareExceptionResponse()</strong></summary>
  <blockquote>

### Description
Prepares an exception response in the ADU.

### Syntax
`adu.prepareExceptionResponse(exceptionCode)`

### Parameters
- `adu`: a `ModbusADU` object.
- `exceptionCode`: sets the exception code to be used in the exception response. Typical values are:  
  - `1`: Illegal Function
  - `2`: Illegal data address
  - `3`: Illegal data value
  - `4`: Server device failure

  </blockquote>
</details>
