#include "fsm.h"
#include "queue.h"
#include "floor.h"
#include "hardware.h"
#include "light.h"
#include "timer.h"
#include "button.h"

#include <stdio.h>

/**
 * @brief Under states such as entry exit for the states under
 * 
 */
typedef enum
{
    ENTRY,
    EXIT,
    NONE
} UNDER_STATE;

static volatile STATE current_state; //the current state 
static volatile UNDER_STATE current_under_state; //the under state such as entry, exit and none

static void fsm_init_state();
static void fsm_waiting_state();
static void fsm_door_open_state();
static void fsm_drive_up();
static void fsm_drive_down();

static void fsm_run_inner();

static void fsm_on_floor_reached();
static void fsm_on_door_timer();
static void fsm_button_control();

void fsm_init()
{
    //initialize the state and the under state
    current_state = INITIALIZE;
    current_under_state = ENTRY;  

    //initialize lights
    light_init();

    //set the callback function for the timer
    timer_set_callback_function(&fsm_on_door_timer);
}

STATE fsm_get_state()
{
    return current_state;
}

void fsm_set_state(STATE new_state)
{
    if(current_state == new_state) return;

    printf("Changing state to %d\n", new_state);

    //will first run exit on the old state
    current_under_state = EXIT;
    fsm_run_inner();

    //then run entry on the new state
    current_state = new_state;
    current_under_state = ENTRY;
    fsm_run_inner();

    //then set under state to NONE
    current_under_state = NONE;
}

void fsm_run()
{
    while (1)
    {
        //poll the timer
        timer_check_timer_finished();

        //run the state machine
        fsm_run_inner();
    }
}

/**
 * @brief The main state machine that runs in a while loop in @c{fsm_run}
 * 
 */
static void fsm_run_inner()
{
    switch (current_state)
    {
    case INITIALIZE:
    {
        fsm_init_state();
        break;
    }

    case DRIVE_UP:
    {
        fsm_drive_up();
        
        break;
    }

    case DRIVE_DOWN:
    {
        fsm_drive_down();
        break;
    }

    case WAITING:
    {
        fsm_waiting_state();
        break;
    }

    case DOOR_OPEN:
        fsm_door_open_state();
        break;

    default:
        break;
    }
}

/**
 * @brief The underlaying finite state machine within the state of Initialize
 * 
 */
static void fsm_init_state()
{
    switch (current_under_state)
    {
    case ENTRY:
    {
        floor_init();
        fsm_set_state(WAITING);

        break;
    }

    case EXIT:
    {
        break;
    }

    default:
        break;
    }
}

/**
 * @brief The underlaying finite state machine within the state of Waiting
 * 
 */
static void fsm_waiting_state()
{
    switch (current_under_state)
    {
        case ENTRY:
        {
            //stop the elevator when entering waiting state
            printf("\n floor order: \n");
            linked_list_print_all_floor_orders();
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);

            //if a valid floor is reaches, clear the lights and remove from the queue
            uint8_t current_floor = (uint8_t) floor_get_last_visited_floor();

            if(floor_at_valid_floor() && queue_order_on_floor(current_floor)){
                queue_delete_orders_at_floor(current_floor);
                light_clear_all_on_floor(current_floor);
                fsm_set_state(DOOR_OPEN);
            }


            break;
        }

        case EXIT: {
            break;
        }

        default:
        {   
            //find the next floor to move to
            FloorOrder* next_floor = queue_get_next_floor_order(floor_get_last_visited_floor(), QUEUE_DIRECTION_STILL);
            if(next_floor != NULL){
                floor_go_to_floor(next_floor->to_floor);

                //if the requested floor is the current floor, remove it and clear the lights
                if(floor_set_last_visited_floor() == MOVEMENT_STILL){
                    queue_delete_orders_at_floor(floor_get_last_visited_floor());
                    light_clear_all_on_floor(floor_get_last_visited_floor());
                    linked_list_print_all_floor_orders();
                }
            }

            //Check if the elevator is moving and set the right state
            switch (floor_set_last_visited_floor())
            {
            case MOVEMENT_UP:
                fsm_set_state(DRIVE_UP);
                break;
            case MOVEMENT_DOWN:
                fsm_set_state(DRIVE_DOWN);
                break;

            default:
                break;
            }

            //check for button presses
            fsm_button_control();
            break;
        }
    }
}

