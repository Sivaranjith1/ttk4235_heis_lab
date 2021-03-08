#include "queue.h"
#include <stdio.h>

void queue_delete_element(FloorOrder *floor_order){
    delete_floor_order(floor_order);
}

void queue_clear(){
    clear_all_floor_order();
}

FloorOrder *queue_add_element(uint8_t to_floor, OrderPriority priority, OrderDirection direction)
{
    return create_sorted_floor_order(direction, to_floor, priority);
}


/**
 * @brief Dealing with interior:
 * Start with start of queue
 * Iterate through and see if 
 * 
 * @param current_floor 
 * @param direction 
 * @return FloorOrder* 
 */
FloorOrder *queue_get_next_floor_order(uint8_t current_floor, QueueDirection current_direction){
    FloorOrder* current_list_element = get_first_floor_order();
    FloorOrder* closet_floor_element = get_first_floor_order();

    if(current_list_element == NULL){
        return NULL;
    }

    if(current_direction == QUEUE_DIRECTION_STILL){
      return current_list_element;
    }

    uint8_t i = 0;
    while(++i < MAX_ITERATION)
    {
      if(current_direction == QUEUE_DIRECTION_DOWN){
        if((current_list_element->toFloor <= current_floor && current_list_element->toFloor >= closet_floor_element->toFloor && current_list_element->direction != DIRECTION_UP) || closet_floor_element->toFloor >= current_floor){
          closet_floor_element = current_list_element;
        }
      }
      else if(current_direction == QUEUE_DIRECTION_UP){
        if((current_list_element->toFloor > current_floor && current_list_element->toFloor <= closet_floor_element->toFloor && current_list_element->direction != DIRECTION_DOWN) || closet_floor_element->toFloor <= current_floor){
          closet_floor_element = current_list_element;
        }
      }


      current_list_element = current_list_element->next;
      if(current_list_element == NULL){
        return closet_floor_element;
      }
    }
}

void queue_delete_orders_at_floor(uint8_t floor){
    delete_floor_order_on_floor(floor);
}

uint8_t queue_order_on_floor(uint8_t floor){
  FloorOrder* current_list_element = get_first_floor_order();

  uint8_t i = 0;
  while(++i < MAX_ITERATION){
    if(current_list_element == NULL) break;

    if(current_list_element->toFloor == floor) return 1;

    current_list_element = current_list_element->next;
  }

  return 0;
}