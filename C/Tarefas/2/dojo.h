/**
 * @file dojo.h
 *
 * @brief Functions and variables to dela with the dojo matrix.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 03/2019
 */

#ifndef __DOJO_H__
#define __DOJO_H__

#include <stdbool.h>

#include "robot.h"

/*****************************************
 * Public Constants
 *****************************************/

#define DOJO_LINES (3*ROBOT_LINES + 2)
#define DOJO_COLUMNS (3*ROBOT_COLUMNS + 2)

/*****************************************
 * Public Variables
 *****************************************/

extern bool match_start;

extern char dojo[DOJO_LINES][DOJO_COLUMNS];

/*****************************************
 * Public Functions Prototypes
 *****************************************/

void clean_dojo();

void print_dojo();

#endif // __DOJO_H__
