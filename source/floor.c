#include "floor.h"
#include "hardware.h"
#include <stdio.h>

static uint8_t last_visited_floor;
static uint8_t door_open;
static uint8_t requested_floor = NUM_FLOOR;
static MOTOR_MOVEMENT direction = MOVEMENT_STILL;

static void (*p_onFloorCallback)();

inline static void run_on_floor_callback_function();
static void move_until_floor_reached();
static void set_on_floor_callback_function(void (*callback_ptr)());

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
                run_on_floor_callback_function();
                return;
            }
        }
        
    }
}

MOTOR_MOVEMENT set_last_visited_floor(){
    
    if(last_visited_floor != 0 && hardware_read_floor_sensor(last_visited_floor - 1)){
        last_visited_floor --;
        run_on_floor_callback_function();
    }

    if(last_visited_floor != NUM_FLOOR - 1 && hardware_read_floor_sensor(last_visited_floor + 1)){
        last_visited_floor ++;
        run_on_floor_callback_function();
    }

    return direction;
}

ALL_FLOORS get_last_visited_floor(){
    return last_visited_floor;
}

MOTOR_MOVEMENT go_to_floor(ALL_FLOORS floor_num){
    requested_floor = floor_num;
    set_on_floor_callback_function(&move_until_floor_reached);
    p_onFloorCallback();
    return direction;
}

/**
 * @brief Set the On Floor Callback Function that is called each time a floor is passed
 * 
 * @param callback_ptr The function pointer to call
 */
static void set_on_floor_callback_function(void (*callback_ptr)()){
    p_onFloorCallback = callback_ptr;
}

/**
 * @brief Runs the callback function when reaching a floor
*/
inline static void run_on_floor_callback_function(){
    hardware_command_floor_indicator_on(last_visited_floor);
    if(p_onFloorCallback == NULL) return;

    (*p_onFloorCallback)();
}

/**
 * @brief move up if below @c{requested_floor} and move down if above. Will stop and change state when @c{last_visited_floor} is equal to @c{requested floor}.
 * @note This should be called everytime @c{last_visited_floor} is changed
 * 
 */
static void move_until_floor_reached(){
    if(requested_floor >= NUM_FLOOR) return;

    if(last_visited_floor == requested_floor) {
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);    
        direction = MOVEMENT_STILL;
        set_on_floor_callback_function(NULL);
        return;
    }

    //if the floor is above
    if(last_visited_floor < requested_floor){
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        direction = MOVEMENT_UP;
    } else if(last_visited_floor > requested_floor){
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        direction = MOVEMENT_DOWN;
    }
}