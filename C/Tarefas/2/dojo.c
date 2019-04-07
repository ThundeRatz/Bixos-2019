/**
 * @file dojo.c
 *
 * @brief Functions and variables to dela with the dojo matrix.
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 03/2019
 */

#include <stdio.h>

#include "dojo.h"

/*****************************************
 * Public Variables Definitions
 *****************************************/

bool match_start = false;

char dojo[DOJO_LINES][DOJO_COLUMNS];

/*****************************************
 * Public Functions Bodies Definitions
 *****************************************/

void clean_dojo() {
    for (int i = 0; i < DOJO_LINES; i++) {
        for (int j = 0; j < DOJO_COLUMNS; j++){
            dojo[i][j] = ' ';
        }
    }
}

void print_dojo() {
    if (match_start) {
        printf("\033[2J\033[H"); /**< Limpa o terminal */
    }

    printf("%s", "╔");
    for (int i = 0; i < DOJO_LINES + 42; i++) {
        printf("%s", "═");
    }
    printf("╗\n");

    for (int i = 0; i < DOJO_LINES; i++) {
        printf("%s", "║");
        for (int j = 0; j < DOJO_COLUMNS; j++){
            printf("%c", dojo[i][j]);
        }
        printf("%s", "║");
        printf("\n");
    }

    printf("%s", "╚");
    for (int i = 0; i < DOJO_LINES + 42; i++) {
        printf("%s", "═");
    }
    printf("╝\n");
}
