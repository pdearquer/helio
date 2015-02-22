/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Data {

Object::Object()
{
}

Object::~Object()
{
}

_bool Object::equals(const Object *other) const
{
   if(other == null)
      return false;
      
   return (this == other);   
}

String Object::toString() const
{
   return getClass() + "(" + Format::def()->toString((_pointer) this) + ")";
}

String Object::getClass() const
{
   try
   {
      return (String) typeid(*this).name();
   }
   catch(std::bad_typeid &e)
   {
      Error *ex = MAKE_ERROR(Error::IllegalClass);
      ex->addPointer("object", this);
      throw ex;
   }
}

} } }

