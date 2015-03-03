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
   return getClass() + "[" + (_pointer)this + "]";
}

String Object::getClass() const
{
   const char *name;
   try
   {
      name = typeid(*this).name();
   }
   catch(std::bad_typeid &e)
   {
      MAKE_ERROR(ex, Error::IllegalClass);
      ex->addPointer("object", this);
      throw ex;
   }
#ifdef __HELIO_COMPONENT_ERROR_TRACE
   return Component::Error::Trace::demangleSymbol(name);
#else
   return (String)name;
#endif
}

} } }

