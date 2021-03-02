#include "timer.h"
#include <stdint.h>
#include <stdio.h>

static time_t timer_start;
static uint8_t timer_enabled = 0;

static void (*p_callback_function)(void) = NULL;

static inline void timer_run_callback_function();

void timer_start_timer(){
  timer_start = time(NULL);
  timer_enabled = 1;
}

void timer_reset_timer(){
  timer_start = time(NULL);
}

time_t* timer_check_timer_finished(){

  time_t current_time = time(NULL);

  if((uint8_t)(current_time - timer_start) > TIMER_WAIT_TIME && timer_enabled != 0){
    #if DEBUGGER
      printf("timer finished\n");
    #endif
    timer_run_callback_function();
  }

  return &timer_start;
}

void timer_set_callback_function(void (*callback_func)(void)){
  p_callback_function = callback_func;
}


/**
 * @brief Runs the callback function if it is not zero and disables the timer. Should be ran when the timer is finished
 * 
 */
static inline void timer_run_callback_function(){
  timer_enabled = 0;

  #if DEBUGGER
      printf("Calling timer callback_func\n");
      if(p_callback_function == NULL) printf("Callback func is NULL\n");
  #endif

  if(p_callback_function != NULL){
    (*p_callback_function)();
  }
}