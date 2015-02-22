/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

#include <Helio.h>

namespace Storage {
namespace Structure {

template<class N> LinkedNode<N>::LinkedNode()
{
   this->_list = null;
   this->_prev = null;
   this->_next = null;
}


template<class N> N *LinkedNode<N>::prev()
{
   return this->_prev;
}

template<class N> N *LinkedNode<N>::next()
{
   return this->_next;
}


template<class N> void LinkedNode<N>::removeThis()
{
   this->removeThis(this->_list->ownership());
}

template<class N> void LinkedNode<N>::removeThis(_bool deleting)
{
   if(this->_prev == null)
   {
      this->_list->_first = this->_next;
      if(this->_next != null)
         this->_next->_prev = null;
      else
         this->_list->_last = null;
   }
   else
   {
      this->_prev->_next = this->_next;
      if(this->_next != null)
         this->_next->_prev = this->_prev;
      else
         this->_list->_last = this->_prev;
   }

   this->removed(this->_list);
   if(deleting)
      delete this;
}

template<class N> void LinkedNode<N>::removePrev()
{
   if(this->_prev == null)
      ERROR(Error::Structure::OutOfBounds);

   this->_prev->removeThis();
}

template<class N> void LinkedNode<N>::removeNext()
{
   if(this->_next == null)
      ERROR(Error::Structure::OutOfBounds);

   this->_next->removeThis();
}


template<class N> void LinkedNode<N>::insertAfter(N *node)
{
   if(node == null)
      ERROR(Error::NullObject);
   if(this == node)
      ERROR(Error::Structure::LoopsNotAllowed);
   
   node->adding(this->_list);

   N *myself = ((Object *)this)->as<N>();
   node->_prev = myself;
   node->_next = this->_next;

   if(this->_next != null)
      this->_next->_prev = node;
   else
      this->_list->_last = node;
   this->_next = node;
}

template<class N> void LinkedNode<N>::insertBefore(N *node)
{
   if(node == null)
      ERROR(Error::NullObject);
   if(this == node)
      ERROR(Error::Structure::LoopsNotAllowed);

   node->adding(this->_list);

   N *myself = ((Object *)this)->as<N>();
   node->_prev = this->_prev;
   node->_next = myself;

   if(this->_prev != null)
      this->_prev->_next = node;
   else
      this->_list->_first = node;
   this->_prev = node;
}


template<class N> void LinkedNode<N>::swapWithPrev()
{
   if(this->_prev == null)
      ERROR(Error::Structure::OutOfBounds);

   this->_prev->swapWithNext();
}

template<class N> void LinkedNode<N>::swapWithNext()
{
   if(this->_next == null)
      ERROR(Error::Structure::OutOfBounds);

   N *prev = this->_prev;
   N *myself = ((Object *)this)->as<N>();
   N *other = this->_next;
   N *next = this->_next->_next;

   other->_prev = prev;
   if(other->_prev == null)
      this->_list->_first = other;
   else
      other->_prev->_next = other;
   other->_next = myself;

   this->_prev = other;
   this->_next = next;
   if(this->_next == null)
      this->_list->_last = myself;
   else
      this->_next->_prev = myself;
}

template<class N> void LinkedNode<N>::swap(N *other)
{
   if(this == other)
      return;
   if(other == null)
      ERROR(Error::NullObject);
   if(this->_list != other->_list)
      ERROR(Error::Structure::InvalidContainer);

   N *myself = ((Object *)this)->as<N>();
   N *prev = other->_prev;
   if(prev == myself)
   {
      other->swapWithPrev();
      return;
   }
   N *next = other->_next;
   if(next == myself)
   {
      other->swapWithNext();
      return;
   }

   other->_prev = this->_prev;
   if(other->_prev == null)
      this->_list->_first = other;
   else
      other->_prev->_next = other;
   other->_next = this->_next;
   if(other->_next == null)
      this->_list->_last = other;
   else
      other->_next->_prev = other;

   this->_prev = prev;
   if(this->_prev == null)
      this->_list->_first = myself;
   else
      this->_prev->_next = myself;
   this->_next = next;
   if(this->_next == null)
      this->_list->_last = myself;
   else
      this->_next->_prev = myself;
}


template<class N> void LinkedNode<N>::adding(Object *container)
{
   this->Node<N>::adding(container);

   LinkedList<N> *list = container->as<LinkedList<N> >();

   if(this->_list != null)
      ERROR(Error::Structure::InvalidContainer);

   this->_list = list;
}

template<class N> void LinkedNode<N>::removed(Object *container)
{
   this->Node<N>::removed(container);

   LinkedList<N> *list = container->as<LinkedList<N> >();

   if(this->_list != list)
      ERROR(Error::Structure::InvalidContainer);

   this->_list = null;
   this->_prev = null;
   this->_next = null;
}

template<class N> _bool LinkedNode<N>::hasLink(N *other)
{
   if(other == null)
      ERROR(Error::NullObject);

   return (other == this->_prev) || (other == this->_next);
}

} }

