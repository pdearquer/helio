/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Binary {

Decoder::Decoder(Binary::Input *in, Encoding *enc, _int step)
{
   _in = in;
   _enc = enc;
   _step = step;
}
   
Decoder::Decoder(Binary::Input *in, String encoding, _int step)
{
   _in = in;
   _enc = Encoding::get(encoding);
   _step = step;
}
   
Decoder::~Decoder()
{
   delete _enc;
}
   
   
_int Decoder::read(Text::Buffer *buf, _int chars, _int start)
{
   if(start < 0 || start > buf->length() || chars < 0)
   {
      MAKE_ERROR(ex, Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("characters", chars);
      ex->addInt("length", buf->length());
      throw ex;
   }
   
   if(chars == 0)
      chars = buf->capacity() - start;
   
   if(chars <= 0)
      return 0;      

   _int count = 0;
   _bool finish = false;
   _int tmp;
   
   while(true)
   {      
      // Copy read chars (empty outbuf)
      if(_outbuf.length() > 0)
      {
         tmp = chars;
         if(tmp > _outbuf.length())
            tmp = _outbuf.length();

         buf->add(start, &_outbuf, tmp);
         start += tmp;
         count += tmp;
         _outbuf.move(tmp);
      }
      
      if(count >= chars || finish)
         return count;
         
      // Read more
      tmp = chars - count;
      if(tmp < _step)
         tmp = _step;
      if(_in->read(&_inbuf, tmp, _inbuf.length()) < tmp)
         finish = true;
      tmp = _enc->decode(&_inbuf, &_outbuf, finish);
      _inbuf.move(tmp);
   }
}


Encoding *Decoder::encoding()
{
   return _enc;
}
   
Encoding *Decoder::encoding(Encoding *enc)
{
   delete _enc;
   _enc = enc;
   return _enc;
}

Encoding *Decoder::encoding(String enc)
{
   delete _enc;
   _enc = Encoding::get(enc);
   return _enc;  
}

_int Decoder::step()
{
   return _step;
}
   
_int Decoder::step(_int step)
{
   if(step < 1)
   {
      MAKE_ERROR(ex, Error::Structure::InvalidLength);
      ex->addInt("step", step);
      throw ex;
   }
   
   _step = step;
   return _step;
}

} } }

