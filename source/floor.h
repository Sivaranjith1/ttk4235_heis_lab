/**
 * @file floor.h
 * @author Ask and Sivaranjith
 * @brief Control the floor position and direction control for request of specific floor
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
 *  Solely used for testing purposes, otherwise uint8_t is used.
 */
typedef enum {
    FLOOR1,
    FLOOR2,
    FLOOR3,
    FLOOR4
} AllFloors;

/**
 * @brief Possible travel direction for the elevator
 * 
 */
typedef enum {
    MOVEMENT_STILL,
    MOVEMENT_UP,
    MOVEMENT_DOWN
} MotorMovement;

/**
 * @brief Specify where the elevator is related to the last visited
 * 
 */
typedef enum {
    FLOOR_POSITION_ABOVE,
    FLOOR_POSITION_BELOW
} FloorPositionBetweenFloor;

/**
 * @brief Initialize the state of floor. Will drive up until it reaches a valid floor
 */
void floor_init();



/**
 * @brief Get the Last Visited Floor object
 * 
 * @return uint8_t the last visited floor
 */
AllFloors floor_get_last_visited_floor();

/**
 * @brief Drive up to the desired floor
 * 
 * @param floor_num the floor that is desired
 * 
 * @return MotorMovement The direction it is currently traveling
 */
MotorMovement floor_go_to_floor(AllFloors floor_num);

/**
 * @brief Set the Last Visited Floor object when detecting a sensor update
 * 
 * @return MotorMovement The direction it is currently traveling
 */
MotorMovement floor_set_last_visited_floor();

/**
 * @brief Checks if the elevator is at a valid floor
 * 
 * @return uint8_t 1 if valid floor, 0 otherwise
 */
uint8_t floor_at_valid_floor();

#endif