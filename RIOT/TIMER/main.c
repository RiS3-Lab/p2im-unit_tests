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
#include <periph/timer.h>


timer_cb_t time;


void timerCB(void *arg, int channel)
{
int a;
int *b;
a=5;
a=channel;
a +=channel;

b= arg;
b=b;

}

int main(void)
{
    int a;

    a=5; 

    time=timerCB;
    
    timer_init(TIMER_DEV(0),1000,time,&a); // 1000 is the number of ticks per second, "time" is the callback and "a" is an optional parameter passed to callback
    
    timer_read(TIMER_DEV(0)); // reads count register of timer, does not affect fucntionality  is only a read of current count 
    timer_set(TIMER_DEV(0),1,100); //set a timeout in ticks (100 ticks)  for channel 1 of timer(0), which calls "time" callback defined in timer_init when timeout ticks have passed 
    timer_stop(TIMER_DEV(0));  // stop the timer
    timer_start(TIMER_DEV(0)); // start de timer this is unnecessary (part of timer_init) unless stop was called previously

    while(1);
    return 0;
}

