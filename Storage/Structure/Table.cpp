/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {

template <class K, class V> Table<K, V>::Table()
{
   this->_count = 0;
   this->_size = 10;
   this->_keys = new K[this->_size];
   this->_values = new V[this->_size];
}

template <class K, class V> Table<K, V>::Table(_int capacity)
{
   if(capacity <= 0)
   {
      MAKE_ERROR(ex, Error::Structure::IllegalCapacity);
      ex->addInt("capacity", capacity);
      throw ex;
   }
   
   this->_count = 0;
   this->_size = capacity;
   this->_keys = new K[this->_size];
   this->_values = new V[this->_size];
}

template <class K, class V> Table<K, V>::Table(const Table<K, V> &other)
{
   this->_count = other._count;
   this->_size = this->_count;
   if(this->_size < 10)
      this->_size = 10;
   this->_keys = new K[this->_size];
   this->_values = new V[this->_size];
   
   for(_int i = 0; i < this->_count; i++)
   {
      this->_keys[i] = other._keys[i];
      this->_values[i] = other._values[i];
   }
}

template <class K, class V> Table<K, V>::~Table()
{
   delete[] this->_keys;
   delete[] this->_values;
}


template <class K, class V> _int Table<K, V>::count() const
{
   return this->_count;
}

template <class K, class V> _bool Table<K, V>::isEmpty() const
{
   return (this->_count == 0);
}


template <class K, class V> _bool Table<K, V>::add(K key, V value)
{
   for(_int i = 0; i < this->_count; i++)
      if(this->_keys[i] == key)
      {
         this->_values[i] = value;
         return true;
      }

   // Add a new pair
   ensureSize(this->_count + 1);
   
   this->_keys[this->_count] = key;
   this->_values[this->_count] = value;
   this->_count++;
   
   return false;
}

template <class K, class V> void Table<K, V>::set(K key, V value)
{
   for(_int i = 0; i < this->_count; i++)
      if(this->_keys[i] == key)
      {
         this->_values[i] = value;
         return;
      }
      
   MAKE_ERROR(ex, Exception::Structure::KeyNotFound);
   //ex->add("key", key);
   throw ex;
}

template <class K, class V> V Table<K, V>::get(K key) const
{
   for(_int i = 0; i < this->_count; i++)
      if(this->_keys[i] == key)
         return this->_values[i];
      
   MAKE_ERROR(ex, Exception::Structure::KeyNotFound);
   //ex->add("key", key);
   throw ex;
}

template <class K, class V> V &Table<K, V>::operator [](const K key)
{
   for(_int i = 0; i < this->_count; i++)
      if(this->_keys[i] == key)
         return this->_values[i];
      
   MAKE_ERROR(ex, Exception::Structure::KeyNotFound);
   //ex->add("key", key);
   throw ex;
}


template <class K, class V> _bool Table<K, V>::contains(K key) const
{
   for(_int i = 0; i < this->_count; i++)
      if(this->_keys[i] == key)
         return true;
   return false;
}

template <class K, class V> _bool Table<K, V>::containsValue(V value) const
{
   for(_int i = 0; i < this->_count; i++)
      if(this->_values[i] == value)
         return true;
   return false;
}

template <class K, class V> _bool Table<K, V>::remove(K key)
{
   _int index = 0;
   for(; index < this->_count; index++)
      if(this->_keys[index] == key)
         break;
   
   if(index >= this->_count)
      return false;
      
   for(_int next = index + 1; next < this->_count; next++)
   {
      this->_keys[next - 1] = this->_keys[next];
      this->_values[next - 1] = this->_values[next];
   }
   this->_count--;
   
   return true;
}

template <class K, class V> void Table<K, V>::clear()
{
   delete[] this->_keys;
   delete[] this->_values;
   
   this->_count = 0;
   this->_size = 10;
   this->_keys = new K[this->_size];
   this->_values = new V[this->_size];
}


template <class K, class V> K Table<K, V>::keyOf(V value) const
{
   for(_int i = 0; i < this->_count; i++)
      if(this->_values[i] == value)
         return this->_keys[i];
      
   MAKE_ERROR(ex, Exception::Structure::ValueNotFound);
   //ex->add("value", value);
   throw ex;
}

template <class K, class V> K Table<K, V>::getKey(_int index) const
{
   if(index >= this->_count)
   {
      MAKE_ERROR(ex, Error::Structure::OutOfBounds);
      ex->addInt("index", index);
      ex->addInt("count", this->_count);
      throw ex;
   }
      
   return this->_keys[index];
}

template <class K, class V> V Table<K, V>::getValue(_int index) const
{
   if(index >= this->_count)
   {
      MAKE_ERROR(ex, Error::Structure::OutOfBounds);
      ex->addInt("index", index);
      ex->addInt("count", this->_count);
      throw ex;
   }
      
   return this->_values[index];
}

template <class K, class V> _bool Table<K, V>::equals(const Table<K, V> &other) const
{
   if(this->_count != other._count)
      return false;
      
   for(_int i = 0; i < this->_count; i++)
   {
      if(!other.contains(this->_keys[i]))
         return false;
         
      if(other.get(this->_keys[i]) != this->_values[i])
         return false;
   }
   
   return true;
}


template <class K, class V> String Table<K, V>::toString() const
{
   StringBuffer ret = "{ ";

   for(_int i = 0; i < this->_count; i++)
   {
      ret.add((StringBuffer)this->_keys[i] + " = " + this->_values[i]);
      if(i < _count - 1)
         ret.add(", ");
   }

   return ret + "}";
}


template <class K, class V> void Table<K, V>::ensureSize(_int min)
{
   if(min <= _size)
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
   
   K *keys2 = new K[size2];
   V *values2 = new V[size2];
   for(_int i = 0; i < _count; i++)
   {
      keys2[i] = this->_keys[i];
      values2[i] = this->_values[i];
   }
   delete[] this->_keys;
   delete[] this->_values;
   
   this->_keys = keys2;
   this->_values = values2;
   this->_size = size2;
}

} }

