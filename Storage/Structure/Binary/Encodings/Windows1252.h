/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Windows-1252 (CP-1252) encoding
 * Western  European language Microsoft Windows code page encoding.
 */
class Windows1252 : 
      public virtual Encoding
{
protected:
   /**
    * 80 to 9F codes translation table.
    */
   static const _uint16 _table[0x20];
   
   
public:

   /**
    * Create an Windows-1252 encoding.
    */
   Windows1252();
   
   
   /**
    * Check if a character is in the set of valid characters for this encode.
    */
   virtual _bool canEncode(_char c);
   
protected:   
   /**
    * Gets the code for the given character or -1 if does not exist.
    */
   _int getCode(__char c);
   
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

