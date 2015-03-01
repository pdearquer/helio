/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Encode a character output.
 * Convert a character output to byte output encoding characters.
 */
class Encoder : 
      public virtual Storage::Structure::Text::Output
{
protected:
   /**
    * Byte output reference.
    */
   Binary::Output *_out;
   
   /**
    * Encoding processor.
    */
   Encoding *_enc;
   
   /**
    * Reading buffers.
    */
   Text::Buffer _inbuf;
   Buffer _outbuf; 
   
   
public:
   /**
    * Prepare the encoder.
    */
   Encoder(Binary::Output *out, Encoding *enc);
   
   /**
    * Prepare the encoder getting the encoding by name.
    */
   Encoder(Binary::Output *out, String encoding);
         
   /**
    * Finish the write and clean up the encoding (not the output).
    */
   ~Encoder();
   
   
   /**
    * Write a buffer of characters.
    * If chars is zero, buffer length is the requested size.
    * Argument start is the start of the buffer where get characters.
    */
   virtual void write(Text::Buffer *buf, _int chars = 0, _int start = 0);
   using Output::write;
   
   /**
    * Ensures the end of write.
    */
   void finish();
   
   
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
};

