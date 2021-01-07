/*
  Jesus Minjares
  Master of Science in Computer Engineering
*/
/*
 *  ======== gpioBlinkLed.c ========
 */
#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>

/* Driver configuration */
#include "ti_drivers_config.h"

/* Library for sleep and usleep */
#include <unistd.h>

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    /* Configure the LED and button pins */
    GPIO_setConfig(CONFIG_GPIO_RED, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW); //set LED as OUTPUT and set at LOW

     while(1){
          GPIO_toggle(CONFIG_GPIO_RED); //toggle RED
          sleep(2); //sleep for 2 seconds
      }
}
/*
 *  ======== secondThread ========
 */
void *secondThread(void *arg0){
    GPIO_setConfig(CONFIG_GPIO_BLUE, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);  //set LED as OUTPUT and set at LOW
    while(1){
            GPIO_toggle(CONFIG_GPIO_BLUE); //toggle BLUE
            usleep(100000); //sleep for .10 seconds
        }
}
