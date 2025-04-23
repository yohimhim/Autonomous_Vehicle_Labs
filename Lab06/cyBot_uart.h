/**
 * lab6_main.c

 */
#include <stdint.h>
#include <stdbool.h>
#include <Math.h>
#include "timer.h"
#include "lcd.h"
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"
#include "uart.h"
#include "cyBot_Scan.h"
#include "open_interface.h"
#include "movement.h"

extern volatile  char uart_data;
extern volatile  char uart_flag;

void printString(char *arr){
    int i=0;
    while(arr[i]){
        uart_sendChar(arr[i]);
        i++;
     }
    uart_sendChar('\n');
    uart_sendChar('\r');
}

int main(void) {
    lcd_init();
    timer_init();
    uart_init();
    char buffer[100];
    lcd_clear();
    int length =0;
    uart_interrupt_init();

    cyBOT_init_Scan(0b0011);
    right_calibration_value = 290500;
    left_calibration_value = 1235500;
    oi_t *sensor = oi_alloc();
    oi_init(sensor);
    int i;
    int smallWidth[2] = {1000000,25000000};
    int objects[40];
        while(1){
        float distVals[91];
        uart_receive();
        if(uart_flag){
            uart_flag = 0x00;
            if(uart_data == 'm'){
              cyBOT_Scan_t scan;
              for(i=0; i<= 180; i+=2){
               cyBOT_Scan(i, &scan);
               distVals[i/2] = scan.sound_dist;
              }
              i = 1;
              int count = 0;
              int obj = 0;
              while(i<=91){
                  if(distVals[i] - 4 < distVals[i-1] && distVals[i-1] < distVals[i]+4 && distVals[i-1] < 100){
                      count++;
                  }else{
                      count =0;
                  }
                  if(count > 3){
                      obj++;
                      objects[(obj-1)*4] = obj;
                      objects[((obj-1)*4)+1] = i*2 - 8;
                      int dist = distVals[i-4]+distVals[i-3]+distVals[i-2]+distVals[i-1];
                      while(distVals[i] - 4 < distVals[i-1] && distVals[i-1] < distVals[i]+4 && distVals[i-1] < 100){
                          dist+= distVals[i];
                          count++;
                          i++;
                      }
                      objects[((obj-1)*4)+2] = dist/count;
                      objects[((obj-1)*4)+3] = i*2 - ((i-count)*2);

                      int width = ((dist/count) * (dist/count) *2) - (4* (dist/count) * cos(objects[((obj-1)*4)+3]));
                      if( width < smallWidth[0]){
                          smallWidth[0] = width;
                          smallWidth[1] = objects[((obj-1)*4)+1];
                      }
                      count = 0;
                      i--;
                  }
                  i++;
              }
              cyBOT_Scan(smallWidth[1], &scan);


              char buffer[100];
              char head[] = "Angle(Degrees)    Distance(m)";
              printString(head);
              for(i =0; i <= 90; i++){
                 snprintf(buffer, 100, "%d                %f", i*2, distVals[i]/100);
                 printString(buffer);
              }

              char head2[] = "Object# Angle    Distance     Width";
              printString(head2);
              for(i = 0; i < obj; i++){
                 snprintf(buffer, 100, "%d        %d      %d           %d", objects[i*4], objects[(i*4)+1], objects[(i*4)+2], objects[(i*4)+3]);
                 printString(buffer);
              }
              snprintf(buffer, 100, "smallest angle location: %d", smallWidth[1]);
                                                           printString(buffer);
              if(smallWidth[1] < 90){
                  turn_clockwise(sensor, 90-smallWidth[1]);
              }else{
                  turn_ccw(sensor, smallWidth[1]-90);
              }
              move_forward(sensor, distVals[smallWidth[1]/2]);

            }
            if(uart_data == 'w'){
                move_forward(sensor, 1);
                lcd_putc(uart_data);
            }else if(uart_data == 's'){
                move_backward(sensor, 1);//forward 5
                lcd_putc(uart_data);
            }else if(uart_data == 'a'){ //under 90
                turn_clockwise(sensor, 12);//turn 20 deg
                lcd_putc(uart_data);
            }else if(uart_data == 'd'){ //over 90
                turn_ccw(sensor, 12);
                lcd_putc(uart_data);
            }
        }

        }


//while(1){
//    //PART 3
//    if(uart_flag){
//     uart_flag = 0x00;
//     lcd_putc(uart_data);
//     uart_sendChar(uart_data);
//    }
//}

//while(1){
//    //PART2
//        char x = uart_receive();
//        buffer[length]=x;
//        buffer[length+1]='\0';
//        length++;
//        if(buffer[length-1] == '\r'){
//            buffer[length-1]='\0';
//            uart_sendStr(buffer);
//            uart_sendChar('\n');
//            length = 0;
//        }
//}


        //PART 1
//        int length = 0;
//        char arr[21];
//        while(length < 20){
//            arr[length] = uart_receive();
//            if(arr[length] == '\r'){
//                arr[length] = '\0';
//                break;
//            }
//            length++;
//            lcd_clear();
//            snprintf(buffer, 50, "%d", length);
//            lcd_puts(buffer);
//        }
//        lcd_clear();
//        arr[20] = '\0';
//        lcd_puts(arr);
//    }

    return 0;
}
