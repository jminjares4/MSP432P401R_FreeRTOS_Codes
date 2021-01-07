/*
  Jesus Minjares
  Master of Science in Computer Engineering
*/
/*
 *  ======== timerWithGpio.c ========
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

/* Timer Callback */
void blinking(Timer_Handle handle){
    GPIO_toggle(CONFIG_GPIO_BLUE);
}
/* GPIO Callback */
void blinkingV2(uint_least8_t index){
    GPIO_toggle(CONFIG_GPIO_RED);
}
/*
 *  ======== main thread ========
 */
void *mainThread(void *arg0){
    //set GPIO configuration for BLUE LED
    GPIO_setConfig(CONFIG_GPIO_BLUE,GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW );

    //TIMERA0 variables
    Timer_Handle handle;
    Timer_Params params;

    //initialize parameter
    Timer_Params_init(&params);

    //set the attributes for the timerA0 params
    params.period = 10;
    params.periodUnits = Timer_PERIOD_HZ;
    params.timerCallback = blinking;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;

    //open timer instance
    handle = Timer_open(CONFIG_TIMER_A0, &params);
    //check for errors
    if(handle == NULL){
        while(1){}
    }
    //start timer and check flag
    if(Timer_start(handle) == Timer_STATUS_ERROR){
        while(1){}
    }
    return (NULL);
}
/*
 *  ======== second thread ========
 */
void *secondThread(void *arg0){
    //set GPIO configuration for RED LED
    GPIO_setConfig(CONFIG_GPIO_RED,GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW );
    //set GPIO interrupt as input and falling edge as pull up
    GPIO_setConfig(CONFIG_GPIO_BUTTON_1,GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);
    //set callback function
    GPIO_setCallback(CONFIG_GPIO_BUTTON_1, blinkingV2);
    //enable interrupt
    GPIO_enableInt(CONFIG_GPIO_BUTTON_1);
    return (NULL);
}
