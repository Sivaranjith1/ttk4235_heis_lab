#include "fsm.h"
#include "floor.h"
#include "hardware.h"

/**
 * @brief Under states such as entry exit for the states under
 * 
 */
typedef enum {
    ENTRY,
    EXIT,
    NONE
} UNDER_STATE;

static volatile STATE current_state;
static volatile UNDER_STATE current_under_state;

static void fsmInitState();
static void fsmWaitingState();
static void fsmDoorOpenState();
static void fsmRunInner();

void fsm_init(){
    current_state = INITIALIZE;
    current_under_state = ENTRY;
}

STATE getFsmState() {
    return current_state;
}

void setFsmState(STATE newState){
    current_under_state = EXIT;
    fsmRunInner();

    current_state = newState;
    current_under_state = ENTRY;
    fsmRunInner();

    current_under_state = NONE;
}

void fsmRun() {
    while(1) {
        fsmRunInner();
    }
}

static void fsmRunInner() {
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

            if(set_last_visited_floor() == MOVEMENT_STILL) setFsmState(WAITING);
            break;
        }

        case DRIVE_DOWN:
        {

            if(set_last_visited_floor() == MOVEMENT_STILL) setFsmState(WAITING);
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
            break;
        }
}

/**
 * @brief The underlaying finite state machine within the state of Initialize
 * 
 */
static void fsmInitState(){
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
        break;
    }
}


/**
 * @brief The underlaying finite state machine within the state of Waiting
 * 
 */
static void fsmWaitingState(){
    switch (current_under_state)
    {
    case ENTRY:
    {
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);

        MOTOR_MOVEMENT direction = go_to_floor(FLOOR1);
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
    
    default:
        break;
    }
}

/**
 * @brief The underlaying finite state machine within the state of Door open
 * 
 */
static void fsmDoorOpenState(){
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