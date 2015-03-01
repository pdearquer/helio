/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

#include <Helio.h>

namespace Storage {
namespace Structure {

template <class T> const_int LinkedQueueNode<T>::CAPACITY;


template <class T> LinkedQueueNode<T>::LinkedQueueNode()
{
   this->_count = 0;
}


template <class T> T *LinkedQueueNode<T>::front()
{
   if(this->_count <= 0)
      THROW_ERROR(Error::Structure::Empty);

   return this->_elements[0];
}

template <class T> _bool LinkedQueueNode<T>::add_front(T *el)
{
   if(this->_count >= this->CAPACITY)
      return false;

   for(_int i = this->_count - 1; i >= 0; i--)
      this->_elements[i + 1] = this->_elements[i];

   this->_elements[0] = el;
   this->_count++;
   return true;
}

template <class T> T *LinkedQueueNode<T>::dequeue()
{
   if(this->_count <= 0)
      THROW_ERROR(Error::Structure::Empty);

   T *el = this->_elements[0];

   this->_count--;
   for(_int i = 0; i < this->_count; i++)
      this->_elements[i] = this->_elements[i + 1];

   return el;
}

template <class T> T *LinkedQueueNode<T>::back()
{
   if(this->_count <= 0)
      THROW_ERROR(Error::Structure::Empty);

   return this->_elements[this->_count - 1];
}

template <class T> _bool LinkedQueueNode<T>::add(T *el)
{
   if(this->_count >= this->CAPACITY)
      return false;

   this->_elements[this->_count] = el;
   this->_count++;
   return true;
}

template <class T> T *LinkedQueueNode<T>::dequeue_back()
{
   if(this->_count <= 0)
      THROW_ERROR(Error::Structure::Empty);

   T *el = this->_elements[this->_count - 1];
   this->_count--;
   return el;
}


template <class T> void LinkedQueueNode<T>::erase(_int start, _int end, _bool deleting)
{
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

   _int ahead = this->_count - end - 1;
   for(_int i = 0; i < ahead; i++)
      this->_elements[start + i] = this->_elements[end + 1 + i];

   this->_count -= end - start + 1;
}

} }

