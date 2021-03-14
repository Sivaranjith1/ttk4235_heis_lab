#include "timer.h"
#include <stdint.h>
#include <stdio.h>

static time_t timer_start; //time when the timer started
static uint8_t timer_enabled = 0; //1 if timer is enabled

static void (*p_callback_function)(void) = NULL; //callback function when the timer is finished

static inline void timer_run_callback_function();

void timer_start_timer(){
  timer_start = time(NULL); //start the timer
  timer_enabled = 1; //enables the timer
}

void timer_reset_timer(){
  timer_start = time(NULL); //reset the timer
}

time_t* timer_check_timer_finished(){

  time_t current_time = time(NULL);

  //check if time has passed more than trigger and if the timer is enabled
  if((uint8_t)(current_time - timer_start) > TIMER_WAIT_TIME && timer_enabled != 0){
    #if DEBUGGER
      printf("timer finished\n");
    #endif
    //run the callback function
    timer_run_callback_function();
  }

  return &timer_start;
}

void timer_set_callback_function(void (*callback_func)(void)){
  //sets the function pointer
  p_callback_function = callback_func;
}


/**
 * @brief Runs the callback function if it is not zero and disables the timer. Should be ran when the timer is finished
 * 
 */
static inline void timer_run_callback_function(){
  //disables the timer after it is finished
  timer_enabled = 0;

  #if DEBUGGER
      printf("Calling timer callback_func\n");
      if(p_callback_function == NULL) printf("Callback func is NULL\n");
  #endif

  //if the callback function not null, call it
  if(p_callback_function != NULL){
    (*p_callback_function)();
  }
}