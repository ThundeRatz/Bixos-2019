/**
 * @file robot.h
 *
 * @brief ASCII robots related functions and variables.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 03/2019
 */

#ifndef __ROBOT_H__
#define __ROBOT_H__

#include <stdint.h>

/*****************************************
 * Public Constants
 *****************************************/

#define ROBOT_LINES 5
#define ROBOT_COLUMNS 19

/*****************************************
 * Public Types
 *****************************************/

typedef enum robot {
    ROZETA,
    OPONENT,
} robot_t;

typedef enum orientation {
    UPWARD,
    DOWNWARD,
} orientation_t;

/*****************************************
 * Public Variables
 *****************************************/

extern orientation_t current_rozeta_orientation;
extern orientation_t current_oponent_orientation;

extern char* upwards_robot[ROBOT_LINES];

extern char* downwards_robot[ROBOT_LINES];

/*****************************************
 * Public Functions Prototypes
 *****************************************/

void set_orientation(robot_t robot, orientation_t orientation);

void print_robot(robot_t robot, uint8_t dist_x, uint8_t dist_y);

#endif // __ROBOT_H__
