/**
 * @file light.h
 * @author Ask & Sivaranjith
 * @brief 
 * @version 0.1
 * @date 2021-02-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef LIGHT.H
#define LIGHT.H


#include "hardware.h"
#include <stdint.h>

#define NUMBER_OF_LIGHTS{15}

/***/
typedef struct
{
    uint8_t floor_light_state[];
    uint8_t stop_light_state;
} Lights;

/**
 * @brief 
 * 
 */
void light_init();

/**
 * @brief Set the floor light object
 * 
 * @param floor 
 * @param order_type 
 * @param on 
 */
void set_floor_light(int floor, HardwareOrder order_type, uint8_t on);

/**
 * @brief Set the stop light object
 * 
 * @param on 
 */
void set_stop_light(uint8_t on);

#endif