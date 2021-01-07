/*
  Jesus Minjares
  Master of Science in Computer Engineering
*/
/*
 *  ======== gpiointerrupt.c ========
 */
#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>

/* Driver configuration */
#include "ti_drivers_config.h"
/* Library for sleep and usleep */
#include <unistd.h>

uint8_t count = 0;
/*GPIO Callback Function*/
void simpleFunction(uint_least8_t index);

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0){
    /*Initialize Driver*/
    GPIO_init();

    /* Configure the LED and button pins */
    GPIO_setConfig(CONFIG_GPIO_RED, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_BLUE, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_GREEN, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

    /*Interrupt Configuration*/
    GPIO_setConfig(CONFIG_BUTTON_LEFT, GPIO_CFG_IN_INT_FALLING |GPIO_CFG_IN_PU);
    /*Set callback function*/
    GPIO_setCallback(CONFIG_BUTTON_LEFT, simpleFunction);
    /*enable interrupt to button*/
    GPIO_enableInt(CONFIG_BUTTON_LEFT);

    return (NULL);
}
/*GPIO Callback Function*/
void simpleFunction(uint_least8_t index){
    switch(++count){ //increment count and check
        case 1:
            GPIO_write(CONFIG_GPIO_RED, CONFIG_GPIO_LED_ON);
            break;
        case 2:
            GPIO_write(CONFIG_GPIO_BLUE, CONFIG_GPIO_LED_ON);
            break;
        case 3:
            GPIO_write(CONFIG_GPIO_GREEN, CONFIG_GPIO_LED_ON);
            break;
        default:
           GPIO_write(CONFIG_GPIO_RED, CONFIG_GPIO_LED_OFF);
           GPIO_write(CONFIG_GPIO_BLUE, CONFIG_GPIO_LED_OFF);
           GPIO_write(CONFIG_GPIO_GREEN, CONFIG_GPIO_LED_OFF);
           count = 0;
    }
}
