/**
 * @file mcu.c
 *
 * @brief MCU related.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 04/2019
 */

#include <stdint.h>

#include "stm32f1xx_hal.h"

#include "gpio.h"
#include "tim.h"

#include "mcu.h"
#include "sensors.h"
#include "buzzer.h"
#include "servo.h"

/*****************************************
 * Public Variables
 *****************************************/

bool button_pressed = false;

/*****************************************
 * Public Function Body Definitions
 *****************************************/

void mcu_init(void) {
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();

    MX_TIM1_Init();
    MX_TIM2_Init();
    MX_TIM3_Init();

    sensors_init();

    servo_init();

    buzzer_init();
}

void mcu_sleep(uint32_t ms) {
    HAL_Delay(ms);
}

void led_toggle(void) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}

/**
 * @brief GPIO External Interupt Callback.
 *
 * @note Detects falling edge on the button pin.
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == GPIO_PIN_14) {
        button_pressed = !button_pressed;
    }
}
