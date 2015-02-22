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
#ifndef __HELIO_TYPE_INT_IS_STATIC
__CHECK_TYPE(sizeof(__int) >= sizeof(_int));
__CHECK_TYPE(sizeof(_int) >= 16/8);
#else
//__CHECK_TYPE(sizeof(__int) > __HELIO_TYPE_INT_MAX);    // In order to detect overflows simpler
#endif
//__CHECK_TYPE(sizeof(__int) >= sizeof(int));


const_int Integer::MIN;

const_int Integer::MAX;


Integer::Integer()
{
   _value = 0;
}

Integer::Integer(const Integer &other)
{
   _value = other._value;
}

Integer::Integer(const Integer *other)
{
   _value = other->_value;
}

#ifndef __HELIO_TYPE_INT_IS_STATIC
Integer::Integer(_int value)
{
   _value = (__int)value;
}
#endif
   
#ifndef __HELIO_TYPE_INT_IS_NATIVE
Integer::Integer(int value)
{
   checkOverflow((__int)value);
}
#endif

Integer::Integer(size_t value)
{
   checkOverflow((__int)value);
}

Integer::Integer(_uint8 value)
{
   checkOverflow((__int)value);
}

Integer::Integer(_uint16 value)
{
   checkOverflow((__int)value);
}

Integer::Integer(_uint32 value)
{
   checkOverflow((__int)value);
}

Integer::Integer(_uint64 value)
{
   checkOverflow((__int)value);
}

Integer::Integer(__sint64 value)
{
   checkOverflow((__int)value);
}

Integer::Integer(const Float &value)
{
   checkOverflow((__int)value.raw());
}
   
#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
Integer::Integer(_float value)
{
   checkOverflow((__int)value);
}
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
Integer::Integer(double value)
{
   checkOverflow((__int)value);
}
#endif


Integer Integer::get() const
{
   Integer copy;
   copy._value = _value;
   return copy;
}

void Integer::set(const Integer &other)
{
   _value = other._value;
}
   
   
_int Integer::getInt() const
{
   return (_int)_value;
}

_float Integer::getFloat() const
{
   return (_float)Float(*this);
}

   
_int Integer::compare(const Integer *other) const
{
   __int val = other->_value;
      
   if(_value == val)
      return 0;
   if(_value < val)
      return -1;
   return +1;
}

_bool Integer::equals(const Integer *other) const
{
   return (_value == other->_value);
}

Integer *Integer::clone() const
{
   return new Integer(this);
}

_uint32 Integer::makeHash() const
{
   return (_uint32)_value;
}


String Integer::toString() const
{
   return Format::def()->toString((_int)_value);
}


#ifndef __HELIO_TYPE_INT_IS_STATIC
Integer::operator _int() const
{
   return (_int)_value;
}
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
Integer::operator int() const
{
   return (int)_value;
}
#endif

Integer::operator size_t() const
{
   if(_value < 0)
      ERROR(Error::Arithmetic::Overflow);
   
   return (size_t)_value;
}
   
Integer::operator _uint8() const
{
   if(_value < __HELIO_TYPE_UINT8_MIN || _value > __HELIO_TYPE_UINT8_MAX)
      ERROR(Error::Arithmetic::Overflow);
   
   return (_uint8)_value;
}
   
Integer::operator _uint16() const
{
   if(_value < __HELIO_TYPE_UINT16_MIN || _value > __HELIO_TYPE_UINT16_MAX)
      ERROR(Error::Arithmetic::Overflow);
      
   return (_uint16)_value;
}
   
Integer::operator _uint32() const
{
   if(_value < __HELIO_TYPE_UINT32_MIN)
      ERROR(Error::Arithmetic::Overflow);
      
   if(sizeof(__int) > sizeof(_uint32) && _value > (__int)__HELIO_TYPE_UINT32_MAX)
      ERROR(Error::Arithmetic::Overflow);
      
   return (_uint32)_value;
}
   
Integer::operator _uint64() const
{
   if(_value < 0)
      ERROR(Error::Arithmetic::Overflow);
      
   return (_uint64)_value;
}

Integer::operator __sint64() const
{
   return (__sint64)_value;
}

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC 
Integer::operator _float() const
{
   return (_float)Float(*this);
}
#endif


void Integer::operator =(const Integer &other)
{
   _value = other._value;   
}

#ifndef __HELIO_TYPE_INT_IS_STATIC
void Integer::operator =(_int other)
{
   _value = (__int)other;
}
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
void Integer::operator =(int other)
{
   checkOverflow((__int)other);
}
#endif

void Integer::operator =(size_t other)
{
   checkOverflow((__int)other);
}


