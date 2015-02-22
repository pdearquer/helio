/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

#include <Helio.h>

namespace Storage {
namespace Structure {

template <class T> LinkedQueue<T>::LinkedQueue()
{
   this->_list = new LinkedList<LinkedQueueNode<T> >();
   this->_count = 0;
}

template <class T> LinkedQueue<T>::LinkedQueue(_bool owner)
{
   this->setOwnership(owner);

   this->_list = new LinkedList<LinkedQueueNode<T> >();
   this->_count = 0;
}

template <class T> LinkedQueue<T>::~LinkedQueue()
{
   if(this->ownership())
   {
      LinkedQueueNode<T> *node = this->_list->first();
      while(node != null)
      {
         for(_int i = 0; i < node->_count; i++)
            if(node->_elements[i] != null)
               delete node->_elements[i];

         node = node->next();
      }
   }

   delete this->_list;
}


template <class T> _int LinkedQueue<T>::count() const
{
   return this->_count;
}

template <class T> _bool LinkedQueue<T>::isEmpty() const
{
   return (this->_count == 0);
}

template <class T> void LinkedQueue<T>::setCount(_int num, _bool deleting)
{
   this->modified();

   if(num < 0 || num > this->_count)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("new", num);
      ex->addInt("count", this->_count);
      throw ex;
   }

   if(this->_count == 0)
      return;

   LinkedQueueNode<T> *node = this->_list->first();
   if(node == null)
      ERROR(Error::Internal);
   _int node_index = 0;
   while(node_index + node->_count < num)
   {
      node_index += node->_count;
      node = node->next();

      if(node == null)
         ERROR(Error::Internal);
   }

   if(num > node_index)
   {
      node->erase(num - node_index, node->_count - 1, deleting);

      node = node->next();
   }

   while(node != null)
   {
      node->erase(0, node->_count - 1, deleting);

      LinkedQueueNode<T> *next = node->next();
      node->removeThis();
      node = next;
   }

   this->_count = num;
}


template <class T> _int LinkedQueue<T>::add(T *el)
{
   this->modified();

   LinkedQueueNode<T> *node = this->_list->last();
   if(node == null)
   {
      node = new LinkedQueueNode<T>();
      this->_list->enqueue(node);
   }

   _int index = this->_count;
   while(!node->add(el))
   {
      node = new LinkedQueueNode<T>();
      this->_list->enqueue(node);
   }

   this->_count++;
   return index;
}

template <class T> void LinkedQueue<T>::set(_int index, T *el, _bool deleting)
{
   this->modified();

   if(index < 0 || index >= this->_count)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("index", index);
      ex->addInt("count", this->_count);
      throw ex;
   }

   LinkedQueueNode<T> *node = this->_list->first();
   while(node != null)
   {
      if(index < node->_count)
      {
         if(deleting)
         {
            if(node->_elements[index] != null && node->_elements[index] != el)
               delete node->_elements[index];
         }

         node->_elements[index] = el;
         return;
      }

      index -= node->_count;
      node = node->next();
   }

   Error *ex = MAKE_ERROR(Error::Internal);
   ex->add("reason", "Unexpected end; list corrupted");
   throw ex;
}

template <class T> T *LinkedQueue<T>::get(_int index) const
{
   if(index < 0 || index >= this->_count)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("index", index);
      ex->addInt("count", this->_count);
      throw ex;
   }

   LinkedQueueNode<T> *node = this->_list->first();
   while(node != null)
   {
      if(index < node->_count)
         return node->_elements[index];

      index -= node->_count;
      node = node->next();
   }

   Error *ex = MAKE_ERROR(Error::Internal);
   ex->add("reason", "Unexpected end; list corrupted");
   throw ex;
}

template <class T> void LinkedQueue<T>::erase(_int start, _int end, _bool deleting)
{
   this->modified();

   if(0 > start || start > end || end >= this->_count)
   {
      Error *ex = MAKE_ERROR(Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("end", end);
      ex->addInt("count", this->_count);
      throw ex;
   }

   if(this->_count == 0)
      return;

   LinkedQueueNode<T> *node = this->_list->first();
   if(node == null)
      ERROR(Error::Internal);
   _int node_index = 0;
   while(node_index + node->_count - 1 < start)
   {
      node_index += node->_count;
      node = node->next();

      if(node == null)
         ERROR(Error::Internal);
   }

   _int node_start = start - node_index;
   _int node_end = end - node_index;
   while(node_end >= node->_count)
   {
      node_index += node->_count;
      node->erase(node_start, node->_count - 1, deleting);

      LinkedQueueNode<T> *next = node->next();
      if(node->_count == 0)
         node->removeThis();
      node = next;
      if(node == null)
         ERROR(Error::Internal);

      node_start = 0;
      node_end = end - node_index;
   }

   node->erase(node_start, node_end, deleting);
   if(node->_count == 0)
      node->removeThis();

   this->_count -= end - start + 1;
}


template <class T> void LinkedQueue<T>::enqueue(T *el)
{
   this->modified();

   this->add(el);
}

template <class T> T *LinkedQueue<T>::dequeue()
{
   this->modified();

   if(this->_count <= 0)
      ERROR(Error::Structure::Empty);

   LinkedQueueNode<T> *node = this->_list->first();
   T *el = node->dequeue();
   if(node->_count == 0)
      node->removeThis();

   this->_count--;
   return el;
}

template <class T> T *LinkedQueue<T>::front() const
{
   if(this->_count == 0)
      ERROR(Error::Structure::Empty);

   LinkedQueueNode<T> *node = this->_list->first();
   return node->front();
}

template <class T> void LinkedQueue<T>::enqueue_front(T *el)
{
   this->modified();

   LinkedQueueNode<T> *node = this->_list->first();
   if(node == null)
   {
      node = new LinkedQueueNode<T>();
      this->_list->enqueue_front(node);
   }

   while(!node->add_front(el))
   {
      node = new LinkedQueueNode<T>();
      this->_list->enqueue_front(node);
   }

   this->_count++;
}

template <class T> T *LinkedQueue<T>::dequeue_back()
{
   this->modified();

   if(this->_count <= 0)
      ERROR(Error::Structure::Empty);

   LinkedQueueNode<T> *node = this->_list->last();
   T *el = node->dequeue_back();
   if(node->_count == 0)
      node->removeThis();

   this->_count--;
   return el;
}

template <class T> T *LinkedQueue<T>::back() const
{
   if(this->_count == 0)
      ERROR(Error::Structure::Empty);

   LinkedQueueNode<T> *node = this->_list->last();
   return node->back();
}


template <class T> DynIterator<T> *LinkedQueue<T>::dynIterate()
{
   return new LinkedQueueIterator<T>(this);
}

} }

