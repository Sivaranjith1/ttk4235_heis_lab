/**
 * @file timer.h
 * @author Ask & Sivaranjith
 * @brief 
 * @version 0.1
 * @date 2021-03-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef TIMER_H
#define TIMER_H

#define TIMER_WAIT_TIME 1
#define DEBUGGER 0
#include <time.h>


/**
 * @brief Enables and start the timer count
 * 
 */
void timer_start_timer();

/**
 * @brief Resets the count of the timer back to zero
 * 
 */
void timer_reset_timer();

/**
 * @brief Check if the time passed is equal ti @c{TIMER_WAIT_TIME}. If this is true a callback function will be called. Should be called atleast once a second
 * @note Call atleast once a second
 * 
 * @return time_t* Returns a pointer to the starting time
 */
time_t* timer_check_timer_finished();

/**
 * @brief Sets the callback function that will be called when the timer is finished
 * 
 * @param callback_func The function to call when the timer is finished
 */
void timer_set_callback_function(void (*callback_func)(void));


#endif