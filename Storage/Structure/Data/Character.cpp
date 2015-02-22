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
 * The internal type must be at least 32 bits long.
 */
__CHECK_TYPE(sizeof(__char) >= 32/8);

Character::Character()
{
   _value = 0;
}

Character::Character(const Character &other)
{
   _value = other._value;
}
   
Character::Character(const Character *other)
{
   _value = other->_value;
}

#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS)
Character::Character(_char value)
{
   setAscii(value);
}

#elif defined(__HELIO_TYPE_CHAR_IS_16BITS)
Character::Character(_char value)
{
   setUtf16(value);
}

#elif defined(__HELIO_TYPE_CHAR_IS_32BITS)
Character::Character(_char value)
{
   setUtf32(value);
}
#endif
#endif
   
#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
Character::Character(char value)
{
   setAscii(value);
}
#endif

#ifndef __HELIO_TYPE_CHAR_IS_INTERNAL
Character::Character(__char value)
{
   _value = value;
}
#endif


Character Character::get() const
{
   Character copy;
   copy._value = _value;
   return copy;
}

void Character::set(const Character &other)
{
   _value = other._value;
}


_bool Character::isValid(__char utf32)
{
   if(utf32 >= 0xD800 && utf32 <= 0xDFFF)
      return false;
      
   if(utf32 > 0x10FFFF)
      return false;
      
   return true;
}
   
_uint8 Character::getAscii() const
{
   if(!Storage::Structure::Binary::Encodings::ASCII::isValid(_value))
   {
      Exception *ex = MAKE_ERROR(Exception::Format::InvalidCharacter);
      ex->add("encoding", "ASCII");
      ex->addUInt32("character", _value);
      throw ex;
   }
      
   return (_uint8) _value;
}

void Character::setAscii(_uint8 ascii)
{
#ifdef __HELIO_STORAGE_STRUCTURE_BINARY_ENCODINGS_ASCII
   if(!Storage::Structure::Binary::Encodings::ASCII::isValid(ascii))
   {
      Exception *ex = MAKE_ERROR(Exception::Format::InvalidByte);
      ex->add("encoding", "ASCII");
      ex->addByte("byte", ascii);
      throw ex;
   }
#endif
   _value = (_uint32) ascii;
}

_uint16 Character::getUtf16() const
{
   if(_value > __HELIO_TYPE_UINT16_MAX)
   {
      Exception *ex = MAKE_ERROR(Exception::Format::InvalidCharacter);
      ex->add("encoding", "UTF-16");
      ex->addUInt32("character", _value);
      throw ex;
   }
      
   return (_uint16) _value;
}
   
void Character::setUtf16(_uint16 utf16)
{
   setUtf32((_uint32)utf16);
}

_uint32 Character::getUtf32() const
{
   return _value;
}
   
void Character::setUtf32(_uint32 utf32)
{
   if(!isValid(utf32))
   {
      Exception *ex = MAKE_ERROR(Exception::Format::InvalidCharacter);
      ex->addUInt32("code", utf32);
      throw ex;
   }
   
   _value = utf32;
}


_bool Character::isLowerCase() const
{
   return ((_value >= 'a') && (_value <= 'z'));
}
   
_bool Character::isUpperCase() const
{
   return ((_value >= 'A') && (_value <= 'Z'));
}
   
Character Character::toLowerCase() const
{
   Character ch;
   if(isUpperCase())
      ch._value = _value + ('a' - 'A');
   else
      ch._value = _value;
   return ch;
}
   
Character Character::toUpperCase() const
{
   Character ch;
   if(isLowerCase())
      ch._value = _value - ('a' - 'A');
   else
      ch._value = _value;
   return ch;
}
   
   
_int Character::compare(const Character *other) const
{
   return compare(*other, false);
}

_int Character::compare(const Character &other, _bool igncase) const
{
   if(!igncase)
   {
      if(_value == other._value)
         return 0;
      if(_value < other._value)
         return -1;
      return +1;
   }
   else
   {
      Character c1 = this->toLowerCase();
      Character c2 = other.toLowerCase();
      if(c1 == c2)
         return 0;
      if(c1 < c2)
         return -1;
      return +1;
   }
}

#ifndef __HELIO_TYPE_CHAR_IS_STATIC
_int Character::compare(_char other, _bool igncase) const
{
   return compare(Character(other), igncase);
}
#endif

