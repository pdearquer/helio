/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

#include <Helio.h>

namespace Storage {
namespace Structure {

template <class T> LinkedQueueIterator<T>::LinkedQueueIterator(LinkedQueue<T> *list)
{
   this->_list = list;
   this->_node = list->_list->first();
   this->_index = 0;
   this->startVersion(this->_list);
}


template <class T> _bool LinkedQueueIterator<T>::hasMore() const
{
   this->checkVersion(this->_list);

   return (this->_node != null);
}

template <class T> T *LinkedQueueIterator<T>::get()
{
   this->checkVersion(this->_list);

   if(this->_node == null)
   {
      MAKE_ERROR(ex, Error::Structure::IterationEnded);
      ex->addInt("count", this->_list->_count);
      throw ex;
   }

   return this->_node->_elements[this->_index];
}

template <class T> T *LinkedQueueIterator<T>::next()
{
   this->checkVersion(this->_list);

   if(this->_node == null)
   {
      MAKE_ERROR(ex, Error::Structure::IterationEnded);
      ex->addInt("count", this->_list->_count);
      throw ex;
   }

   T *current = this->_node->_elements[this->_index];

   this->_index++;
   if(this->_index >= this->_node->_count)
   {
      this->_node = this->_node->next();
      this->_index = 0;
   }

   return current;
}

} }

