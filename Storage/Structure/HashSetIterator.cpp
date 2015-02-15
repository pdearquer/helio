/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {

template <class T> HashSetIterator<T>::HashSetIterator(HashSet<T> *set)
{
   this->_set = set;
   this->_node = null;
   this->startVersion(this->_set);
      
   for(this->_index = 0; this->_index < this->_set->_capacity; this->_index++)
   {
      if(this->_set->_table[this->_index] != null)
      {
         this->_node = this->_set->_table[this->_index];
         break;
      }
   }
}

template <class T> _bool HashSetIterator<T>::hasMore() const
{
   this->checkVersion(this->_set);

   return (this->_node != null);
}
   
template <class T> T *HashSetIterator<T>::get()
{
   this->checkVersion(this->_set);

   if(this->_node == null)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.IterationEnd");
      ex->addInt("count", this->_set->_count);
      throw ex;
   }

   return this->_node->element;
}
   
template <class T> T *HashSetIterator<T>::next()
{
   this->checkVersion(this->_set);

   if(this->_node == null)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.IterationEnd");
      ex->addInt("count", this->_set->_count);
      throw ex;
   }

   T *current = this->_node->element;

   this->_node = this->_node->next;
   if(this->_node != null)
      return current;   

   this->_index++;
   for(; this->_index < this->_set->_capacity; this->_index++)
   {
      if(this->_set->_table[this->_index] != null)
      {
         this->_node = this->_set->_table[this->_index];
         break;
      }
   }
   
   return current;
}

} }

