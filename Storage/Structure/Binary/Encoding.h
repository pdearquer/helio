/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Abstract encoding
 * Generic framework for encoding implementations.
 */
class Encoding : 
      public virtual Object
{
protected:
   /**
    * Encoding name.
    */
   String _name;
   
   
   /**
    * Protected constructor; setName() must be called.
    */
   Encoding();
   
   /**
    * Sets the encoding name.
    * Must be called once and only once in the constructor.
    */
   virtual void setName(String name);
   
public:

   /**
    * Returns the encoding name.
    */
   virtual String name();
   
   
   /**
    * Check if a character is in the set of valid characters for this encode.
    */
   virtual _bool canEncode(_char c) = 0;
   
   
   /**
    * Decode a buffer of bytes and append it to a string of characters.
    * Returns the actual number of bytes decoded (processed).
    * If finish is true, all bytes are forced to be decoded.
    */
   virtual _int decode(const Buffer *in, Text::Buffer *out, _bool finish = true) = 0;
   
   /**
    * Encode a string of characters and add it to a buffer of bytes.
    * Returns the actual number of characters encoded (processed).
    * If finish is true, all characters are forced to be encoded.
    */
   virtual _int encode(const Text::Buffer *in, Buffer *out, _bool finish = true) = 0;
   
   
   /**
    * Gets an encoding by name or throw an exception if not supported.
    */
   static Encoding *get(String name);
};

