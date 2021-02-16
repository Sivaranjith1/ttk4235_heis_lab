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

static STATE current_state;
static UNDER_STATE current_under_state;

void fsmInitState();
void fsmWaitingState();
void fsmDoorOpenState();

void fsm_init(){
    current_state = INITIALIZE;
    current_under_state = ENTRY;
}

STATE getFsmState() {
    return current_state;
}

void setFsmState(STATE newState){
    current_under_state = EXIT;
    fsmRun();

    current_state = newState;
    current_under_state = ENTRY;
    fsmRun();

    current_under_state = NONE;
}

void fsmRun() {
    while(1) {
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

            set_last_visited_floor();
            break;
        }

        case DRIVE_DOWN:
        {

            set_last_visited_floor();
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
}

/**
 * @brief The underlaying finite state machine within the state of Initialize
 * 
 */
void fsmInitState(){
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
void fsmWaitingState(){
    switch (current_under_state)
    {
    case ENTRY:
    {
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        goToFloor(0);
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
void fsmDoorOpenState(){
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