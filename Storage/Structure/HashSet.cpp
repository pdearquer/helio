/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {

template <class T> const_int HashSet<T>::INICIAL_CAPACITY;

template <class T> const_float HashSet<T>::LOAD_FACTOR;


template <class T> HashSet<T>::HashSet()
{
   _capacity = INICIAL_CAPACITY;
   _count = 0;
   
   _table = new HashSetNode<T>*[_capacity];
   for(_int i = 0; i < _capacity; i++)
      _table[i] = null;
}

template <class T> HashSet<T>::HashSet(_bool owner)
{
   _capacity = INICIAL_CAPACITY;
   _count = 0;
   
   _table = new HashSetNode<T>*[_capacity];
   for(_int i = 0; i < _capacity; i++)
      _table[i] = null;

   this->setOwnership(owner);
}

template <class T> HashSet<T>::~HashSet()
{
   clear();
   
   delete[] _table;
}


template <class T> _int HashSet<T>::count() const
{
   return _count;
}

template <class T> _bool HashSet<T>::add(T *el, _bool deleting)
{
   this->modified();

   if(el == null)
   {
      Error *ex = MAKE_ERROR(Error::NullObject);
      ex->add("reason", "The Set containers do not allow null elements");
      throw ex;
   }

   // Worst case considered. Its better than make the growth later
   ensureCap(_count + 1);  

   _uint32 hash = el->makeHash();
   _int index = (_int)(hash % (_uint32)_capacity);
   
   if(_table[index] == null)
   {
      _table[index] = new HashSetNode<T>(el);
      _count++;
      return true;
   }
   
   HashSetNode<T> *node = _table[index];
   while(node->next != null)
   {
      if(node->element->equals(el))
      {
         if(deleting)
            delete node->element;
         node->element = el;
         return false;
      }
   
      node = node->next;
   }
   
   if(node->element->equals(el))
   {
      if(deleting)
         delete node->element;
      node->element = el;
      return false;
   }
   
   node->next = new HashSetNode<T>(el);
   _count++;
   return true;
}
   
template <class T> _bool HashSet<T>::contains(T *el)
{
   _uint32 hash = el->makeHash();
   _int index = (_int)(hash % (_uint32)_capacity);
   
   if(_table[index] == null)
      return false;
      
   HashSetNode<T> *node = _table[index];
   while(node != null)
   {
      if(node->element->equals(el))
         return true;
   
      node = node->next;
   }
   return false;
}

template <class T> T *HashSet<T>::get(T *el)
{
   _uint32 hash = el->makeHash();
   _int index = (_int)(hash % (_uint32)_capacity);
   
   if(_table[index] == null)
      return null;

   HashSetNode<T> *node = _table[index];
   while(node != null)
   {
      if(node->element->equals(el))
         return node->element;

      node = node->next;
   }
   return null;
}

template <class T> _bool HashSet<T>::remove(T *el, _bool deleting)
{
   this->modified();

   _uint32 hash = el->makeHash();
   _int index = (_int)(hash % (_uint32)_capacity);
   
   if(_table[index] == null)
      return false;
      
   HashSetNode<T> *node = _table[index];
   if(node->element->equals(el))
   {
      if(deleting)
         delete node->element;
      
      _table[index] = node->next;
      delete node;
      _count--;
      return true;
   }
   
   HashSetNode<T> *previous = node;
   node = node->next;
   while(node != null)
   {
      if(node->element->equals(el))
      {
         if(deleting)
            delete node->element;
         
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
   
template <class T> void HashSet<T>::clear(_bool deleting)
{
   this->modified();

   for(_int i = 0; i < _capacity; i++)
   {
      HashSetNode<T> *node = _table[i];
      while(node != null)
      {
         if(deleting)
            delete node->element;
         
         HashSetNode<T> *temp = node->next;
         delete node;
         node = temp;
      }
      _table[i] = null;
   }
   _count = 0;
}

   
template <class T> DynIterator<T> *HashSet<T>::dynIterate()
{
   return new HashSetIterator<T>(this);
}


template <class T> void HashSet<T>::ensureCap(_int min)
{
   _int threshold = (_int)(LOAD_FACTOR * (_float)_capacity);
   if(min <= threshold)
      return;
      
   _int old_cap = _capacity;
   HashSetNode<T> **old_table = _table;
   
   _capacity = _capacity * 2 + 1;
   _count = 0;
   _table = new HashSetNode<T>*[_capacity];
   for(_int i = 0; i < _capacity; i++)
      _table[i] = null;
   
   
   for(_int i = 0; i < old_cap; i++)
   {
      HashSetNode<T> *node = old_table[i];
      while(node != null)
      {
         add(node->element, true);
         
         HashSetNode<T> *temp = node->next;
         delete node;
         node = temp;
      }
   }   
   delete old_table;
}

} }

