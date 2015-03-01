/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** UTF-8 encoding
 * UCS Transformation Format to 8 bit words
 */
class Utf8 : 
      public virtual Encoding
{
   friend class Storage::Structure::Data::String;
   friend class Storage::Structure::Text::Buffer;

public:

   /**
    * Create an UTF-8 encoding.
    */
   Utf8();
   
   
   /**
    * Check if a character is in the set of valid characters for this encode.
    */
   virtual _bool canEncode(_char c);
    
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
   
   
protected:
   /**
    * Returns the number of bytes of an UTF-8 encoded character.
    */
   static _int charlen(const _uint8 *buf);
   
   /**
    * Returns the number of bytes required to encode UTF-8 a character.
    */
   static _int charlen(_char c);
   
   /**
    * Encode a single character in a UTF-8 raw buffer.
    * Returns the number of bytes written.
    */
   static _int charenc(_char ch, _uint8 *buf);
   
   /**
    * Decode a single character from a UTF-8 raw buffer.
    * Returns the number of bytes read.
    */
   static _int chardec(_char *ch, const _uint8 *buf);
   
   /**
    * Returns the number of UTF-8 characters in a buffer.
    */
   static _int charcount(const _uint8 *buf, _int bytes);
   
   /**
    * Returns the number of bytes of the UTF-8 buffer are len characters.
    */
   static _int charbytes(const _uint8 *buf, _int len);
};

