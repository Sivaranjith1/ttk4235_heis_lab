#include "fsm.h"
#include "floor.h"
#include "hardware.h"

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

static void fsmInitState();
static void fsmWaitingState();
static void fsmDoorOpenState();
static void fsm_drive_up();
static void fsm_drive_down();

static void fsmRunInner();

void fsm_init()
{
    current_state = INITIALIZE;
    current_under_state = ENTRY;
}

STATE getFsmState()
{
    return current_state;
}

void setFsmState(STATE newState)
{
    current_under_state = EXIT;
    fsmRunInner();

    current_state = newState;
    current_under_state = ENTRY;
    fsmRunInner();

    current_under_state = NONE;
}

void fsmRun()
{
    while (1)
    {
        fsmRunInner();
    }
}

static void fsmRunInner()
{
    switch (current_state)
    {
    case INITIALIZE:
    {
        fsmInitState();
        /* code */
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
        fsmWaitingState();
        break;
    }

    case DOOR_OPEN:
        /* code */
        break;

    default:
    {
        fsm_button_controls();
        break;
    }
    }
}

/**
 * @brief The underlaying finite state machine within the state of Initialize
 * 
 */
static void fsmInitState()
{
    switch (current_under_state)
    {
    case ENTRY:
    {
        floor_init();
        setFsmState(WAITING);

        break;
    }

    case EXIT:
    {
        break;
    }

    default:
    {
        fsm_button_controls();
        break;
    }
    }
}

/**
 * @brief The underlaying finite state machine within the state of Waiting
 * 
 */
static void fsmWaitingState()
{
    switch (current_under_state)
    {
    case ENTRY:
    {
        //hardware_command_movement(HARDWARE_MOVEMENT_STOP);

        MOTOR_MOVEMENT direction = go_to_floor(floor_temp++);
        if(floor_temp >= 4) floor_temp = 0;
        switch (direction)
        {
        case MOVEMENT_UP:
            setFsmState(DRIVE_UP);
            break;
        case MOVEMENT_DOWN:
            setFsmState(DRIVE_DOWN);
            break;

        default:
            break;
        }
        break;
    }
    case EXIT:
    {
        break;
    }
    default:
    {
        fsm_button_controls();
        break;
    }
    }
}

/**
 * @brief The underlaying finite state machine within the state of Door open
 * 
 */
static void fsmDoorOpenState()
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
        fsm_button_controls();
        break;
    }
    }
}

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
        fsm_button_controls();
        if (set_last_visited_floor() == MOVEMENT_STILL)
        {
            setFsmState(WAITING);
        }
        break;
    }
    }
}

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
        fsm_button_controls();
        if (set_last_visited_floor() == MOVEMENT_STILL)
        {
            setFsmState(WAITING);
        }
        break;
    }
    }
}

static void fsm_button_controls(){
    uint8_t buttons_pressed = button_check_buttons_pressed();

    switch (buttons_pressed)
    {
    case STOP_BUTTON_PRESSED:
    {
        button_on_stop_button_press();
        break;
    }
    case OBSTRUCTION_BUTTON_PRESSED:
    {
        button_on_obstruction_press();
        break;
    }
    case EXTERNAL_ORDER_EXISTS:
    {
        button_on_external_order_button_press();
        break;
    }
    case INTERNAL_ORDER_EXISTS:
    {
        button_on_internal_order_button_press();
        break;
    }
    default:
    {
        break;
    }
    }
}