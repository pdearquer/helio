/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** HTML especial characters escaping
 * HTML especial characters escaping.
 * Entities used can be added or removed.
 */
class HTML : 
      public virtual Escaping
{
protected:
   /**
    * Entities table.
    */
   Table<Character, String> _entities;


public:
   /**
    * Create a HTML escaping conversor.
    */
   HTML();


   /**
    * Add a new entity to escape.
    */
   void addEntity(Character c, String name);


   /**
    * Process the escaping rules over the window.
    */
   virtual void escape(WritableWindow *w);
   
   /**
    * Process the unescaping rules over the window.
    */
   virtual void unescape(WritableWindow *w);
};

