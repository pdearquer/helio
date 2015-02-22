/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Device {
namespace Time {

Clock *Clock::_default = null;
   

void Clock::getDefault(Date *date)
{
   if(_default == null)
   {
#ifdef __HELIO_DEVICE_TIME_UNIXCLOCK
      _default = new UnixClock();
#else
      Exception *ex = MAKE_ERROR(Exception::Device::NoDefault);
      ex->add("interface", "Device.Time.Clock");
      throw ex;
#endif      
   }
      
   _default->get(date);
}

_uint64 Clock::getCurrentMillis()
{
#ifdef __HELIO_DEVICE_TIME_UNIXCLOCK
   return UnixClock::getCurrentMillis();
#else
   return 0;
#endif  
}

} }

