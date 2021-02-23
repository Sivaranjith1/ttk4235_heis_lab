/**
 * @file queue.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-02-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "linked_list.h"
#include <stdio.h>

typedef enum{
    QUEUE_DIRECTION_UP,
    QUEUE_DIRECTION_DOWN
} QueueDirection;

/**
 * @brief Add a new order to the queue
 * 
 * @param to_floor the requested floor
 * @param priority the priority of the button press. Lower number means that this will be higher prioritized
 * @param direction The direction the button press is. Inside, Up or Down
 * @return FloorOrder* Return the new FloorOrder element created
 */
inline FloorOrder *queue_add_element(uint8_t to_floor, OrderPriority priority, OrderDirection direction);

/**
 * @brief Delete all orders in the linked list
 * 
 */
inline void queue_clear();

/**
 * @brief Gets the next floor to go to given the direction and current floor
 * 
 * @param current_floor The last visited floor
 * @param current_direction The direction the elevator is traveling, Up or Down
 * @return FloorOrder* Floor Order object of the next target floor
 */
FloorOrder* queue_get_next_floor_order(uint8_t current_floor, QueueDirection current_direction);

/**
 * @brief Delete a given floor order object
 * 
 * @param floor_order The floor order object to delete
 */
inline void queue_delete_element(FloorOrder* floor_order);
#endif