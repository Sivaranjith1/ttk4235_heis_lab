#include "fsm.h"
#include "queue.h"
#include "floor.h"
#include "hardware.h"
#include "light.h"

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


static void fsm_on_floor_reached();
static void fsm_run_inner();

void fsm_init()
{
    current_state = INITIALIZE;
    current_under_state = ENTRY;  

    queue_add_element(FLOOR4, PRIORITY_INSIDE, DIRECTION_INSIDE);
    queue_add_element(FLOOR3, PRIORITY_OUTSIDE, DIRECTION_INSIDE);
    queue_add_element(FLOOR1, PRIORITY_INSIDE, DIRECTION_INSIDE);
    queue_add_element(FLOOR2, PRIORITY_OUTSIDE, DIRECTION_INSIDE);
    print_all_floor_orders();

    light_init();
}

STATE get_fsm_state()
{
    return current_state;
}

void set_fsm_state(STATE newState)
{
    current_under_state = EXIT;
    fsm_run_inner();

    current_state = newState;
    current_under_state = ENTRY;
    fsm_run_inner();

    current_under_state = NONE;
}

void fsm_run()
{
    while (1)
    {
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
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            break;
        }

        case EXIT: {
            break;
        }

        default:
        {   
            //find the next floor to move to
            FloorOrder* next_floor = queue_get_next_floor_order(get_last_visited_floor(), QUEUE_DIRECTION_STILL);
            next_floor = get_first_floor_order();
            if(next_floor != NULL){
                printf("Going to floor %d\n", next_floor->toFloor);
                go_to_floor(next_floor->toFloor);
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

        /* code */
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
            go_to_floor(next_floor->toFloor);
        }
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
            go_to_floor(next_floor->toFloor);
        }
        break;
    }
    }
}

/**
 * @brief Event when the elevator changes from driving to stopping
 * 
 */
static void fsm_on_floor_reached(){
    uint8_t current_floor = (uint8_t) get_last_visited_floor();
    queue_delete_orders_at_floor(current_floor);
    light_clear_all_on_floor(current_floor);
    
    set_fsm_state(WAITING);
}