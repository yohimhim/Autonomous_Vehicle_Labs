///*
//*
//*   uart.c
//*
//*
//*
//*
//*
//*   @author
//*   @date
//*/
//
//#include "uart.h"
//#include "Timer.h"
//#include "lcd.h"
//#include <inc/tm4c123gh6pm.h>
//
//volatile  char uart_data;
//volatile  char uart_flag;
//
//
//void uart_init(void){
//    //TODO
//    SYSCTL_RCGCUART_R = 0x02;
//    SYSCTL_RCGCGPIO_R |= 0x02;
//    timer_waitMillis(1);
//    GPIO_PORTB_AFSEL_R |= 0x03;    //U1Rx PB0 1   U1Tx PB1  1
//
//    GPIO_PORTB_PCTL_R &= 0xFFFFFF00;     // Force 0's in the disired locations
//    GPIO_PORTB_PCTL_R |= 0x00000011;     // Force 1's in the disired locations
//    GPIO_PORTB_DEN_R |= 0x03;
//    GPIO_PORTB_DIR_R &= 0b11111100;      // Force 0's in the disired locations
//    GPIO_PORTB_DIR_R |= 0b00000010;      // Force 1's in the disired locataions
//
//    //compute baud values [UART clock= 16 MHz]
//       double fbrd;
//       int    ibrd;
//       int brd;
//
//       brd = 16000000 / (16 * 115200) ; // page 903
//       ibrd = (int)brd;
//       fbrd = (int)(brd-ibrd)*64 + .5;
//
//    UART1_CTL_R &= 0xDE;        //disable UART
//    UART1_IBRD_R = 0x8;         //set the baud rate period to 8
//    UART1_FBRD_R = 0x2C;        //set the fractional baud rate period
//    UART1_LCRH_R = 0x60;        //set baud rate to 115200, data bits to 8, one stop bit, no parity
//    UART1_CC_R  = 0x0;          //set UARTCC as 0 to select system clk as the source
//    UART1_CTL_R = 0x301;         //enable UART 1 AND enable UART Recive and transmit
//}
//
//void uart_sendChar(char data){
//    //TODO
//
//    while((UART1_FR_R & 0x20) == 0x20); //wait till flag says transmit queue is full
//    UART1_DR_R = data; //send data
//}
//
//char uart_receive(void){
//    //TODO
//    char recived;
//    while((UART1_FR_R & 0x10));  //wait till flag says receive queue is full
//    recived = UART1_DR_R & 0xFF; //get data from reg
//    //lcd_putc(recived);
//    return recived;
//}
//
//void uart_sendStr(const char *data){
//    //TODO for reference see lcd_puts from lcd.c file
//    while(*data != '\0')
//        {
//            uart_sendChar(*data);
//            data++;
//        }
//
//}
//
//void uart_interrupt_init()
//{
//    // Enable interrupts for receiving bytes through UART1
//   UART1_IM_R |= 0x10 ; //enable interrupt on receive - page 924
//
//    // Find the NVIC enable register and bit responsible for UART1 in table 2-9
//    // Note: NVIC register descriptions are found in chapter 3.4
//   NVIC_EN0_R |= 0x40 ; //enable uart1 interrupts - page 104
//
//    // Find the vector number of UART1 in table 2-9
//   IntRegister(INT_UART1, uart1_Handler); //give the microcontroller the address of our interrupt handler - page 104 22 is the vector number
//
//}
//
//void uart1_Handler(void){
//    if(UART1_IM_R & 0x10){ //check interrupt status
//        uart_flag = 0x01;
//        uart_data =  UART1_DR_R & 0xFF; //change data
//    }
//    UART1_ICR_R |= 0x10; //clear interrupt
//}
