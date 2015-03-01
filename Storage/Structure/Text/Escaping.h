/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Abstract escaping interface.
 * Escaping translation interface.
 */
class Escaping : 
      public virtual Object
{
protected:
   /**
    * Escaping name.
    */
   String _name;
   
   
   /**
    * Protected constructor; setName() must be called.
    */
   Escaping();
   
   /**
    * Sets the escaping name.
    * Must be called once and only once in the constructor.
    */
   virtual void setName(String name);
   
public:
   /**
    * Returns the escaping name.
    */
   virtual String name();  
   
   
   /**
    * Process the escaping rules over the window.
    */
   virtual void escape(WritableWindow *w) = 0;
   
   /**
    * Process the unescaping rules over the window.
    */
   virtual void unescape(WritableWindow *w) = 0;
   
   
   /**
    * Processes the escaping over a String.
    */
   virtual String escString(String input);
   
   /**
    * Processes the unescaping over a String.
    */
   virtual String unescString(String input);
   
   
   /**
    * Gets an escaping by name or throw an exception if not supported.
    */
   static Escaping *get(String name);   
};

