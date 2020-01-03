/**
 * @file sensor.h
 *
 * @brief Sensors initialization and reading.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 04/2019
 */

#ifndef __SENSORS_H__
#define __SENSORS_H__

#include <stdbool.h>

#include "mcu.h"

/*****************************************
 * Public Constants
 *****************************************/

#define SENSORS_CHANNELS 3

#define POTENTIOMETER_MAX_VALUE 4034

/*****************************************
 * Public Types
 *****************************************/

/**
 * @brief Possible actions for the position of the sensors.
 */
typedef enum sensor_position {
    RIGHT,
    CENTER,
    LEFT,
} sensor_position_t;

/*****************************************
 * Public Variables
 *****************************************/

/**
 * @brief Holds sensors reading values.
 */
extern volatile uint32_t sensor_reading_value[SENSORS_CHANNELS];

/**
 * @brief Holds potentiometer reading value.
 */
extern volatile uint32_t potentiometer;

/*****************************************
 * Public Functions Prototypes
 *****************************************/

/**
 * @brief Initializes the sensors.
 */
void sensors_init();

/**
 * @brief Control leds brightness with the sensors reading values.
 */
void sensors_leds_control();

#endif
