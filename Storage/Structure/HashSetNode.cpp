/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {

template <class T> HashSetNode<T>::HashSetNode(T *el)
{
   element = el;
   next = null;
}

} }

