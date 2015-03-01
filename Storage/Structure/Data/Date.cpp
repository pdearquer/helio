/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Data {

Date::Date()
{
#ifdef __HELIO_DEVICE_TIME_CLOCK
   Device::Time::Clock::getDefault(this);
#else
   _secs = 0;
#endif
}

Date::Date(const Date &other)
{
   _secs = other._secs;
}

Date::Date(const Date *other)
{
   _secs = other->_secs;
}
   
Date::Date(_uint32 secs)
{
   _secs = secs;
}

Date::Date(_uint32 utime, _bool saturate)
{
   setUnix(utime, saturate);
}
   

_uint32 Date::secs() const 
{
   return _secs;
}
   
_uint32 Date::secs(_uint32 s)
{
   _secs = s;
   return _secs;
}


_uint32 Date::setUnix(_uint32 utime, _bool saturate)
{
   if(utime >= (((_uint32) 30 * 365 * 24 + 167) * 60 * 60))
   {
      _secs = utime - (((_uint32) 30 * 365 * 24 + 167) * 60 * 60);
   }
   else
   {
      if(saturate)
      {
         _secs = 0;
      }
      else
      {
         MAKE_ERROR(ex, Exception::Format::DateLimit);
         ex->addUInt32("unix", utime);
         throw ex;
      }
   }
   return _secs;
}

_uint32 Date::getUnix(_bool saturate) const
{
   if(_secs > ((_uint32) 0xFFFFFFFF - ((_uint32) 30 * 365 * 24 + 167) * 60 * 60))
   {
      if(saturate)
      {
         return (_uint32) 0xFFFFFFFF;
      }
      else
      {
         MAKE_ERROR(ex, Exception::Format::DateLimit);
         ex->addUInt32("seconds", _secs);
         throw ex;
      }
   }
   
   return (_secs + (((_uint32) 30 * 365 * 24 + 167) * 60 * 60));
}


_int Date::compare(const Date *other) const
{
   if(_secs == other->_secs)
      return 0;
   if(_secs < other->_secs)
      return -1;
   return +1;
}

_bool Date::equals(const Date *other) const
{
   return (_secs == other->_secs);
}

Date *Date::clone() const
{
   return new Date(this);
}

_uint32 Date::makeHash() const
{
   return (_uint32)_secs;
}


String Date::toString() const
{
   return Format::def()->toString(*this);
}

String Date::now()
{
   Date *d = new Date();
   String str = d->toString();
   delete d;
   
   return str;
}

   
void Date::operator =(const Date &other)
{
   _secs = other._secs;
}
   

_bool Date::operator ==(const Date &other) const
{
   return (_secs == other._secs);
}

_bool Date::operator !=(const Date &other) const
{
   return (_secs != other._secs);
}

_bool Date::operator <(const Date &other) const
{
   return (_secs < other._secs);
}

_bool Date::operator >(const Date &other) const
{
   return (_secs > other._secs);
}

_bool Date::operator <=(const Date &other) const
{
   return (_secs <= other._secs);
}

_bool Date::operator >=(const Date &other) const
{
   return (_secs >= other._secs);
}

} } }

