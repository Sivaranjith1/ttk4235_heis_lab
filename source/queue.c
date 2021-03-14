#include "queue.h"
#include <stdio.h>

void queue_delete_element(FloorOrder *floor_order){
  //delete the choosen FloorOrder
  linked_list_delete_floor_order(floor_order);
}

void queue_clear(){
  //delete all the floor orders
  linked_list_clear_all_floor_order();
}

FloorOrder *queue_add_element(uint8_t to_floor, OrderPriority priority, OrderDirection direction)
{
  //add a new to the linked list and sort it
  return linked_list_create_sorted_floor_order(direction, to_floor, priority);
}


FloorOrder *queue_get_next_floor_order(uint8_t current_floor, QueueDirection current_direction){
    FloorOrder* current_list_element = linked_list_get_first_floor_order(); //get the first element, will be used to iterate
    FloorOrder* closet_floor_element = linked_list_get_first_floor_order(); //get the first elemen, will be the output

    if(!current_list_element){
        return NULL; //if the linked list is empty, return NULL
    }

    if(current_direction == QUEUE_DIRECTION_STILL){
      //since the linked list is already sorted, the first item will be the next place to go to if the elevator is still
      return current_list_element;
    }

    uint8_t i = 0;
    while(++i < MAX_ITERATION)
    {
      if(current_direction == QUEUE_DIRECTION_DOWN){
        /*
        If the elevator is moving down, get the first down object, or any internal presses. If this is not found, get the furtherest with request upward
        */
        if((current_list_element->to_floor < current_floor && current_list_element->to_floor >= closet_floor_element->to_floor && current_list_element->direction != DIRECTION_UP)
         || closet_floor_element->to_floor >= current_floor 
         || (closet_floor_element->direction == DIRECTION_UP && current_list_element->direction != DIRECTION_UP && current_list_element->to_floor < current_floor)){
          closet_floor_element = current_list_element;
        }
      }
      else if(current_direction == QUEUE_DIRECTION_UP){
        /*
        If the elevator is moving up, get the first up object, or any internal presses. If this is not found, get the downward request that is the topmost
        */
        if((current_list_element->to_floor > current_floor && current_list_element->to_floor <= closet_floor_element->to_floor 
        && current_list_element->direction != DIRECTION_DOWN) || closet_floor_element->to_floor <= current_floor 
        || (closet_floor_element->direction == DIRECTION_DOWN && current_list_element->direction != DIRECTION_DOWN)
        || (closet_floor_element->direction == DIRECTION_DOWN && current_list_element->direction == DIRECTION_DOWN && current_list_element->to_floor >= closet_floor_element->to_floor )
        ){
          closet_floor_element = current_list_element;
        }
      }


      current_list_element = current_list_element->next; //iterate to next element
      if(!current_list_element){ //if this is the end return the choosen
        return closet_floor_element;
      }
    }

    return NULL; //if nothing is found, will never happen
}

void queue_delete_orders_at_floor(uint8_t floor){
  //delete all the orders at a given floor
  linked_list_delete_floor_order_on_floor(floor);
}

uint8_t queue_order_on_floor(uint8_t floor){
  FloorOrder* current_list_element = linked_list_get_first_floor_order();

  uint8_t i = 0;
  while(++i < MAX_ITERATION){
    if(!current_list_element) break;

    if(current_list_element->to_floor == floor) return 1; //if there is a element in the linked list with the floor return 1

    current_list_element = current_list_element->next;
  }

  return 0; //if nothing is found, there is no such element, hence 0 should be returned
}