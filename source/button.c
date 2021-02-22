#include "button.h"


void on_stop_button_press(){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    queue_delete_all();
}


/**
 * @brief 
 * 
 */
void on_obstruction_press(time_t* current_time){
    *current_time = time(NULL);
}

uint8_t check_buttons_pressed(){
   int stop_pressed = hardware_read_stop_signal();
   int obstruction_pressed = hardware_read_obstruction_signal();

   if(stop_pressed) {
        return STOP_BUTON_PRESSED;
   }

   else if(obstruction_pressed){
        return OBSTRUCTION_BUTTON_PRESSED;
   }
   else
   {
       return 0;
   }
}