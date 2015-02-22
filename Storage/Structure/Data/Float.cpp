/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

#include <math.h>
#include <stdio.h>  

namespace Storage {
namespace Structure {
namespace Data {

/**
 * Types enforment:
 * The internal type must support all the rest.
 */
#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
__CHECK_TYPE(sizeof(__float) >= sizeof(_float));
#endif
__CHECK_TYPE(sizeof(__float) >= sizeof(float));


const_float Float::MIN;

const_float Float::MAX;
   
const_float Float::EPSILON;


Float::Float()
{
   _value = 0.0;
}

Float::Float(const Float &other)
{
   _value = other._value;
}

Float::Float(const Float *other)
{
   _value = other->_value;
}

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
Float::Float(_float value)
{
   _value = (__float)value;
}
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
Float::Float(double value)
{
   _value = (__float)value;
}
#endif


Float::Float(const Integer &value)
{
   checkOverflow((__float)value.raw());
}
   
#ifndef __HELIO_TYPE_INT_IS_STATIC
Float::Float(_int value)
{
   checkOverflow((__float)value);
}
#endif

#ifndef __HELIO_TYPE_INT_IS_NATIVE
Float::Float(int value)
{
   checkOverflow((__float)value);
}
#endif


Float Float::get() const
{
   Float copy;
   copy._value = _value;
   return copy;
}

void Float::set(const Float &other)
{
   _value = other._value;
}


_int Float::getInt() const
{
   return (_int)Integer(*this);
}

_float Float::getFloat() const
{
   return (_float)_value;
}

_bool Float::isNumber() const
{
   //return (_value == _value);
   return isnormal(_value);
}
   
_bool Float::isNaN() const
{
   return isnan(_value);
}
   
_bool Float::isInfinity() const
{
   return isinf(_value);
}

   
_int Float::compare(const Float *other) const
{
   __float val = other->_value;
      
   if(_value == val)
      return 0;
   if(_value < val)
      return -1;
   return +1;
}

_bool Float::equals(const Float *other) const
{
   return (_value == other->_value);
}

Float *Float::clone() const
{
   return new Float(this);
}

_uint32 Float::makeHash() const
{
   _uint32 hash = (_uint32)_value;
   hash += (_uint32)(_value * 1000000000.0f);
   return hash;
}


String Float::toString() const
{
   return Format::def()->toString((_float)_value);
}


#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
Float::operator _float() const
{
   return (_float)_value;
}
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
Float::operator double() const
{
   return (double)_value;
}
#endif

#ifndef __HELIO_TYPE_INT_IS_STATIC
Float::operator _int() const
{
   return (_int)Integer(*this);
}
#endif


void Float::operator =(const Float &other)
{
   _value = other._value;
}

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
void Float::operator =(_float other)
{
   _value = (__float)other;
}
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
void Float::operator =(double other)
{
   _value = (__float)other;
}
#endif


_bool Float::operator ==(const Float &other) const
{
   return (_value <= other._value + EPSILON && _value >= other._value - EPSILON);
}

_bool Float::operator !=(const Float &other) const
{
   return (_value > other._value + EPSILON || _value < other._value - EPSILON);
}

_bool Float::operator <(const Float &other) const
{
   return (_value < other._value);
}

_bool Float::operator >(const Float &other) const
{
   return (_value > other._value);
}

_bool Float::operator <=(const Float &other) const
{
   return (_value <= other._value + EPSILON);
}

_bool Float::operator >=(const Float &other) const
{
   return (_value >= other._value - EPSILON);
}

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
_bool Float::operator ==(_float other) const
{
   return (_value <= (__float)other + EPSILON && _value >= (__float)other - EPSILON);
}

_bool Float::operator !=(_float other) const
{
   return (_value > (__float)other + EPSILON || _value < (__float)other - EPSILON);
}

_bool Float::operator <(_float other) const
{
   return (_value < (__float)other);
}

_bool Float::operator >(_float other) const
{
   return (_value > (__float)other);
}

_bool Float::operator <=(_float other) const
{
   return (_value <= (__float)other + EPSILON);
}

_bool Float::operator >=(_float other) const
{
   return (_value >= (__float)other - EPSILON);
}
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
_bool Float::operator ==(double other) const
{
   return (_value <= (__float)other + EPSILON && _value >= (__float)other - EPSILON);
}

_bool Float::operator !=(double other) const
{
   return (_value > (__float)other + EPSILON || _value < (__float)other - EPSILON);
}

_bool Float::operator <(double other) const
{
   return (_value < (__float)other);
}

_bool Float::operator >(double other) const
{
   return (_value > (__float)other);
}

_bool Float::operator <=(double other) const
{
   return (_value <= (__float)other + EPSILON);
}

_bool Float::operator >=(double other) const
{
   return ( _value >= (__float)other - EPSILON);
}
#endif


void Float::operator +=(const Float &other)
{
   checkOverflow(_value + other._value);
}

void Float::operator -=(const Float &other)
{
   checkOverflow(_value - other._value);
}

void Float::operator *=(const Float &other)
{
   checkOverflow(_value * other._value);
}

void Float::operator /=(const Float &other)
{
   checkOverflow(_value / other._value);
}

void Float::operator %=(const Float &other)
{
   checkOverflow(fmod(_value, other._value));
}
   

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
void Float::operator +=(_float other)
{
   checkOverflow(_value + (__float)other);
}
   
void Float::operator -=(_float other)
{
   checkOverflow(_value - (__float)other);
}
   
void Float::operator *=(_float other)
{
   checkOverflow(_value * (__float)other);
}
   
void Float::operator /=(_float other)
{
   checkOverflow(_value / (__float)other);
}
   
void Float::operator %=(_float other)
{
   checkOverflow(fmod(_value, (__float)other));
}
#endif


#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
void Float::operator +=(double other)
{
   checkOverflow(_value + (__float)other);
}
   
void Float::operator -=(double other)
{
   checkOverflow(_value - (__float)other);
}
   
void Float::operator *=(double other)
{
   checkOverflow(_value * (__float)other);
}
   
void Float::operator /=(double other)
{
   checkOverflow(_value / (__float)other);
}
   
void Float::operator %=(double other)
{
   checkOverflow(fmod(_value, (__float)other));
}
#endif
   

void Float::operator ++(int)
{
   checkOverflow(_value + 1.0);
}
   
void Float::operator ++()
{
   checkOverflow(_value + 1.0);
}

void Float::operator --(int)
{
   checkOverflow(_value - 1.0);
}
   
void Float::operator --()
{
   checkOverflow(_value - 1.0);
}
   
const Float Float::operator -() const
{
   Float result;
   result.checkOverflow(-_value);
   return result;
}
   
   
const Float Float::operator +(const Float &other) const
{
   Float result = *this;
   result += other;
   return result;
}

const Float Float::operator -(const Float &other) const
{
   Float result = *this;
   result -= other;
   return result;
}

const Float Float::operator *(const Float &other) const
{
   Float result = *this;
   result *= other;
   return result;
}

const Float Float::operator /(const Float &other) const
{
   Float result = *this;
   result /= other;
   return result;
}

const Float Float::operator %(const Float &other) const
{
   Float result = *this;
   result %= other;
   return result;
}
   
#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
const Float Float::operator +(_float other) const
{
   Float result = *this;
   result += other;
   return result;
}
   
const Float Float::operator -(_float other) const
{
   Float result = *this;
   result -= other;
   return result;
}
   
const Float Float::operator *(_float other) const
{
   Float result = *this;
   result *= other;
   return result;
}
   
const Float Float::operator /(_float other) const
{
   Float result = *this;
   result /= other;
   return result;
}
   
const Float Float::operator %(_float other) const
{
   Float result = *this;
   result %= other;
   return result;
}
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
const Float Float::operator +(double other) const
{
   Float result = *this;
   result += other;
   return result;
}
   
const Float Float::operator -(double other) const
{
   Float result = *this;
   result -= other;
   return result;
}
   
const Float Float::operator *(double other) const
{
   Float result = *this;
   result *= other;
   return result;
}

const Float Float::operator /(double other) const
{
   Float result = *this;
   result /= other;
   return result;
}
   
const Float Float::operator %(double other) const
{
   Float result = *this;
   result %= other;
   return result;
}
#endif


__float Float::raw() const
{
   return _value;
}

void Float::setRaw(__float value)
{
   checkOverflow(value);
}

void Float::checkOverflow(__float value)
{
   switch(fpclassify(value))
   {
      default:
      case FP_INFINITE:
      case FP_NAN:
         ERROR(Error::Arithmetic::Overflow);
         break;
      
      case FP_ZERO:      
      case FP_SUBNORMAL:
         _value = 0.0;
         break;
         
      case FP_NORMAL:
         __float positive = value < 0 ? -value : value;
         if(positive < MIN || positive > MAX)
            ERROR(Error::Arithmetic::Overflow);
            
         _value = value;
         break;
  }
}

} } }

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
_bool operator ==(_float a, const Storage::Structure::Data::Float &b)
{
   return (Float(a) == b);
}

