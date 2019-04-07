/**
 * @file movement.c
 *
 * @brief Movement related functions and variables.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 03/2019
 */

#include <stdint.h>

#include "movement.h"
#include "dojo.h"
#include "delay.h"

/*****************************************
 * Public Variables Definitions
 *****************************************/

float delay_time = 0.5;

uint8_t rozeta_line = DOJO_LINES - ROBOT_LINES;
uint8_t rozeta_column = (DOJO_COLUMNS - ROBOT_COLUMNS)/2; 

uint8_t oponent_line = 0;
uint8_t oponent_column = 0; 

/*****************************************
 * Public Functions Bodies Definitions
 *****************************************/

void set_speed(float speed) {
    delay_time = (1/speed) * 1000; /**< Delay time in microseconds */
}

void move_up() {
    if (rozeta_line - 1 > 0) {
        rozeta_line--;
    }

    clean_dojo();

    print_robot(OPONENT, oponent_line, oponent_column);
    print_robot(ROZETA, rozeta_line, rozeta_column);

    delay(delay_time);

    print_dojo();
}

void move_down() {
    if (rozeta_line + (ROBOT_LINES - 1) < DOJO_LINES - 1) {
        rozeta_line++;
    }

    clean_dojo();

    print_robot(OPONENT, oponent_line, oponent_column);
    print_robot(ROZETA, rozeta_line, rozeta_column);

    delay(delay_time);

    print_dojo();
}

void move_right() {
    if (rozeta_column + (ROBOT_COLUMNS - 1) < DOJO_COLUMNS - 1) {
        rozeta_column++;
    }

    clean_dojo();

    print_robot(OPONENT, oponent_line, oponent_column);
    print_robot(ROZETA, rozeta_line, rozeta_column);

    delay(delay_time);

    print_dojo();
}

void move_left() {
    if (rozeta_column - 1 > 0) {
        rozeta_column--;
    }

    clean_dojo();

    print_robot(OPONENT, oponent_line, oponent_column);
    print_robot(ROZETA, rozeta_line, rozeta_column);

    delay(delay_time);

    print_dojo();
}