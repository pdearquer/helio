/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Base64 encoding
 * Radix-64 ASCII representation for binary data.
 */
class Base64 : 
      public virtual Encoding
{
protected:
   /**
    * Characters table without last two symbols (0x3E characters).
    */
   static_const_String _table =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz"
      "0123456789";
         
   
   /**
    * If the end have to be padded (with '=' or '==')
    */
   _bool _padding;
   
   /**
    * Line lenght or -1 if no insert line feeds.
    */
   _int _line;
   
   /**
    * Line character position.
    */
   _int _linePos;
   

   /**
    * Last two symbol characters (indeces 62 and 63).
    */
   _char _char62;
   _char _char63;
 
 
   /**
    * If the end has been reached.
    */
   _bool _end;
   
   
public:
   /**
    * Create an Base64 encoding.
    */
   Base64();
   
   
   /**
    * Check if a character is in the set of valid characters for this encode.
    */
   virtual _bool canEncode(_char c);
   
protected:   
   /**
    * Gets the value for the given character or -1 if does not exist.
    */
   _int getValue(__char c);
   
   /**
    * Return the character for the given value.
    */
   _char getChar(_int val);
   
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
   
   
   /**
    * Gets if the end have to be padded (with '=' or '==')
    */
   _bool padding();
   
   /**
    * Sets if the end have to be padded (with '=' or '==')
    */
   _bool padding(_bool pad);
   
   
   /**
    * Gets the line lenght or -1 if no insert line feeds.
    */
   _int line();
   
   /**
    * Sets the line lenght or -1 if no insert line feeds.
    */
   _int line(_int lin);
   
   /**
    * Gets the 62 symbol character.
    */
   _char char62();

   /**
    * Sets the 62 symbol character.
    */
   void setChar62(_char c);

   /**
    * Gets the 63 symbol character.
    */
   _char char63();

   /**
    * Sets the 63 symbol character.
    */
   void setChar63(_char c);
   
   /**
    * Restore normal symbols ('+' and '/').
    */
   void modeNormal();

   /**
    * Set URL symbols ('-' and '_').
    */
   void modeURL();
   
   /**
    * Set XML symbols ('.' and '-').
    */
   void modeXML();
};

