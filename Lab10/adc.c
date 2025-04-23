/*
 * adc.c
 *
 *  Created on: Apr 2, 2025
 *      Author: yohimhim
 */


#include "adc.h"

void adc_init(){
    SYSCTL_RCGCGPIO_R |= 0x2; //activate ADC
    while(!(SYSCTL_RCGCGPIO_R & 0x2));

    GPIO_PORTB_AFSEL_R |= 0x10; //enable alternate function
    GPIO_PORTB_DEN_R &= ~(0x10); // disable digital I/O
    GPIO_PORTB_AMSEL_R |= 0x10; // enable analog functionality
    GPIO_PORTB_DIR_R &= ~(0x10); // make input

    SYSCTL_RCGCADC_R |= 0x1; // activate clock for port B
    while(!(SYSCTL_RCGCADC_R & 0x1));
    ADC0_ACTSS_R &= ~(0x8);
    while(ADC0_ACTSS_R & 0x8);
    ADC0_EMUX_R &= ~(0xF000);
    ADC0_SSMUX3_R |= 0xA;
    ADC0_IM_R &= ~(0x8);
    ADC0_SSCTL3_R |= 0x4;
    ADC0_SAC_R |= 0x6;
    ADC0_ACTSS_R |= 0x8;
}

uint16_t adc_read(){
    uint16_t temp;

    ADC0_PSSI_R |= 0x8; // 1) initiate SS3
    while(!(ADC0_RIS_R & 0x8));
    temp = ADC0_SSFIFO3_R & 0xFFF; // 3) read temp
    ADC0_ISC_R |= 0x8;
    return temp;
}
