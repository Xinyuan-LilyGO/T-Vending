/**
 * @file      SPIExample.ino
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @copyright Copyright (c) 2023  Shenzhen Xin Yuan Electronic Technology Co., Ltd
 * @date      2023-06-21
 *
 */

#include <Arduino.h>
#include <SPI.h>


#define SPI_MOSI    40       //OUTPUT
#define SPI_MISO    2       //INPUT
#define SPI_SCK     13      //OUTPUT
#define SPI_CS      21      //OUTPUT

void setup()
{
    // Using SPI requires an explicit call
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, SPI_CS);
    // do someing ..
}

void loop()
{

}