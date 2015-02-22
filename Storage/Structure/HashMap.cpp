/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {

template<class K, class V> const_int HashMap<K, V>::INICIAL_CAPACITY;

template<class K, class V> const_float HashMap<K, V>::LOAD_FACTOR;


template<class K, class V> HashMap<K, V>::HashMap()
{
   _capacity = INICIAL_CAPACITY;
   _count = 0;
   
   _table = new HashMapNode<K, V>*[_capacity];
   for(_int i = 0; i < _capacity; i++)
      _table[i] = null;
}

template<class K, class V> HashMap<K, V>::HashMap(_bool owner)
{
   _capacity = INICIAL_CAPACITY;
   _count = 0;

   _table = new HashMapNode<K, V>*[_capacity];
   for(_int i = 0; i < _capacity; i++)
      _table[i] = null;
   
   this->setOwnership(owner);
}

template<class K, class V> HashMap<K, V>::~HashMap()
{
   clear();
   
   delete[] _table;
}


template<class K, class V> _int HashMap<K, V>::count() const
{
   return _count;
}

template<class K, class V> _bool HashMap<K, V>::add(K *key, V *value, _bool deleting)
{
   this->modified();

   if(key == null)
   {
      Error *ex = MAKE_ERROR(Error::NullObject);
      ex->add("reason", "This container do not allow null keys");
      throw ex;
   }

   // Worst case considered. Its better than make the growth later
   ensureCap(_count + 1);  

   _uint32 hash = key->makeHash();
   _int index = (_int)(hash % (_uint32)_capacity);
   
   if(_table[index] == null)
   {
      _table[index] = new HashMapNode<K, V>(key, value);
      _count++;
      return true;
   }
   
   HashMapNode<K, V> *node = _table[index];
   while(node->next != null)
   {
      if(node->key->equals(key))
      {
         if(deleting)
         {
            delete node->key;
            if(node->value != null)
               delete node->value;
         }
         
         node->key = key;
         node->value = value;
         return false;
      }
   
      node = node->next;
   }
   
   if(node->key->equals(key))
   {
      if(deleting)
      {
         delete node->key;
         if(node->value != null)
            delete node->value;
      }
      
      node->key = key; 
      node->value = value;
      return false;
   }
   
   node->next = new HashMapNode<K, V>(key, value);
   _count++;
   return true;
}

template<class K, class V> _bool HashMap<K, V>::contains(K *key)
{
   if(key == null)
   {
      Error *ex = MAKE_ERROR(Error::NullObject);
      ex->add("reason", "This container do not allow null keys");
      throw ex;
   }
   
   _uint32 hash = key->makeHash();
   _int index = (_int)(hash % (_uint32)_capacity);
   
   if(_table[index] == null)
      return false;
      
   HashMapNode<K, V> *node = _table[index];
   while(node != null)
   {
      if(node->key->equals(key))
         return true;
   
      node = node->next;
   }
   return false;
}

template<class K, class V> V *HashMap<K, V>::get(K *key)
{
   if(key == null)
   {
      Error *ex = MAKE_ERROR(Error::NullObject);
      ex->add("reason", "This container do not allow null keys");
      throw ex;
   }
   
   _uint32 hash = key->makeHash();
   _int index = (_int)(hash % (_uint32)_capacity);
   
   if(_table[index] == null)
      return null;

   HashMapNode<K, V> *node = _table[index];
   while(node != null)
   {
      if(node->key->equals(key))
         return node->value;

      node = node->next;
   }
   return null;
}
   
template<class K, class V> _bool HashMap<K, V>::remove(K *key, _bool deleting)
{
   this->modified();

   if(key == null)
   {
      Error *ex = MAKE_ERROR(Error::NullObject);
      ex->add("reason", "This container do not allow null keys");
      throw ex;
   }
   
   _uint32 hash = key->makeHash();
   _int index = (_int)(hash % (_uint32)_capacity);
   
   if(_table[index] == null)
      return false;
      
   HashMapNode<K, V> *node = _table[index];
   if(node->key->equals(key))
   {
      if(deleting)
      {
         delete node->key;
         if(node->value != null)
            delete node->value;
      }
      
      _table[index] = node->next;
      delete node;
      _count--;
      return true;
   }
   
   HashMapNode<K, V> *previous = node;
   node = node->next;
   while(node != null)
   {
      if(node->key->equals(key))
      {
         if(deleting)
         {
            delete node->key;
            if(node->value != null)
               delete node->value;
         }
         
         previous->next = node->next;
         delete node;
         _count--;
         return true;
      }
   
      previous = node;
      node = node->next;
   }
   return false;
}
   
template<class K, class V> void HashMap<K, V>::clear(_bool deleting)
{
   this->modified();

   for(_int i = 0; i < _capacity; i++)
   {
      HashMapNode<K, V> *node = _table[i];
      while(node != null)
      {
         if(deleting)
         {
            delete node->key;
            if(node->value != null)
               delete node->value;
         }
         
         HashMapNode<K, V> *temp = node->next;
         delete node;
         node = temp;
      }
      _table[i] = null;
   }
   _count = 0;
}

   
template<class K, class V> DynIterator<K> *HashMap<K, V>::dynIterate()
{
   return new HashMapIterator<K, V>(this);
}


template<class K, class V> void HashMap<K, V>::ensureCap(_int min)
{
   _int threshold = (_int)(LOAD_FACTOR * (_float)_capacity);
   if(min <= threshold)
      return;
      
   _int old_cap = _capacity;
   HashMapNode<K, V> **old_table = _table;
   
   _capacity = _capacity * 2 + 1;
   _count = 0;
   _table = new HashMapNode<K, V>*[_capacity];
   for(_int i = 0; i < _capacity; i++)
      _table[i] = null;
   
   
   for(_int i = 0; i < old_cap; i++)
   {
      HashMapNode<K, V> *node = old_table[i];
      while(node != null)
      {
         add(node->key, node->value, true);
         
         HashMapNode<K, V> *temp = node->next;
         delete node;
         node = temp;
      }
   }   
   delete old_table;
}

} }

