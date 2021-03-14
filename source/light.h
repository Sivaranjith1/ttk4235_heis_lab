/**
 * @file lights.h
 * @author Ask and Sivaranjith
 * @brief Clear all lights and clear all lights at floor
 * @version 0.1
 * @date 2021-03-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef LIGHT_H
#define LIGHT_H

#include <stdint.h>

/**
 * @brief Resets all the lights on different floors
 * 
 */
void light_init();


/**
 * @brief Clears all the lights on one floor
 * 
 * @param floor The floor to clear the lights on
 */
void light_clear_all_on_floor(uint8_t floor);

#endif