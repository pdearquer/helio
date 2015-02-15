/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {

template <class T> _bool Set<T>::add(T *el)
{
   this->modified();

   return add(el, this->ownership());
}

} }

