/*
 *  ======== empty.c ========
 */

/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
/* Driver Header files */
#include <ti/drivers/GPIO.h>
// #include <ti/drivers/I2C.h>
// #include <ti/drivers/SPI.h>
 #include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>
#include <ti/display/Display.h>

/* Driver configuration */
#include "ti_drivers_config.h"

/*
 *  ======== mainThread ========
 */
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
#define BUFFER 82
char gpsData[82];
void *gpsThread(void *arg0){
//    char *gpsData = malloc(sizeof(char)*BUFFER);
    GPIO_init();
    Display_init();
    UART_init();

    /*GPIO*/
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_write(CONFIG_GPIO_LED_0, 1);

    /*Display*/
    Display_Handle displayHandle;
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
    uartParams.readTimeout = 1000;
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
    while(1){
        char c;
        UART_read(uartHandle, &c, 1);
        gpsData[index++] = c;
        if( gpsData[index-1] == '\r'){
            if(isSubstring((char*)gpsData,"GNRMC")){
                Display_printf(displayHandle, 0,0,"%s\n", gpsData);
            }
            index = 0;
            memset(gpsData, 0, sizeof(gpsData));
        }

    }
}
