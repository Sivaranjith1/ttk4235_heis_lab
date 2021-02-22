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
#include "linked_list.h"
#include "fsm.h"
#include <time.h>


#define STOP_BUTON_PRESSED 1
#define OBSTRUCTION_BUTTON_PRESSED 2
/**
 * @brief Handles the stop button. When called it stops the elevator, clears the queue of all orders.
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
 * @return uint8_t 
 */
uint8_t check_buttons_pressed();
#endif