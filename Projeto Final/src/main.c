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

    for (;;) {
        mcu_sleep(300);
    }
}
