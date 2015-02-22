/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {

template <class T> const_int ArrayBase<T>::INICIAL_CAPACITY;


template <class T> ArrayBase<T>::ArrayBase()
{
   this->_count = 0;
   this->_size = this->INICIAL_CAPACITY;
   this->_elements = new T*[this->_size];
}
   
template <class T> ArrayBase<T>::~ArrayBase()
{
   delete[] this->_elements;
}
   

template <class T> void ArrayBase<T>::ensureSize(_int min)
{
   if(min <= this->_size)
      return;

   _int size2 = this->_size;
   while(size2 < min)
   {
      if(size2 < 256)
         size2 = size2 * 2;
      else
         size2 += 256;
   }
   
   T **elements2 = new T*[size2];
   for(_int i = 0; i < this->_count; i++)
      elements2[i] = this->_elements[i];
   delete[] this->_elements;
   
   this->_elements = elements2;
   this->_size = size2;
}
   
template <class T> _int ArrayBase<T>::appendElement(T *el)
{
   this->ensureSize(this->_count + 1);
   this->_count++;
   this->_elements[this->_count - 1] = el;
   return this->_count - 1;
}

template <class T> void ArrayBase<T>::eraseElements(_int start, _int end)
{
   if(0 > start || start > end || end >= this->_count)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("end", end);
      ex->addInt("count", this->_count);
      throw ex;
   }
   
   _int ahead = this->_count - end - 1;
   for(_int i = 0; i < ahead; i++)
      this->_elements[start + i] = this->_elements[end + 1 + i];
      
   this->_count -= end - start + 1;
}

} }

