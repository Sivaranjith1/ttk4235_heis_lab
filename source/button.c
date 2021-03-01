#include "button.h"

OrderDirection button_find_order_direction(HardwareOrder order_type){
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

inline void button_on_stop_button_press(){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    queue_clear();
}

inline void button_on_obstruction_press(time_t* current_time){
    *current_time = time(NULL);
}

uint8_t button_check_buttons_pressed(){
   int stop_pressed = hardware_read_stop_signal();
   int obstruction_pressed = hardware_read_obstruction_signal();


   if(stop_pressed) {
        return STOP_BUTTON_PRESSED;
   }

   else if(obstruction_pressed){
        return OBSTRUCTION_BUTTON_PRESSED;
   }
   else
   {
       for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
               if(hardware_read_order(i, HARDWARE_ORDER_DOWN)) return EXTERNAL_ORDER_EXISTS;
               else if(hardware_read_order(i, HARDWARE_ORDER_UP)) return EXTERNAL_ORDER_EXISTS;
               else if(hardware_read_order(i, HARDWARE_ORDER_INSIDE)) return INTERNAL_ORDER_EXISTS;
       }
       return 0;
   }
}

void button_on_external_order_button_press(uint8_t floor, HardwareOrder order_type){
    OrderDirection direction = button_find_order_direction(order_type);
    queue_add_element(floor, PRIORITY_OUTSIDE, direction);
    hardware_command_order_light(floor, PRIORITY_OUTSIDE, 1);
}

void button_on_internal_order_button_press(uint8_t floor){
    queue_add_element(floor, PRIORITY_INSIDE, DIRECTION_INSIDE);
    hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 1);
}

int button_poll_floor(){
    
}