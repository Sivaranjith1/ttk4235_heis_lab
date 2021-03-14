#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief The head of the linked list
*/
static FloorOrder* first_floor_order = NULL;

FloorOrder* linked_list_create_floor_order(OrderDirection direction, uint8_t to_floor, OrderPriority priority, FloorOrder* prev){
  FloorOrder* new_floor = malloc(sizeof(FloorOrder)); //creates a new FloorOrder

  //set direction, priority and to_floor of the new element
  new_floor->direction = direction;
  new_floor->priority = priority;
  new_floor->to_floor = to_floor;

  //check if there is a element before this
  if(!prev){
    
    new_floor->prev = NULL;
    new_floor->next = NULL;

    //it is assumed that if there is nothing before this, this have to be the first
    first_floor_order = new_floor;

  }else {
    FloorOrder* prevsNext = prev->next; //prevsNext is the next of the previous object, this should be the news next
    new_floor->prev = prev; //set prev to previous FloorOrder
    new_floor->next = prevsNext; //set next to previous next
    prev->next = new_floor;
  }

  return new_floor;
}

FloorOrder* linked_list_create_sorted_floor_order(OrderDirection direction, uint8_t to_floor, OrderPriority priority){
  if(priority > PRIORITY_OUTSIDE || direction > DIRECTION_DOWN) return NULL; //return Null if invalid param is passes

  FloorOrder* new_floor = malloc(sizeof(FloorOrder)); //creates a new FloorOrder

  //set direction, priority and to_floor of the new element
  new_floor->direction = direction;
  new_floor->priority = priority;
  new_floor->to_floor = to_floor;

  //if there are not first_floor_order, this will be the first floor order
  if(!first_floor_order){
    new_floor->prev = NULL;
    new_floor->next = NULL;

    first_floor_order = new_floor;
  } else {
    FloorOrder* next = first_floor_order; //start of the linked list iteration
    FloorOrder* prev = NULL;

    while(next){ //while it is not null

      //check for duplicate
      if(next->priority == new_floor->priority && next->direction == new_floor->direction && next->to_floor == new_floor->to_floor){
        free(new_floor); //free the new object of a duplicate exits
        new_floor = NULL;
        return next; //return the duplicate of the new object
      }

      //sorting algorithm. Place before next if this has lower priority, lower direction and lower floor. Will create a sorted linked list
      //where priority is first, and then sorted by direction and then sorted by increasing floor 
      else if(next->priority > new_floor->priority 
        || (next->priority == new_floor->priority && next->direction > new_floor->direction) 
        || (next->priority == new_floor->priority && next->direction == new_floor->direction && next->to_floor > new_floor->to_floor) 
        ){

        //if the old object is the first element, the new object should be the first
        if(next == first_floor_order){
          first_floor_order = new_floor;
          new_floor->prev = NULL; //first element does not have 
          next->prev = new_floor;
          new_floor->next = next; //set the old object to next
          break;
        }

        if(next->prev){ //if a previus exist
          next->prev->next = new_floor; //set the prev pointer of the next to the new object
        }

        //make sure next and prevoius points to the right places
        new_floor->prev = next->prev;
        new_floor->next = next;
        next->prev = new_floor;

        break;
      }

      //iterate to the next element in the linked list
      prev = next;
      next = next->next;
    }

    if(!next){ //if there are no next element, the new element is the last of the linked_list
      prev->next = new_floor;
      new_floor->prev = prev;
    }
  }

  return new_floor;
}

FloorOrder* linked_list_get_first_floor_order(){
  return first_floor_order;
}

void linked_list_delete_floor_order(FloorOrder* order_to_delete){

  if(order_to_delete == first_floor_order){ //if the order_to_delete is the first, the second item is now the new first item
    first_floor_order = order_to_delete->next;
  }

  //fix prev and next for objects around the object to delete
  if(order_to_delete->prev){
    order_to_delete->prev->next = order_to_delete->next;
  }

  if(order_to_delete->next){
    order_to_delete->next->prev = order_to_delete->prev;
  }

  order_to_delete = NULL;
}

void linked_list_delete_floor_order_on_floor(uint8_t floor){
  FloorOrder* next = first_floor_order;

  uint8_t i = 0;
  while(++i < MAX_ITERATION){
    if(!next) return; //stop iteration if the whole linked list have been deleted

    if(next->to_floor == floor){
      FloorOrder* nexts_next = next->next; //the next of current list item
      linked_list_delete_floor_order(next); //delete the current
      next = nexts_next;
    } else {
      next = next->next; //iterates
    }
  }
}

void linked_list_clear_all_floor_order(){
  if(!first_floor_order) return; //if the linked list is empty there is nothing to delete
  FloorOrder* current_elem = first_floor_order;
  FloorOrder* next = first_floor_order->next;

  uint8_t i = 0;
  while(++i < MAX_ITERATION){
    linked_list_delete_floor_order(current_elem);
    current_elem = next;
    if(!current_elem){
      break;
    }
    next = current_elem->next; //next element
  }
  
  first_floor_order = NULL; //set first_floor_order to Null after it is freed
}

void linked_list_print_floor_order(FloorOrder* order_to_print){
  if(!order_to_print) return;
  printf("Priority %d, direction %d, to_floor %d\n", order_to_print->priority, order_to_print->direction, order_to_print->to_floor);
}

void linked_list_print_all_floor_orders(){
  printf("Printing floor orders: \n");
  FloorOrder* next = first_floor_order;

  uint8_t i = 0;
  while(++i < MAX_ITERATION){
    if(!next) return;
    linked_list_print_floor_order(next);
    if(i + 1 >= MAX_ITERATION){
      free(next->next); //this is a sanity check
      next->next = NULL;
    } else {
      next = next->next;
    }
  }
}