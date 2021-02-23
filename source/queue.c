#include "queue.h"

inline void queue_delete_element(FloorOrder *floor_order){
    delete_floor_order(floor_order);
}

inline void queue_clear(){
    clear_all_floor_order();
}

inline FloorOrder *queue_add_element(uint8_t to_floor, OrderPriority priority, OrderDirection direction)
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

    if(current_list_element == NULL){
        return NULL;
    }

    OrderPriority priority = current_list_element->priority;

    while(1)
    {
        if(current_direction == QUEUE_DIRECTION_UP){

            if((priority == current_list_element->priority) && (current_list_element->toFloor >= current_floor)){
                return current_list_element;
            }

            else if(priority != current_list_element->priority){
                return current_list_element->prev;
            }
        }

        else if(current_direction == QUEUE_DIRECTION_DOWN || current_direction== QUEUE_DIRECTION_STILL){

            if((priority != current_list_element->priority) || (current_list_element->toFloor >= current_floor)){
                return current_list_element->prev;
            }
        }

        if(current_list_element->next == NULL){
            return current_list_element;
        }

        current_list_element = current_list_element->next;
    }
}

inline void queue_delete_on_floor(uint8_t floor){
    delete_floor_order_on_floor(floor);
}