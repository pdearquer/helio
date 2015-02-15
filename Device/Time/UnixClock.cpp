/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

namespace Device {
namespace Time {

void UnixClock::get(Date *date)
{
   date->setUnix((_uint32) time(null));
}

String UnixClock::format(const Date *date)
{
   time_t t = (time_t) date->getUnix();
   struct tm *cal = localtime(&t);

   char buf[32];
   sprintf(buf, "%02i:%02i:%02i %02i/%02i/%04i",
         cal->tm_hour, cal->tm_min, cal->tm_sec,
         cal->tm_mday, cal->tm_mon + 1, cal->tm_year + 1900);
   
   return (String) buf;
}

_uint64 UnixClock::getCurrentMillis()
{
   struct timeval time;

   gettimeofday(&time, NULL);

   return (_uint64)time.tv_sec * 1000L + (_uint64)time.tv_usec / 1000L;
}

} }

