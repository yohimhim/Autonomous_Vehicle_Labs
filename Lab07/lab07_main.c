#include <math.h>
#include <stdio.h>
#include "Timer.h"
#include "lcd.h"
#include "cyBot_Scan.h"
#include "uart.h"
#include "movement.h"
#include "open_interface.h"

// Up to 4 scans (you can change this)
#define MAX_RECURSION_DEPTH 4
#define AVERAGE_COUNT 4

typedef struct obj {
    int objNum;
    int width;
    int angle;
    double distance;
    double TRUEWIDTH;
} obj;

/**
 * Recursively scans, finds objects, drives to the smallest, and repeats.
 *
 * @param sensor_data   Pointer to iRobot sensor struct
 * @param scan          A cyBOT_Scan_t struct (reused each time)
 * @param depth         Current recursion depth, starts at 1
 */
void run_autonomous_scan(oi_t *sensor_data, cyBOT_Scan_t *scan, int depth)
{
    // 1) Base case: if we've reached the recursion limit, stop
    if (depth > MAX_RECURSION_DEPTH) {
        uart_sendStr("Reached max recursion depth.\r\n");
        return;
    }

    // 2) Clear any leftover objects
    obj storedObj[10] = {0};

    // Variables for scanning
    double distanceReadings[AVERAGE_COUNT] = {0};
    int index = 0;
    int currentObj = 0;
    int objCount = 0;
    int firstDegree = 0, lastDegree = 0;
    double firstDistance = 0;

    // 3) Perform the scan loop, same as your 'm' command
    timer_waitMillis(500); // let servo settle
    int angle;
    for (angle = 5; angle <= 180; angle += 2) {

        cyBOT_Scan(angle, scan);

        // Rolling average distance
        distanceReadings[index] = scan->sound_dist;
        index = (index + 1) % AVERAGE_COUNT;

        double avgDistance = 0;
        int j;
        for (j = 0; j < AVERAGE_COUNT; j++) {
            avgDistance += distanceReadings[j];
        }
        avgDistance /= AVERAGE_COUNT;

        // Print data
        char data_line[64];
        sprintf(data_line, "Angle: %d PING: %.2f IR: %d AvgDist: %.2f\r\n",
                angle, scan->sound_dist, scan->IR_raw_val, avgDistance);
        uart_sendStr(data_line);

        // Simple IR-based detection: IR >= 900 & distance < 60
        if (scan->IR_raw_val >= 900 && currentObj == 0 && avgDistance < 60.0) {
            objCount++;
            currentObj = 1;
            firstDegree = angle;
            firstDistance = avgDistance;
        }
        else if (scan->IR_raw_val < 900 && currentObj == 1) {
            lastDegree = angle;
            currentObj = 0;

            // Record object
            int degObj = (firstDegree + lastDegree) / 2;
            int radialWidth = lastDegree - firstDegree;

            char msg[80];
            sprintf(msg, "OBJECT #%d: angle=%d dist=%.2f width=%d\r\n",
                    objCount, degObj, firstDistance, radialWidth);
            uart_sendStr(msg);

            storedObj[objCount - 1].objNum  = objCount;
            storedObj[objCount - 1].width  = radialWidth;
            storedObj[objCount - 1].angle  = degObj;
            storedObj[objCount - 1].distance = firstDistance;

            double size = ((double) radialWidth / 360.0) * (2.0 * M_PI) * firstDistance;
            storedObj[objCount - 1].TRUEWIDTH = size;

            sprintf(msg, "SIZE: %.2f\r\n", size);
            uart_sendStr(msg);
        }
    } // end for

    // 4) If no objects, done
    if (objCount == 0) {
        uart_sendStr("No objects detected.\r\n");
        return;
    }

    // 5) Pick smallest object
    obj smallestObj = storedObj[0];
    double smallestWidth = storedObj[0].TRUEWIDTH;

    int i;
    for(i = 1; i < objCount; i++){
        if(storedObj[i].TRUEWIDTH < smallestWidth){
            smallestWidth = storedObj[i].TRUEWIDTH;
            smallestObj = storedObj[i];
        }
    }

    // 6) Drive to smallest object
    // Re-scan that angle (optional)
    cyBOT_Scan(smallestObj.angle, scan);

    char str[80];
    if (smallestObj.angle < 90) {
        sprintf(str, "SCAN COMPLETE - TURN RIGHT\r\n");
        uart_sendStr(str);
        turn_clockwise(sensor_data, 81 - smallestObj.angle);
        timer_waitMillis(500);
        move_forward(sensor_data, smallestObj.distance * 8);
    } else {
        sprintf(str, "SCAN COMPLETE - TURN LEFT\r\n");
        uart_sendStr(str);
        turn_counterclockwise(sensor_data, smallestObj.angle - 111);
        timer_waitMillis(500);
        move_forward(sensor_data, smallestObj.distance * 8);
    }

    // 7) Recursively call ourselves again to see if there's a new environment
    // We increment 'depth' so eventually we stop recursing.
    int bumped = move_forward(sensor_data, smallestObj.distance * 8);

    if (bumped) {
        // We bumped into something, so let's do another scan.
        run_autonomous_scan(sensor_data, scan, depth + 1);
    } else {
        // No bump -> done
        uart_sendStr("Reached smallest object with no bump. Stopping.\r\n");
    }}

//------------------------------------------------------------------------------

int main(void)
{
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    lcd_init();
    lcd_clear();
    timer_init();

    // Initialize servo, IR, PING
    cyBOT_init_Scan(0b0111);
    //cyBOT_SERVO_cal();

    // Cal values for your servo
    right_calibration_value = 232750;
    left_calibration_value  = 1246000;

    uart_init();

    // We’ll reuse this single scan struct each time
    cyBOT_Scan_t myScan;

    // Main loop: if user presses 'm', do a recursive scan
    while (1) {
        char input = uart_receive();
        uart_sendChar(input);

        if (input == 'm') {
            run_autonomous_scan(sensor_data, &myScan, 1);
        }
    }

    // Cleanup
    oi_setWheels(0,0);
    oi_free(sensor_data);
    return 0;
}
