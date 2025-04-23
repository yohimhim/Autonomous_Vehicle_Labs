/**
 * @file lab9_template.c
 * @author
 * Template file for CprE 288 Lab 9
 */

#include "Timer.h"
#include "lcd.h"
#include "ping.h"

// Uncomment or add any include directives that are needed

#warning "Possible unimplemented functions"
#define REPLACEME 0

int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	ping_init();

	// YOUR CODE HERE
	volatile int i = 0;

	while(1)
	{
      // YOUR CODE HERE
	    float distance = 0;
	    distance = ping_getDistance();
	    lcd_printf( "Distance: %.2f cm \nWidth: %.2f \nOverflow: %.2f", distance, getPulsewidth(), getOverflow());
        timer_waitMillis(150);

	}

}
