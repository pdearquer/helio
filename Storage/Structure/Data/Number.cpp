/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Data {

_bool Number::equals(const Number *other) const
{
   return (compare(other) == 0);
}

_int Number::compare(const Number *other) const
{
   if(other == null)
      THROW_ERROR(Error::NullObject);

   _float val = other->getFloat();
   _float me = getFloat();
   
   if(me == val)
      return 0;
   if(me < val)
      return -1;
   return +1;
}

} } }

