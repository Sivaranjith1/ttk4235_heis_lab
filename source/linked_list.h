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

#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdint.h>
#include "hardware.h"

/**
 * @brief Priority for the Floor order
 * 
 */
typedef enum {
  PRIORITY_INSIDE,
  PRIORITY_UP,
} OrderPriority;

typedef enum {
  DIRECTION_UP,
  DIRECTION_DOWN
} OrderDirection;

typedef struct FloorOrder FloorOrder;

/**
 * @brief Floor Order: A linked list of requests for floors
 * 
 */
struct FloorOrder {
  OrderDirection direction;
  uint8_t toFloor;
  OrderPriority priority;

  FloorOrder* prev;
  FloorOrder* next;
};

/**
 * @brief Create a Floor Order object, will make next of prev to the new element
 * 
 * @param direction OrderDirection the direction of the request
 * @param toFloor The requested floor
 * @param priority OrderPriority, which priority level it is
 * @param prev FloorOrder* Previous object in the linked list
 * @return FloorOrder* a new floor order in the linked list
 */
FloorOrder* create_floor_order(OrderDirection direction, uint8_t toFloor, OrderPriority priority, FloorOrder* prev);

/**
 * @brief Create a Floor object and adds it in a sorted linked list, it assume the linked list is sorted before calling this function. The linked list will be sorted by priority, than direction, than floor
 * 
 * @param direction OrderDirection the direction of the request
 * @param toFloor The requested floor
 * @param priority OrderPriority, which priority level it is
 * @param prev FloorOrder* Previous object in the linked list
 * @return FloorOrder* a new floor order in the linked list
 */
FloorOrder* create_sorted_floor_order(OrderDirection direction, uint8_t toFloor, OrderPriority priority);

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

/**
 * @brief Print for a floor order
 * 
 * @param order_to_print The floor order to print
 */
void print_floor_order(FloorOrder* order_to_print);

/**
 * @brief Print every Floor Object in the linked list
 * 
 */
void print_all_floor_orders();

#endif