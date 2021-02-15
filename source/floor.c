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

void setLastVisitedFloor(){
    if(last_visited_floor != 0){
        if(hardware_read_floor_sensor(last_visited_floor - 1)){
            last_visited_floor --;
        }
    } 
    
    if(last_visited_floor != NUM_FLOOR - 1){
        if(hardware_read_floor_sensor(last_visited_floor + 1)){
            last_visited_floor ++;
        }
    }
}

uint8_t getLastVisitedFloor(){
    return last_visited_floor;
}

void goToFloor(uint8_t floor_num){
    if(last_visited_floor == floor_num) {
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);    
        return;
    }

    //if the floor is above
    if(last_visited_floor < floor_num){
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
    } else if(last_visited_floor > floor_num){
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }
}