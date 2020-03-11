/*
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Hello World application template, modified for the P2IM project 2018 
 *
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @author      Ludwig Knüpfer <ludwig.knuepfer@fu-berlin.de>
 * @author      Alejandro Mera <mera.a@husky.neu.edu>
 * @author      Bo Feng <feng.bo@husky.neu.edu>
 * 
 * @}
 */

#include <stdio.h>
#include <board.h>
#include <periph/i2c.h>

int  main(void){
/*outdated  in current RIOT version
i2c_init_master(I2C_DEV(0),I2C_SPEED_NORMAL);
i2c_acquire(I2C_DEV(0));
i2c_write_byte(I2C_DEV(0), 0x03, 0x01);
i2c_release(I2C_DEV(0));
*/

int device_addr=0x03;
int reg_addr=0x01;
int reg_value=0;

char reg_data[2];

reg_data[0]=0xde;
reg_data[1]=0xbe;



// example to read a byte
// https://riot-os.org/api/group__drivers__periph__i2c.html
// initialize the bus (this is normally done during boot time)
i2c_init(I2C_DEV(0));
// before accessing the bus, we need to acquire it
i2c_acquire(I2C_DEV(0));
// next we write the register address, but create no STOP condition when done
i2c_write_byte(I2C_DEV(0), device_addr, reg_addr, (I2C_NOSTOP | I2C_ADDR10));
// and now we read the register value
i2c_read_byte(I2C_DEV(0), device_addr, &reg_value, I2C_ADDR10);
// finally we have to release the bus
i2c_release(I2C_DEV(0));


// example to write a byte
// initialize the bus
i2c_init(I2C_DEV(0));
// first, acquire the shared bus again
i2c_acquire(I2C_DEV(0));
// write the 16-bit register address to the device and prevent STOP condition
i2c_write_byte(I2C_DEV(0), device_addr, reg_addr, I2C_NOSTOP);
// and write the data after a REPEATED START
i2c_write_bytes(I2C_DEV(0), device_addr, reg_data, 2, 0);
// and finally free the bus again
i2c_release(I2C_DEV(0));


    while(1);
    return 0;
}
