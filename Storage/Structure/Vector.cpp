/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

#include <Helio.h>

namespace Storage {
namespace Structure {

template <class T> Vector<T>::Vector()
{
   this->_count = 0;
   this->_size = 10;
   this->_elements = new T[_size];
}

template <class T> Vector<T>::Vector(_int capacity)
{
   if(capacity <= 0)
   {
      MAKE_ERROR(ex, Error::Structure::IllegalCapacity);
      ex->addInt("capacity", capacity);
      throw ex;
   }
   
   this->_count = 0;
   this->_size = capacity;
   this->_elements = new T[_size];
}

template <class T> Vector<T>::Vector(const Vector<T> &other)
{
   this->_count = other._count;
   this->_size = _count;
   if(this->_size < 10)
      this->_size = 10;
   this->_elements = new T[this->_size];
   
   for(_int i = 0; i < this->_count; i++)
      this->_elements[i] = other._elements[i];
}

template <class T> Vector<T>::~Vector()
{
   delete[] this->_elements;
}


template <class T> _int Vector<T>::count() const
{
   return this->_count;
}

template <class T> void Vector<T>::setCount(_int num)
{
   if(num < 0)
   {
      MAKE_ERROR(ex, Error::Structure::InvalidLength);
      ex->addInt("count", num);
      throw ex;
   }
      
   if(num > this->_count)
   {
      MAKE_ERROR(ex, Error::Structure::InvalidLength);
      ex->addInt("count", num);
      ex->addInt("current", this->_count);
      throw ex;
   }
      
   this->_count = num;
}

template <class T> _bool Vector<T>::isEmpty() const
{
   return (this->_count == 0);
}


template <class T> _int Vector<T>::add(T obj)
{
   this->ensureSize(this->_count + 1);
   
   this->_elements[this->_count] = obj;
   
   _int index = this->_count;
   this->_count++;
   return index;
}

template <class T> void Vector<T>::set(_int index, T obj)
{
   if(index < 0 || index >= this->_count)
   {
      MAKE_ERROR(ex, Error::Structure::OutOfBounds);
      ex->addInt("index", index);
      ex->addInt("count", this->_count);
      throw ex;
   }
   
   this->_elements[index] = obj;
}

template <class T> T Vector<T>::get(_int index) const
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

template <class T> T &Vector<T>::operator [](const _int index)
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


template <class T> T Vector<T>::push(T obj)
{
   this->add(obj);
   return obj;
}
   
template <class T> T Vector<T>::pop()
{
   if(this->_count <= 0)
      THROW_ERROR(Error::Structure::Empty);
   
   T obj = this->_elements[this->_count - 1];
   this->_count--;
   return obj;
}
   
template <class T> T Vector<T>::peek() const
{
   if(this->_count <= 0)
      THROW_ERROR(Error::Structure::Empty);
   
   return this->_elements[this->_count - 1];
}


template <class T> _bool Vector<T>::contains(T obj) const
{
   return (this->indexOf(obj) != -1);
}

template <class T> _bool Vector<T>::remove(_int index)
{
   if(index < 0 || index >= this->_count)
   {
      MAKE_ERROR(ex, Error::Structure::OutOfBounds);
      ex->addInt("index", index);
      ex->addInt("count", this->_count);
      throw ex;
   }
      
   for(_int next = index + 1; next < this->_count; next++)
      this->_elements[next - 1] = this->_elements[next];
   this->_count--;
   return true;
}

template <class T> void Vector<T>::clear()
{
   delete[] this->_elements;
   
   this->_count = 0;
   this->_size = 10;
   this->_elements = new T[this->_size];
}


template <class T> _int Vector<T>::indexOf(T obj) const
{
   for(_int i = 0; i < this->_count; i++)
   {
      if(this->_elements[i] == obj)
         return i;
   }
   
   return -1;
}

template <class T> _int Vector<T>::indexOf(T obj, _int start) const
{
   if(start < 0 || start >= this->_count)
   {
      MAKE_ERROR(ex, Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("count", this->_count);
      throw ex;
   }
      
   for(_int i = start; i < _count; i++)
   {
      if(this->_elements[i] == obj)
         return i;
   }
   
   return -1;
}


template <class T> _bool Vector<T>::equals(const Vector<T> &other) const
{
   if(this->_count != other._count)
      return false;
      
   for(_int i = 0; i < this->_count; i++)
      if(!(this->_elements[i] == other._elements[i]))
         return false;
         
   return true;
}


template <class T> String Vector<T>::toString() const
{
   StringBuffer ret = "{ ";

   for(_int i = 0; i < this->_count; i++)
   {
      ret.add(this->_elements[i]);
      ret.add(" ");
   }

   return ret + "}";
}


template <class T> void Vector<T>::ensureSize(_int min)
{
   if(min <= this->_size)
      return;

   _int size2 = this->_size;
   if(size2 == 0)
      size2 = min;
      
   while(size2 < min)
   {
      if(size2 < 256)
         size2 = size2 * 2;
      else
         size2 += 256;
   }
   
   T *elements2 = new T[size2];
   for(_int i = 0; i < this->_count; i++)
      elements2[i] =this-> _elements[i];
   delete[] this->_elements;
   
   this->_elements = elements2;
   this->_size = size2;
}

} }

