/**
 * @file mcu.h
 *
 * @brief MCU related.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 04/2019
 */

#ifndef __MCU_H__
#define __MCU_H__

#include <stdint.h>
#include <stdbool.h>

/*****************************************
 * Public Function Prototypes
 *****************************************/

/**
 * @brief Initializes System Clock.
 *
 * @note  Defined by cube.
 */
void SystemClock_Config(void);

/**
 * @brief Initializes MCU and some peripherals.
 */
void mcu_init(void);

/**
 * @brief Put the MCU to sleep.
 *
 * @param ms Sleep time in milliseconds.
 */
void mcu_sleep(uint32_t ms);

/**
 * @brief Toggles LED.
 */
void led_toggle(void);

#endif // __MCU_H__
