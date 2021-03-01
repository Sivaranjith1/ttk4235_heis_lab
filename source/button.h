/**
 * @file button.h
 * @author Ask and Sivaranjith
 * @brief File for button controls and interactions
 * @version 0.1
 * @date 2021-02-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef BUTTON_H
#define BUTTON_H

#include "hardware.h"
#include "queue.h"
#include <time.h>
#include <stdint.h>

#define STOP_BUTTON_PRESSED 1
#define OBSTRUCTION_BUTTON_PRESSED 2
#define EXTERNAL_ORDER_EXISTS 3
#define INTERNAL_ORDER_EXISTS 4
/**
 * @brief Handles the stop button. When called it stops the elevator, clears the queue of all orders.
 * 
 */
inline void button_on_stop_button_press();


/**
 * @brief 
 * 
 */
inline void button_on_obstruction_press();

/**
 * @brief 
 * 
 * @param order_type 
 * @return OrderDirection
 */
OrderDirection button_find_order_direction(HardwareOrder order_type);

/**
 * @brief 
 * 
 * @param floor 
 * @param order_type 
 */
void button_on_external_order_button_press();


/**
 * @brief 
 * 
 * @param floor 
 */
void button_on_internal_order_button_press();


/**
 * @brief 
 * 
 */
uint8_t button_poll_floor();


/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t button_check_buttons_pressed();
#endif