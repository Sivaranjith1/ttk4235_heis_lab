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
#include <time.h>
#include <stdint.h>

#define BUTTON_DEBUGGING 0

#define STOP_BUTTON_PRESSED 1
#define OBSTRUCTION_BUTTON_PRESSED 2
#define EXTERNAL_ORDER_EXISTS 3
#define INTERNAL_ORDER_EXISTS 4

#define INVALID_HARDWARE_ORDER 3
/**
 * @brief Handles the stop button. When called it stops the elevator, clears the queue of all orders.
 * 
 */
void button_on_stop_button_press();


/**
 * @brief When called will at the currently external pressed button to queue
 * @note Should be called when an external order button press is detected
 * 
 */
void button_on_external_order_button_press();


/**
 * @brief When called will at the currently internal pressed button to queue
 * @note Should be called when an internal order button press is detected
 * 
 */
void button_on_internal_order_button_press();


/**
 * @brief Poll all the buttons and return if a button type is pressed
 * 
 * @return uint8_t return the button type that is pressed. Can be 0 if notting is pressed or @c STOP_BUTTON_PRESSED, @c OBSTRUCTION_BUTTON_PRESSED, @c EXTERNAL_ORDER_EXISTS or @c INTERNAL_ORDER_EXISTS
 */
uint8_t button_check_buttons_pressed();
#endif