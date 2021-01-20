/*
 *  ======== pressureSensor.c ========
 */
/* DriverLib Includes */
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include <semaphore.h>

/* Driver Header files */
#include <ti/drivers/ADCBuf.h>

/* Display Header files */
#include <ti/display/Display.h>
#include <ti/display/DisplayUart.h>

/* Board Header file */
#include "ti_drivers_config.h"

#define ADCBUFFERSIZE    (5)

uint16_t sampleBufferOne[ADCBUFFERSIZE];
uint16_t sampleBufferTwo[ADCBUFFERSIZE];
uint32_t buffersCompletedCounter = 0;
uint16_t outputBuffer[ADCBUFFERSIZE];

/* Display Driver Handle */
Display_Handle displayHandle;

/* ADCBuf semaphore */
sem_t adcbufSem;

void adcBufCallback(ADCBuf_Handle handle, ADCBuf_Conversion *conversion,
    void *completedADCBuffer, uint32_t completedChannel) {
    uint_fast16_t i;
    uint16_t *completedBuffer = (uint16_t *) completedADCBuffer;

    for (i = 0; i < ADCBUFFERSIZE; i++) {
        outputBuffer[i] = completedBuffer[i];
    }
 
    /* post adcbuf semaphore */
    sem_post(&adcbufSem);
}

/*
 *  ======== pressureSensor ========
 */
void *pressureSensor(void *arg0)
{
    Display_Params displayParams;
    ADCBuf_Handle adcBuf;
    ADCBuf_Params adcBufParams;
    ADCBuf_Conversion continuousConversion;
    uint_fast16_t i;
    int32_t status;

    /* Call driver init functions */
    ADCBuf_init();
    Display_init();

    /* Configure & open Display driver */
    Display_Params_init(&displayParams);
    displayParams.lineClearMode = DISPLAY_CLEAR_BOTH;
    displayHandle = Display_open(Display_Type_UART, &displayParams);
    if (displayHandle == NULL) {
        Display_printf(displayHandle, 0, 0, "Error creating displayHandle\n");
        while (1);
    }
    
    status = sem_init(&adcbufSem, 0, 0);
    if (status != 0) {
        Display_printf(displayHandle, 0, 0, "Error creating adcbufSem\n");
        while(1);
    }

    Display_printf(displayHandle, 0, 0, "Starting the ADCBuf Multi-Channel example");

    /* Set up an ADCBuf peripheral in ADCBuf_RECURRENCE_MODE_CONTINUOUS */
    ADCBuf_Params_init(&adcBufParams);
    adcBufParams.callbackFxn = adcBufCallback;
    adcBufParams.recurrenceMode = ADCBuf_RECURRENCE_MODE_CONTINUOUS;
    adcBufParams.returnMode = ADCBuf_RETURN_MODE_CALLBACK;
    adcBufParams.samplingFrequency = 200;
    adcBuf = ADCBuf_open(CONFIG_ADCBUF0, &adcBufParams);

    /* Configure the conversion struct for two channels on same sequencer */
    continuousConversion.arg = NULL;
    continuousConversion.adcChannel = CONFIG_ADCBUF0CHANNEL_0;
    continuousConversion.sampleBuffer = sampleBufferOne;
    continuousConversion.sampleBufferTwo = sampleBufferTwo;
    continuousConversion.samplesRequestedCount = ADCBUFFERSIZE;

    if (!adcBuf){
        /* AdcBuf did not open correctly. */
        while(1);
    }
    /* Start converting sequencer 0. */
    if (ADCBuf_convert(adcBuf, &continuousConversion, 1) !=
        ADCBuf_STATUS_SUCCESS) {
        /* Did not start conversion process correctly. */
        while(1);
    }
    while(1) {
        sem_wait(&adcbufSem);
        Display_printf(displayHandle, 0, 0, "\r\nBuffer %u finished:",
            (unsigned int)buffersCompletedCounter++);

        for (i = 0; i < ADCBUFFERSIZE; i++) {
            Display_printf(displayHandle, 0, 0,
                "    %u,", outputBuffer[i]);
        }
        uint32_t adcAvg = 0;
        for(i = 0; i < ADCBUFFERSIZE; i++)
             adcAvg += outputBuffer[i];

        Display_printf(displayHandle, 0,0,"Average: %u\n", adcAvg/ADCBUFFERSIZE);
        usleep(100000);
    }
}
