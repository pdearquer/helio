/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** ASCII encoding
 * American Standard Code for Information Interchange.
 * This implementation include C0 and C1 control codes.
 */
class Ascii : 
      public virtual Encoding
{
   friend class Storage::Structure::Data::Character;
   friend class Storage::Structure::Data::String;
   
public:
   /**
    * Create an ASCII encoding.
    */
   Ascii();
   
   
   /**
    * Check if a character is in the set of valid characters for this encode.
    */
   virtual _bool canEncode(_char c);
   
protected:   
   /**
    * Check if a character is in the set of valid characters for this encode.
    */
   static _bool isValid(__char c);
   
public:   
   /**
    * Decode a buffer of bytes and append it to a string of characters.
    * Returns the actual number of bytes decoded (processed).
    * If finish is true, all bytes are forced to be decoded.
    */
   virtual _int decode(const Buffer *in, Text::Buffer *out, _bool finish = true);
   
   /**
    * Encode a string of characters and add it to a buffer of bytes.
    * Returns the actual number of characters encoded (processed).
    * If finish is true, all characters are forced to be encoded.
    */
   virtual _int encode(const Text::Buffer *in, Buffer *out, _bool finish = true);
};

