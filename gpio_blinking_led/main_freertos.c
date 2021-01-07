/*
  Jesus Minjares
  Master of Science in Computer Engineering
*/
/*
 *  ======== main_freertos.c ========
 */
#include <stdint.h>

#ifdef __ICCARM__
#include <DLib_Threads.h>
#endif

/* POSIX Header files */
#include <pthread.h>

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>

/* Driver configuration */
#include <ti/drivers/Board.h>
#include <ti/drivers/GPIO.h>
extern void *mainThread(void *arg0);
extern void *secondThread(void *arg0); //use extern keyboard for function in another source file
/* Stack size in bytes */
#define THREADSTACKSIZE   1024

/*
 *  ======== main ========
 */
int main(void)
{
    pthread_t           thread, thread2; //pthread_t data type for the threads
    pthread_attr_t      attrs,attrs2; // attributes
    struct sched_param  priParam,priParam2; //scheduling paramaters for FreeRTOS
    int                 retc,retc2; //variable to hold pthread feedback

    /* initialize the system locks */
#ifdef __ICCARM__
    __iar_Initlocks();
#endif

    /* Call driver init functions */
    Board_init();
    GPIO_init();// set GPIO drivers
    /* Initialize the attributes structure with default values */
    pthread_attr_init(&attrs);

    /* Set priority, detach state, and stack size attributes */
    priParam.sched_priority = 1;
    retc = pthread_attr_setschedparam(&attrs, &priParam);
    retc |= pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_DETACHED);
    retc |= pthread_attr_setstacksize(&attrs, THREADSTACKSIZE);
    if (retc != 0) {
        /* failed to set attributes */
        while (1) {}
    }

    retc = pthread_create(&thread, &attrs, mainThread, NULL);
    if (retc != 0) {
        /* pthread_create() failed */
        while (1) {}
    }

    priParam2.sched_priority = 1; //set priority as 1 (maximum)
    retc2 = pthread_attr_setschedparam(&attrs2, &priParam2); //set the scheduling to the attribute
    retc2 |= pthread_attr_setdetachstate(&attrs2, PTHREAD_CREATE_DETACHED); //set pthread as detach, to be destory
    retc2 |= pthread_attr_setstacksize(&attrs2, THREADSTACKSIZE); //set the thread stack to the MACRO
    retc2 = pthread_create(&thread2, &attrs2, secondThread, NULL); //create second thread
    if (retc2 != 0) {
        /* pthread_create() failed */
        while (1) {}
    }

    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler();

    return (0);
}

//*****************************************************************************
//
//! \brief Application defined malloc failed hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationMallocFailedHook()
{
    /* Handle Memory Allocation Errors */
    while(1)
    {
    }
}

//*****************************************************************************
//
//! \brief Application defined stack overflow hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    //Handle FreeRTOS Stack Overflow
    while(1)
    {
    }
}
