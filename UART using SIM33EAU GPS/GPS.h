/**
    Author: Jesus Minjares 
    Last Modified:  11/04/2020
    This library is design to organize the NMEA format gather from
    GPS Module(SIM33EAU) by Serial Communication.
*/
#ifndef GPS_H
#define GPS_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//NMEA_GNMRC Data Structure 
typedef struct NMEA_GNRMC{
    char *name;
    char *utc_time;
    char *status;
    char *latitude;
    char *latitudeDirection;
    char *longitude;
    char *longitudeDirection;
    char *speedOverGround;
    char *courseOverGround;
    char *utc_date;
    char *modeIndicatorAndcheckSum;
}NMEA_GNRMC;
//UTC_TIME Data Structure
typedef struct UTC_TIME{
    char hour[3];
    char minute[3];
    char second[3];
    char milli[4];
}UTC_TIME;
//COORDINATE Data Structure
typedef struct COORDINATE{
    char latitude[15];
    char longitude[15];
}COORDINATE;
//prototype functions
char* token(char *str, char *delimitter);
void print_NMEA_GNRMC(const NMEA_GNRMC *data);
void print_UTC_TIME(const UTC_TIME *time);
NMEA_GNRMC setGnrmc(char *str);
UTC_TIME setTime(char *utcTime);
COORDINATE setCoordinates(const NMEA_GNRMC *data);
void print_COORDINATE(const COORDINATE *tempCoordinate);
double latitudeDegrees(char* latitude, char *direction);
double longitudeDegrees(char *longitude,char *direction);

#endif
