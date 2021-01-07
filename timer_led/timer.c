/*
  Jesus Minjares
  Master of Science in Computer Engineering
*/
/*
 *  ======== timer.c ========
 */
#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>
/* Driver configuration */
#include "ti_drivers_config.h"
/* Library for sleep and usleep */
#include <unistd.h>
void timerA0Callback(Timer_Handle handle){
     GPIO_toggle(CONFIG_GPIO_RED); //toggle RED LED
}
void timerA1Callback(Timer_Handle handle){
    GPIO_toggle(CONFIG_GPIO_BLUE); //toggle BLUE LED
}
/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0){

    //set GPIO RED led as output and @ low
    GPIO_setConfig(CONFIG_GPIO_RED, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW );

    //create instance of Timer
    Timer_Handle timerA0Handle; //create an Timer_Handle
    Timer_Params timerA0Params; //create an Timer_Params

    //initialize Timer_Params, pass by refrence
    Timer_Params_init(&timerA0Params); //pass reference
    //set the timer parameters
    timerA0Params.period = 10; //10 hertz
    timerA0Params.periodUnits = Timer_PERIOD_HZ;
    timerA0Params.timerCallback = timerA0Callback; //once the timer triggers, it will go to it memory address
    timerA0Params.timerMode = Timer_CONTINUOUS_CALLBACK; //set timer as continous call back

    timerA0Handle = Timer_open(CONFIG_TIMER_A0, &timerA0Params); //open the instance of the timer

    //check if the handle is pointing to memory
    if(timerA0Handle == NULL){
        while(1){}
    }
    //check if there was an error with timer
    if (Timer_start(timerA0Handle) == Timer_STATUS_ERROR) {
           /* Failed to start timer */
           while (1) {}
    }
    return (NULL);
}
void *secondThread(void *arg0){

    //set GPIO BLUE led as output and @ low
    GPIO_setConfig(CONFIG_GPIO_BLUE, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW );

    //create instance of Timer A1
    Timer_Handle  timerA1Handle;//create Timer_Handle
    Timer_Params timerA1Params; //create Timer_Params

    //initialize Timer A1 parameter
    Timer_Params_init(&timerA1Params);
    //set the parameters
    timerA1Params.period = 1; // 1 hertz or 1 second
    timerA1Params.periodUnits = Timer_PERIOD_HZ; // set at hertz
    timerA1Params.timerCallback = timerA1Callback; //once the timer triggers, it will go to it memory address
    timerA1Params.timerMode = Timer_CONTINUOUS_CALLBACK; //set as continous call back

    //open the instance of timer A1
    timerA1Handle = Timer_open(CONFIG_TIMER_A1, &timerA1Params);

    //check if Timer_Handle is point to a memory address
    if(timerA1Handle == NULL){
        while(1){
        }
    }
    //check if there was an error with timer
    if (Timer_start(timerA1Handle) == Timer_STATUS_ERROR) {
           /* Failed to start timer */
           while (1) {}
    }
    return (NULL);
}
