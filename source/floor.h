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
 * @brief Initialize the state of floor. Will drive up until it reaches a valid floor
 */
void floor_init();



/**
 * @brief Get the Last Visited Floor object
 * 
 * @return uint8_t the last visited floor
 */
uint8_t getLastVisitedFloor();

/**
 * @brief Drive up to the desired floor
 * 
 * @param floor_num the floor that is desired
 */
void goToFloor(uint8_t floor_num);

/**
 * @brief Set the Last Visited Floor object when detecting a sensor update
 * 
 */
void set_last_visited_floor();

void setOnFloorCallbackFunction(void (*callback_ptr)());

#endif