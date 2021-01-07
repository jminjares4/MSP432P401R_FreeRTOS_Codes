/*
  Jesus Minjares
  Master of Science in Computer Engineering
*/
/*
 *  ======== pwm_with_threads.c ========
 */

/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
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
    //variables
    uint16_t duty = 0, dutyInc = 100, period = 3000;

    //Initialize PWM parameter
    PWM_Params_init(&params);
    //set params
    params.dutyUnits = PWM_DUTY_US;
    params.dutyValue = duty;
    params.periodUnits = PWM_PERIOD_US;
    params.periodValue = period;
    params.idleLevel = PWM_IDLE_LOW;

    //open PWM instance
    handle = PWM_open(CONFIG_PWM_0, &params);
    //check for error
    if(handle == NULL){
        while(1){}
    }
    //start PWM
    PWM_start(handle);
    while(1){
        //set duty, and check for error
        if(PWM_setDuty(handle, duty) == PWM_STATUS_ERROR){
            while(1){
                /*error setting the duty*/
            }
        }
        //increment duty
        duty = duty + dutyInc;
        //update if out of bound
        if(duty >= period){
            duty = 0;
        }
        usleep(500000); //.5 seconds
    }
}
/*
 *  ======== secondThread ========
 */
void *secondThread(void *arg0){
    //set GPIO configuration
    GPIO_setConfig(CONFIG_GPIO_RED, GPIO_CFG_OUT_STD|GPIO_CFG_OUT_LOW);
    sleep(2); //wait 2 seconds
    //turn LED ON
    GPIO_write(CONFIG_GPIO_RED, CONFIG_GPIO_LED_ON);
    while(1){
        sleep(1); // 1 second delay
        GPIO_toggle(CONFIG_GPIO_RED); //toggle LED
    }
}
