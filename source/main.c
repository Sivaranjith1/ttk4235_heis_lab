#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "fsm.h"

int main(){
    int error = hardware_init(); //initalize the hardware
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
    
    fsm_init(); //initalize the finite state machine

    fsm_run(); //this is a blocking function
    
    fprintf(stderr, "Unable to run finite state machine\n");

    return 0;
}
