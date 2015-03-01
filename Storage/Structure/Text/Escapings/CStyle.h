/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** C style strings escaping
 * C style strings escaping ("" delimiters are NOT included).
 */
class CStyle : 
      public virtual Escaping
{
protected:
   /**
    * String containing all special characters.
    */
   static_const_String SPECIAL = "\t\n\r\"\'\b\a\f\\";


   /**
    * Hexadecimal escaping formatter.
    */
   Format *fmt;
   
   
public:
   /**
    * Create a C Style escaping converser.
    */
   CStyle();

   /**
    * Release the converser.
    */
   ~CStyle();


   /**
    * Process the escaping rules over the window.
    */
   virtual void escape(WritableWindow *w);
   
   /**
    * Process the unescaping rules over the window.
    */
   virtual void unescape(WritableWindow *w);
};

