/*
  Jesus Minjares
  Master of Science in Computer Engineering
*/
/*
 *  ======== pwm_with_leds_threads.c ========
 */

/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/PWM.h>

/* Driver configuration */
#include "ti_drivers_config.h"
#include <unistd.h>
/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0){
    //PWM
    PWM_Handle handle = NULL;
    PWM_Params params;
    //variable
    uint16_t duty = 0, dutyInc = 100, period = 3000;

    //PWM Initialization
    PWM_Params_init(&params);
    //set PWM parameter
    params.dutyUnits = PWM_DUTY_US;
    params.dutyValue = duty;
    params.periodUnits = PWM_PERIOD_US;
    params.periodValue = period;
    params.idleLevel = PWM_IDLE_LOW;
    //open PWM
    handle = PWM_open(CONFIG_PWM_0, &params);
    //check for errors
    if(handle == NULL){
        while(1){}
    }
    //Start PWM
    PWM_start(handle);
    while(1){
        //set duty and check for error
        if(PWM_setDuty(handle, duty) == PWM_STATUS_ERROR){
            while(1){
                /*error setting the duty*/
            }
        }
        //increment duty
        duty = duty + dutyInc;
        //check for out of bound
        if(duty >= period){
            duty = 0;
        }
        usleep(100000); // .1 second delay
    }
}
void *secondThread(void *arg0){
    //PWM
    PWM_Handle handle = NULL;
    PWM_Params params;
    //variable
    uint16_t duty = 0, dutyInc = 100, period = 3000;

    //PWM Initialization
    PWM_Params_init(&params);
    //set PWM parameter
    params.dutyUnits = PWM_DUTY_US;
    params.dutyValue = duty;
    params.periodUnits = PWM_PERIOD_US;
    params.periodValue = period;
    params.idleLevel = PWM_IDLE_LOW;
    //open PWM
    handle = PWM_open(CONFIG_PWM_1, &params);
    //check for errors
    if(handle == NULL){
        while(1){}
    }
    //Start PWM
    PWM_start(handle);
    while(1){
        //set duty and check for error
        if(PWM_setDuty(handle, duty) == PWM_STATUS_ERROR){
            while(1){
                /*error setting the duty*/
            }
        }
        //increment duty
        duty = duty + dutyInc;
        //check for out of bound
        if(duty >= period){
            duty = 0;
        }
        usleep(100000); // .1 second delay
    }
}
