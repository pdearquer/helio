/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Dynamic elements iterator
 * Provide a method to run over all elements of a container.
 * This iterator is intended to be used as dynamic type, so it must be deleted.
 *
 * Remember to call startVersion() in your constructor and checkVersion()
 * on hasMore(), get() and next().
 */
template<class T>
class DynIterator :
      public virtual Object
{
protected:
   /**
    * Current number of references to this iterator.
    * When the number of references is 0, this instance must be deleted.
    */
   _int _refs;
   
   /**
    * Version of the container in which this iteration has began.
    */
   _int _version;

   
   /**
    * Start references count.
    * Remember to call startVersion() in your constructor
    */
   DynIterator();

   /**
    * Saves the container current version.
    * This method must be called once in the constructor.
    */
   void startVersion(Container<T> *container);

   /**
    * Checks that the container version has not changed.
    * Throws an exception if modified.
    */
   virtual void checkVersion(Container<T> *container) const;


public:  
   /**
    * Increment the number of references to this instance.
    */
   virtual _int incrementRef();
   
   /**
    * Decrement the number of references to this instance and returns it.
    * When the number returned is 0, this instance must be deleted.
    */
   virtual _int decrementRef();
   

   /**
    * If the container has more elements to iterate.
    * If this method returns false, any call to get() or next() will throw an exception.
    * Remember to call checkVersion() first thing.
    */
   virtual _bool hasMore() const = 0;
   
   /**
    * Returns the current element in the container.
    * If hasMore() is false, this method will throw an Error::Structure::IterationEnded exception.
    * Remember to call checkVersion() first thing.
    */
   virtual T *get() = 0;
   
   /**
    * Moves to the next element returning the current one.
    * If hasMore() is false, this method will throw an Error::Structure::IterationEnded exception.
    * Remember to call checkVersion() first thing.
    */
   virtual T *next() = 0;
};

