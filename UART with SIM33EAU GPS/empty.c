/*
 *  ======== empty.c ========
 */

/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include "GPS.h"
// #include <ti/drivers/I2C.h>
// #include <ti/drivers/SPI.h>
 #include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>
#include <ti/display/Display.h>
#include <ti/drivers/Timer.h>
/* Driver configuration */
#include "ti_drivers_config.h"

/*
 *  ======== mainThread ========
 */
#define BUFFER 82
typedef struct SysTime{
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint16_t milli;
}SysTime;
char gpsData[82];
/*Data Structures*/
NMEA_GNRMC nmeaGnrmc;
UTC_TIME utcTime;
COORDINATE coordinate;
SysTime sysTime;

/*Functions*/
bool isSubstring(char *str, char *substr);
uint8_t str_to_uint8(char *str);
uint16_t str_to_uint16(char *str);
SysTime setSysTime(const UTC_TIME  *gpsUtcTime);

/*Callback*/
void timerCallback(Timer_Handle handle);
Display_Handle displayHandle;
void *gpsThread(void *arg0){
    GPIO_init();
    Display_init();
    UART_init();
    Timer_init();

    /*GPIO*/
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_write(CONFIG_GPIO_LED_0, 1);

    /*Display*/

    Display_Params displayParams;

    Display_Params_init(&displayParams);
    displayParams.lineClearMode = DISPLAY_CLEAR_BOTH;

    displayHandle = Display_open(Display_Type_UART, &displayParams);
    if(displayHandle == NULL){
        while(1);
    }
    else{
        Display_printf(displayHandle,0,0, "Display has been sucessfully setup!\n");
    }

    UART_Handle uartHandle;
    UART_Params uartParams;

    UART_Params_init(&uartParams);
    uartParams.readMode = UART_MODE_BLOCKING;
    uartParams.writeMode = UART_MODE_BLOCKING;
    uartParams.readTimeout = UART_WAIT_FOREVER;
    uartParams.writeTimeout = UART_WAIT_FOREVER;
    uartParams.readCallback = NULL;
    uartParams.writeCallback = NULL;
    uartParams.readReturnMode = UART_RETURN_NEWLINE;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.writeDataMode = UART_DATA_TEXT;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 9600;
    uartParams.dataLength = UART_LEN_8;
    uartParams.stopBits = UART_STOP_ONE;
    uartParams.parityType = UART_PAR_NONE;

    uartHandle = UART_open(SIM33EAU, &uartParams);
    if(uartHandle == NULL){
        while(1);
    }
    int index = 0;
    int strCount = 0;
    while(strCount < 10){
        char c;
        UART_read(uartHandle, &c, 1);
        gpsData[index++] = c;
        if( gpsData[index-1] == '\r'){
            if(isSubstring((char*)gpsData,"GNRMC")){
                strCount++;
                Display_printf(displayHandle, 0,0, "count: %d\n", strCount);
                Display_printf(displayHandle, 0,0,"%s\n", gpsData);
                nmeaGnrmc = setGnrmc(gpsData);
                utcTime = setTime(nmeaGnrmc.utc_time);
                coordinate = setCoordinates(&nmeaGnrmc);
                sysTime = setSysTime(&utcTime);
                Display_printf(displayHandle, 0,0, "/* NMEA_GNRMC */\n");
                Display_printf(displayHandle, 0,0, "NMEA: %s\n", nmeaGnrmc.name);
                Display_printf(displayHandle, 0,0, "UTC_TIME: %s\n", nmeaGnrmc.utc_time);
                Display_printf(displayHandle, 0,0, "Status: %s\n", nmeaGnrmc.status);
                Display_printf(displayHandle, 0,0,"Latitude: %s\tDirection: %s\n",nmeaGnrmc.latitude, nmeaGnrmc.latitudeDirection);
                Display_printf(displayHandle, 0,0,"Longitude: %s\tDirection: %s\n",nmeaGnrmc.longitude, nmeaGnrmc.longitudeDirection);
                Display_printf(displayHandle, 0,0, "Speed over ground: %s\n", nmeaGnrmc.speedOverGround);
                Display_printf(displayHandle, 0,0,"Course over ground: %s\n", nmeaGnrmc.courseOverGround);
                Display_printf(displayHandle, 0,0, "UTC_DATE: %s\n", nmeaGnrmc.utc_date);
                Display_printf(displayHandle,0,0,"Mode Indicator and Check Sum: %s\n", nmeaGnrmc.modeIndicatorAndcheckSum);
                Display_printf(displayHandle, 0,0, "/* UTC_TIME */\n");
                Display_printf(displayHandle,0,0,"UTC_TIME: %s:%s:%s:%s\n", utcTime.hour, utcTime.minute, utcTime.second, utcTime.milli);
                Display_printf(displayHandle, 0,0, "/* COORDINATE */\n");
                Display_printf(displayHandle, 0,0, "LAT,LON: %lf,%lf\n", coordinate.latitude, coordinate.longitude);
                Display_printf(displayHandle, 0,0, "/* SysTime */\n");
                Display_printf(displayHandle,0,0,"UTC_TIME: %u:%u:%u:%u\n", sysTime.hour, sysTime.minute, sysTime.second, sysTime.milli);
                sleep(5);
                Display_printf(displayHandle,0,0,"%c[2J%c[H",27,27);
            }
//            Display_printf(displayHandle, 0,0,"%s\n", gpsData);
            index = 0;
            memset(gpsData, 0, sizeof(gpsData));
        }
    }
//    UART_close(SIM33EAU);
    Display_printf(displayHandle, 0,0, "SIM33EAU has been close...\n");
    Timer_Handle timerHandle;
    Timer_Params timerParams;
    Timer_Params_init(&timerParams);
    timerParams.period = 10;
    timerParams.periodUnits = Timer_PERIOD_HZ;
    timerParams.timerCallback = timerCallback;
    timerParams.timerMode = Timer_CONTINUOUS_CALLBACK;

    timerHandle = Timer_open(CONFIG_TIMER_A0, &timerParams);
    if(timerHandle == NULL){
        while(1){}
    }
    //start timer and check flag
    int32_t status = Timer_start(timerHandle);
    if(status == Timer_STATUS_ERROR){
        while(1){}
    }
    while(1){
        Display_printf(displayHandle,0,0,"UTC_TIME: %u:%u:%u:%u\n", sysTime.hour, sysTime.minute, sysTime.second, sysTime.milli);
    };
}
SysTime setSysTime(const UTC_TIME  *gpsUtcTime){
    SysTime tempSysTime;
    tempSysTime.hour = str_to_uint8((char*)gpsUtcTime->hour);
    tempSysTime.minute = str_to_uint8((char*)gpsUtcTime->minute);
    tempSysTime.second = str_to_uint8((char *)gpsUtcTime->second);
    tempSysTime.milli = str_to_uint16((char*)gpsUtcTime->milli);
    return tempSysTime;
}
bool isSubstring(char *str, char *substr){
    int i;
    int len = strlen(str);
    int len2 = strlen(substr);
    for(i = 0; i < len; i++){
        if(str[i] == substr[0]){
            int j;
            int temp = i;
            for(j = 0; j < len2; j++){
                if(substr[j] == str[temp++])
                    continue;
                else{
                    break;
                }
            }
            if(temp - i == strlen(substr)){
                return true;
            }
        }
    }
    return false;
}
uint8_t str_to_uint8(char *str){
    uint8_t result;
    uint8_t puiss;
    result = 0;
    puiss = 1;
    while (('-' == (*str)) || ((*str) == '+')){
        if (*str == '-')
            puiss = puiss * -1;
        str++;
    }
    while ((*str >= '0') && (*str <= '9')){
        result = (result * 10) + ((*str) - '0');
        str++;
    }
    return (result * puiss);
}
uint16_t str_to_uint16(char *str){
    uint16_t result;
    uint16_t puiss;
    result = 0;
    puiss = 1;
    while (('-' == (*str)) || ((*str) == '+')){
        if (*str == '-')
            puiss = puiss * -1;
        str++;
    }
    while ((*str >= '0') && (*str <= '9')){
        result = (result * 10) + ((*str) - '0');
        str++;
    }
    return (result * puiss);
}
void timerCallback(Timer_Handle handle){
    /*every 100ms*/
    sysTime.milli+= 100; //incrmement every TA2 interval
    if(sysTime.milli >= 999){ sysTime.second++; sysTime.milli = 0;  }
    if(sysTime.second >= 59){ sysTime.minute++; sysTime.second = 0;
//        Display_printf(displayHandle,0,0,"UTC_TIME: %u:%u:%u:%u\n", sysTime.hour, sysTime.minute, sysTime.second, sysTime.milli);
        GPIO_toggle(CONFIG_GPIO_LED_0);
    }
    if(sysTime.minute >= 59){ sysTime.hour++;   sysTime.minute = 0; }
    if(sysTime.hour >= 23){   sysTime.hour = 0;}
   }
