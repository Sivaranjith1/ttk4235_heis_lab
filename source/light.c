#include "light.h"
#include "hardware.h"

static HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
};

void light_init(){
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, 0);
        }
    }
}


void light_clear_all_on_floor(uint8_t floor){
    for(int i = 0; i < 3; i++){
        HardwareOrder type = order_types[i];
        hardware_command_order_light(floor, type, 0);
    }
}