#import <stdbool.h>
#import <stdint.h>
#import <stdio.h>
#import "header_file.h"

#define STRATEGIES_AMOUNT 6

#define STAR_RIGHT_TURN_TIME_MS 320
#define STAR_LEFT_TURN_TIME_MS 350

#define DS_THRESHOLD 220
#define TURN_SPEED MAX_SPEED

#define BASE_SPEED 15

#define DELAY 0

typedef void (*strategy_rozeta_t)(void);
typedef void (*strategy_onix_t)(bool);

static void estrela(void);
static void dibre(void);
static void arco_esquerda(void);
static void defensiva(void);
static void calibra_estrela(void);
static void emergencia(void);

static void estrelinha(bool delayed);
static void full_bomba(bool delayed);
static void static_defensive(bool delayed);
static void swing_defensive(bool delayed);
static void arc(bool delayed);
static void toquinho(bool delayed);

static void pid(float kp, float ki, float kd, int16_t base_speed, int8_t speed_left, int8_t speed_right);

static const strategy_rozeta_t rozeta_strategies[STRATEGIES_AMOUNT] = {estrela, dibre, arco_esquerda,
                                                                       defensiva, emergencia, calibra_estrela};

static const strategy_onix_t onix_strategies[STRATEGIES_AMOUNT] = {estrelinha, toquinho, arc, static_defensive,
                                                                   swing_defensive, full_bomba};

static strategy_rozeta_t rozeta_strategy;
static strategy_onix_t onix_strategy;

static uint16_t timer = 0;

static int desvio = 0;

static int swing_speed_right = SWING_SPEED;
static int swing_speed_left = -SWING_SPEED;

void rozeta_strategy_set(uint8_t strategy) {
    rozeta_strategy = rozeta_strategies[strategy-1];
}

void rozeta_strategy_run(void) {
    rozeta_strategy();
}

void onix_strategy_set(uint8_t strategy){
    onix_strategy = onix_strategies[strategy-1];
}

void onix_strategy_run(void) {
    onix_strategy(true)
}

void estrela(void) {

    turn_speed_multiplier = 1; /**< Turn speed multiplier */
    turn_time = 0;           /**< Turn time */

    distance_sensors_update();

    if (is_line_sensor_high(LS_FRONT_LEFT) || is_line_sensor_high(LS_FRONT_RIGHT)) {
        motors(MIN_SPEED, MIN_SPEED);

        if (is_line_sensor_high(LS_FRONT_RIGHT)) {
            turn_speed_multiplier = 1;
            turn_time = STAR_LEFT_TURN_TIME_MS;
        } else {
            turn_speed_multiplier = -1;
            turn_time = STAR_RIGHT_TURN_TIME_MS;
        }

        while (get_timer(timer) < turn_time) {
            if (distance_sensor_get(DS_FRONT_CENTER) < DS_THRESHOLD || last_bt_recv() != 0) {
                break;
            }

            motors(TURN_SPEED * turn_speed_multiplier, -TURN_SPEED * turn_speed_multiplier);
            distance_sensors_update();
        }

        return;
    }

    if (is_line_sensor_high(LS_BACK_LEFT) || is_line_sensor_high(LS_BACK_RIGHT) ||
        distance_sensor_get(DS_FRONT_CENTER) < DS_THRESHOLD) {
        motors(MAX_SPEED, MAX_SPEED);
        return;
    }

    int8_t speed_left = 0;
    int8_t speed_right = 0;

    pid(40, 0, 0, BASE_SPEED, &speed_left, &speed_right);

    motors(speed_left, speed_right);


}

void dibre(void) {

    static const uint32_t time_turn1 = 60;
    static const uint32_t time_straight1 = 115;
    static const uint32_t time_turn2 = 238;
    static const uint32_t time_straight2 = 518;
    static const uint32_t time_turn3 = 773;
    static const uint32_t time_straight3 = 795;

    uint8_t next_strategy = last_bt_recv();

    if (is_line_sensor_high(LS_FRONT_RIGHT) || is_line_sensor_high(LS_FRONT_LEFT)) {
        rozeta_strategy = rozeta_strategies[next_strategy];
        return;
    }

    if (get_timer(timer) < time_turn1) {
        motors(MAX_SPEED, MIN_SPEED);
    } else if (get_timer(timer) < time_straight1) {
        motors(MAX_SPEED, MAX_SPEED);
    } else if (get_timer(timer) < time_turn2) {
        motors(MIN_SPEED, MAX_SPEED);
    } else if (get_timer(timer) < time_straight2) {
        motors(MAX_SPEED, MAX_SPEED);
    } else if (get_timer(timer) < time_turn3) {
        motors(MIN_SPEED, MAX_SPEED);
    } else if (get_timer(timer) < time_straight3) {
        motors(20, 20);
    } else {
        motors(20, 20);
    }
}

