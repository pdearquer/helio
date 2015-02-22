/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {

template <class T> ArrayListIterator<T>::ArrayListIterator(ArrayList<T> *list)
{
   this->_list = list;
   this->_position = 0;
   this->startVersion(this->_list);
}


template <class T> _bool ArrayListIterator<T>::hasMore() const
{
   this->checkVersion(this->_list);

   return (this->_position < this->_list->_count);
}
   
template <class T> T *ArrayListIterator<T>::get()
{
   if(!hasMore())
   {
      Error *ex = MAKE_ERROR(Error::Structure::IterationEnded);
      ex->addInt("position", this->_position);
      ex->addInt("count", this->_list->_count);
      throw ex;
   }
   
   return this->_list->_elements[this->_position];
}
   
template <class T> T *ArrayListIterator<T>::next()
{
   if(!hasMore())
   {
      Error *ex = MAKE_ERROR(Error::Structure::IterationEnded);
      ex->addInt("position",this-> _position);
      ex->addInt("count", this->_list->_count);
      throw ex;
   }

   T *current = this->_list->_elements[this->_position];
   this->_position++;
   return current;
}

} }

