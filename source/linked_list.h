/**
 * @file linked_list.h
 * @author Ask & Sivaranjith
 * @brief Create. sort and delete from and the whole linked list
 * @version 0.1
 * @date 2021-02-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdint.h>

#define MAX_ITERATION 100

/**
 * @brief Priority for the Floor order
 * 
 */
typedef enum {
  PRIORITY_INSIDE,
  PRIORITY_OUTSIDE
} OrderPriority;

/**
 * @brief The direction for the Floor order, is is corrulated with the button press
 * 
 */
typedef enum {
  DIRECTION_INSIDE,
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
  uint8_t to_floor;
  OrderPriority priority;

  FloorOrder* prev;
  FloorOrder* next;
};

/**
 * @brief Create a Floor Order object, will make next of prev to the new element
 * 
 * @param direction OrderDirection the direction of the request
 * @param to_floor The requested floor
 * @param priority OrderPriority, which priority level it is
 * @param prev FloorOrder* Previous object in the linked list
 * @return FloorOrder* a new floor order in the linked list
 */
FloorOrder* linked_list_create_floor_order(OrderDirection direction, uint8_t to_floor, OrderPriority priority, FloorOrder* prev);

/**
 * @brief Create a Floor object and adds it in a sorted linked list, it assume the linked list is sorted before calling this function. The linked list will be sorted by priority, than direction, than floor
 * 
 * @param direction OrderDirection the direction of the request
 * @param to_floor The requested floor
 * @param priority OrderPriority, which priority level it is
 * @param prev FloorOrder* Previous object in the linked list
 * @return FloorOrder* a new floor order in the linked list
 */
FloorOrder* linked_list_create_sorted_floor_order(OrderDirection direction, uint8_t to_floor, OrderPriority priority);

/**
 * @brief Get the first floor order object in the linked list
 * 
 * @return FloorOrder* the first element in the linked list
 */
FloorOrder* linked_list_get_first_floor_order();

/**
 * @brief Delete the given floor order, and make the next previous' next, and prev next's prev
 * 
 * @param order_to_delete The Floor Order to delete
 */
void linked_list_delete_floor_order(FloorOrder* order_to_delete);

/**
 * @brief Deletes all the Floor orders at a floor
 * 
 * @param floor the floor to delete all orders from
 */
void linked_list_delete_floor_order_on_floor(uint8_t floor);

/**
 * @brief Delete all floor orders in the linked list
 * 
 */
void linked_list_clear_all_floor_order();

/**
 * @brief Print for a floor order
 * 
 * @param order_to_print The floor order to print
 */
void linked_list_print_floor_order(FloorOrder* order_to_print);

/**
 * @brief Print every Floor Object in the linked list
 * 
 */
void linked_list_print_all_floor_orders();

#endif