_bool operator !=(_float a, const Storage::Structure::Data::Float &b)
{
   return (Float(a) != b);
}

_bool operator <(_float a, const Storage::Structure::Data::Float &b)
{
   return (Float(a) < b);
}

_bool operator >(_float a, const Storage::Structure::Data::Float &b)
{
   return (Float(a) > b);
}

_bool operator <=(_float a, const Storage::Structure::Data::Float &b)
{
   return (Float(a) <= b);
}

_bool operator >=(_float a, const Storage::Structure::Data::Float &b)
{
   return (Float(a) >= b);
}
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
_bool operator ==(double a, const Storage::Structure::Data::Float &b)
{
   return (Float(a) == b);
}

_bool operator !=(double a, const Storage::Structure::Data::Float &b)
{
   return (Float(a) != b);
}

_bool operator <(double a, const Storage::Structure::Data::Float &b)
{
   return (Float(a) < b);
}

_bool operator >(double a, const Storage::Structure::Data::Float &b)
{
   return (Float(a) > b);
}

_bool operator <=(double a, const Storage::Structure::Data::Float &b)
{
   return (Float(a) <= b);
}

_bool operator >=(double a, const Storage::Structure::Data::Float &b)
{
   return (Float(a) >= b);
}
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_STATIC
const Storage::Structure::Data::Float operator +(_float a, const Storage::Structure::Data::Float &b)
{
   Float result = a;
   result += b;
   return result;
}

