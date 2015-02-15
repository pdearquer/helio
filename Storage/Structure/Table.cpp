/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {

template <class K, class T> Table<K, T>::Table()
{
   _length = 0;
   _size = 10;
   _keys = new K[_size];
   _values = new T[_size];
}

template <class K, class T> Table<K, T>::Table(_int capacity)
{
   if(capacity <= 0)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.BadCapacity");
      ex->addInt("capacity", capacity);
      throw ex;
   }
   
   _length = 0;
   _size = capacity;
   _keys = new K[_size];
   _values = new T[_size];
}

template <class K, class T> Table<K, T>::Table(const Table<K, T> &other)
{
   _length = other._length;
   _size = _length;
   if(_size < 10)
      _size = 10;
   _keys = new K[_size];
   _values = new T[_size];
   
   for(_int i = 0; i < _length; i++)
   {
      _keys[i] = other._keys[i];
      _values[i] = other._values[i];
   }
}

template <class K, class T> Table<K, T>::~Table()
{
   delete[] _keys;
   delete[] _values;
}


template <class K, class T> _int Table<K, T>::count() const
{
   return _length;
}

template <class K, class T> _bool Table<K, T>::empty() const
{
   return (_length == 0);
}


template <class K, class T> _bool Table<K, T>::add(K key, T value)
{
   for(_int i = 0; i < _length; i++)
      if(_keys[i] == key)
      {
         _values[i] = value;
         return true;
      }

   // Add a new pair
   ensureSize(_length + 1);
   
   _keys[_length] = key;
   _values[_length] = value;
   _length++;
   
   return false;
}

template <class K, class T> void Table<K, T>::set(K key, T value)
{
   for(_int i = 0; i < _length; i++)
      if(_keys[i] == key)
      {
         _values[i] = value;
         return;
      }
      
   Exception *ex = MAKE_ERROR("Storage.Structure.KeyNotFound");
   //ex->add("key", key);
   throw ex;
}

template <class K, class T> T Table<K, T>::get(K key) const
{
   for(_int i = 0; i < _length; i++)
      if(_keys[i] == key)
         return _values[i];
      
   Exception *ex = MAKE_ERROR("Storage.Structure.KeyNotFound");
   //ex->add("key", key);
   throw ex;
}

template <class K, class T> T &Table<K, T>::operator [](const K key)
{
   for(_int i = 0; i < _length; i++)
      if(_keys[i] == key)
         return _values[i];
      
   Exception *ex = MAKE_ERROR("Storage.Structure.KeyNotFound");
   //ex->add("key", key);
   throw ex;
}


template <class K, class T> _bool Table<K, T>::contains(T value) const
{
   for(_int i = 0; i < _length; i++)
      if(_values[i] == _values)
         return true;
   return false;
}

template <class K, class T> _bool Table<K, T>::containsKey(K key) const
{
   for(_int i = 0; i < _length; i++)
      if(_keys[i] == key)
         return true;
   return false;
}

template <class K, class T> T Table<K, T>::remove(K key)
{
   _int index = 0;
   for(; index < _length; index++)
      if(_keys[index] == key)
         break;
   
   if(index >= _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.KeyNotFound");
      //ex->add("key", key);
      throw ex;
   }
      
   T ret = _values[index];
      
   for(_int next = index + 1; next < _length; next++)
   {
      _keys[next - 1] = _keys[next];
      _values[next - 1] = _values[next];
   }
   _length--;
   
   return ret;
}

template <class K, class T> void Table<K, T>::clear()
{
   delete[] _keys;
   delete[] _values;
   
   _length = 0;
   _size = 10;
   _keys = new K[_size];
   _values = new T[_size];
}


template <class K, class T> K Table<K, T>::keyOf(T value) const
{
   for(_int i = 0; i < _length; i++)
      if(_values[i] == value)
         return _keys[i];
      
   Exception *ex = MAKE_ERROR("Storage.Structure.ValueNotFound");
   //ex->add("value", value);
   throw ex;
}

template <class K, class T> K Table<K, T>::getKey(_int index) const
{
   if(index >= _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("index", index);
      ex->addInt("length", _length);
      throw ex;
   }
      
   return _keys[index];
}

template <class K, class T> T Table<K, T>::getValue(_int index) const
{
   if(index >= _length)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.OutOfBounds");
      ex->addInt("index", index);
      ex->addInt("length", _length);
      throw ex;
   }
      
   return _values[index];
}

template <class K, class T> _bool Table<K, T>::equals(const Table<K, T> &other) const
{
   if(_length != other._length)
      return false;
      
   for(_int i = 0; i < _length; i++)
   {
      if(!other.containsKey(_keys[i]))
         return false;
         
      if(other.get(_keys[i]) != _values[i])
         return false;
   }
   
   return true;
}


template <class K, class T> String Table<K, T>::toString() const
{
   StringBuffer ret = "{ ";

   for(_int i = 0; i < _length; i++)
   {
      ret.add((StringBuffer)_keys[i] + " = " + _values[i]);
      if(i < _length - 1)
         ret.add(", ");
   }

   return ret + "}";
}


template <class K, class T> void Table<K, T>::ensureSize(_int min)
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
   
   K *keys2 = new K[size2];
   T *values2 = new T[size2];
   for(_int i = 0; i < _length; i++)
   {
      keys2[i] = _keys[i];
      values2[i] = _values[i];
   }
   delete[] _keys;
   delete[] _values;
   
   _keys = keys2;
   _values = values2;
   _size = size2;
}

} }
