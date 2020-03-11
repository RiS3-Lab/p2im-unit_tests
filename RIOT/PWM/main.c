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
#include <periph/pwm.h>



int main(void)
{
    int a;

    a=5; 
    a=a;

    pwm_init(PWM_DEV(0),PWM_LEFT,1000,10);
    pwm_set(PWM_DEV(0),1,100);
    pwm_poweroff(PWM_DEV(0)); 
    pwm_poweron(PWM_DEV(0));

    while(1);
    return 0;
}
