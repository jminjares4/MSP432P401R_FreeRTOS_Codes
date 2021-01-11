/*
  Jesus Minjares
  Master of Science in Computer Engineering
*/
/*
 *  ======== pwm_with_interrupt.c ========
 */

/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/PWM.h>
#include <ti/drivers/GPIO.h>

/* Driver configuration */
#include "ti_drivers_config.h"

/* Interrupt Callback Functions */
void redCallback(uint_least8_t index);
void greenCallback(uint_least8_t index);

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0){
    //PWM variables
    PWM_Handle handle = NULL;
    PWM_Params params;
    uint32_t duty = 0, inc = 300, period = 3000;

    //Initialize Driverse
    PWM_init();
    GPIO_init();
    /*GPIO Configuration*/
    //Set RED LED and BUTTON1
    GPIO_setConfig(CONFIG_GPIO_RED, GPIO_CFG_OUT_STD|GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_BUTTON1, GPIO_CFG_IN_PU| GPIO_CFG_IN_INT_FALLING);
    //Set GREEN LED and BUTTON2
    GPIO_setConfig(CONFIG_GPIO_GREEN, GPIO_CFG_OUT_STD|GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_BUTTON2, GPIO_CFG_IN_PU| GPIO_CFG_IN_INT_FALLING);
    //Set callback function to buttons
    GPIO_setCallback(CONFIG_GPIO_BUTTON1,  redCallback);
    GPIO_setCallback(CONFIG_GPIO_BUTTON2,  greenCallback);
    //enable interrupts
    GPIO_enableInt(CONFIG_GPIO_BUTTON1);
    GPIO_enableInt(CONFIG_GPIO_BUTTON2);


    /*PWM Configuration*/
    //initialize params
    PWM_Params_init(&params);
    //set values for params
    //SMLCK = 12Mhz/4 = 3Mhz, LED @ 1khz
    //3Mhz/1Khz = 3000 us
    params.dutyUnits = PWM_DUTY_US;
    params.dutyValue = duty;
    params.idleLevel = PWM_IDLE_LOW;
    params.periodUnits = PWM_PERIOD_US;
    params.periodValue = period;

    //open the instance of PWN
    handle = PWM_open(CONFIG_PWM_0,&params);
    if(handle == NULL){//check for error
        while(1){}
    }
    //start PWM
    PWM_start(handle);

    //infinite loop
    while(1){
        //set duty and check for error
        if(PWM_setDuty(handle, duty) == PWM_STATUS_ERROR){
            while(1){}
        }
        duty += inc; //increment by 10%
        if(duty >= period){ //check for out of bound
            duty = 0;
        }
        usleep(500000); //.5 second
    }
}
void redCallback(uint_least8_t index){
    GPIO_toggle(CONFIG_GPIO_RED); //toggle RED
}
void greenCallback(uint_least8_t index){
    GPIO_toggle(CONFIG_GPIO_GREEN); //toggle GREEN
}
