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
 */
void go_to_floor(ALL_FLOORS floor_num);

/**
 * @brief Set the Last Visited Floor object when detecting a sensor update
 * 
 */
void set_last_visited_floor();

/**
 * @brief Set the On Floor Callback Function that is called each time a floor is passed
 * 
 * @param callback_ptr The function pointer to call
 */
void set_on_floor_callback_function(void (*callback_ptr)());

#endif