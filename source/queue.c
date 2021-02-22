#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief The head of the linked list
*/
static FloorOrder* first_floor_order = NULL;

FloorOrder* create_floor_order(OrderDirection direction, uint8_t toFloor, OrderPriority priority, FloorOrder* prev){
  FloorOrder* newFloor = malloc(sizeof(FloorOrder));
  newFloor->direction = direction;
  newFloor->priority = priority;
  newFloor->toFloor = toFloor;
  if(prev == NULL){
    
    newFloor->prev = NULL;
    newFloor->next = NULL;

    first_floor_order = newFloor;

  }else {
    FloorOrder* prevsNext = prev->next;
    newFloor->prev = prev;
    newFloor->next = prevsNext;
    prev->next = newFloor;
    // free(prevsNext);
  }

  return newFloor;
}

FloorOrder* create_sorted_floor_order(OrderDirection direction, uint8_t toFloor, OrderPriority priority){
  FloorOrder* newFloor = malloc(sizeof(FloorOrder));
  newFloor->direction = direction;
  newFloor->priority = priority;
  newFloor->toFloor = toFloor;

  if(first_floor_order == NULL){
    newFloor->prev = NULL;
    newFloor->next = NULL;

    first_floor_order = newFloor;
  } else {
    FloorOrder* next = first_floor_order;
    FloorOrder* prev = NULL;

    while(next != NULL){
      if(next->priority > newFloor->priority || (next->priority == newFloor->priority && next->direction > newFloor->direction) || (next->priority == newFloor->priority && next->direction == newFloor->direction && newFloor->direction == DIRECTION_UP && next->toFloor < newFloor->toFloor) || (next->priority == newFloor->priority && next->direction == newFloor->direction && newFloor->direction == DIRECTION_DOWN && next->toFloor > newFloor->toFloor)){

        if(next == first_floor_order){
          first_floor_order = newFloor;
          newFloor->prev = NULL;
          next->prev = newFloor;
          newFloor->next = next;
          break;
        }

        if(next->prev != NULL){
          next->prev->next = newFloor;
        }
        newFloor->prev = next->prev;
        newFloor->next = next;
        next->prev = newFloor;

        break;
      }
      prev = next;
      next = next->next;
    }

    if(next == NULL){
      prev->next = newFloor;
      newFloor->prev = prev;
    }
  }

  return newFloor;
}

FloorOrder* get_first_floor_order(){
  return first_floor_order;
}

void delete_floor_order(FloorOrder* order_to_delete){

  if(order_to_delete == first_floor_order){
    first_floor_order = order_to_delete->next;
  }

  if(order_to_delete->prev != NULL){
    order_to_delete->prev->next = order_to_delete->next;
  }

  if(order_to_delete->next != NULL){
    order_to_delete->next->prev = order_to_delete->prev;
  }

  free(order_to_delete);
  order_to_delete = NULL;
}

void clear_all_floor_order(){
  if(first_floor_order == NULL) return;
  FloorOrder* currentElem = first_floor_order;
  FloorOrder* next = first_floor_order->next;

  while(1){
    delete_floor_order(currentElem);
    currentElem = next;
    if(currentElem == NULL){
      break;
    }
    next = currentElem->next;
  }

  free(currentElem);
  free(next);

  first_floor_order = NULL;
}

void print_floor_order(FloorOrder* order_to_print){
  printf("Priority %d, direction %d, toFloor %d\n", order_to_print->priority, order_to_print->direction, order_to_print->toFloor);
}

void print_all_floor_orders(){
  FloorOrder* next = first_floor_order;
  while(next != NULL){
    print_floor_order(next);
    next = next->next;
  }

  free(next);
}