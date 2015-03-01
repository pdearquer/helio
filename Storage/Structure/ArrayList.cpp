/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {

template <class T> ArrayList<T>::ArrayList()
{
}

template <class T> ArrayList<T>::ArrayList(_bool owner)
{
   this->setOwnership(owner);
}

template <class T> ArrayList<T>::~ArrayList()
{
   if(this->ownership())
   {
      for(_int i = 0; i < this->_count; i++)
         if(this->_elements[i] != null)
            delete this->_elements[i];
   }
}
   

template <class T> _int ArrayList<T>::count() const
{
   return this->_count;
}
   
template <class T> void ArrayList<T>::setCount(_int num, _bool deleting)
{
   this->modified();

   if(num < 0 || num > this->_count)
   {
      MAKE_ERROR(ex, Error::Structure::InvalidLength);
      ex->addInt("new", num);
      ex->addInt("count", this->_count);
      throw ex;
   }
   
   if(deleting)
   {
      for(_int i = num; i < this->_count; i++)
         if(this->_elements[i] != null)
            delete this->_elements[i];
   }
   
   this->_count = num;
}

template <class T> _int ArrayList<T>::add(T *el)
{
   this->modified();

   return this->appendElement(el);
}
   
template <class T> void ArrayList<T>::set(_int index, T *el, _bool deleting)
{
   this->modified();

   if(index < 0 || index >= this->_count)
   {
      MAKE_ERROR(ex, Error::Structure::OutOfBounds);
      ex->addInt("index", index);
      ex->addInt("count", this->_count);
      throw ex;
   }
   
   if(deleting)
   {
      if(this->_elements[index] != null && this->_elements[index] != el)
         delete this->_elements[index];
   }
   
   this->_elements[index] = el;
}
      
template <class T> T *ArrayList<T>::get(_int index) const
{
   if(index < 0 || index >= this->_count)
   {
      MAKE_ERROR(ex, Error::Structure::OutOfBounds);
      ex->addInt("index", index);
      ex->addInt("count", this->_count);
      throw ex;
   }
   
   return this->_elements[index];
}

template <class T> void ArrayList<T>::erase(_int start, _int end, _bool deleting)
{
   this->modified();

   if(0 > start || start > end || end >= this->_count)
   {
      MAKE_ERROR(ex, Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("end", end);
      ex->addInt("count", this->_count);
      throw ex;
   }
   
   if(deleting)
   {
      for(_int i = start; i <= end; i++)
         if(this->_elements[i] != null)
            delete this->_elements[i];
   }

   this->eraseElements(start, end);
}

template <class T> void ArrayList<T>::push(T *el)
{
   this->modified();

   add(el);
}
   
template <class T> T *ArrayList<T>::pop()
{
   this->modified();

   _int c = count();
   if(c == 0)
      THROW_ERROR(Error::Structure::Empty);
      
   T *el = get(c - 1);
   setCount(c - 1, false);   
   return el;
}
   
template <class T> T *ArrayList<T>::peek() const
{
   _int c = count();
   if(c == 0)
      THROW_ERROR(Error::Structure::Empty);
      
   return get(c - 1);
}

   
template <class T> DynIterator<T> *ArrayList<T>::dynIterate()
{
   return new ArrayListIterator<T>(this);
}


/* Container member implemented here due to a dependency conflict. */
template <class T> List<T> *Container<T>::asList() const
{
   List<T> *list = new ArrayList<T>(false);
   
   for(T *el : this)
      list->add(el);
   
   return list;
}

} }

