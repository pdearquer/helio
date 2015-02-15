/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

#include <Helio.h>

namespace Storage {
namespace Structure {

template <class T> Vector<T>::Vector()
{
   _length = 0;
   _size = 10;
   _elements = new T[_size];
}

template <class T> Vector<T>::Vector(_int capacity)
{
   if(capacity <= 0)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.BadCapacity");
      ex->addInt("capacity", capacity);
      throw ex;
   }
   
   _length = 0;
   _size = capacity;
   _elements = new T[_size];
}

template <class T> Vector<T>::Vector(const Vector<T> &other)
{
   _length = other._length;
   _size = _length;
   if(_size < 10)
      _size = 10;
   _elements = new T[_size];
   
   for(_int i = 0; i < _length; i++)
      _elements[i] = other._elements[i];
}

template <class T> Vector<T>::~Vector()
{
   delete[] _elements;
}


template <class T> _int Vector<T>::count() const
{
   return _length;
}

template <class T> _int Vector<T>::count(_int len)
{
   if(len < 0)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.InvalidLength");
      ex->addInt("length", len);
      throw ex;
   }
      
   if(len > _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.InvalidLength");
      ex->addInt("length", len);
      ex->addInt("current", _length);
      throw ex;
   }
      
   _length = len;
   return _length;
}

template <class T> _bool Vector<T>::empty() const
{
   return (_length == 0);
}


template <class T> _int Vector<T>::add(T obj)
{
   ensureSize(_length + 1);
   
   _elements[_length] = obj;
   
   _int index = _length;
   _length++;
   return index;
}

template <class T> void Vector<T>::set(_int index, T obj)
{
   if(index < 0 || index >= _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("index", index);
      ex->addInt("length", _length);
      throw ex;
   }
   
   _elements[index] = obj;
}

template <class T> T Vector<T>::get(_int index) const
{
   if(index < 0 || index >= _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("index", index);
      ex->addInt("length", _length);
      throw ex;
   }
   
   return _elements[index];
}

template <class T> T &Vector<T>::operator [](const _int index)
{
   if(index < 0 || index >= _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("index", index);
      ex->addInt("length", _length);
      throw ex;
   }
   
   return _elements[index];
}


template <class T> T Vector<T>::push(T obj)
{
   add(obj);
   return obj;
}
   
template <class T> T Vector<T>::pop()
{
   if(_length <= 0)
      ERROR("Storage.Structure.Empty");
   
   T obj = _elements[_length - 1];
   _length--;
   return obj;
}
   
template <class T> T Vector<T>::poll()
{
   if(_length <= 0)
      ERROR("Storage.Structure.Empty");
   
   T obj = _elements[0];
   for(_int i = 0; i < _length - 1; i++)
   {
      _elements[i] = _elements[i + 1];
   }
   _length--;
   return obj;
}
   
template <class T> T Vector<T>::peek() const
{
   if(_length <= 0)
      ERROR("Storage.Structure.Empty");
   
   return _elements[_length - 1];
}
   
template <class T> T Vector<T>::front() const
{
   if(_length <= 0)
      ERROR("Storage.Structure.Empty");
   
   return _elements[0];
}


template <class T> _bool Vector<T>::contains(T obj) const
{
   return (indexOf(obj) != -1);
}

template <class T> void Vector<T>::remove(_int index)
{
   if(index < 0 || index >= _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("index", index);
      ex->addInt("length", _length);
      throw ex;
   }
      
   for(_int next = index + 1; next < _length; next++)
      _elements[next - 1] = _elements[next];
   _length--;
}

template <class T> void Vector<T>::clear()
{
   delete[] _elements;
   
   _length = 0;
   _size = 10;
   _elements = new T[_size];
}


template <class T> _int Vector<T>::indexOf(T obj) const
{
   for(_int i = 0; i < _length; i++)
   {
      if(_elements[i] == obj)
         return i;
   }
   
   return -1;
}

template <class T> _int Vector<T>::indexOf(T obj, _int start) const
{
   if(start < 0 || start >= _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("start", start);
      ex->addInt("length", _length);
      throw ex;
   }
      
   for(_int i = start; i < _length; i++)
   {
      if(_elements[i] == obj)
         return i;
   }
   
   return -1;
}


template <class T> _bool Vector<T>::equals(const Vector<T> &other) const
{
   if(_length != other._length)
      return false;
      
   for(_int i = 0; i < _length; i++)
      if(!(_elements[i] == other._elements[i]))
         return false;
         
   return true;
}


template <class T> String Vector<T>::toString() const
{
   StringBuffer ret = "{ ";

   for(_int i = 0; i < _length; i++)
   {
      ret.add(_elements[i]);
      ret.add(" ");
   }

   return ret + "}";
}


template <class T> void Vector<T>::ensureSize(_int min)
{
   if(min <= _size)
      return;

   _int size2 = _size;
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
   for(_int i = 0; i < _length; i++)
      elements2[i] = _elements[i];
   delete[] _elements;
   
   _elements = elements2;
   _size = size2;
}

} }

