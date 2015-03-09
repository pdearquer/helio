/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Array list for static types
 * Array list of a certain kind of elements implemented and handled as static types.
 * It is implemented as a template to avoid casting.
 */
template <class T>
class Vector :
      public virtual StaticObject
{
protected:
   /**
    * Array of stored elements.
    */
   T *_elements;
   
   /**
    * Number of elements of the container.
    */
   _int _count;
   
   /**
    * Number of elements allocated in the array.
    */
   _int _size;
   
   
public:
   /**
    * Create an empty vector.
    */
   Vector();
   
   /**
    * Create an empty vector ensuring a minimum capacity.
    */
   Vector(_int capacity);
   
   /**
    * Copy other vector.
    */
   Vector(const Vector<T> &other);
   
   /**
    * Destroy the vector.
    */
   virtual ~Vector();
   

   /**
    * Gets the number of elements.
    */
   _int count() const;
   
   /**
    * Sets the total number of elements. Remove the remaining
    */
   void setCount(_int num);
   
   /**
    * Says if the vector has no element.
    */
   _bool isEmpty() const;
   
   
   /**
    * Adds an element at the end of the vector and returns its index
    */
   _int add(T obj);
   
   /**
    * Sets the indicated element with a new given.
    */
   void set(_int index, T obj);
   
   /**
    * Returns the indicated element of the list.
    */
   T get(_int index) const;
         
   /**
    * Index operator (write allowed)
    */
   T &operator [](const _int index);
   
   
   /**
    * Adds an element at the end of the array.
    */
   T push(T obj);
   
   /**
    * Returns and remove the last element of the array.
    */
   T pop();
   
   /**
    * Returns the last element of the array but doesn't remove it.
    */
   T peek() const;
   
   
   /**
    * Checks if the element is in the vector.
    */
   _bool contains(T obj) const;
   
   /**
    * Removes an element.
    * Note that ahead elements are moved back one position.
    * @return Always true.
    */
   _bool remove(_int index);
   
   /**
    * Removes all elements.
    */
   void clear();
   
   
   /**
    * Returns the position of an object.
    * Returns -1 if the object isn't in the list.
    */
   _int indexOf(T obj) const;
   
   /**
    * Returns the position of an object, starting after an indicated element.
    * Returns -1 if the object isn't in the list.
    */
   _int indexOf(T obj, _int start) const;   
    
   
   /**
    * Compare itself with another vector.
    * Return true if the information is similar, but note that comparison is
    * performed by the == operator.
    */
   virtual _bool equals(const Vector<T> &other) const;
   using Object::equals;
   
   
   /**
    * Generate a human readable string representing the object information.
    */
   virtual String toString() const;
   
   
   /**
    * Ensure a minimum capacity.
    */
   void ensureSize(_int min);
};

