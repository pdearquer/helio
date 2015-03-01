/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Covert Line Feed conventions in texts
 * Converts Line Feeds to Unix style ('\n' characters) and unescape back
 * to Windows style ('\r' and '\n' characters).
 */
class LineFeed : 
      public virtual Escaping
{
public:
   /**
    * Create a Line Feed escaping converser.
    */
   LineFeed();


   /**
    * Process the escaping rules over the window.
    */
   virtual void escape(WritableWindow *w);
   
   /**
    * Process the unescaping rules over the window.
    */
   virtual void unescape(WritableWindow *w);
};

