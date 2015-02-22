/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {

template <class T> Iterator<T>::Iterator()
{
   _it = null;
}

template <class T> Iterator<T>::Iterator(DynIterator<T> *it)
{
   _it = it;   
   _it->incrementRef();
}
   
template <class T> Iterator<T>::Iterator(const Iterator<T> &other)
{
   _it = other._it;
   if(_it != null)
      _it->incrementRef();
}
   
template <class T> Iterator<T>::~Iterator()
{
   if(_it != null && _it->decrementRef() == 0)
      delete _it;
}
   
   
template <class T> const Iterator<T> &Iterator<T>::operator=(const Iterator<T> &other)
{
   if(_it != null && _it->decrementRef() == 0)
      delete _it;
   
   _it = other._it;
   if(_it != null)
      _it->incrementRef();
   return *this;
}


template <class T> DynIterator<T> *Iterator<T>::dynIter() const
{
   return _it;
}
   
   
template <class T> _bool Iterator<T>::hasMore() const
{
   return _it->hasMore();
}
   
template <class T> T *Iterator<T>::get()
{
   return _it->get();
}
   
template <class T> T *Iterator<T>::next()
{
   return _it->next();
}
     
template <class T> _bool Iterator<T>::operator!=(const Iterator<T> &otro) const
{
   if(otro._it != null)
   {
      Exception *ex = MAKE_ERROR(Exception::NotSupported);
      ex->add("reason", "Only end iterator supported for comparison");
      throw ex;
   }
   
   return _it->hasMore();
}
   
template <class T> T *Iterator<T>::operator*()
{
   return _it->get();
}
   
template <class T> const Iterator<T> &Iterator<T>::operator++()
{
   _it->next();
   return *this;
}


template <class T> Iterator<T> Iterator<T>::makeEnd()
{
   return Iterator<T>();
}

} }

