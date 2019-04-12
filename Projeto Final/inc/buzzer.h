/**
 * @file buzzer.h
 *
 * @brief Buzzer initialization and control.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 04/2019
 */

#ifndef __BUZZER_H__
#define __BUZZER_H__

#include <stdint.h>

/*****************************************
 * Public Functions Prototypes
 *****************************************/

/**
 * @brief Initializes the buzzer.
 */
void buzzer_init();

/**
 * @brief Turns on the buzzer at a specified frequency.
 *
 * @param frequency Sound frequency.
 */
void buzzer_control(uint16_t frequency);

#endif // __BUZZER_H__
