/**
 * @file movement.h
 *
 * @brief Movement related functions and variables.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 03/2019
 */

#ifndef __MOVEMENT_H__
#define __MOVEMENT_H__

#include <stdint.h>

/*****************************************
 * Public Variables
 *****************************************/

extern float delay_time;

extern uint8_t rozeta_line;
extern uint8_t rozeta_column;

extern uint8_t oponent_line;
extern uint8_t oponent_column;

/*****************************************
 * Public Functions Prototypes
 *****************************************/

/**
 * @brief Movement related functions and variables.
 *
 * @param speed robot speed in line/second.
 */
void set_speed(float speed);

void move_up();

void move_down();

void move_right();

void move_left();

#endif // __MOVEMENT_H__
