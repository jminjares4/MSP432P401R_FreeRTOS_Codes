/**
    Author: Jesus Minjares
    Last Modified:  11/04/2020
    This library is design to organize the NMEA format gather from
    GPS Module(SIM33EAU) by Serial Communication.
*/
#include "GPS.h"
/**
 * USE:       Print the GNRMC structure
 * PARAMETER: expected reference to a NMEA_GNRMC structure
 * RETURN:    void
 * NOTE:      const, state that within the function, the "data" variable
              should not be alter
*/
void print_NMEA_GNRMC(const NMEA_GNRMC *data){
    printf("NAME: %s\n", data->name);
    printf("UTC TIME: %s\n", data->utc_time);
    printf("STATUS: %s\n",data->status);
    printf("LATITUDE: %s\n",data->latitude);
    printf("LATITUDE DIRECTION: %s\n", data->latitudeDirection);
    printf("LONGITUDE: %s\n",data->longitude);
    printf("LONGITUDE DIRECTION: %s\n", data->longitudeDirection);
    printf("SPEED: %s\n", data->speedOverGround);
    printf("COURSE: %s\n", data->courseOverGround);
    printf("UTC DATE: %s\n", data->utc_date);
    printf("MODE & CHECKSUM: %s\n", data->modeIndicatorAndcheckSum);
}
/**
 *USE:       tokenize a string by the its delimitter
 *PARAMETER: desired string, delimiter
 *RETURN:    void
*/
char* token(char *str, char *delimitter){
    static char *state;   // state is a char pointer point to a specific char
    // location in "str". It records non-scanned part
    char *d, *beg;
    if (str != NULL)
        state = str;
    for (; *state != '\0'; state++) {   // find beg, delete previous delimitter
        for (d = delimitter; *d != '\0'; d++)
            if (*d == *state)
                break;
        if (*d == '\0')
            break;
    }
    if (*state == '\0')    // if reach '\0', no token, return NULL
        return NULL;
    else
        beg = state;       // else, find beg

    for (; *state != '\0'; state++) {   // find end
        for (d= delimitter; *d != '\0'; d++)
            if (*d == *state)
                break;
        if (*d != '\0')
            break;
    }
    if (*state != '\0')     // if not reach '\0', put '\0', and state++
        *state++ = '\0';

    return beg;    // return beg of token
}
/**
 *USE:       Print the UTC TIME Structure
 *PARAMETER: expects the reference to the UTC_TIME structure
 *RETURN::   return a string
 *NOTE:      const, state the the function can not modified the variable
*/
void print_UTC_TIME(const UTC_TIME *time){
    printf("HOUR: %s\n", time->hour);
    printf("MINUTE: %s\n", time->minute);
    printf("SECOND: %s\n", time->second);
    printf("MILLI: %s\n", time->milli);
    printf("---TIME---\n");
    printf("%s:%s:%s.%s\n",time->hour,time->minute,time->second, time->milli);
}
 /**
  *USE:       Parse the GNRMC string and store in an instance of NMEA_GNRMC
  *PARAMETER: String to be parsed, "GNRMC"
  *NOTE:      The first instance of token takes the string.
  *           The next token will use a null, as in the token
  *           there is no need to insert a new string because of the static variable.
  *RETURN:    Return a instance of the NMEA_GNRMC to be stored
*/
NMEA_GNRMC setGnrmc(char *str){
    NMEA_GNRMC temp; //create a instance of NMEA_GNRMC
    char *del = ","; //set the delimitter
    //tokenize the string
    temp.name = token(str,del);
    temp.utc_time = token(NULL,del);
    temp.status = token(NULL,del);
    temp.latitude = token(NULL,del);
    temp.latitudeDirection =token(NULL,del);
    temp.longitude = token(NULL,del);
    temp.longitudeDirection  = token(NULL,del);
    temp.speedOverGround = token(NULL,del);
    temp.courseOverGround  = token(NULL,del);
    temp.utc_date  = token(NULL,del);
    temp.modeIndicatorAndcheckSum  = token(NULL,del);
    return temp; //return the instance of the NMEA_GNMRC
}
/**
 * USE:       Set the time to the UTC_TIME Structure
 * PARAMETER: UTC_TIME string from the NMEA_GNRMC
 * RETURN:    Return an instance of the UTC_TIME to be stored
 * NOTE:      void *memset(void *s, int c, size_t n);
 *            void *memcpy(void *dest, const void *src, size_t n);
 *            --------------------------------
 *            memset, is being use to clearing the data in the memory
 *            of the UTC_TIME instance
 *            mempcy, is being use to copy certain amount of bytes from the string
 *            into each member of the UTC_TIME
*/
UTC_TIME setTime(char *utcTime){
    UTC_TIME time;//create an instance of the UTC
    //set the memory of each member to empty
    memset((void*)&time.hour, 0, sizeof(time.hour));
    memset((void*)&time.minute, 0, sizeof(time.minute));
    memset((void*)&time.second, 0, sizeof(time.second));
    memset((void*)&time.milli, 0, sizeof(time.milli));

    //copy part of the string to the corresponding UTC_TIME member
    memcpy((void*)&time.hour, (void*)&utcTime[0],2 );
    memcpy((void*)&time.minute,(void*)&utcTime[2],2);
    memcpy((void*)&time.second,(void*)&utcTime[4], 2);
    memcpy((void*)&time.milli,(void*)&utcTime[7], 4);
    return time; //return the time
}
/**
 * USE:       Set the coordinate from the GNRMC in a COORDINATE data structure
 * PARAMETER: Pass reference the NMEA_GNRMC as a constant to avoid altering it
 * RETURN:    Return an instance of the COORDINATE
 * NOTE:      sprintf(char *str, const char *format, ...);
 *            sprintf is used to print into the buffer, converts a double to a string
*/
COORDINATE setCoordinates(const NMEA_GNRMC *data){
    COORDINATE tempCoordinates; //create an instance COORDINATE
    //use sprintf to convert double to string
    //and store in COORDINATE members
    tempCoordinates.latitude  = latitudeDegrees(data->latitude, data->latitudeDirection);
    tempCoordinates.longitude = longitudeDegrees(data->longitude, data->longitudeDirection);
    return tempCoordinates;
}
/**
 * USE:       Print the Coordinate in degrees
 * PARAMETER: Pass reference COORDINATE as a const
 * RETURN:    No Return
*/
void print_COORDINATE(const COORDINATE *tempCoor){
    printf("LAT: %lf\n",tempCoor->latitude);
    printf("LON: %lf\n",tempCoor->longitude);
    printf("%lf,%lf\n",tempCoor->latitude, tempCoor->longitude);
}
/**
 * USE: Convert NMEA Latitude to NMEA to DEGREE
 * PARAMETER: NMEA latitude and latitude direction
 * RETURN:  Return the NMEA Latitude string as in DEGREE format as a double
 * NOTE:    double strtod(const char *nptr, char **endptr);
 *          converts a string into a double
*/
double latitudeDegrees(char *latitude, char *direction){
  double latitudeAsDouble = str_to_double(latitude);
  //NMEA format: ddmm.mmmm
  int dd = latitudeAsDouble / 100;  //get the dd
  double mmmm = latitudeAsDouble - dd*100; //get mmm in double
  if(direction[0] == 'N') //if the direction is N then i will be positive
    return dd + mmmm/60;
  else if(direction[0] == 'S') //if the direction is S, then it will negative
      return -1*(dd + mmmm/60);
  else
      return 0;
  //return (direction[0] == 'N') ? ddd+mmmm/60 : -1*(ddd + mmmm/60);
}
/**
 * USE: Convert NMEA Longitude to NMEA to DEGREE
 * PARAMETER: NMEA Longitude and longitude direction
 * RETURN:  Return the NMEA Longitude string as in DEGREE format as a double
 * NOTE:    double strtod(const char *nptr, char **endptr);
 *          converts a string into a double
*/
double longitudeDegrees(char *longitude, char *direction){
  double longitudeAsDouble = str_to_double(longitude);
  //NMEA format: dddmm.mmmm
  int ddd = longitudeAsDouble/100; //get the DD for the longtiude
  double mmmm = longitudeAsDouble - ddd*100; //get the mm.mmmm from the longitude
  if(direction[0] == 'E') //if direction is East, then postive
    return ddd + mmmm/60;
  else if(direction[0] == 'W') //if direction is West, then Negative
      return -1*(ddd + mmmm/60);
  else
    return 0; //if it recieve a errnous character return a 0
  //return (direction[0] == 'E') ? ddd+mmmm/60 : -1*(ddd + mmmm/60);
}
double str_to_double(char* num)
 {
     if (!num || !*num)
         return 0;
     double integerPart = 0;
     double fractionPart = 0;
     int divisorForFraction = 1;
     int sign = 1;
     bool inFraction = false;
     /*Take care of +/- sign*/
     if (*num == '-')
     {
         ++num;
         sign = -1;
     }
     else if (*num == '+')
     {
         ++num;
     }
     while (*num != '\0')
     {
         if (*num >= '0' && *num <= '9')
         {
             if (inFraction)
             {
                 /*See how are we converting a character to integer*/
                 fractionPart = fractionPart*10 + (*num - '0');
                 divisorForFraction *= 10;
             }
             else
             {
                 integerPart = integerPart*10 + (*num - '0');
             }
         }
         else if (*num == '.')
         {
             if (inFraction)
                 return sign * (integerPart + fractionPart/divisorForFraction);
             else
                 inFraction = true;
         }
         else
         {
             return sign * (integerPart + fractionPart/divisorForFraction);
         }
         ++num;
     }
     return sign * (integerPart + fractionPart/divisorForFraction);
 }
