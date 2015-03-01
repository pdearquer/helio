/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Interface for objects that can clone themselves
 * Interface for objects that can clone themselves, that is
 * making a copy in a different instance that contains the same
 * information.
 */
class Cloneable : 
      public virtual Object
{
public:
   /**
    * Makes a copy of the object.
    */
   virtual Object *clone() const = 0;
};

