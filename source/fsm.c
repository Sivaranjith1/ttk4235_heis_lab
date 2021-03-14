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

static volatile STATE current_state;
static volatile UNDER_STATE current_under_state;

static uint8_t floor_temp = 0; //need to remove

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
    current_state = INITIALIZE;
    current_under_state = ENTRY;  

    light_init();
    timer_set_callback_function(&fsm_on_door_timer);
}

STATE get_fsm_state()
{
    return current_state;
}

void set_fsm_state(STATE new_state)
{
    if(current_state == new_state) return;

    printf("Changing state to %d\n", new_state);
    current_under_state = EXIT;
    fsm_run_inner();

    current_state = new_state;
    current_under_state = ENTRY;
    fsm_run_inner();

    current_under_state = NONE;
}

void fsm_run()
{
    while (1)
    {
        timer_check_timer_finished();

        fsm_run_inner();
    }
}

/**
 * @brief The main state machine that runs in a while loop in $c{fsm_run}
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
        set_fsm_state(WAITING);

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
            printf("\n floor order: \n");
            print_all_floor_orders();
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);

            uint8_t current_floor = (uint8_t) get_last_visited_floor();

            if(floor_at_valid_floor() && queue_order_on_floor(current_floor)){
                queue_delete_orders_at_floor(current_floor);
                light_clear_all_on_floor(current_floor);
                set_fsm_state(DOOR_OPEN);
            }


            break;
        }

        case EXIT: {
            break;
        }

        default:
        {   
            //find the next floor to move to
            FloorOrder* next_floor = queue_get_next_floor_order(get_last_visited_floor(), QUEUE_DIRECTION_STILL);
            if(next_floor != NULL){
                go_to_floor(next_floor->to_floor);

                if(set_last_visited_floor() == MOVEMENT_STILL){
                    queue_delete_orders_at_floor(get_last_visited_floor());
                    light_clear_all_on_floor(get_last_visited_floor());
                    print_all_floor_orders();
                }
            }

            //Check if the elevator is moving 
            switch (set_last_visited_floor())
            {
            case MOVEMENT_UP:
                set_fsm_state(DRIVE_UP);
                break;
            case MOVEMENT_DOWN:
                set_fsm_state(DRIVE_DOWN);
                break;

            default:
                break;
            }

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

        hardware_command_door_open(1);
        timer_start_timer();
        break;
    }

    case EXIT:
    {
        hardware_command_door_open(0);
        break;
    }

    default:
    {
        fsm_button_control();
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
        if (set_last_visited_floor() == MOVEMENT_STILL)
        {
            fsm_on_floor_reached();
            break;
        }

        FloorOrder* next_floor = queue_get_next_floor_order(get_last_visited_floor(), QUEUE_DIRECTION_UP);
        if(next_floor != NULL){
            go_to_floor(next_floor->to_floor);
        }
        fsm_button_control();
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
        if (set_last_visited_floor() == MOVEMENT_STILL)
        {
            fsm_on_floor_reached();
            break;
        }

        FloorOrder* next_floor = queue_get_next_floor_order(get_last_visited_floor(), QUEUE_DIRECTION_DOWN);
        if(next_floor != NULL){
            go_to_floor(next_floor->to_floor);
        }
        fsm_button_control();
        break;
    }
    }
}

/**
 * @brief Event when the elevator changes from driving to stopping
 * 
 */
static void fsm_on_floor_reached(){
    set_fsm_state(WAITING);
}


/**
 * @brief Callback function for when the door timer is finished
 * 
 */
static void fsm_on_door_timer(){
    if(current_state == DOOR_OPEN){
        set_fsm_state(WAITING);
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
            timer_reset_timer();
            break;
        }
        case STOP_BUTTON_PRESSED:
        {
            button_on_stop_button_press();
            light_init();
            hardware_command_stop_light(1);
            timer_reset_timer();

            if(floor_at_valid_floor()){
                set_fsm_state(DOOR_OPEN);
            } else {
                set_fsm_state(WAITING);
            }
            break;
        }
        case INTERNAL_ORDER_EXISTS:
        {
            printf("Internal\n");
            button_on_internal_order_button_press();
            print_all_floor_orders();
            break;
        }

        case EXTERNAL_ORDER_EXISTS:
        {
            button_on_external_order_button_press();
            print_all_floor_orders();
            break;
        }
        default:
            break;
    }

    if(buttons_pressed != STOP_BUTTON_PRESSED) hardware_command_stop_light(0);
}