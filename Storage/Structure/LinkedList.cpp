/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

#include <Helio.h>

namespace Storage {
namespace Structure {

template<class N> LinkedList<N>::LinkedList()
{
   this->_first = null;
   this->_last = null;
}

template<class N> LinkedList<N>::LinkedList(_bool owner)
{
   this->setOwnership(owner);

   this->_first = null;
   this->_last = null;
}

template<class N> LinkedList<N>::~LinkedList()
{
   N *node = this->_first;
   while(node != null)
   {
      N *next = node->_next;

      node->removed(this);
      if(this->ownership())
         delete node;

      node = next;
   }
}


template<class N> _int LinkedList<N>::count() const
{
   N *node = this->_first;
   _int ret = 0;
   while(node != null)
   {
      ret++;
      node = node->_next;
   }
   return ret;
}

template<class N> _int LinkedList<N>::countReverse() const
{
   N *node = this->_last;
   _int ret = 0;
   while(node != null)
   {
      ret++;
      node = node->_prev;
   }
   return ret;
}

template<class N> _bool LinkedList<N>::isEmpty() const
{
   return (this->_first == null);
}

template<class N> _bool LinkedList<N>::remove(N *node, _bool deleting)
{
   this->modified();

   if(node->_list != this)
      return false;     // Belongs to another list

   node->removeThis(deleting);
   return true;
}

template<class N> void LinkedList<N>::clear(_bool deleting)
{
   this->modified();

   N *node = this->_first;
   while(node != null)
   {
      N *next = node->_next;

      node->removed(this);
      if(deleting)
         delete node;

      node = next;
   }

   this->_first = null;
   this->_last = null;
}


template<class N> N *LinkedList<N>::first() const
{
   return this->_first;
}

template<class N> N *LinkedList<N>::last() const
{
   return this->_last;
}


template<class N> void LinkedList<N>::enqueue(N *node)
{
   this->modified();

   node->adding(this);

   if(this->_last == null)
   {
      this->_first = this->_last = node;
      node->_prev = null;
      node->_next = null;
   }
   else
   {
      this->_last->_next = node;
      node->_prev = this->_last;
      node->_next = null;
      this->_last = node;
   }
}

template<class N> N *LinkedList<N>::dequeue()
{
   this->modified();

   if(this->_first == null)
      return null;

   N *node = this->_first;
   this->_first = node->_next;
   if(this->_first == null)
      this->_last = null;
   else
      this->_first->_prev = null;

   node->removed(this);
   return node;
}

template<class N> N *LinkedList<N>::front() const
{
   return this->_first;
}

template<class N> void LinkedList<N>::enqueue_front(N *node)
{
   this->modified();

   node->adding(this);

   if(this->_first == null)
   {
      this->_first = this->_last = node;
      node->_prev = null;
      node->_next = null;
   }
   else
   {
      node->_prev = null;
      node->_next = this->_first;
      this->_first->_prev = node;
      this->_first = node;
   }
}

template<class N> N *LinkedList<N>::dequeue_back()
{
   this->modified();

   if(this->_last == null)
      return null;

   N *node = this->_last;
   this->_last = node->_prev;
   if(this->_last == null)
      this->_first = null;
   else
      this->_last->_next = null;

   node->removed(this);
   return node;
}

template<class N> N *LinkedList<N>::back() const
{
   return this->_last;
}


template<class N> DynIterator<N> *LinkedList<N>::dynIterate()
{
   return new LinkedListIterator<N>(this);
}

} }

