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


#ifndef BUTTON.H
#define BUTTON.H
#include "hardware.h"
#include "queue.h"
#include "fsm.h"

/**
 * @brief Handles the stop button. When called it stops the elevator, clears the queue of all orders and prevents new orders.
 * 
 */
void on_stop_button_press();


/**
 * @brief 
 * 
 */
void on_obstruction_press();


/**
 * @brief 
 * 
 * @param floor 
 * @param order_type 
 */
void on_external_order_button_press(int floor, HardwareOrder order_type);


/**
 * @brief 
 * 
 * @param floor 
 */
void on_internal_order_button_press(int floor);


/**
 * @brief 
 * 
 */
void button_init();


/**
 * @brief 
 * 
 */
void check_buttons_pressed();
#endif