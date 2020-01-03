/**
 * @file buzzer.c
 *
 * @brief Buzzer initialization and control.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 04/2019
 */

#include "tim.h"
#include "buzzer.h"

/*****************************************
 * Private Constants
 *****************************************/

#define BUZZER_MAX_FREQUENCY 1000000

/*****************************************
 * Public Functions Bodies Definitions
 *****************************************/

void buzzer_init() {
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}

void buzzer_control(uint16_t frequency) {
    uint16_t counter = BUZZER_MAX_FREQUENCY / frequency;

    __HAL_TIM_SET_COUNTER(&htim1, counter);

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, counter);
}