/**
 * @brief The underlaying finite state machine within the state of Door open
 * 
 */
static void fsm_door_open_state()
{
    switch (current_under_state)
    {
    case ENTRY:
    {
        //open the door and start the timer when entering door open state
        hardware_command_door_open(1);
        timer_start_timer();
        break;
    }

    case EXIT:
    {
        //close the door when exiting the door open state
        hardware_command_door_open(0);
        break;
    }

    default:
    {
        fsm_button_control(); //check for button presses
        break;
    }
    }
}

/**
 * @brief State for driving up
 * 
 */
static void fsm_drive_up()
{
    switch (current_under_state)
    {
    case ENTRY:
    {

        /* code */
        break;
    }

    case EXIT:
    {
        break;
    }

    default:
    {
        //requested floor was reached if the elevator stops moving
        if (floor_set_last_visited_floor() == MOVEMENT_STILL)
        {
            fsm_on_floor_reached();
            break;
        }

        //check if there is a new floor to move to in the path of the traveling direction
        FloorOrder* next_floor = queue_get_next_floor_order(floor_get_last_visited_floor(), QUEUE_DIRECTION_UP);
        if(next_floor != NULL){
            floor_go_to_floor(next_floor->to_floor);
        }

        fsm_button_control(); //check for button press
        break;
    }
    }
}

/**
 * @brief State machine for driving down
 * 
 */
static void fsm_drive_down(){
    switch (current_under_state)
    {
    case ENTRY:
    {

        /* code */
        break;
    }

    case EXIT:
    {
        break;
    }

    default:
    {
        //requested floor was reached if the elevator stops moving
        if (floor_set_last_visited_floor() == MOVEMENT_STILL)
        {
            fsm_on_floor_reached();
            break;
        }

        //check if there is a new floor to move to in the path of the traveling direction
        FloorOrder* next_floor = queue_get_next_floor_order(floor_get_last_visited_floor(), QUEUE_DIRECTION_DOWN);
        if(next_floor != NULL){
            floor_go_to_floor(next_floor->to_floor);
        }
        fsm_button_control(); //check for button press
        break;
    }
    }
}

/**
 * @brief Event when the elevator changes from driving to stopping
 * 
 */
static void fsm_on_floor_reached(){
    fsm_set_state(WAITING);
}


/**
 * @brief Callback function for when the door timer is finished
 * 
 */
static void fsm_on_door_timer(){

    //when the timer is reached and the current state is door_open, change to waiting
    if(current_state == DOOR_OPEN){
        fsm_set_state(WAITING);
    }
}

/**
 * @brief Function for controling button presses
 * 
 */
static void fsm_button_control(){
    uint8_t buttons_pressed = button_check_buttons_pressed();

    switch (buttons_pressed)
    {
        case OBSTRUCTION_BUTTON_PRESSED:
        {
            //reset timer if obstruction
            timer_reset_timer();
            break;
        }
        case STOP_BUTTON_PRESSED:
        {
            //when stop button is pressed clear all lights and reset the timer
            button_on_stop_button_press();
            light_init();
            hardware_command_stop_light(1);
            timer_reset_timer();

            //open the door if at a valid floor
            if(floor_at_valid_floor()){
                fsm_set_state(DOOR_OPEN);
            } else {
                fsm_set_state(WAITING);
            }
            break;
        }
        case INTERNAL_ORDER_EXISTS:
        {
            button_on_internal_order_button_press();
            linked_list_print_all_floor_orders();
            break;
        }

        case EXTERNAL_ORDER_EXISTS:
        {
            button_on_external_order_button_press();
            linked_list_print_all_floor_orders();
            break;
        }
        default:
            break;
    }

    //clear the stop button light if stop button is not pressed anymore
    if(buttons_pressed != STOP_BUTTON_PRESSED) hardware_command_stop_light(0);
}