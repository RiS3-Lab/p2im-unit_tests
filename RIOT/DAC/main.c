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
#include<periph/dac.h>

int main(void)
{
    int a;
    a=dac_init(ARDUINO_DAC0);
    if(a==DAC_OK){
    dac_set(ARDUINO_DAC0 , 5000);
    
    }
    while(1);
    return 0;
}
