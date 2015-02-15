/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Container elements iterator.
 * Provide a method to run through all the elements of a container.
 * Static iterator that wrap the dynamic polymorphic iterator.
 *
 * If you want to use this class directly, do it as:
 *    Iterator<MyClass> it = container->iterate();
 *    while(it.hasMore())
 *    {
 *       MyClass *el = it.next();
 *       // Do something with el
 *    }
 *
 * Static object.
 */
template<class T>
class Iterator :
      public virtual Object
{
protected:
   /**
    * Dynamic iterator reference
    */
   DynIterator<T> *_it;
   
   
   /**
    * Empty constructor for EndIterator to be created with no real iterator.
    */
   Iterator();
public:

   /**
    * Create the iterator from the dynamic one.
    */
   Iterator(DynIterator<T> *it);
   
   /**
    * Copy constructor.
    */   
   Iterator(const Iterator<T> &other);
   
   /**
    * Ensure correct memory clean.
    */
   virtual ~Iterator();
   
   
   /**
    * Assingment operator.
    */
   const Iterator<T> &operator=(const Iterator<T> &other);


   /**
    * Returns the internal dynamic reference.
    */
   DynIterator<T> *dynIter() const;
   
   
   /**
    * Checks if the container has more elements to iterate.
    * That means that get() returns a valid element.
    */
   _bool hasMore() const;
   
   /**
    * Returns the current element of the container.
    */
   T *get();
   
   /**
    * Moves to the next element returning the current one.
    */
   T *next();
     
   /**
    * Check if the iteration has finished.
    * Not a real comparision, it only compares againts EndIterator.
    */
   _bool operator!=(const Iterator<T> &otro) const;
   
   /**
    * Returns the current element.
    */
   T *operator*();
   
   /**
    * Move to the next element.
    */
   const Iterator<T> &operator++();
   
   
   /**
    * Return an invalid end iterator.
    */
   static Iterator<T> makeEnd();
};

