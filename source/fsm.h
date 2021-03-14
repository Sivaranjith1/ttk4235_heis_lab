/**
 * @file 
 * @brief File for the finite state machine
*/

#ifndef FSM_H
#define FSM_H

/**
 * @brief The different states in the state machine
*/
typedef enum {
    INITIALIZE,
    DRIVE_UP,
    DRIVE_DOWN,
    WAITING,
    DOOR_OPEN
} STATE;

/**
 * @brief initialize the finite state machine
*/
void fsm_init();

/**
 * @brief gets the current state of the finite state machine
 * @returns STATE the state of the current state
*/
STATE get_fsm_state();

/**
 * @brief sets the current state to the new_state
 * @param new_state the new_state to set current state equal to
*/
void set_fsm_state(STATE new_state);

/**
 * @brief A blocking function running the finite state machine
*/
void fsm_run();

#endif