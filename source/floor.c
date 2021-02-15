#include "floor.h"
#include "hardware.h"

static uint8_t last_visited_floor;
static uint8_t door_open;

void floor_init(){
    door_open = 0;
    hardware_command_movement(HARDWARE_MOVEMENT_UP);

    while (1)
    {
        for (uint8_t i = 0; i < NUM_FLOOR; i++)
        {
            if(hardware_read_floor_sensor(i)){
                last_visited_floor = i;
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                return;
            }
        }
        
    }
    

}