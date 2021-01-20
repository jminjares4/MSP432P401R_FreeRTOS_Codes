/*
 *  ======== bluetooth.c ========
 */

/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
/* Driver Header files */
#include <ti/drivers/UART.h>
#include <ti/display/Display.h>

/* Driver configuration */
#include "ti_drivers_config.h"
/*
 *  ======== mainThread ========
 */
 UART_Handle uartHandle;
#define BLUETOOTH_BUFFER 512

char bluetooth_buffer[BLUETOOTH_BUFFER];


void bluetooth_char(char *buffer, char c, uint32_t *index);
void bluetooth_string(char *buffer, char *string, uint32_t *index);
void bluetooth_integer(char *buffer, int integer, uint32_t *index);
void bluetooth_float(char *buffer, float n, uint8_t decimal_places, uint32_t *index);

void bluetooth_sprintf(char *buffer, const char *fs, ...);
void bluetooth_send(double lat, double lon, uint16_t time, uint32_t adc);
void *bluetoothThread(void *arg0){
    /*Drivers*/
    Display_init();
    UART_init();

    /*Display*/
    Display_Handle displayHandle;
    Display_Params displayParams;
    /*initialize display*/
    Display_Params_init(&displayParams);
    displayParams.lineClearMode = DISPLAY_CLEAR_BOTH;
    /*open display instance*/
    displayHandle = Display_open(Display_Type_UART, &displayParams);
    if(displayHandle == NULL){
        Display_printf(displayHandle, 0,0, "ERROR!\n");
        while(1);
    }
    Display_printf(displayHandle, 0,0,"Display has been initialize...\n");



    UART_Params uartParams;
    UART_Params_init(&uartParams);
    uartParams.readMode = UART_MODE_BLOCKING;
    uartParams.writeMode = UART_MODE_BLOCKING;
    uartParams.readTimeout = UART_WAIT_FOREVER;
    uartParams.writeTimeout = UART_WAIT_FOREVER;
    uartParams.readCallback = NULL;
    uartParams.writeCallback = NULL;
    uartParams.readReturnMode = UART_RETURN_NEWLINE;
    uartParams.readDataMode = UART_DATA_TEXT;
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 9600;
    uartParams.dataLength = UART_LEN_8;
    uartParams.stopBits = UART_STOP_ONE;
    uartParams.parityType = UART_PAR_NONE;

    uartHandle = UART_open(BLUETOOTH,&uartParams);
    if(uartHandle == NULL){
        Display_printf(displayHandle, 0,0, "Error with UART...\n");
        while(1);
    }
    /*coordinate, time, adc*/
    uint16_t time = 1643;
    double lat = 31.123412;
    double lon = -106.1243;
    uint32_t adc = 13354;
    while(1){
        bluetooth_send(lat,lon,time,adc);
        sleep(5);
    }

}


void bluetooth_char(char *buffer, char c, uint32_t *index)
{
    buffer[*index] = c;
    *index = *index + 1;
}
void bluetooth_string(char *buffer, char *string, uint32_t *index)
{
    /*while the string is not the null character*/
    while(*string)
    {
        bluetooth_char(buffer, *string, index);
        string++;
    }
}
void bluetooth_integer(char *buffer, int integer, uint32_t *index)
{
    if(integer == 0)
    {
        bluetooth_char(buffer, '0', index);
    }

    if(integer < 0)
    {
        bluetooth_char(buffer, '-', index);
        integer = -integer;
    }

    char b[10];
    int digit = integer;

    uint8_t i = 0;
    while(digit)
    {
        b[i++] = digit % 10;
        digit /= 10;
    }

    while(i)
    {
        bluetooth_char(buffer, '0' + b[i-1], index);
        i--;
    }
}
void bluetooth_float(char *buffer, float n, uint8_t decimal_places, uint32_t *index)
{
    if (n < 0)
    {
        bluetooth_char(buffer, '-', index);
      n = -n;
    }

    uint8_t decimals = decimal_places;
    while (decimals >= 2)
    {
      // Quickly convert values expected to be E0 to E-4.
      n *= 100;
      decimals -= 2;
    }

    if (decimals)
    {
      n *= 10;
    }

    // Add rounding factor. Ensures carryover through entire value.
    n += 0.5;

    // Generate digits backwards and store in string.
    uint8_t buf[32];
    uint8_t i = 0;
    uint32_t a = (long)n;
    // Place decimal point, even if decimal places are zero.
    buf[decimal_places] = '.';

    while(a > 0)
    {
    // Skip decimal point location
    if (i == decimal_places)
    {
        i++;
    }

    // Get digit
    buf[i++] = (a % 10) + '0';
    a /= 10;
    }

    while (i < decimal_places)
    {
      // Fill in zeros to decimal point for (n < 1)
     buf[i++] = '0';
    }

    // Fill in leading zero, if needed.
    if (i == decimal_places)
    {
    i++;
    buf[i++] = '0';
    }

    // Print the generated string.
    for (; i > 0; i--)
    {
        bluetooth_char(buffer, buf[i-1], index);
    }
}
void bluetooth_sprintf(char *buffer, const char *fs, ...)
{
    va_list valist;
    va_start(valist, fs);
    int i;
    char *s;
    float f;
    uint32_t index = 0;

    while(*fs)
    {
        if(*fs != '%')
        {
            bluetooth_char(buffer, *fs, &index);
            fs++;
        }
        else
        {
            switch(*++fs)
            {
            case 'c':
                i = va_arg(valist, int);
                bluetooth_char(buffer, (char)i, &index);
                break;
            case 's':
                s = va_arg(valist, char*);
                bluetooth_string(buffer, s, &index);
                break;
            case 'i':
                i = va_arg(valist, int);
                bluetooth_integer(buffer, i, &index);
                break;
            case 'f':
                f = va_arg(valist, double);
                bluetooth_float(buffer, f, 3, &index);
                break;
            }

            ++fs;
        }
    }

    buffer[index] = '\0';
}
void bluetooth_send(double lat, double lon, uint16_t time, uint32_t adc)
{
    bluetooth_sprintf(bluetooth_buffer, "DATA:%f,%f,%i,%i\r\n",lat,lon,time,adc);

    UART_write(uartHandle, bluetooth_buffer, strlen(bluetooth_buffer));
}
