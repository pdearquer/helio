/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {

template <class T> void List<T>::setCount(_int num)
{
   setCount(num, this->ownership());
}

template <class T> void List<T>::set(_int index, T *el)
{
   this->modified();

   set(index, el, this->ownership());
}

template <class T> _bool List<T>::contains(T *el)
{
   for(_int i = 0; i < this->count(); i++)
   {
      T *e = get(i);
      if(e == null && el == null)
         return true;
      if(e != null && el != null && el->equals(e))
         return true;
   }
   return false;
}

template <class T> _bool List<T>::remove(T *el, _bool deleting)
{
   this->modified();

   if(el == null)
      return true;

   for(_int i = 0; i < this->count(); i++)
   {
      T *e = get(i);
      if(e != null && el->equals(e))
         return remove(i, deleting);
   }
   return false;
}
     
template <class T> _bool List<T>::remove(_int index)
{
   this->modified();

   return remove(index, this->ownership());
}

template <class T> _bool List<T>::remove(_int index, _bool deleting)
{
   this->modified();

   set(index, null, deleting);
   return true;
}

template <class T> void List<T>::clear(_bool deleting)
{
   setCount(0, deleting);
}

template <class T> void List<T>::erase(_int start, _int end)
{
   return erase(start, end, this->ownership());
}

   
template <class T> _int List<T>::indexOf(T *el) const
{
   for(_int i = 0; i < this->count(); i++)
   {
      T *e = get(i);
      if(e == null && el == null)
         return i;
      if(e != null && el != null && el->equals(e))
         return i;
   }
   
   return -1;
}
   
template <class T> _int List<T>::indexOf(T *el, _int start) const
{
   _int length = this->count();
   
   if(start < 0 || start >= length)
   {
      MAKE_ERROR(ex, Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("count", length);
      throw ex;
   }
   
   for(_int i = start; i < length; i++)
   {
      T *e = get(i);
      if(e == null && el == null)
         return i;
      if(e != null && el != null && el->equals(e))
         return i;
   }

   return -1;
}

} }