_bool Integer::operator ==(const Integer &other) const
{
   return (_value == other._value);
}

_bool Integer::operator !=(const Integer &other) const
{
   return (_value != other._value);
}

_bool Integer::operator <(const Integer &other) const
{
   return (_value < other._value);
}

_bool Integer::operator >(const Integer &other) const
{
   return (_value > other._value);
}

_bool Integer::operator <=(const Integer &other) const
{
   return (_value <= other._value);
}

_bool Integer::operator >=(const Integer &other) const
{
   return (_value >= other._value);
}

#ifndef __HELIO_TYPE_INT_IS_STATIC
_bool Integer::operator ==(_int other) const
{
   return (_value == (__int)other);
}

_bool Integer::operator !=(_int other) const
{
   return (_value != (__int)other);
}

_bool Integer::operator <(_int other) const
{
   return (_value < (__int)other);
}

_bool Integer::operator >(_int other) const
{
   return (_value > (__int)other);
}

_bool Integer::operator <=(_int other) const
{
   return (_value <= (__int)other);
}

_bool Integer::operator >=(_int other) const
{
   return (_value >= (__int)other);
}
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
_bool Integer::operator ==(int other) const
{
   return (_value == (__int)other);
}

_bool Integer::operator !=(int other) const
{
   return (_value != (__int)other);
}

_bool Integer::operator <(int other) const
{
   return (_value < (__int)other);
}

_bool Integer::operator >(int other) const
{
   return (_value > (__int)other);
}

_bool Integer::operator <=(int other) const
{
   return (_value <= (__int)other);
}

_bool Integer::operator >=(int other) const
{
   return (_value >= (__int)other);
}
#endif

_bool Integer::operator ==(size_t other) const
{
   return (_value == (__int)other);
}

_bool Integer::operator !=(size_t other) const
{
   return (_value != (__int)other);
}

_bool Integer::operator <(size_t other) const
{
   return (_value < (__int)other);
}

_bool Integer::operator >(size_t other) const
{
   return (_value > (__int)other);
}

_bool Integer::operator <=(size_t other) const
{
   return (_value <= (__int)other);
}

_bool Integer::operator >=(size_t other) const
{
   return (_value >= (__int)other);
}


void Integer::operator +=(const Integer &other)
{
   checkOverflow(_value + other._value);
}

void Integer::operator -=(const Integer &other)
{
   checkOverflow(_value - other._value);
}

void Integer::operator *=(const Integer &other)
{
   checkOverflow(_value * other._value);
}

void Integer::operator /=(const Integer &other)
{
   if(other._value == 0)
      ERROR(Error::Arithmetic::DivisionByCero);
   
   if(_value == MIN && other._value == -1)
      ERROR(Error::Arithmetic::Overflow);
   
   _value /= other._value;
}

void Integer::operator %=(const Integer &other)
{
   if(other._value == 0)
      ERROR(Error::Arithmetic::ModuloByCero);
   
   if(_value == MIN && other._value == -1)
      ERROR(Error::Arithmetic::Overflow);
   
   _value %= other._value;
}
   

#ifndef __HELIO_TYPE_INT_IS_STATIC
void Integer::operator +=(_int other)
{
   checkOverflow(_value + (__int)other);
}
   
void Integer::operator -=(_int other)
{
   checkOverflow(_value - (__int)other);
}
   
void Integer::operator *=(_int other)
{
   checkOverflow(_value * (__int)other);
}

void Integer::operator /=(_int other)
{
   if((__int)other == 0)
      ERROR(Error::Arithmetic::DivisionByCero);
   
   if(_value == MIN && (__int)other == -1)
      ERROR(Error::Arithmetic::Overflow);
   
   checkOverflow(_value / (__int)other);
}
   
void Integer::operator %=(_int other)
{
   if((__int)other == 0)
      ERROR(Error::Arithmetic::ModuloByCero);
      
   if(_value == MIN && (__int)other == -1)
      ERROR(Error::Arithmetic::Overflow);
      
   _value %= (__int)other;
}
#endif


#ifndef __HELIO_TYPE_INT_IS_NATIVE
void Integer::operator +=(int other)
{
   checkOverflow(_value + (__int)other);
}
   
void Integer::operator -=(int other)
{
   checkOverflow(_value - (__int)other);
}
   
void Integer::operator *=(int other)
{
   checkOverflow(_value * (__int)other);
}
   
void Integer::operator /=(int other)
{
   if((__int)other == 0)
      ERROR(Error::Arithmetic::DivisionByCero);
   
   if(_value == MIN && (__int)other == -1)
      ERROR(Error::Arithmetic::Overflow);
   
   checkOverflow(_value / (__int)other);
}
   
