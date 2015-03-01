/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {

template <class T> ArraySet<T>::ArraySet()
{
}

template <class T> ArraySet<T>::ArraySet(_bool owner)
{
   this->setOwnership(owner);
}

template <class T> ArraySet<T>::~ArraySet()
{
   if(this->ownership())
   {
      for(_int i = 0; i < this->_count; i++)
         delete this->_elements[i];
   }
}


template <class T> _int ArraySet<T>::count() const
{
   return this->_count;
}

template <class T> _bool ArraySet<T>::add(T *el, _bool deleting)
{
   this->modified();

   if(el == null)
   {
      MAKE_ERROR(ex, Error::NullObject);
      ex->add("reason", "The Set containers do not allow null elements");
      throw ex;
   }
   
   for(_int i = 0; i < this->_count; i++)
   {
      if(el->equals(this->_elements[i]))
      {
         if(deleting)
            delete this->_elements[i];
         this->_elements[i] = el;
         return false;
      }
   }

   this->appendElement(el);
   return true;
}
   
template <class T> _bool ArraySet<T>::contains(T *el)
{
   for(_int i = 0; i < this->_count; i++)
   {
      if(el->equals(this->_elements[i]))
         return true;
   }
   return false;
}

template <class T> T *ArraySet<T>::get(T *el)
{
   for(_int i = 0; i < this->_count; i++)
   {
      if(el->equals(this->_elements[i]))
         return this->_elements[i];
   }
   return null;
}

template <class T> _bool ArraySet<T>::remove(T *el, _bool deleting)
{
   this->modified();

   for(_int i = 0; i < this->_count; i++)
   {
      if(el->equals(this->_elements[i]))
      {
         delete this->_elements[i];
         this->eraseElements(i, i);
         return true;
      }
   }
   return false;
}
   
template <class T> void ArraySet<T>::clear(_bool deleting)
{
   this->modified();

   if(deleting)
   {
      for(_int i = 0; i < this->_count; i++)
         delete this->_elements[i];
   }
   
   this->_count = 0;
}

   
template <class T> DynIterator<T> *ArraySet<T>::dynIterate()
{
   return new ArraySetIterator<T>(this);
}

} }

