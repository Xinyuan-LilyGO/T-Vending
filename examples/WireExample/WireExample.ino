/**
 * @file      WireExample.ino
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @copyright Copyright (c) 2023  Shenzhen Xin Yuan Electronic Technology Co., Ltd
 * @date      2023-06-21
 *
 */

#include <Arduino.h>
#include <Wire.h>


// Grove cable
#define I2C_SDA 44          //Board screen printing <RX>  
#define I2C_SCL 43          //Board screen printing <TX>  

void setup()
{
    // Using Wire requires an explicit call
    Wire.begin(I2C_SDA, I2C_SCL);
    // do someing ..
}

void loop()
{

}