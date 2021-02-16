#include "floor.h"
#include "hardware.h"
#include "fsm.h"
#include <stdio.h>

static uint8_t last_visited_floor;
static uint8_t door_open;
static uint8_t requested_floor = NUM_FLOOR;

static void (*p_onFloorCallback)();

inline static void runCallbackFunction();
static void move_until_floor_reached();

void floor_init(){
    door_open = 0;
    p_onFloorCallback = NULL;

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

void set_last_visited_floor(){
    
    if(last_visited_floor != 0 && hardware_read_floor_sensor(last_visited_floor - 1)){
        last_visited_floor --;
        runCallbackFunction();
    }

    if(last_visited_floor != NUM_FLOOR - 1 && hardware_read_floor_sensor(last_visited_floor + 1)){
        last_visited_floor ++;
        runCallbackFunction();
    }
}

uint8_t getLastVisitedFloor(){
    return last_visited_floor;
}

void goToFloor(uint8_t floor_num){
    requested_floor = floor_num;
    setOnFloorCallbackFunction(&move_until_floor_reached);
    p_onFloorCallback();
}

void setOnFloorCallbackFunction(void (*callback_ptr)()){
    p_onFloorCallback = callback_ptr;
}

inline static void runCallbackFunction(){
    if(p_onFloorCallback == NULL) return;

    (*p_onFloorCallback)();
}

static void move_until_floor_reached(){
    if(requested_floor >= NUM_FLOOR) return;

    if(last_visited_floor == requested_floor) {
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);    
        setFsmState(WAITING);
        setOnFloorCallbackFunction(NULL);
        return;
    }

    //if the floor is above
    if(last_visited_floor < requested_floor){
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        setFsmState(DRIVE_UP);
    } else if(last_visited_floor > requested_floor){
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        setFsmState(DRIVE_DOWN);
    }
}