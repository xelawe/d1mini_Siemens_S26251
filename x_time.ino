
#include <TimeLib.h> // https://github.com/PaulStoffregen/Time
#include <TimeAlarms.h>
#include <Timezone.h>    //https://github.com/JChristensen/Timezone

//int SyncInt = 300;
const int timeZone = 0;     // UTC

// Central European Time Zone (Vienna)
TimeChangeRule myDST = {"CEDT", Last, Sun, Mar, 2, 120};    //Daylight time = UTC - 1 hours
TimeChangeRule mySTD = {"CET", Last, Sun, Oct, 3,  60};     //Standard time = UTC - 2 hours
Timezone myTZ(myDST, mySTD);

TimeChangeRule *tcr;        //pointer to the time change rule, use to get TZ abbrev
