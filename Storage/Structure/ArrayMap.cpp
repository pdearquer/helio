/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {

template<class K, class V> ArrayMap<K, V>::ArrayMap()
{
}

template<class K, class V> ArrayMap<K, V>::ArrayMap(_bool owner)
{
   this->setOwnership(owner);
}

template<class K, class V> ArrayMap<K, V>::~ArrayMap()
{
   for(_int i = 0; i < this->_count; i++)
   {
      if(this->ownership())
      {
         delete this->_elements[i]->key;
         if(this->_elements[i]->value != null)
            delete this->_elements[i]->value;
      }
      
      delete this->_elements[i];      
   }
}


template<class K, class V> _int ArrayMap<K, V>::count() const
{
   return this->_count;
}


template<class K, class V> _bool ArrayMap<K, V>::add(K *key, V *value, _bool deleting)
{
   this->modified();

   if(key == null)
   {
      Exception *ex = MAKE_ERROR("NullObject");
      ex->add("reason", "This container do not allow null keys");
      throw ex;
   }
   
   for(_int i = 0; i < this->_count; i++)
   {
      if(this->_elements[i]->key->equals(key))
      {
         if(deleting)
         {
            delete this->_elements[i]->key;
            if(this->_elements[i]->value != null)
               delete this->_elements[i]->value;
         }
         
         this->_elements[i]->key = key;
         this->_elements[i]->value = value;
         
         return false;
      }
   }
   
   this->appendElement(new MapEntry<K, V>(key, value));
   
   return true;
}

template<class K, class V> _bool ArrayMap<K, V>::contains(K *key)
{
   if(key == null)
   {
      Exception *ex = MAKE_ERROR("NullObject");
      ex->add("reason", "This container do not allow null keys");
      throw ex;
   }
   
   for(_int i = 0; i < this->_count; i++)
   {
      if(this->_elements[i]->key->equals(key))
         return true;
   }
   
   return false;
}

template<class K, class V> _bool ArrayMap<K, V>::containsValue(V *value)
{
   for(_int i = 0; i < this->_count; i++)
   {
      if(value == null)
      {
         if(this->_elements[i]->value == null)
            return true;
      }
      else
      {
         if(this->_elements[i]->value != null && this->_elements[i]->value->equals(value))
            return true;
      }
   }
   
   return false;
}

template<class K, class V> V *ArrayMap<K, V>::get(K *key)
{
   if(key == null)
   {
      Exception *ex = MAKE_ERROR("NullObject");
      ex->add("reason", "This container do not allow null keys");
      throw ex;
   }
   
   for(_int i = 0; i < this->_count; i++)
   {
      if(this->_elements[i]->key->equals(key))
         return this->_elements[i]->value;
   }
   
   return null;
}

template<class K, class V> _bool ArrayMap<K, V>::remove(K *key, _bool deleting)
{
   this->modified();

   if(key == null)
   {
      Exception *ex = MAKE_ERROR("NullObject");
      ex->add("reason", "This container do not allow null keys");
      throw ex;
   }
   
   for(_int i = 0; i < this->_count; i++)
   {
      if(this->_elements[i]->key->equals(key))
      {
         if(deleting)
         {
            delete this->_elements[i]->key;
            if(this->_elements[i]->value != null)
               delete this->_elements[i]->value;
         }         
         delete this->_elements[i];
         
         this->eraseElements(i, i);
         
         return true;
      }
   }
   
   return false;
}

template<class K, class V> void ArrayMap<K, V>::clear(_bool deleting)
{
   this->modified();

   for(_int i = 0; i < this->_count; i++)
   {
      if(deleting)
      {
         delete this->_elements[i]->key;
         if(this->_elements[i]->value != null)
            delete this->_elements[i]->value;
      }
      
      delete this->_elements[i];      
   }
   
   this->_count = 0;
}


template<class K, class V> DynIterator<K> *ArrayMap<K, V>::dynIterate()
{
   return new ArrayMapIterator<K, V>(this);
}

} }

