#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief The head of the linked list
*/
static FloorOrder* first_floor_order = NULL;

FloorOrder* create_floor_order(OrderDirection direction, uint8_t to_floor, OrderPriority priority, FloorOrder* prev){
  FloorOrder* new_floor = malloc(sizeof(FloorOrder));
  new_floor->direction = direction;
  new_floor->priority = priority;
  new_floor->to_floor = to_floor;
  if(!prev){
    
    new_floor->prev = NULL;
    new_floor->next = NULL;

    first_floor_order = new_floor;

  }else {
    FloorOrder* prevsNext = prev->next;
    new_floor->prev = prev;
    new_floor->next = prevsNext;
    prev->next = new_floor;
  }

  return new_floor;
}

FloorOrder* create_sorted_floor_order(OrderDirection direction, uint8_t to_floor, OrderPriority priority){
  if(priority > PRIORITY_OUTSIDE || direction > DIRECTION_DOWN) return NULL;

  FloorOrder* new_floor = malloc(sizeof(FloorOrder));
  new_floor->direction = direction;
  new_floor->priority = priority;
  new_floor->to_floor = to_floor;

  if(!first_floor_order){
    new_floor->prev = NULL;
    new_floor->next = NULL;

    first_floor_order = new_floor;
  } else {
    FloorOrder* next = first_floor_order;
    FloorOrder* prev = NULL;

    while(next){
      if(next->priority == new_floor->priority && next->direction == new_floor->direction && next->to_floor == new_floor->to_floor){
        free(new_floor);
        new_floor = NULL;
        return next;
      }
      else if(next->priority > new_floor->priority 
        || (next->priority == new_floor->priority && next->direction > new_floor->direction) 
        || (next->priority == new_floor->priority && next->direction == new_floor->direction && next->to_floor > new_floor->to_floor) 
        ){

        if(next == first_floor_order){
          first_floor_order = new_floor;
          new_floor->prev = NULL;
          next->prev = new_floor;
          new_floor->next = next;
          break;
        }

        if(next->prev){
          next->prev->next = new_floor;
        }
        new_floor->prev = next->prev;
        new_floor->next = next;
        next->prev = new_floor;

        break;
      }
      prev = next;
      next = next->next;
    }

    if(!next){
      prev->next = new_floor;
      new_floor->prev = prev;
    }
  }

  return new_floor;
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

    if(next->to_floor == floor){
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
  FloorOrder* current_elem = first_floor_order;
  FloorOrder* next = first_floor_order->next;

  uint8_t i = 0;
  while(++i < MAX_ITERATION){
    delete_floor_order(current_elem);
    current_elem = next;
    if(!current_elem){
      break;
    }
    next = current_elem->next;
  }
  
  first_floor_order = NULL;
}

void print_floor_order(FloorOrder* order_to_print){
  if(!order_to_print) return;
  printf("Priority %d, direction %d, to_floor %d\n", order_to_print->priority, order_to_print->direction, order_to_print->to_floor);
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