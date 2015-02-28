/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Window status descriptor for debug information.
 * Keep trace of the line and characeter to better error reporting.
 */
class WindowStatus :
      public virtual Object
{
protected:
   /**
    * Line number.
    */
   _int _line;
   
   /**
    * Character column or position within the line.
    */
   _int _column;
   
   
public:   
   /**
    * Initial status.
    */
   WindowStatus();
   
   /**
    * Copy the status from another.
    */
   WindowStatus(WindowStatus *other);
   
   
   /**
    * Line number.
    */
   _int line();
   
   /**
    * Character column or position within the line.
    */
   _int column();
   
   
   /**
    * Update the status moving a character.
    */
   void update(_char c);
   
   /**
    * Update the status moving throw the given text.
    */
   void update(const Buffer *text);
   
   /**
    * Update the status moving throw the given text.
    */
   void update(const String &text);
};

