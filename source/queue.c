#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

static FloorOrder* first_floor_order = NULL;

FloorOrder* create_floor_order(HardwareOrder direction, uint8_t toFloor, OrderPriority priority, FloorOrder* prev){
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

FloorOrder* get_first_floor_order(){
  return first_floor_order;
}

void delete_floor_order(FloorOrder* order_to_delete){

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
}