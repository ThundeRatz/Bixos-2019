/**
 * @file main.c
 *
 * @brief Main function.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 03/2019
 */

#include <stdio.h>

#include "delay.h"
#include "dojo.h"
#include "robot.h"
#include "movement.h"
#include "initialization.h"
#include "strategies.h"

/*****************************************
 * Main Function
 *****************************************/

int main() {
    initialization();

    printf("\n\nDigite a posição do robo: ");
    scanf("%d", &sensor_position);

    set_oponent_position(sensor_position);

    print_dojo();

    char mov;
    printf("\n\nIniciar movimento [s/n]: ");
    scanf(" %c", &mov);

    if (mov != 's') {
        printf("Bye bye");
        return 0;
    }

    strategie_one();
    
    return 0;
}
