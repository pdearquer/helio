/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {

template<class K, class V> HashMapIterator<K, V>::HashMapIterator(HashMap<K, V> *map)
{
   this->_map = map;
   this->_node = null;
   this->startVersion(this->_map);
      
   for(this->_index = 0; this->_index < this->_map->_capacity; _index++)
   {
      if(this->_map->_table[this->_index] != null)
      {
         this->_node = this->_map->_table[this->_index];
         break;
      }
   }
}

template<class K, class V> _bool HashMapIterator<K, V>::hasMore() const
{
   this->checkVersion(this->_map);

   return (this->_node != null);
}
   
template<class K, class V> K *HashMapIterator<K, V>::get()
{
   this->checkVersion(this->_map);

   if(this->_node == null)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.IterationEnd");
      ex->addInt("count", this->_map->_count);
      throw ex;
   }

   return this->_node->key;
}
   
template<class K, class V> K *HashMapIterator<K, V>::next()
{
   this->checkVersion(this->_map);

   if(this->_node == null)
   {
      Exception *ex = MAKE_ERROR("Storage.Structure.IterationEnd");
      ex->addInt("count", this->_map->_count);
      throw ex;
   }

   K *current = this->_node->key;

   this->_node = this->_node->next;
   if(this->_node != null)
      return current;   

   this->_index++;
   for(; this->_index < this->_map->_capacity; this->_index++)
   {
      if(this->_map->_table[this->_index] != null)
      {
         this->_node = this->_map->_table[_index];
         break;
      }
   }
   
   return current;
}

} }

