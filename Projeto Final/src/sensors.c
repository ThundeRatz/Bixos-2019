/**
 * @file sensor.c
 *
 * @brief Sensors initialization and reading.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 04/2019
 */

#include <stdbool.h>

#include "sensors.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "utils.h"

/*****************************************
 * Private Constants
 *****************************************/

#define ADC1_CHANNELS 4

#define ADC_BUFFER_SIZE (ADC1_CHANNELS * 70)

/*****************************************
 * Private Variables
 *****************************************/

static uint32_t adc1_buffer[ADC_BUFFER_SIZE] = {0};

/*****************************************
 * Public Variables
 *****************************************/

volatile uint32_t sensor_reading_value[3] = {0};
volatile uint32_t potentiometer = 0;

/*****************************************
 * Public Functions Bodies Definitions
 *****************************************/

void sensors_init() {
    MX_DMA_Init();
    MX_ADC1_Init();
    HAL_ADC_Start_DMA(&hadc1, adc1_buffer, ADC_BUFFER_SIZE);

    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
}

void sensors_leds_control() {
    /**< Code **/
}

/**
 * @brief ADC Conversion Complete Callback.
 *
 * @note Detects adc1_buffer overflow, makes the average of the read values
 *       and store this value in sensor_reading_value[] and potenciometer.
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    if (hadc->Instance == ADC1) {
        uint32_t val[ADC1_CHANNELS] = {0};

        for (int i = 0; i < ADC_BUFFER_SIZE / ADC1_CHANNELS; i++) {
            for (int j = 0; j < ADC1_CHANNELS; j++) {
                val[j] += adc1_buffer[ADC1_CHANNELS * i + j];
            }
        }

        for (int i = 0; i < ADC1_CHANNELS; i++) {
            val[i] /= ADC_BUFFER_SIZE / ADC1_CHANNELS;
        }

        sensor_reading_value[RIGHT] = val[RIGHT];
        sensor_reading_value[CENTER] = val[CENTER];
        sensor_reading_value[LEFT] = val[LEFT];

        potentiometer = val[3];
    }
}
