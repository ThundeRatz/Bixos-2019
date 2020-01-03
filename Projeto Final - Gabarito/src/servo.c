/**
 * @file servo.c
 *
 * @brief Servo initialization and control.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 04/2019
 */

#include "servo.h"
#include "tim.h"
#include "utils.h"
#include "sensors.h"

/*****************************************
 * Public Functions Bodies Definitions
 *****************************************/

void servo_init() {
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
}

void servo_control(int16_t angle) {
    angle = constrain(angle, -90, 90);

    angle = map(angle, -90, 90, 700, 2300);

    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, angle);
}

void servo_potentiometer_control() {
    int16_t angle = map(potentiometer, 0, POTENTIOMETER_MAX_VALUE, -90, 90);

    servo_control(angle);
}

void laser_control(laser_action_t action) {
    switch (action) {
        case ON:
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
            break;

        case OFF:
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
            break;
    }
}
