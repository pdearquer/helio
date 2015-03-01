/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {

template <class T> ArraySetIterator<T>::ArraySetIterator(ArraySet<T> *set)
{
   this->_set = set;
   this->_position = 0;
   this->startVersion(this->_set);
}


template <class T> _bool ArraySetIterator<T>::hasMore() const
{
   this->checkVersion(this->_set);

   return (this->_position < this->_set->_count);
}
   
template <class T> T *ArraySetIterator<T>::get()
{
   if(!hasMore())
   {
      MAKE_ERROR(ex, Error::Structure::IterationEnded);
      ex->addInt("position", this->_position);
      ex->addInt("count", this->_set->_count);
      throw ex;
   }
   
   return this->_set->_elements[this->_position];
}
   
template <class T> T *ArraySetIterator<T>::next()
{
   if(!hasMore())
   {
      MAKE_ERROR(ex, Error::Structure::IterationEnded);
      ex->addInt("position", this->_position);
      ex->addInt("count", this->_set->_count);
      throw ex;
   }

   T *current = this->_set->_elements[this->_position];
   this->_position++;
   return current;
}

} }

