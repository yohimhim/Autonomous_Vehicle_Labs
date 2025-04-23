/**
 * @file lab9_template.c
 * @author
 * Template file for CprE 288 Lab 9
 */

#include "Timer.h"
#include "lcd.h"
#include "servo.h"
#include "button.h"
#include <stdint.h>
#include <stdio.h>


int main(void) {
    timer_init(); // Must be called before lcd_init(), which uses timer functions
    lcd_init();
    button_init();
    servo_init();
//  uint8_t button = 0;
//  uint8_t current_angle = 90;
//  uint8_t current_direction = 0;  //0 - left; 1 - right
//  uint32_t match_value;
//  char info[100];

//  servo_move(current_angle);

    //part 3
    servo_calibrate();

  // YOUR CODE HERE
    while(1){
        //part 1
        servo_move(90);
        lcd_printf("servo at 90 degrees");
        timer_waitMillis(1500);
        servo_move(30);
        lcd_printf("servo at 30 degrees");
        timer_waitMillis(1500);
        servo_move(150);
        lcd_printf("servo at 150 degrees");
        timer_waitMillis(1500);
        servo_move(90);
        lcd_printf("servo at 90 degrees");
        timer_waitMillis(1500);

        //part 2
//      match_value = (TIMER1_TBPMR_R << 16) + TIMER1_TBMATCHR_R;
//
//      if(!current_direction){
//          sprintf(info, "%X | counterclockwise", match_value);
//      }else sprintf(info, "%X | clockwise", match_value);
//
//      lcd_clear();
//      lcd_puts(info);
//
//        button = button_getButton();
//
//        if (button == 1){
//            if(!current_direction && current_angle < 180){
//                current_angle++;
//            }
//            else if(current_direction && current_angle > 0){
//                current_angle--;
//            }
//            servo_move(current_angle);
//        }
//        else if (button == 2){
//            if(!current_direction){
//                if(current_angle < 176){
//                    current_angle += 5;
//                }else current_angle = 180;
//            }
//            else if(current_direction){
//                if(current_angle > 4){
//                    current_angle -= 5;
//                }else current_angle = 0;
//            }
//            servo_move(current_angle);
//        }
//        else if (button == 3){
//            current_direction = !current_direction;
//            servo_move(current_angle);
//        }
//        else if (button == 4){
//            if(current_direction){
//                current_angle = 5;
//            } else current_angle = 175;
//            servo_move(current_angle);
//        }
//
//        timer_waitMillis(100);
    }




}
