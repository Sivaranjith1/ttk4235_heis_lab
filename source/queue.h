/**
 * @file queue.h
 * @author Ask & Sivaranjith
 * @brief 
 * @version 0.1
 * @date 2021-02-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef QUEUE_H
#define QUEUE_H
#include <stdint.h>
#include "hardware.h"

/**
 * @brief Priority for the Floor order
 * 
 */
typedef enum {
  Priority_Inside
} OrderPriority;

typedef struct FloorOrder FloorOrder;

/**
 * @brief Floor Order: A linked list of requests for floors
 * 
 */
struct FloorOrder {
  HardwareOrder direction;
  uint8_t toFloor;
  OrderPriority priority;

  FloorOrder* prev;
  FloorOrder* next;
};

/**
 * @brief Create a Floor Order object, will make next of prev to the new element
 * 
 * @param direction HardwareOrder the direction of the request
 * @param toFloor The requested floor
 * @param priority OrderPriority, which priority level it is
 * @param prev FloorOrder* Previous object in the linked list
 * @return FloorOrder* a new floor order in the linked list
 */
FloorOrder* create_floor_order(HardwareOrder direction, uint8_t toFloor, OrderPriority priority, FloorOrder* prev);

/**
 * @brief Get the first floor order object in the linked list
 * 
 * @return FloorOrder* the first element in the linked list
 */
FloorOrder* get_first_floor_order();

/**
 * @brief Delete the given floor order, and make the next previous' next, and prev next's prev
 * 
 * @param order_to_delete The Floor Order to delete
 */
void delete_floor_order(FloorOrder* order_to_delete);

/**
 * @brief Delete all floor orders in the linked list
 * 
 */
void clear_all_floor_order();

#endif