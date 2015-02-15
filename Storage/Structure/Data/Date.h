/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Date and time data
 * Date and time data.
 * It is stored by the seconds from 2000 (up to 2135).
 *
 * Static object.
 */
class Date : 
      public virtual Cloneable, public virtual Orderable<Date>,
      public virtual Hashable<Date>
{
protected:
   /**
    * Seconds from 00:00:00 01/01/2000.
    */
   _uint32 _secs;


public:
   /**
    * Create a new date for now.
    */
   Date();
   
   /**
    * Copy constructor.
    */   
   Date(const Date &other);
   
   /**
    * Copy constructor.
    */   
   Date(const Date *other);
   
   /**
    * Create a new date from the seconds from 00:00:00 01/01/2000. 
    */
   Date(_uint32 secs);
   
   /**
    * Create a new date from a unix time (seconds from 01/01/1970).
    * When the date is out of bounds and saturate is true, the neares value
    * is get, else an exception is thrown.
    */
   Date(_uint32 utime, _bool saturate);

   
   /**
    * Gets the number of seconds from 2000.
    */
   _uint32 secs() const;
   
   /**
    * Sets the number of seconds from 2000.
    */
   _uint32 secs(_uint32 s);
   
   
   /**
    * Sets the date from a unix time (seconds from 01/01/1970).
    * When the date is out of bounds and saturate is true, the neares value
    * is get, else an exception is thrown.
    */
   _uint32 setUnix(_uint32 utime, _bool saturate = false);
   
   /**
    * Returns the date in unix format (seconds from 01/01/1970).
    * When the date is out of bounds and saturate is true, the neares value
    * is get, else an exception is thrown.
    */
   _uint32 getUnix(_bool saturate = false) const;
   

   /**
    * Compare to other date.
    * Return 0 if equals, -1 if less (before) and +1 if more (after) than it.
    */
   virtual _int compare(const Date *other) const;
   
   /**
    * Compare itself with another date.
    * Return true if are the same.
    */
   virtual _bool equals(const Date *other) const;
   
   /**
    * Makes a copy of the object.
    */
   virtual Date *clone() const;

   /**
    * Calculates a hash of the contained information.
    */
   virtual _uint32 makeHash() const;


   /**
    * Generate a human readable string representing the date.
    */
   virtual String toString() const;
   
   /**
    * Returns the current date and time in String format.
    * If you need it in Date format use the empty constructor.
    */
   static String now();
   
   
   /**
    * Assignment operator. Copy other into this.
    */
   void operator =(const Date &other);
   
   
   /**
    * Comparison operator; Equal.
    */
   _bool operator ==(const Date &other) const;
   
   /**
    * Comparison operator; Unequal.
    */
   _bool operator !=(const Date &other) const;

   /**
    * Comparison operator; Less than.
    */
   _bool operator <(const Date &other) const;

   /**
    * Comparison operator; Greater than.
    */
   _bool operator >(const Date &other) const;

   /**
    * Comparison operator; Less than or equal to.
    */
   _bool operator <=(const Date &other) const;

   /**
    * Comparison operator; Greater than or equal to.
    */
   _bool operator >=(const Date &other) const;
};

