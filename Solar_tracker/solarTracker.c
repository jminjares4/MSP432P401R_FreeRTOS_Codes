/*
 *  ======== solarTracker.c ========
 */

/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/ADC.h>
#include <ti/drivers/PWM.h>
#include <ti/display/Display.h>
/* Driver configuration */
#include "ti_drivers_config.h"

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0){
    ADC_init();
    PWM_init();
    Display_init();

    /*Display*/
    Display_Handle disHandle;
    Display_Params disParams;

    Display_Params_init(&disParams);
    disParams.lineClearMode = DISPLAY_CLEAR_BOTH;

    disHandle = Display_open(Display_Type_UART, &disParams);
    if(disHandle == NULL){
        while(1);
    }
    else{
        Display_printf(disHandle, 0,0,"Display has been successfully set.\n");
    }
    ADC_Handle adcHandle;
    ADC_Params adcParams;
    ADC_Params_init(&adcParams);
    adcHandle = ADC_open(SOLAR_PANEL,&adcParams);
    if(adcHandle == NULL){
        while(1);
    }
    else{
        Display_printf(disHandle, 0,0,"ADC has been successfully set.\n");
    }
    /*read adc*/
    uint16_t adcData;
//    ADC_convert(adcHandle, &adcData);
    /*PWM*/
    PWM_Handle pwmHandle;
    PWM_Params pwmParams;
    /*
     * SG90 operate 50hz
     * -90->5%
     * 0->7.5%
     * 90->10%
     * 3Mhz/50hz->60000 ticks
     * 5% * 60000 -> 3000
     * 7.5% * 60000 -> 4500
     * 10% * 60000 -> 6000
     *
     * */
    uint32_t duty = 3000;
    PWM_Params_init(&pwmParams);
    pwmParams.dutyUnits = PWM_DUTY_COUNTS;
    pwmParams.dutyValue = 3000;
    pwmParams.idleLevel = PWM_IDLE_LOW;
    pwmParams.periodUnits = PWM_PERIOD_COUNTS;
    pwmParams.periodValue = 60000;

    pwmHandle = PWM_open(X_AXIS,&pwmParams);
    if(pwmHandle == NULL){
        while(1);
    }
    PWM_start(pwmHandle);
    PWM_Handle pwmHandle2 = PWM_open(Y_AXIS, &pwmParams);
    if(pwmHandle2 == NULL){
        while(1);
    }


   while(1){
       if(PWM_setDuty(pwmHandle, duty) == PWM_STATUS_ERROR){
           PWM_setDuty(pwmHandle, duty);
       }
       duty+= 150;
       if(duty > 30000){
           duty = 3000;
       }
       usleep(18000);
   }




}
