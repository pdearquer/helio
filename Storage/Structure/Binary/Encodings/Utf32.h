/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** UTF-32 encoding
 * UCS Transformation Format to 32 bit words
 */
class Utf32 : 
      public virtual Encoding
{
protected:
   /**
    * Say if byte order is Big Endian (true) or Little Endian (false).
    */   
   _bool _endian;   
   
   /**
    * Say if send the BOM character.
    */
   _bool _bom;
   
   
public:

   /**
    * Create an UTF-32 encoding.
    * Use target endianness (at least BOM found)
    */
   Utf32();
   
   /**
    * Create an UTF-32 encoding forcing Big or Little Endian.
    */
   Utf32(_bool bigEndian);
   
   
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
   
   
   /** 
    * Gets if the byte order is or not Big Endian.
    */
   _bool bigEndian();
   
   /** 
    * Gets if the byte order is or not Little Endian.
    */
   _bool littleEndian();
   
   
   /**
    * Gets if send the BOM character or if it has been found.
    */
   _bool bom();
   
   /**
    * Sets if send the BOM character (when sent the flag is disabled).
    */
   void setBom(_bool bom);
};

