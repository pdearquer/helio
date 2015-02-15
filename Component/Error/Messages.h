/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Multi-language messages manager
 * This class translates exception identifiers to message in the correct language.
 */
class Messages :
   public virtual Object
{
protected:
#ifdef __HELIO_STORAGE_STRUCTURE_XML_READER
   /**
    * Database document.
    */
   Storage::Structure::XML::Document *xml;
#endif

   /**
    * Current language identifier.
    */
   String lang;
   
   /**
    * Current country identifier.
    */
   String country;
   
   
   /**
    * Static messages manager.
    */
   static Messages *msgs;
   

public:
   /**
    * Load the messages database and set default language.
    */
   Messages();
   
   /**
    * Release resources
    */
   ~Messages();
   
   
   /**
    * Retrieve the message for the given exception identifier.
    * Warning: If the message is not found an exception is thrown.
    */
   String getMsg(String id);
   
protected:
#ifdef __HELIO_STORAGE_STRUCTURE_XML_READER
   /**
    * Retrieve the message for the given exception identifier from the language tag.
    * Warning: If the message is not found an exception is thrown.
    */
   String getMsg(String id, Storage::Structure::XML::Tag *tag);
#endif   
   
public:
   /**
    * Retrieve the message for the given exception identifier.
    * Create the manager if needed.
    * Warning: If the message is not found an exception is thrown.
    */
   static String get(String id);
   
   
   /**
    * Destroy the singleton manager if created.
    */
   static void destroy();
};

