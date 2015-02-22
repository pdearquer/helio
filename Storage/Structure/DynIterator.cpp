/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {

template <class T> DynIterator<T>::DynIterator()
{
   this->_refs = 0;
   this->_version = 0;
}

template <class T> void DynIterator<T>::startVersion(Container<T> *container)
{
   this->_version = container->version();
}

template <class T> void DynIterator<T>::checkVersion(Container<T> *container) const
{
   if(this->_version != container->version())
      ERROR(Error::Structure::IteratorInvalidated);
}


template <class T> _int DynIterator<T>::incrementRef()
{
   this->_refs++;
   return this->_refs;
}
   
template <class T> _int DynIterator<T>::decrementRef()
{   
   this->_refs--;
   return this->_refs;
}

} }

