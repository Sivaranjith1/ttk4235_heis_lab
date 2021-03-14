#include "floor.h"
#include "hardware.h"
#include <stdio.h>

static uint8_t last_visited_floor; //the last sensor activated
static uint8_t requested_floor = NUM_FLOOR; //the desired floor
static MOTOR_MOVEMENT direction = MOVEMENT_STILL; //direction the elevator is moving
static FLOOR_POSITION_BETWEEN_FLOOR floor_position_to_last_visited_floor = FLOOR_POSITION_ABOVE; //if the elevator is above or below last visited floor

static void (*p_on_floor_callback)();

inline static void run_on_floor_callback_function();
static void move_until_floor_reached();
static void set_on_floor_callback_function(void (*callback_ptr)());

void floor_init(){
    p_on_floor_callback = NULL; //initalize the callback function to be null pointer

    //go up until a sensor is reached
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

MotorMovement floor_set_last_visited_floor(){
    
    //check if the sensor below the current floor triggers, decrement by 1 if that happens
    if(last_visited_floor != 0 && hardware_read_floor_sensor(last_visited_floor - 1)){
        last_visited_floor --;
        run_on_floor_callback_function(); //run the callback function pointer
    }

    //check if the sensor above the current floor trigger, increment by 1 if tha happens
    else if(last_visited_floor != NUM_FLOOR - 1 && hardware_read_floor_sensor(last_visited_floor + 1)){
        last_visited_floor ++;
        run_on_floor_callback_function();//run the callback function pointer
    }
    //sanity check. Check if any other sensor trigger and set the last_visited_floor equal to this
    else {
        for (uint8_t i = 0; i < NUM_FLOOR; i++)
        {
            if (hardware_read_floor_sensor(i))
            {
                last_visited_floor = i;
                break;
            }
        }
    }

    return direction;
}

AllFloors floor_get_last_visited_floor(){
    return last_visited_floor;
}

MotorMovement floor_go_to_floor(AllFloors floor_num){
    if(floor_num != requested_floor){
        printf("Going to floor %d\n", floor_num);
    }
        
    requested_floor = floor_num;

    //sets the callback function when a floor is reached
    set_on_floor_callback_function(&move_until_floor_reached);
    p_on_floor_callback();
    return direction;
}

uint8_t floor_at_valid_floor(){
    return hardware_read_floor_sensor(last_visited_floor);
}

/**
 * @brief Set the On Floor Callback Function that is called each time a floor is passed
 * 
 * @param callback_ptr The function pointer to call
 */
static void set_on_floor_callback_function(void (*callback_ptr)()){
    p_on_floor_callback = callback_ptr;
}

/**
 * @brief Runs the callback function when reaching a floor
*/
inline static void run_on_floor_callback_function(){
    hardware_command_floor_indicator_on(last_visited_floor);
    if(p_on_floor_callback == NULL) return;

    (*p_on_floor_callback)();
}

/**
 * @brief move up if below @c{requested_floor} and move down if above. Will stop and change state when @c{last_visited_floor} is equal to @c{requested floor}.
 * @note This should be called everytime @c{last_visited_floor} is changed
 * 
 */
static void move_until_floor_reached(){
    if(requested_floor >= NUM_FLOOR) return; //don't do anything if the requested floor is greater than the number of floors

    //if the requested floor is reached, stop the motor and clear the callback function pointer
    if(last_visited_floor == requested_floor && floor_at_valid_floor()) { 
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);    
        direction = MOVEMENT_STILL;
        set_on_floor_callback_function(NULL);
        return;
    }

    //if the requested_floor is above the current floor
    if (last_visited_floor < requested_floor || (last_visited_floor == requested_floor && floor_position_to_last_visited_floor == FLOOR_POSITION_BELOW))
    {
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        direction = MOVEMENT_UP;
    }
    //if the requested_floor is below the current floor
    else if (last_visited_floor > requested_floor || (last_visited_floor == requested_floor && floor_position_to_last_visited_floor == FLOOR_POSITION_ABOVE))
    {
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        direction = MOVEMENT_DOWN;
    }

    //if at a valid floor and moving up, set the position to be above the last visited floor
    if(floor_at_valid_floor() && direction == MOVEMENT_UP){
        floor_position_to_last_visited_floor = FLOOR_POSITION_ABOVE;
    }

    //if at a valid floor and moving down, set the position to be down the last visited floor
    else if (floor_at_valid_floor() && direction == MOVEMENT_DOWN)
    {
        floor_position_to_last_visited_floor = FLOOR_POSITION_BELOW;
    }
}