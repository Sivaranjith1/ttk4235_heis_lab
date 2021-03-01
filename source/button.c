#include "button.h"

OrderDirection find_order_direction(HardwareOrder order_type){
    OrderDirection return_direction;
    if(order_type == HARDWARE_ORDER_DOWN){
        return_direction = DIRECTION_DOWN;
    }
    else if (order_type == HARDWARE_ORDER_UP)
    {
        return_direction = DIRECTION_UP;
    }
    else{
        return_direction = DIRECTION_INSIDE; // should never happen
    }

    return return_direction;
}

inline void on_stop_button_press(){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    queue_clear();
}

inline void on_obstruction_press(time_t* current_time){
    *current_time = time(NULL);
}

uint8_t check_buttons_pressed(){
   int stop_pressed = hardware_read_stop_signal();
   int obstruction_pressed = hardware_read_obstruction_signal();
   int floor_order_exists;

   if(stop_pressed) {
        return STOP_BUTTON_PRESSED;
   }

   else if(obstruction_pressed){
        return OBSTRUCTION_BUTTON_PRESSED;
   }
   else
   {
       for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
               if(floor_order_exists = hardware_read_order(i, HARDWARE_ORDER_DOWN)) return EXTERNAL_ORDER_EXISTS;
               else if(floor_order_exists = hardware_read_order(i, HARDWARE_ORDER_UP)) return EXTERNAL_ORDER_EXISTS;
               else if(floor_order_exists = hardware_read_order(i, HARDWARE_ORDER_INSIDE)) return INTERNAL_ORDER_EXISTS;
       }
       return 0;
   }
}

void on_external_order_button_press(uint8_t floor, HardwareOrder order_type){
    OrderDirection direction = find_order_direction(order_type);
    queue_add_element(floor, PRIORITY_OUTSIDE, direction);
    hardware_command_order_light(floor, PRIORITY_OUTSIDE, 1);
}

void on_internal_order_button_press(uint8_t floor){
    queue_add_element(floor, PRIORITY_INSIDE, DIRECTION_INSIDE);
    hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 1);
}