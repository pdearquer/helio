/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Data {

/**
 * Types enforment:
 * The internal type must support all the rest.
 */
#ifndef __HELIO_TYPE_BOOL_IS_STATIC
__CHECK_TYPE(sizeof(__bool) >= sizeof(_bool));
#endif
__CHECK_TYPE(sizeof(__bool) >= sizeof(bool));


const_bool Boolean::FALSE;
   
const_bool Boolean::TRUE;


Boolean::Boolean()
{
   _value = false;
}

Boolean::Boolean(const Boolean &other)
{
   _value = other._value;
}

Boolean::Boolean(const Boolean *other)
{
   _value = other->_value;
}

#ifndef __HELIO_TYPE_BOOL_IS_STATIC
Boolean::Boolean(_bool value)
{
   _value = value;
}
#endif

#ifndef __HELIO_TYPE_BOOL_IS_NATIVE
Boolean::Boolean(bool value)
{
   _value = value;
}
#endif


Boolean Boolean::get() const
{
   Boolean copy;
   copy._value = _value;
   return copy;
}
   
void Boolean::set(const Boolean &other)
{
   _value = other._value;
}
   
   
_bool Boolean::equals(const Boolean *other) const
{
   return (_value && other->_value) || (!_value && !other->_value);
}

Boolean *Boolean::clone() const
{
   return new Boolean(this);
}

_uint32 Boolean::makeHash() const
{
   return _value ? 1 : 0;
}


String Boolean::toString() const
{
   return Format::def()->toString((_bool)_value);
}


#ifndef __HELIO_TYPE_BOOL_IS_STATIC
Boolean::operator _bool() const
{
   return (_bool)_value;
}
#endif

#ifndef __HELIO_TYPE_BOOL_IS_NATIVE
Boolean::operator bool() const
{
   return (bool)_value;
}
#endif


void Boolean::operator =(const Boolean &other)
{
   _value = other._value;
}

#ifndef __HELIO_TYPE_BOOL_IS_STATIC
void Boolean::operator =(_bool other)
{
   _value = (__bool)other;
}
#endif

#ifndef __HELIO_TYPE_BOOL_IS_NATIVE
void Boolean::operator =(bool other)
{
   _value = (__bool)other;
}
#endif


const Boolean Boolean::operator !() const
{
   return Boolean(!_value);
}

const Boolean Boolean::operator &&(const Boolean& other) const
{
   return Boolean(_value && other._value);
}

const Boolean Boolean::operator ||(const Boolean& other) const
{
   return Boolean(_value || other._value);
}


#ifndef __HELIO_TYPE_BOOL_IS_STATIC
const Boolean Boolean::operator &&(_bool other) const
{
   return Boolean(_value && other);
}

const Boolean Boolean::operator ||(_bool other) const
{
   return Boolean(_value || other);
}
#endif

#ifndef __HELIO_TYPE_BOOL_IS_NATIVE
const Boolean Boolean::operator &&(bool other) const
{
   return Boolean(_value && other);
}

const Boolean Boolean::operator ||(bool other) const
{
   return Boolean(_value || other);
}
#endif

} } }