void arco_esquerda(void) {
    static const uint32_t time1 = 325;
    static const uint32_t time2 = 525;
    static const uint32_t time3 = 625;
    static const uint32_t time4 = 775;
    static const uint32_t time5 = 875;
    static const uint32_t time6 = 1250;

    uint8_t next_strategy = last_bt_recv();

    if (is_line_sensor_high(LS_FRONT_RIGHT) || is_line_sensor_high(LS_FRONT_LEFT)) {
        rozeta_strategy = rozeta_strategies[next_strategy];
        return;
    }

    if (get_timer(timer) < time1) {
        motors(100, 45);
    } else if (get_timer(timer) < time2) {
        motors(100, 10);
    } else if (get_timer(timer) < time3) {
        motors(100, 18);
    } else if (get_timer(timer) < time4) {
        motors(100, 10);
    } else if (get_timer(timer) < time5) {
        motors(100, 5);
    } else if (get_timer(timer) < time6) {
        motors(100, 0);
    } else {
        motors(100, 0);
    }
}

void defensiva(void) {
    distance_sensors_update();
    reset_timer(&timer);

    int8_t speed_left;
    int8_t speed_right;

    pid(40, 0, 0, 0, &speed_left, &speed_right);

    if (abs(speed_left) > 10) {
        reset_timer(&timer);
    }

    if (get_timer(timer) > 5000 || distance_sensor_get(DS_FRONT_CENTER) < DS_THRESHOLD) {
        rozeta_strategy = estrela;
    } else {
        motors(speed_left, speed_right);
    }
}

void emergencia(void) {
    motors(MAX_SPEED, MAX_SPEED);
}

void calibra_estrela(void) {
    int8_t turn_speed_multiplier = 1; /**< Turn speed multiplier */
    uint16_t turn_time = 0;           /**< Turn time */

    distance_sensors_update();

    if (is_line_sensor_high(LS_FRONT_LEFT) || is_line_sensor_high(LS_FRONT_RIGHT)) {
        motors(MIN_SPEED, MIN_SPEED);

        if (is_line_sensor_high(LS_FRONT_RIGHT)) {
            turn_speed_multiplier = 1;
            turn_time = STAR_LEFT_TURN_TIME_MS;
        } else {
            turn_speed_multiplier = -1;
            turn_time = STAR_RIGHT_TURN_TIME_MS;
        }

        while (get_timer(timer) < turn_time) {
            if (distance_sensor_get(DS_FRONT_CENTER) < DS_THRESHOLD || last_bt_recv() != 0) {
                break;
            }

            motors(TURN_SPEED * turn_speed_multiplier, -TURN_SPEED * turn_speed_multiplier);
            distance_sensors_update();
        }

        return;
    }

    if (is_line_sensor_high(LS_BACK_LEFT) || is_line_sensor_high(LS_BACK_RIGHT) ||
        distance_sensor_get(DS_FRONT_CENTER) < DS_THRESHOLD) {
        motors(MAX_SPEED, MAX_SPEED);
        return;
    }

    motors(BASE_SPEED, BASE_SPEED);
}

static void pid(float kp, float ki, float kd, int16_t base_speed, int8_t* speed_left, int8_t* speed_right) {
    static float pid_error = 0.0;
    static float pid_last_error = 0.0;
    static float pid_weight = 0.0;

    static float pid_integrative = 0.0;
    static float pid_derivative = 0.0;
    static float pid_action = 0.0;

    pid_error = (-2) * (DS_MAX_RANGE + 1 - distance_sensor_get(DS_SIDE_LEFT)) +
                (-1) * (DS_MAX_RANGE + 1 - distance_sensor_get(DS_FRONT_RIGHT)) +
                (+1) * (DS_MAX_RANGE + 1 - distance_sensor_get(DS_FRONT_LEFT)) +
                (+2) * (DS_MAX_RANGE + 1 - distance_sensor_get(DS_SIDE_RIGHT));

    pid_weight = (DS_MAX_RANGE + 1 - distance_sensor_get(DS_SIDE_LEFT)) +
                 (DS_MAX_RANGE + 1 - distance_sensor_get(DS_FRONT_RIGHT)) +
                 (DS_MAX_RANGE + 1 - distance_sensor_get(DS_FRONT_LEFT)) +
                 (DS_MAX_RANGE + 1 - distance_sensor_get(DS_SIDE_RIGHT));

    pid_error /= pid_weight;
    pid_integrative += pid_error;
    pid_derivative = pid_error - pid_last_error;
    pid_last_error = pid_error;
    pid_action = kp * pid_error + ki * pid_integrative + kd * pid_derivative;

    if (distance_sensor_get(DS_FRONT_LEFT) > 150 && distance_sensor_get(DS_FRONT_RIGHT) > 150) {
        *speed_left = constrain(base_speed + pid_action, MIN_SPEED, MAX_SPEED);
        *speed_right = constrain(base_speed - pid_action, MIN_SPEED, MAX_SPEED);
    } else {
        *speed_left = constrain(base_speed - pid_action, MIN_SPEED, MAX_SPEED);
        *speed_right = constrain(base_speed + pid_action, MIN_SPEED, MAX_SPEED);
    }
}

