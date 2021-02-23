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
 * @brief 
 * 
 */
void queue_init();

inline FloorOrder *queue_add_element(uint8_t to_floor, OrderPriority priority, OrderDirection direction);

inline void queue_clear();

FloorOrder* queue_get_next_floor_order(uint8_t current_floor, QueueDirection current_direction);

inline void queue_delete_element(FloorOrder* floor_order);
#endif