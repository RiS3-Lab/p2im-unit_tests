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
#include<periph/adc.h>

int errorf(void)
{
int a=1;
a=a+1;
return a;
}


int main(void)
{
    int a;
    //#if BOARD==arduino-due
    //  a=adc_init(ARDUINO_A0);
    //#else
    a=adc_init(ADC_LINE(0));
    //#endif
    
    if (a==0)
    {
    
    //#if BOARD==arduino-due
    //  a=adc_sample(ARDUINO_A0,ADC_RES_10BIT);
    //#else
    a=adc_sample(ADC_LINE(0),ADC_RES_10BIT);
    //#endif


    if(a<0)
    { 
      a=a;
      errorf();
      while(1);
     }

    }
    while(1); 
    return 0;
}
