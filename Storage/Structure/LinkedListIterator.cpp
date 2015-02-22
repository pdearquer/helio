/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

#include <Helio.h>

namespace Storage {
namespace Structure {

template<class N> LinkedListIterator<N>::LinkedListIterator(LinkedList<N> *list)
{
   this->_list = list;
   this->_node = this->_list->first();
   this->startVersion(this->_list);
}


template<class N> _bool LinkedListIterator<N>::hasMore() const
{
   this->checkVersion(this->_list);

   return (this->_node != null);
}

template<class N> N *LinkedListIterator<N>::get()
{
   this->checkVersion(this->_list);

   if(this->_node == null)
      ERROR(Error::Structure::IterationEnded);

   return _node;
}

template<class N> N *LinkedListIterator<N>::next()
{
   this->checkVersion(this->_list);

   if(this->_node == null)
      ERROR(Error::Structure::IterationEnded);

   N *current = this->_node;
   this->_node = this->_node->next();
   return current;
}

} }

