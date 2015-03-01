/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Interface of an iterator provider.
 * It allows the iteration over an enumeration of elements of generic type.
 *
 * This class allows C++ 11 foreach iteration:
 *  for(Integer *i : list)
 *  {
 *     // Do something with i
 *  }
 * This iteration pattern is preferred to the classical based on index because
 * prevents any off-by-one bugs.
 */
template<class T>
class Iterable :
      public virtual Object
{
public:
   /**
    * Gets a dynamic iterator over the elements.
    * This iterator must be deleted by the user.
    * Do not modify the container while iterating or the iterator will
    * be invalidated with undetermined behaviour.
    */
   virtual DynIterator<T> *dynIterate() = 0;

   /**
    * Gets a static iterator over the elements.
    * The iterator must not be deleted.
    * Do not modify the container while iterating or the iterator will
    * be invalidated with undetermined behaviour.
    */
   virtual Iterator<T> iterate();
};


/**
 * C++ for each begin implementation.
 */
template<class T>
Iterator<T> begin(const Iterable<T> *cont);

/**
 * C++ for each end implementation.
 */
template<class T>
Iterator<T> end(const Iterable<T> *cont);

