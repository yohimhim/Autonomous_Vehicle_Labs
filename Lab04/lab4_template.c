/**
 * lab4_template.c
 *
 * Template file for CprE 288 lab 4
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 */

#include "button.h"
#include "Timer.h"
#include "lcd.h"
#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1

#warning "Possible unimplemented functions"
#define REPLACEME 0



int main(void) {
    button_init();
    timer_init(); // Must be called before lcd_init(), which uses timer functions
    lcd_init();
    cyBot_uart_init();
    button_getButton();
                // Don't forget to initialize the cyBot UART before trying to use it

    // YOUR CODE HERE


//    while(1)
//    {
//
//      // YOUR CODE HERE
//
//        uint8_t btn = button_getButton();
//        lcd_printf("Button pressed: %d\n", btn);
//
//
//
//
//    }

//    while(1)
//        {
//
//          // YOUR CODE HERE
//            uint8_t data = button_getButton();
//
//            if(data == 4){
//                lcd_printf("Button 4 Pressed!");
//            }
//            else if(data == 3){
//                lcd_printf("Button 3 Pressed!");
//
//            }
//            else if(data == 2){
//                lcd_printf("Button 2 Pressed!");
//
//            }
//            else if(data == 1){
//                lcd_printf("Button 1 Pressed!");
//
//            }
//            else {
//                lcd_printf("No button Pressed :(");
//            }
//
//
//        }

}