/*****************************************
 * Rozeta Strategies
 *****************************************/

void reversion_right(){
    motors(-100,-100);
    motors(-REVERSION_TURN_SPEED,+REVERSION_TURN_SPEED);
}

void reversion_left(){
    motors(-100,-100);
    motors(REVERSION_TURN_SPEED,-REVERSION_TURN_SPEED);
}

void straight_search(){
    motors(50,50);
}

void swing_search(bool swing_start){

    motors(swing_speed_left,swing_speed_right);

    if(swing_start == true || get_timer(timer) >= (SWING_PERIOD)/2){
        reset_timer(&timer);
        swing_start = false;
        swing_speed_left = - swing_speed_left;
        swing_speed_right = - swing_speed_right;
    }

    if (get_timer(timer) >= SWING_PERIOD ){
        reset_timer(&timer);
        swing_speed_left = - swing_speed_left;
        swing_speed_right = - swing_speed_right;
    }
}

void pulse_search(){

    if [get_timer(timer) > 2000] {
        motors(PULSE_SPEED,PULSE_SPEED);
        reset_timer(&timer);
    }

}

void arc_move_right(){

    // turn left
    motors(MAX_SPEED, 0);
    // straight
    motors(MAX_SPEED, MAX_SPEED);
    // turn right
    motors(0, MAX_SPEED);
    // straight
    motors(MAX_SPEED, 75);

}

void arc_move_left(){

    // turn right
    motors(0,MAX_SPEED);
    // straight
    motors(MAX_SPEED, MAX_SPEED);
    // turn left
    motors(MAX_SPEED,0);
    // straight
    motors(MAX_SPEED, 75);

}

void attack(){
    motors(50,50);
}

/*****************************************
 * Onix Strategies                       *
 *****************************************/

void full_bomba(bool delayed) {
    if (delayed == true) {
        delayed = false;
    }
    motors(MAX_SPEED, 75);
}

void static_defensive(bool delayed) {
    if (delayed == true) {
        delayed = false;
    }

    if (line_see(LS_RIGHT) || line_see(LS_LEFT)) {
        if(sensors[LS_LEFT] < sensors[LS_RIGHT]){
            reversion_right();
        } else{
            reversion_left();
        }

    } elseif ((sensors[DS_LEFT] > LONG_DISTANCE && sensors[DS_LEFT] < SHORT_DISTANCE) &&
               (sensors[DS_RIGHT] > LONG_DISTANCE && sensors[DS_RIGHT] < SHORT_DISTANCE)) {
        motors(60, 80);
    } else if (sensors[DS_LEFT] > LONG_DISTANCE && sensors[DS_LEFT] < SHORT_DISTANCE) {
        motors(0, 80);
    } else if (sensors[DS_RIGHT] > LONG_DISTANCE && sensors[DS_RIGHT] < SHORT_DISTANCE) {
        motors(60, 0);
    } else if (sensors[DS_LEFT] > SHORT_DISTANCE || sensors[DS_RIGHT] > SHORT_DISTANCE) {
        motors(75, MAX_SPEED);
    } else {
        motors(0, 0);
    }
}

