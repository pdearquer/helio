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
#ifndef __HELIO_TYPE_POINTER_IS_STATIC
__CHECK_TYPE(sizeof(__pointer) >= sizeof(_pointer));
#endif
__CHECK_TYPE(sizeof(__pointer) >= sizeof(void *));


const_pointer Pointer::NULL;


Pointer::Pointer()
{
   _value = (__pointer)null;
}

Pointer::Pointer(const Pointer &other)
{
   _value = other._value;
}

#ifndef __HELIO_TYPE_POINTER_IS_STATIC   
Pointer::Pointer(_pointer p)
{
   _value = (__pointer)p;
}
#endif

#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
Pointer::Pointer(const void *p)
{
   _value = (__pointer)p;
}
#endif

#ifndef __HELIO_TYPE_POINTER_IS_STATIC  
Pointer::Pointer(_pointer p, _int bytes)
{
   _value = (__pointer)p;
   move(bytes);
}
#endif
   
#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
Pointer::Pointer(const void *p, _int bytes)
{
   _value = (__pointer)p;
   move(bytes);
}
#endif


Pointer Pointer::get() const
{
   Pointer copy;
   copy._value = _value;
   return copy;
}

void Pointer::set(const Pointer &other)
{
   _value = other._value;
}
   
_bool Pointer::isNull() const
{
   return (_value == (__pointer)null);
}


void Pointer::move(_int bytes)
{
   _value += bytes;
}

_int Pointer::diff(const Pointer &to) const
{
   return (_int)((__pointer)to._value - _value);
}

#ifndef __HELIO_TYPE_POINTER_IS_STATIC   
_int Pointer::diff(_pointer to) const
{
   return (_int)((__pointer)to - _value);
}
#endif


_int Pointer::compare(const Pointer *other) const
{
   if(_value == other->_value)
      return 0;
   if(_value < other->_value)
      return -1;
   return +1;
}

_bool Pointer::equals(const Pointer *other) const
{
   return (_value == other->_value);
}

Pointer *Pointer::clone() const
{
   return new Pointer(this);
}

_uint32 Pointer::makeHash() const
{
   return (_uint32)_value;
}


String Pointer::toString() const
{
   return Format::def()->toString((_pointer)Pointer(*this));
}
   

#ifndef __HELIO_TYPE_POINTER_IS_STATIC
Pointer::operator _pointer() const
{
   return (_pointer)_value;
}
#endif

#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
Pointer::operator void*() const
{
   return (void *)_value;
}
#endif

   
void Pointer::operator =(const Pointer &other)
{
   _value = other._value;   
}

#ifndef __HELIO_TYPE_POINTER_IS_STATIC
void Pointer::operator =(_pointer other)
{
   _value = (__pointer)other;
}
#endif

#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
void Pointer::operator =(const void *other)
{
   _value = (__pointer)other;
}
#endif


_bool Pointer::operator ==(const Pointer &other) const
{
   return (_value == other._value);
}

_bool Pointer::operator !=(const Pointer &other) const
{
   return (_value != other._value);
}

_bool Pointer::operator <(const Pointer &other) const
{
   return (_value < other._value);
}

_bool Pointer::operator >(const Pointer &other) const
{
   return (_value > other._value);
}
_bool Pointer::operator <=(const Pointer &other) const
{
   return (_value <= other._value);
}

_bool Pointer::operator >=(const Pointer &other) const
{
   return (_value >= other._value);
}

#ifndef __HELIO_TYPE_POINTER_IS_STATIC
_bool Pointer::operator ==(_pointer other) const
{
   return (_value == (__pointer)other);
}

_bool Pointer::operator !=(_pointer other) const
{
   return (_value != (__pointer)other);
}

_bool Pointer::operator <(_pointer other) const
{
   return (_value < (__pointer)other);
}

_bool Pointer::operator >(_pointer other) const
{
   return (_value > (__pointer)other);
}

_bool Pointer::operator <=(_pointer other) const
{
   return (_value <= (__pointer)other);
}

_bool Pointer::operator >=(_pointer other) const
{
   return (_value >= (__pointer)other);
}
#endif

#ifndef __HELIO_TYPE_POINTER_IS_NATIVE
_bool Pointer::operator ==(const void *other) const
{
   return (_value == (__pointer)other);
}

_bool Pointer::operator !=(const void *other) const
{
   return (_value != (__pointer)other);
}

_bool Pointer::operator <(const void *other) const
{
   return (_value < (__pointer)other);
}

_bool Pointer::operator >(const void *other) const
{
   return (_value > (__pointer)other);
}

_bool Pointer::operator <=(const void *other) const
{
   return (_value <= (__pointer)other);
}

_bool Pointer::operator >=(const void *other) const
{
   return (_value >= (__pointer)other);
}
#endif


__pointer Pointer::raw() const
{
   return _value;
}

void Pointer::setRaw(__pointer value)
{
   _value = value;
}


Pointer Pointer::move(const Pointer &p, _int bytes)
{
   Pointer ptr = p;
   ptr._value += bytes;
   return ptr;
}

#ifndef __HELIO_TYPE_POINTER_IS_STATIC
_pointer Pointer::move(_pointer p, _int bytes)
{
   __pointer ptr = (__pointer)p;
   ptr += bytes;
   return (_pointer)ptr;
}
#endif

_int Pointer::diff(const Pointer &from, const Pointer &to)
{
   return (_int)(to._value - from._value);
}
   
#ifndef __HELIO_TYPE_POINTER_IS_STATIC
_int Pointer::diff(_pointer from, _pointer to)
{
   return (_int)((__pointer)to - (__pointer)from);
}
#endif

} } }