void Integer::operator %=(int other)
{
   if((__int)other == 0)
      ERROR(Error::Arithmetic::ModuloByCero);
      
   if(_value == MIN && (__int)other == -1)
      ERROR(Error::Arithmetic::Overflow);
      
   _value %= (__int)other;
}
#endif

void Integer::operator +=(size_t other)
{
   checkOverflow(_value + (__int)other);
}

void Integer::operator -=(size_t other)
{
   checkOverflow(_value - (__int)other);
}
   
void Integer::operator *=(size_t other)
{
   checkOverflow(_value * (__int)other);
}
   
void Integer::operator /=(size_t other)
{
   if(other == 0)
      ERROR(Error::Arithmetic::DivisionByCero);
   
   if(_value == MIN && (__int)other == -1)
      ERROR(Error::Arithmetic::Overflow);

   _value /= (__int)other;
}
   
void Integer::operator %=(size_t other)
{
   if((__int)other == 0)
      ERROR(Error::Arithmetic::ModuloByCero);
      
   if(_value == MIN && (__int)other == -1)
      ERROR(Error::Arithmetic::Overflow);
      
   _value %= (__int)other;
}
   

void Integer::operator ++(int)
{
   checkOverflow(_value + 1);
}

void Integer::operator ++()
{
   checkOverflow(_value + 1);
}

void Integer::operator --(int)
{
   checkOverflow(_value - 1);
}

void Integer::operator --()
{
   checkOverflow(_value - 1);
}
   
const Integer Integer::operator -() const
{
   if(_value == MIN)
      ERROR(Error::Arithmetic::Overflow);
      
   Integer result;
   result.checkOverflow(-_value);
   return result;
}

   
const Integer Integer::operator +(const Integer &other) const
{
   Integer result = *this;
   result += other;
   return result;
}

const Integer Integer::operator -(const Integer &other) const
{
   Integer result = *this;
   result -= other;
   return result;
}

const Integer Integer::operator *(const Integer &other) const
{
   Integer result = *this;
   result *= other;
   return result;
}

const Integer Integer::operator /(const Integer &other) const
{
   Integer result = *this;
   result /= other;
   return result;
}

const Integer Integer::operator %(const Integer &other) const
{
   Integer result = *this;
   result %= other;
   return result;
}
   
   
#ifndef __HELIO_TYPE_INT_IS_STATIC
const Integer Integer::operator +(_int other) const
{
   Integer result = *this;
   result += other;
   return result;
}
   
const Integer Integer::operator -(_int other) const
{
   Integer result = *this;
   result -= other;
   return result;
}
   
const Integer Integer::operator *(_int other) const
{
   Integer result = *this;
   result *= other;
   return result;
}
   
const Integer Integer::operator /(_int other) const
{
   Integer result = *this;
   result /= other;
   return result;
}
   
const Integer Integer::operator %(_int other) const
{
   Integer result = *this;
   result %= other;
   return result;
}
#endif


#ifndef __HELIO_TYPE_INT_IS_NATIVE
const Integer Integer::operator +(int other) const
{
   Integer result = *this;
   result += other;
   return result;
}
   
const Integer Integer::operator -(int other) const
{
   Integer result = *this;
   result -= other;
   return result;
}
   
const Integer Integer::operator *(int other) const
{
   Integer result = *this;
   result *= other;
   return result;
}
   
const Integer Integer::operator /(int other) const
{
   Integer result = *this;
   result /= other;
   return result;
}
   
const Integer Integer::operator %(int other) const
{
   Integer result = *this;
   result %= other;
   return result;
}
#endif

const Integer Integer::operator +(size_t other) const
{
   Integer result = *this;
   result += other;
   return result;
}
   
const Integer Integer::operator -(size_t other) const
{
   Integer result = *this;
   result -= other;
   return result;
}
   
const Integer Integer::operator *(size_t other) const
{
   Integer result = *this;
   result *= other;
   return result;
}
   
const Integer Integer::operator /(size_t other) const
{
   Integer result = *this;
   result /= other;
   return result;
}
   
const Integer Integer::operator %(size_t other) const
{
   Integer result = *this;
   result %= other;
   return result;
}


__int Integer::raw() const
{
   return _value;
}

void Integer::checkOverflow(__int value)
{
   if(value < MIN || value > MAX)
      ERROR(Error::Arithmetic::Overflow);
   
   _value = value;
}

} } }

#ifndef __HELIO_TYPE_INT_IS_STATIC
_bool operator ==(_int a, const Storage::Structure::Data::Integer &b)
{
   return ((__int)a == b.raw());
}

_bool operator !=(_int a, const Storage::Structure::Data::Integer &b)
{
   return ((__int)a != b.raw());
}

