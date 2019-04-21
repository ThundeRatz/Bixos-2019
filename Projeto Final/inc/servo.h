/**
 * @file servo.h
 *
 * @brief Servo initialization and control.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 04/2019
 */

#ifndef __SERVO_H__
#define __SERVO_H__

#include <stdint.h>

/*****************************************
 * Public Types
 *****************************************/

/**
 * @brief Possible actions for the laser.
 */
typedef enum laser_action {
    ON,
    OFF,
} laser_action_t;

/*****************************************
 * Public Functions Prototypes
 *****************************************/

/**
 * @brief Initializes the servo.
 */
void servo_init();

/**
 * @brief Control servo position.
 *
 * @param angle Angle of the servo.
 */
void servo_control(int16_t angle);

/**
 * @brief Controls the state of the laser.
 *
 * @param action State of the laser.
 */
void laser_control(laser_action_t action);

#endif // __SERVO_H__