const Storage::Structure::Data::Float operator -(_float a, const Storage::Structure::Data::Float &b)
{
   Float result = a;
   result -= b;
   return result;
}

const Storage::Structure::Data::Float operator *(_float a, const Storage::Structure::Data::Float &b)
{
   Float result = a;
   result *= b;
   return result;
}

const Storage::Structure::Data::Float operator /(_float a, const Storage::Structure::Data::Float &b)
{
   Float result = a;
   result /= b;
   return result;
}

const Storage::Structure::Data::Float operator %(_float a, const Storage::Structure::Data::Float &b)
{
   Float result = a;
   result %= b;
   return result;
}
#endif

#ifndef __HELIO_TYPE_FLOAT_IS_NATIVE
const Storage::Structure::Data::Float operator +(double a, const Storage::Structure::Data::Float &b)
{
   Float result = a;
   result += b;
   return result;
}

const Storage::Structure::Data::Float operator -(double a, const Storage::Structure::Data::Float &b)
{
   Float result = a;
   result -= b;
   return result;
}

const Storage::Structure::Data::Float operator *(double a, const Storage::Structure::Data::Float &b)
{
   Float result = a;
   result *= b;
   return result;
}

const Storage::Structure::Data::Float operator /(double a, const Storage::Structure::Data::Float &b)
{
   Float result = a;
   result /= b;
   return result;
}

const Storage::Structure::Data::Float operator %(double a, const Storage::Structure::Data::Float &b)
{
   Float result = a;
   result %= b;
   return result;
}
#endif

