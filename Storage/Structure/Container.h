/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Base of any container of objects.
 * Base of any container of objects.
 *
 * By default, the container takes ownership of all the elements
 * added. This means that the container delete all the elements on
 * it when it is deleted and the elements removed are also deleted.
 * The onwership can be disable with the setOnwership() method.
 *
 * Every container have an attribute called version which is incremented
 * on every modification of the container. It is used by the iterators
 * to ensure that the container has not changed and throw an
 * InvalidatedIterator exception.
 *
 * Make sure of calling modified() on every change to the container.
 */
template<class T>
class Container :
      public virtual Iterable<T>
{
   __CHECK_BASE(T, Object);

protected:
   /**
    * true if this container must delete its elements on removal.
    */
   _bool _ownership;

   /**
    * Unique version of the container state.
    * It gets incremented on every change.
    */
   _int _version;


public:
   /**
    * Create a container with the ownership enabled.
    */
   Container();


   /**
    * Returns true if the container is taken ownership of its elements.
    */
   virtual _bool ownership();

   /**
    * Set or unsets the ownership of this container.
    */
   virtual void setOwnership(_bool owner);

   /**
    * Notify the container of a modification.
    * This method must be called before modifing or attempting to modify
    * the container. It doesn't matter if the action fails and the container
    * is actually not modified or if it is called more than once.
    * This method invalidates all the iterators.
    */
   virtual void modified();

   /**
    * Returns the current version of the container.
    */
   virtual _int version() const;


   /**
    * Gets the number of elements.
    */
   virtual _int count() const = 0;
   
   /**
    * Says if the container has no element.
    */
   virtual _bool isEmpty() const;
   
   /**
    * Checks if the container has an element.
    * The equals() interface is used as in Comparable<T>.
    */
   virtual _bool contains(T *el);
   
   /**
    * Removes an element from the container (deleting or not depending on the ownership).
    * The equals() interface is used as in Comparable<T>.
    * @return true if the element was found.    
    */
   virtual _bool remove(T *el);

   /**
    * Removes an element from the container overriding the ownership.
    * The equals() interface is used as in Comparable<T>.
    * @return true if the element was found.
    */
   virtual _bool remove(T *el, _bool deleting) = 0;
   
   /**
    * Removes all elements (deleting or not depending on the ownership).
    */
   virtual void clear();
   
   /**
    * Removes all elements overriding the ownership.
    */
   virtual void clear(_bool deleting) = 0;

   
   /**
    * Returns a list containing all the elements of this container.
    * The elements of the list follow the container's iterator order.
    * @return A list without ownership that must be deleted by the user.
    */
   virtual List<T> *asList() const;

   
   /**
    * Generate a human readable string representing the container.
    */
   virtual String toString() const;
};

