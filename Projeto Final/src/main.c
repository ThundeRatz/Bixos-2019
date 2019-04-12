/**
 * @file main.c
 *
 * @brief Main function.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 04/2019
 */

#include "mcu.h"
#include "sensors.h"
#include "servo.h"
#include "buzzer.h"

/*****************************************
 * Main Function
 *****************************************/

int main(void) {
    mcu_init();

    // laser_control(ON);
    // mcu_sleep(2000);
    // laser_control(ON);

    for (;;) {
        if (button_pressed) {
            laser_control(OFF);

            // buzzer_control(200);
        } else {
            laser_control(ON);

            // buzzer_control(0);
        }

        sensors_leds_control();
        servo_potentiometer_control();

        // buzzer_control(0);
        mcu_sleep(300);
    }
}
