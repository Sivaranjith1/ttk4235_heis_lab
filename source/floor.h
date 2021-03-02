/**
 * @file floor.h
 * @author Ask & Sivaranjith
 * @brief 
 * @version 0.1
 * @date 2021-02-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef FLOOR_H
#define FLOOR_H

#include <stdint.h>

#define NUM_FLOOR 4U

/**
 * @brief Enum with all the valid floors
 * 
 */
typedef enum {
    FLOOR1,
    FLOOR2,
    FLOOR3,
    FLOOR4
} ALL_FLOORS;

typedef enum {
    MOVEMENT_STILL,
    MOVEMENT_UP,
    MOVEMENT_DOWN
} MOTOR_MOVEMENT;

/**
 * @brief Initialize the state of floor. Will drive up until it reaches a valid floor
 */
void floor_init();



/**
 * @brief Get the Last Visited Floor object
 * 
 * @return uint8_t the last visited floor
 */
ALL_FLOORS get_last_visited_floor();

/**
 * @brief Drive up to the desired floor
 * 
 * @param floor_num the floor that is desired
 * 
 * @return MOTOR_MOVEMENT The direction it is currently traveling
 */
MOTOR_MOVEMENT go_to_floor(ALL_FLOORS floor_num);

/**
 * @brief Set the Last Visited Floor object when detecting a sensor update
 * 
 * @return MOTOR_MOVEMENT The direction it is currently traveling
 */
MOTOR_MOVEMENT set_last_visited_floor();

/**
 * @brief Checks if the elevator is at a valid floor
 * 
 * @return uint8_t 1 if valid floor, 0 otherwise
 */
uint8_t floor_at_valid_floor();


#endif