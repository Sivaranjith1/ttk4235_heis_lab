#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief The head of the linked list
*/
static FloorOrder* first_floor_order = NULL;

FloorOrder* create_floor_order(OrderDirection direction, uint8_t toFloor, OrderPriority priority, FloorOrder* prev){
  FloorOrder* newFloor = malloc(sizeof(FloorOrder));
  newFloor->direction = direction;
  newFloor->priority = priority;
  newFloor->toFloor = toFloor;
  if(!prev){
    
    newFloor->prev = NULL;
    newFloor->next = NULL;

    first_floor_order = newFloor;

  }else {
    FloorOrder* prevsNext = prev->next;
    newFloor->prev = prev;
    newFloor->next = prevsNext;
    prev->next = newFloor;
  }

  return newFloor;
}

FloorOrder* create_sorted_floor_order(OrderDirection direction, uint8_t toFloor, OrderPriority priority){
  if(priority > PRIORITY_OUTSIDE || direction > DIRECTION_DOWN) return NULL;

  FloorOrder* newFloor = malloc(sizeof(FloorOrder));
  newFloor->direction = direction;
  newFloor->priority = priority;
  newFloor->toFloor = toFloor;

  if(!first_floor_order){
    newFloor->prev = NULL;
    newFloor->next = NULL;

    first_floor_order = newFloor;
  } else {
    FloorOrder* next = first_floor_order;
    FloorOrder* prev = NULL;

    while(next){
      if(next->priority == newFloor->priority && next->direction == newFloor->direction && next->toFloor == newFloor->toFloor){
        free(newFloor);
        newFloor = NULL;
        return next;
      }
      else if(next->priority > newFloor->priority 
        || (next->priority == newFloor->priority && next->direction > newFloor->direction) 
        || (next->priority == newFloor->priority && next->direction == newFloor->direction && next->toFloor > newFloor->toFloor) 
        ){

        if(next == first_floor_order){
          first_floor_order = newFloor;
          newFloor->prev = NULL;
          next->prev = newFloor;
          newFloor->next = next;
          break;
        }

        if(next->prev){
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

    if(!next){
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

  if(order_to_delete->prev){
    order_to_delete->prev->next = order_to_delete->next;
  }

  if(order_to_delete->next){
    order_to_delete->next->prev = order_to_delete->prev;
  }

  // free(order_to_delete);
  order_to_delete = NULL;
}

void delete_floor_order_on_floor(uint8_t floor){
  FloorOrder* next = first_floor_order;

  uint8_t i = 0;
  while(++i < MAX_ITERATION){
    if(!next) return;

    if(next->toFloor == floor){
      FloorOrder* nexts_next = next->next;
      delete_floor_order(next);
      next = nexts_next;
    } else {
      next = next->next;
    }
  }
}

void clear_all_floor_order(){
  if(!first_floor_order) return;
  FloorOrder* currentElem = first_floor_order;
  FloorOrder* next = first_floor_order->next;

  uint8_t i = 0;
  while(++i < MAX_ITERATION){
    delete_floor_order(currentElem);
    currentElem = next;
    if(!currentElem){
      break;
    }
    next = currentElem->next;
  }
  
  first_floor_order = NULL;
}

void print_floor_order(FloorOrder* order_to_print){
  if(!order_to_print) return;
  printf("Priority %d, direction %d, toFloor %d\n", order_to_print->priority, order_to_print->direction, order_to_print->toFloor);
}

void print_all_floor_orders(){
  printf("Printing floor orders: \n");
  FloorOrder* next = first_floor_order;

  uint8_t i = 0;
  while(++i < MAX_ITERATION){
    if(!next) return;
    print_floor_order(next);
    if(i + 1 >= MAX_ITERATION){
      free(next->next);
      next->next = NULL;
    } else {
      next = next->next;
    }
  }
}