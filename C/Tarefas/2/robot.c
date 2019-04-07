/**
 * @file robot.c
 *
 * @brief ASCII robots related functions and variables.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 03/2019
 */

#include "robot.h"
#include "dojo.h"

/*****************************************
 * Public Variables Definitions
 *****************************************/

orientation_t current_rozeta_orientation = UPWARD;
orientation_t current_oponent_orientation = UPWARD;

char* upwards_robot[] = {
"                   ",
"    ___________    ",
"   |___________|   ",
"   |           |   ",
"  [|___________|]  ", 
};

char* downwards_robot[] = {
"                   ",
"    ___________    ",
"  [|           |]  ",
"   |___________|   ",
"   |___________|   ",
};

/*****************************************
 * Public Functions Bodies Definitions
 *****************************************/

void set_orientation(robot_t robot, orientation_t orientation) {
    switch (robot) {
        case ROZETA: {
            current_rozeta_orientation = orientation;
            break;
        }
        case OPONENT: {
            current_oponent_orientation = orientation;
            break;
        }
    }
}

void print_robot(robot_t robot, uint8_t dist_x, uint8_t dist_y) {
    char robot_apearence[ROBOT_LINES][ROBOT_COLUMNS];

    switch (robot) {
        case ROZETA: {
            switch (current_rozeta_orientation) {
                case UPWARD: {
                    for (int i = 0; i < ROBOT_LINES; i++) {
                        for (int j = 0; j < ROBOT_COLUMNS; j++) {
                           robot_apearence[i][j] = upwards_robot[i][j];
                        }
                    }
                    break;
                }
                case DOWNWARD: {
                    for (int i = 0; i < ROBOT_LINES; i++) {
                        for (int j = 0; j < ROBOT_COLUMNS; j++) {
                            robot_apearence[i][j] = downwards_robot[i][j];
                        }
                    }
                    break;
                }
            }

            robot_apearence[3][9] = 'R';

            if (!match_start) {
                robot_apearence[2][0] = '0';
                robot_apearence[0][4] = '1';
                robot_apearence[0][9] = '2';
                robot_apearence[0][14] = '3';
                robot_apearence[2][18] = '4';
                match_start = true;
            }

            break;
        } 
        case OPONENT: {
            switch (current_oponent_orientation) {
                case UPWARD: {
                    for (int i = 0; i < ROBOT_LINES; i++) {
                        for (int j = 0; j < ROBOT_COLUMNS; j++) {
                            robot_apearence[i][j] = upwards_robot[i][j];
                        }
                    }
                    robot_apearence[3][9] = ' ';
                    break;
                }
                case DOWNWARD: {
                    for (int i = 0; i < ROBOT_LINES; i++) {
                        for (int j = 0; j < ROBOT_COLUMNS; j++) {
                            robot_apearence[i][j] = downwards_robot[i][j];
                        }
                    }
                    robot_apearence[3][9] = '_';
                    break;
                }
            }
        }
    }

    for (int i = 0; i < ROBOT_LINES; i++) {
        for (int j = 0; j < ROBOT_COLUMNS; j++) {
            dojo[i + dist_x][j + dist_y] = robot_apearence[i][j];
        }
    }
}