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
//#include <uart_stdio.h>
#include <stdio_base.h>

int errorF(void);

int errorF(void)
{
int a;
a=5;
a=a+1;
return a;
}

char buffer[64]; //this variable is required for reading data from USART

int main(void)
{
 //   char buffer[64];
//    int a;
    puts("Hello World!");

    printf("You are running RIOT on a(n) %s board.\n", RIOT_BOARD);
    printf("This board features a(n) %s MCU.\n", RIOT_MCU);
    while(1)
    {
//	  the next lines should be enabled to test reading data from USART
      //int a=stdio_read(buffer,2);
      
	  //if(a<0)
	  //  {
	  //  	errorF();
	  //  }

    }
    return 0;
}
