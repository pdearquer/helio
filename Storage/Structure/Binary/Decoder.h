/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Decode a byte input.
 * Convert a byte input to character input decoding characters.
 */
class Decoder : 
      public virtual Storage::Structure::Text::Input
{
protected:
   /**
    * Byte input reference.
    */
   Binary::Input *_in;
   
   /**
    * Encoding processor.
    */
   Encoding *_enc;
   
   /**
    * Bytes to read in each step.
    */
   _int _step;
   
   /**
    * Reading buffers.
    */
   Buffer _inbuf;
   Text::Buffer _outbuf; 
   
   
public:
   /**
    * Prepare the decoder.
    */
   Decoder(Binary::Input *in, Encoding *enc, _int step = 128);
   
   /**
    * Prepare the decoder getting the encoding by name.
    */
   Decoder(Binary::Input *in, String encoding, _int step = 128);
         
   /**
    * Clean up the encoding (not the input).
    */
   ~Decoder();
   
   
   /**
    * Read some characters to the buffer (increase capacity if necesary).
    * Returns the number of characters read.
    * If chars is zero, buffer lenght is the requested size.
    * Argument start is the start of the buffer where place characters.
    */
   virtual _int read(Text::Buffer *buf, _int chars = 0, _int start = 0);
   
   
   /**
    * Gets current encoding.
    */
   Encoding *encoding();
   
   /**
    * Sets current encoding.
    */
   Encoding *encoding(Encoding *enc);
   
   /**
    * Sets current encoding by name.
    */
   Encoding *encoding(String enc);
   
   /**
    * Gets the number of bytes to read in each step.
    */
   _int step();
   
   /**
    * Sets the number of bytes to read in each step.
    */
   _int step(_int step);
};

