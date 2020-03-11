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

//#include <stdio.h>
//#include <uart_stdio.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <enc28j60.h>
//#include <periph/spi.h>
//#include <board.h>

char buffer[32];
uint8_t dTX;
uint8_t dRX;


int main(void)
{
    //puts("Hello World!");
    //printf("You are running RIOT on a(n) %s board.\n", RIOT_BOARD);
    //printf("This board features a(n) %s MCU.\n", RIOT_MCU);
    //uart_stdio_read(buffer,2);
    int tmp;
   
    dTX='a';
    spi_init(SPI_DEV(0));
    tmp = spi_acquire(SPI_DEV(0),SPI_CS_UNDEF,SPI_MODE_0,SPI_CLK_1MHZ);
    dRX= spi_transfer_byte(SPI_DEV(0),SPI_CS_UNDEF,false, dTX);
    spi_release(SPI_DEV(0));
    dRX=dRX;
    tmp=tmp;
   
 while(1){};
    return 0;
}
