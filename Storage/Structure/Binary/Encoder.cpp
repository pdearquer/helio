/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Binary {

Encoder::Encoder(Binary::Output *out, Encoding *enc)
{
   _out = out;
   _enc = enc;
}
   
Encoder::Encoder(Binary::Output *out, String encoding)
{
   _out = out;
   _enc = Encoding::get(encoding);  
}
   
Encoder::~Encoder()
{
   finish();
         
   delete _enc;
}
   
   
void Encoder::write(Text::Buffer *buf, _int chars, _int start)
{
   if(start < 0 || chars < 0)
   {
      MAKE_ERROR(ex, Error::Structure::OutOfBounds);
      ex->addInt("start", start);
      ex->addInt("characters", chars);
      throw ex;
   }
      
   if(chars == 0)
      chars = buf->length();
      
   if(chars == 0)
      return;
      
   _inbuf.add(buf, chars, start);
   
   _int tmp;
   tmp = _enc->encode(&_inbuf, &_outbuf, false);
   _inbuf.move(tmp);
     
   if(_outbuf.length() > 0)
   {
      _out->write(&_outbuf);
      _outbuf.clear();
   }
}

void Encoder::finish()
{
   if(_inbuf.length() > 0)
      _enc->encode(&_inbuf, &_outbuf, true);
     
   if(_outbuf.length() > 0)
      _out->write(&_outbuf);
}


Encoding *Encoder::encoding()
{
   return _enc;
}
   
Encoding *Encoder::encoding(Encoding *enc)
{
   delete _enc;
   _enc = enc;
   return _enc;
}

Encoding *Encoder::encoding(String enc)
{
   delete _enc;
   _enc = Encoding::get(enc);
   return _enc;  
}

} } }

