/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

#include <Helio.h>

namespace Storage {
namespace Structure {

template <class T> Iterator<T> Iterable<T>::iterate()
{
   return Iterator<T>(this->dynIterate());
}


template<class T> Iterator<T> begin(const Iterable<T> *cont)
{
   return const_cast<Iterable<T> *>(cont)->iterate();
}

template<class T> Iterator<T> end(const Iterable<T> *cont)
{
   return Iterator<T>::makeEnd();
}

}
}
