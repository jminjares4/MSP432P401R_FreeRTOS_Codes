/*
  Jesus Minjares
  Master of Science in Computer Engineering
*/
/*
 *  ======== pwm_with_timer.c ========
 */

/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/PWM.h>
#include <ti/drivers/Timer.h>

/* Driver configuration */
#include "ti_drivers_config.h"

/*Macros*/
#define BLUE CONFIG_GPIO_LED_1
#define RED CONFIG_GPIO_LED_0

/*Timer A0 Callback*/
void timerA0Callback(Timer_Handle handle);

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0){
   //Initialize PWM Driver
   PWM_init();
   //create PWM variables
   PWM_Handle handle = NULL;
   PWM_Params params;
   //initialize params
   PWM_Params_init(&params);
   //SMCLK = 12Mhz/4 = 3Mhz
   //3Mhz/2K = 1500
   //15/1500 = 1%
   uint32_t period = 1500, duty = 0, inc = 15; //set period @ 2Khz, duty @ 0 and increment of 1%
   //Set Params
   params.dutyValue = 0;
   params.dutyUnits = PWM_DUTY_US;
   params.idleLevel = PWM_IDLE_LOW;
   params.periodValue = 1500;
   params.periodUnits = PWM_PERIOD_US;

   //Open PWM instance
   handle = PWM_open(CONFIG_PWM_0, &params);
   if(handle == NULL){//check for errors
       while(1){}
   }
   //start PWM
   PWM_start(handle);
   while(1){
       //set duty and check STATUS_ERROR
       if(PWM_setDuty(handle, duty) == PWM_STATUS_ERROR){
           PWM_setDuty(handle, duty); //reset duty
       }
       duty += inc; //increment by 1%
       //once duty reaches 50% reset
       if(duty >= (uint32_t)(period*.5)){
           duty = 0;
       }
       usleep(750000); //.75 second delay
   }
}
/*
 *  ======== secondThread ========
 */
void *secondThread(void *arg0){
    //Initialize Drivers
    GPIO_init();
    Timer_init();

    /*GPIO Configuration*/
    GPIO_setConfig(RED, GPIO_CFG_OUT_STD |GPIO_CFG_OUT_LOW);
    GPIO_setConfig(BLUE, GPIO_CFG_OUT_STD |GPIO_CFG_OUT_LOW);
    /*Timer variables*/
    Timer_Handle handle = NULL;
    Timer_Params params;

    /*Initialize Timer params @ 1hz or 1 second*/
    Timer_Params_init(&params);
    params.period = 1; //1Hz
    params.periodUnits = Timer_PERIOD_HZ;
    params.timerCallback = timerA0Callback;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    /*
    params.period = 3000000; //3M us for 1hz
    params.periodUnits = Timer_PERIOD_US;
    params.timerCallback = timerA0Callback;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    */
    //open Timer instance
    handle = Timer_open(CONFIG_TIMER_A0, &params);
    if(handle == NULL){ //check for error
        while(1){}
    }
    //start timer and check status
    if(Timer_start(handle) == Timer_STATUS_ERROR){
        while(1){}
    }
    while(1){
        GPIO_toggle(BLUE); //toggle BLUE LED
        sleep(30); //30 second delay
    }
}
/*Timer A0 Callback*/
void timerA0Callback(Timer_Handle handle){
    GPIO_toggle(RED); //toggle RED LED @ 1Hz
}