_bool Character::equals(const Character *other) const
{
   return equals(*other, false);
}

_bool Character::equals(const Character &other, _bool igncase) const
{
   if(!igncase)
   {
      return (_value == other._value);
   }
   else
   {  
      Character c1 = this->toLowerCase();
      Character c2 = other.toLowerCase();
      return (c1 == c2);
   }
}

#ifndef __HELIO_TYPE_CHAR_IS_STATIC
_bool Character::equals(_char other, _bool igncase) const
{
   return equals(Character(other), igncase);
}
#endif

Character *Character::clone() const
{
   return new Character(this);
}

_uint32 Character::makeHash() const
{
   return (_uint32)_value;
}


String Character::toString() const
{
   return String(*this);
}


#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS)
Character::operator _char() const
{
   return getAscii();
}

#elif defined(__HELIO_TYPE_CHAR_IS_16BITS)
Character::operator _char() const
{
   return getUtf16();
}

#elif defined(__HELIO_TYPE_CHAR_IS_32BITS)
Character::operator _char() const
{
   return getUtf32();
}
#endif
#endif
   
#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
Character::operator char() const
{
   return getAscii();
}
#endif

#ifndef __HELIO_TYPE_CHAR_IS_INTERNAL
Character::operator __char() const
{
   return _value;
}
#endif


void Character::operator =(const Character &other)
{
   _value = other._value;   
}

#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS)
void Character::operator =(_char other)
{
   setAscii(other);
}

#elif defined(__HELIO_TYPE_CHAR_IS_16BITS)
void Character::operator =(_char other)
{
   setUtf16(other);
}

#elif defined(__HELIO_TYPE_CHAR_IS_32BITS)
void Character::operator =(_char other)
{
   setUtf32(other);
}
#endif
#endif
   
#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
void Character::operator =(char other)
{
   setAscii(other);
}
#endif

#ifndef __HELIO_TYPE_CHAR_IS_INTERNAL
void Character::operator =(__char other)
{
   _value = other;
}
#endif


_bool Character::operator ==(const Character &other) const
{
   return (_value == other._value);
}

_bool Character::operator !=(const Character &other) const
{
   return (_value != other._value);
}

_bool Character::operator <(const Character &other) const
{
   return (_value < other._value);
}

_bool Character::operator >(const Character &other) const
{
   return (_value > other._value);
}

_bool Character::operator <=(const Character &other) const
{
   return (_value <= other._value);
}

_bool Character::operator >=(const Character &other) const
{
   return (_value >= other._value);
}


#ifndef __HELIO_TYPE_CHAR_IS_STATIC
#if defined(__HELIO_TYPE_CHAR_IS_8BITS) || defined(__HELIO_TYPE_CHAR_IS_16BITS) || defined(__HELIO_TYPE_CHAR_IS_32BITS)
_bool Character::operator ==(_char c) const
{
   // No validation is done for comparisons
   return (_value == (__char) c);
}

_bool Character::operator !=(_char c) const
{
   // No validation is done for comparisons
   return (_value != (__char) c);
}

_bool Character::operator <(_char c) const
{
   // No validation is done for comparisons
   return (_value < (__char) c);
}

_bool Character::operator >(_char c) const
{
   // No validation is done for comparisons
   return (_value > (__char) c);
}

_bool Character::operator <=(_char c) const
{
   // No validation is done for comparisons
   return (_value <= (__char) c);
}

_bool Character::operator >=(_char c) const
{
   // No validation is done for comparisons
   return (_value >= (__char) c);
}
#endif
#endif
   
#ifndef __HELIO_TYPE_CHAR_IS_NATIVE
_bool Character::operator ==(char c) const
{
   // No validation is done for comparisons
   return (_value == (__char) c);
}

_bool Character::operator !=(char c) const
{
   // No validation is done for comparisons
   return (_value != (__char) c);
}

_bool Character::operator <(char c) const
{
   // No validation is done for comparisons
   return (_value < (__char) c);
}

_bool Character::operator >(char c) const
{
   // No validation is done for comparisons
   return (_value > (__char) c);
}

_bool Character::operator <=(char c) const
{
   // No validation is done for comparisons
   return (_value <= (__char) c);
}

_bool Character::operator >=(char c) const
{
   // No validation is done for comparisons
   return (_value >= (__char) c);
}
#endif

} } }