void swing_defensive(bool delayed) {
    if (delayed == true) {
        delayed = false;
    }

    if (line_see(LS_RIGHT) || line_see(LS_LEFT)) {
        if(sensors[LS_LEFT] < sensors[LS_RIGHT]){
            reversion_right();
        } else{
            reversion_left();
        }

    } else if ((sensors[DS_LEFT] > LONG_DISTANCE && sensors[DS_LEFT] < SHORT_DISTANCE) &&
               (sensors[DS_RIGHT] > LONG_DISTANCE && sensors[DS_RIGHT] < SHORT_DISTANCE)) {
        motors(60, 80);
    } else if (sensors[DS_LEFT] > LONG_DISTANCE && sensors[DS_LEFT] < SHORT_DISTANCE) {
        motors(0, 80);
    } else if (sensors[DS_RIGHT] > LONG_DISTANCE && sensors[DS_RIGHT] < SHORT_DISTANCE) {
        motors(60, 0);
    } else if (sensors[DS_LEFT] > SHORT_DISTANCE || sensors[DS_RIGHT] > SHORT_DISTANCE) {
        motors(75, MAX_SPEED);
    } else {
        swing_search(0);
    }
}


void toquinho(bool delayed) {
    if (delayed == true) {
        delayed = false;
    }

    if (line_see(LS_RIGHT) || line_see(LS_LEFT)) {
        if(sensors[LS_LEFT] < sensors[LS_RIGHT]){
            reversion_right();
        } else{
            reversion_left();
        }
    } else if ((sensors[DS_LEFT] > LONG_DISTANCE && sensors[DS_LEFT] < SHORT_DISTANCE) &&
               (sensors[DS_RIGHT] > LONG_DISTANCE && sensors[DS_RIGHT] < SHORT_DISTANCE)) {
        motors(30, 55);
    } else if (sensors[DS_LEFT] > LONG_DISTANCE && sensors[DS_LEFT] < SHORT_DISTANCE) {
        motors(0, 30);
    } else if (sensors[DS_RIGHT] > LONG_DISTANCE && sensors[DS_RIGHT] < SHORT_DISTANCE) {
        motors(30, 0);
    } else if (sensors[DS_LEFT] > SHORT_DISTANCE || sensors[DS_RIGHT] > SHORT_DISTANCE) {
        motors_straight_line(75, MAX_SPEED);

    } else {
        pulse_search();
    }
}


void estrelinha(bool delayed) {
    if (delayed == true) {
        delayed = false;
    }

    straight_search();

   if (line_see(LS_RIGHT) || line_see(LS_LEFT)) {
        if(sensors[LS_LEFT] < sensors[LS_RIGHT]){
            reversion_right();
        } else{
            reversion_left();
        }

    } else if ((sensors[DS_LEFT] > LONG_DISTANCE && sensors[DS_LEFT] < SHORT_DISTANCE) &&
               (sensors[DS_RIGHT] > LONG_DISTANCE && sensors[DS_RIGHT] < SHORT_DISTANCE)) {
        motors(30, 55);
    } else if (sensors[DS_LEFT] > LONG_DISTANCE && sensors[DS_LEFT] < SHORT_DISTANCE) {
        motors(0, 30);
    } else if (sensors[DS_RIGHT] > LONG_DISTANCE && sensors[DS_RIGHT] < SHORT_DISTANCE) {
        motors(30, 0);
    } else if (sensors[DS_LEFT] > SHORT_DISTANCE || sensors[DS_RIGHT] > SHORT_DISTANCE) {
        motors(75, MAX_SPEED);
    }
}

void arc(bool delayed) {
    if (delayed == true) {
        delayed = false;
        desvio = 0;
    }

    if (desvio == 0){
        desvio = 1;
    }

    if (line_see(LS_RIGHT) || line_see(LS_LEFT)) {
        if(sensors[LS_LEFT] < sensors[LS_RIGHT]){
            reversion_right();
        } else{
            reversion_left();
        }


    } else if ((sensors[DS_LEFT] > LONG_DISTANCE && sensors[DS_LEFT] < SHORT_DISTANCE) &&
               (sensors[DS_RIGHT] > LONG_DISTANCE && sensors[DS_RIGHT] < SHORT_DISTANCE)) {
        motors(60, 85);
    } else if (sensors[DS_LEFT] > LONG_DISTANCE && sensors[DS_LEFT] < SHORT_DISTANCE) {
        motors(0, 85);
    } else if (sensors[DS_RIGHT] > LONG_DISTANCE && sensors[DS_RIGHT] < SHORT_DISTANCE) {
        motors(60, 0);
    } else if (sensors[DS_LEFT] > SHORT_DISTANCE || sensors[DS_RIGHT] > SHORT_DISTANCE) {
        motors(MAX_SPEED, MAX_SPEED);
    } else {
        motors(0, 0);
    }
}