_bool operator <(_int a, const Storage::Structure::Data::Integer &b)
{
   return ((__int)a < b.raw());
}

_bool operator >(_int a, const Storage::Structure::Data::Integer &b)
{
   return ((__int)a > b.raw());
}

_bool operator <=(_int a, const Storage::Structure::Data::Integer &b)
{
   return ((__int)a <= b.raw());
}

_bool operator >=(_int a, const Storage::Structure::Data::Integer &b)
{
   return ((__int)a >= b.raw());
}
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
_bool operator ==(int a, const Storage::Structure::Data::Integer &b)
{
   return ((__int)a == b.raw());
}

_bool operator !=(int a, const Storage::Structure::Data::Integer &b)
{
   return ((__int)a != b.raw());
}

_bool operator <(int a, const Storage::Structure::Data::Integer &b)
{
   return ((__int)a < b.raw());
}

_bool operator >(int a, const Storage::Structure::Data::Integer &b)
{
   return ((__int)a > b.raw());
}

_bool operator <=(int a, const Storage::Structure::Data::Integer &b)
{
   return ((__int)a <= b.raw());
}

_bool operator >=(int a, const Storage::Structure::Data::Integer &b)
{
   return ((__int)a >= b.raw());
}
#endif

_bool operator ==(size_t a, const Storage::Structure::Data::Integer &b)
{
   return ((__int)a == b.raw());
}

_bool operator !=(size_t a, const Storage::Structure::Data::Integer &b)
{
   return ((__int)a != b.raw());
}

_bool operator <(size_t a, const Storage::Structure::Data::Integer &b)
{
   return ((__int)a < b.raw());
}

_bool operator >(size_t a, const Storage::Structure::Data::Integer &b)
{
   return ((__int)a > b.raw());
}

_bool operator <=(size_t a, const Storage::Structure::Data::Integer &b)
{
   return ((__int)a <= b.raw());
}

_bool operator >=(size_t a, const Storage::Structure::Data::Integer &b)
{
   return ((__int)a >= b.raw());
}

#ifndef __HELIO_TYPE_INT_IS_STATIC
const Storage::Structure::Data::Integer operator +(_int a, const Storage::Structure::Data::Integer &b)
{
   Integer result = a;
   result += b;
   return result;
}

const Storage::Structure::Data::Integer operator -(_int a, const Storage::Structure::Data::Integer &b)
{
   Integer result = a;
   result -= b;
   return result;
}

const Storage::Structure::Data::Integer operator *(_int a, const Storage::Structure::Data::Integer &b)
{
   Integer result = a;
   result *= b;
   return result;
}

const Storage::Structure::Data::Integer operator /(_int a, const Storage::Structure::Data::Integer &b)
{
   Integer result = a;
   result /= b;
   return result;
}

const Storage::Structure::Data::Integer operator %(_int a, const Storage::Structure::Data::Integer &b)
{
   Integer result = a;
   result %= b;
   return result;
}
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
const Storage::Structure::Data::Integer operator +(int a, const Storage::Structure::Data::Integer &b)
{
   Integer result = a;
   result += b;
   return result;
}

const Storage::Structure::Data::Integer operator -(int a, const Storage::Structure::Data::Integer &b)
{
   Integer result = a;
   result -= b;
   return result;
}

const Storage::Structure::Data::Integer operator *(int a, const Storage::Structure::Data::Integer &b)
{
   Integer result = a;
   result *= b;
   return result;
}

const Storage::Structure::Data::Integer operator /(int a, const Storage::Structure::Data::Integer &b)
{
   Integer result = a;
   result /= b;
   return result;
}

const Storage::Structure::Data::Integer operator %(int a, const Storage::Structure::Data::Integer &b)
{
   Integer result = a;
   result %= b;
   return result;
}
#endif

const Storage::Structure::Data::Integer operator +(size_t a, const Storage::Structure::Data::Integer &b)
{
   Integer result = a;
   result += b;
   return result;
}

const Storage::Structure::Data::Integer operator -(size_t a, const Storage::Structure::Data::Integer &b)
{
   Integer result = a;
   result -= b;
   return result;
}

const Storage::Structure::Data::Integer operator *(size_t a, const Storage::Structure::Data::Integer &b)
{
   Integer result = a;
   result *= b;
   return result;
}

const Storage::Structure::Data::Integer operator /(size_t a, const Storage::Structure::Data::Integer &b)
{
   Integer result = a;
   result /= b;
   return result;
}

const Storage::Structure::Data::Integer operator %(size_t a, const Storage::Structure::Data::Integer &b)
{
   Integer result = a;
   result %= b;
   return result;
}

