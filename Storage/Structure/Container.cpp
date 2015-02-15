/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {

template <class T> Container<T>::Container()
{
   this->_ownership = true;
   this->_version = 0;
}


template <class T> _bool Container<T>::ownership()
{
   return this->_ownership;
}

template <class T> void Container<T>::setOwnership(_bool owner)
{
   this->_ownership = owner;
}

template <class T> void Container<T>::modified()
{
   this->_version++;
}

template <class T> _int Container<T>::version() const
{
   return this->_version;
}


template <class T> _bool Container<T>::isEmpty() const
{
   return (this->count() == 0);
}

template <class T> _bool Container<T>::contains(T *el)
{
   for(T *e : this)
      if(el->equals(e))
         return true;
   return false;
}

template <class T> _bool Container<T>::remove(T *el)
{
   this->modified();

   return this->remove(el, ownership());
}
   
template <class T> void Container<T>::clear()
{
   this->modified();

   this->clear(ownership());
}


//template <class T> List<T> *Container<T>::asList() const
/* Implemented in ArrayList.cpp due to a dependency conflict. */

template <class T> String Container<T>::toString() const
{
   StringBuffer ret = "{ ";
   for(T *el : this)
      ret += el->toString() + " ";   
   ret += "}";   
   return ret;
}

} }

