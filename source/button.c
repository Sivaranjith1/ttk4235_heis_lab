#include "button.h"


inline void on_stop_button_press(){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    queue_delete_all();
}

inline void on_obstruction_press(time_t* current_time){
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

void on_external_order_button_press(int floor, HardwareOrder order_type){

}