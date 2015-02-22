/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Binary {

Encoding::Encoding()
{
}


void Encoding::setName(String name)
{
   _name = name;
}

String Encoding::name()
{
   return _name;
}


Encoding *Encoding::get(String name)
{
#ifdef __HELIO_STORAGE_STRUCTURE_BINARY_ENCODINGS_ASCII
   if(name.equals("ASCII", true) || name.equals("US-ASCII", true))
      return new Encodings::ASCII();
#endif
   
#ifdef __HELIO_STORAGE_STRUCTURE_BINARY_ENCODINGS_UTF_8
   if(name.equals("UTF-8", true) || name.equals("UTF8", true))
      return new Encodings::UTF_8();
#endif
      
#ifdef __HELIO_STORAGE_STRUCTURE_BINARY_ENCODINGS_UTF_16
   if(name.equals("UTF-16", true) || name.equals("UTF16", true) || name.equals("UCS2", true))
      return new Encodings::UTF_16();
   if(name.equals("UTF-16BE", true) || name.equals("UTF16BE", true))
      return new Encodings::UTF_16(true);
   if(name.equals("UTF-16LE", true) || name.equals("UTF16LE", true))
      return new Encodings::UTF_16(false);
#endif
      
#ifdef __HELIO_STORAGE_STRUCTURE_BINARY_ENCODINGS_UTF_32
   if(name.equals("UTF-32", true) || name.equals("UTF32", true))
      return new Encodings::UTF_32();
   if(name.equals("UTF-32BE", true) || name.equals("UTF32BE", true))
      return new Encodings::UTF_32(true);
   if(name.equals("UTF-32LE", true) || name.equals("UTF32LE", true))
      return new Encodings::UTF_32(false);
#endif
      
#ifdef __HELIO_STORAGE_STRUCTURE_BINARY_ENCODINGS_ISO_8859_1
   if(name.equals("ISO 8859-1", true) || name.equals("ISO/IEC 8859-1", true)
         || name .equals("Latin-1", true) || name.equals("ISO-8859-1", true))
      return new Encodings::ISO_8859_1();
#endif
      
#ifdef __HELIO_STORAGE_STRUCTURE_BINARY_ENCODINGS_ISO_8859_2
   if(name.equals("ISO 8859-2", true) || name.equals("ISO/IEC 8859-2", true)
         || name.equals("Latin-2", true) || name.equals("ISO-8859-2", true))
      return new Encodings::ISO_8859_2();
#endif
   
#ifdef __HELIO_STORAGE_STRUCTURE_BINARY_ENCODINGS_WINDOWS1250
   if(name.equals("Windows-1250", true) || name.equals("CP-1250", true))
      return new Encodings::Windows1250();
#endif

#ifdef __HELIO_STORAGE_STRUCTURE_BINARY_ENCODINGS_WINDOWS1252
   if(name.equals("Windows-1252", true) || name.equals("CP-1252", true))
      return new Encodings::Windows1252();
#endif

#ifdef __HELIO_STORAGE_STRUCTURE_BINARY_ENCODINGS_BASE64
   if(name.equals("Base64", true))
      return new Encodings::Base64();
#endif
   
   Exception *ex = MAKE_ERROR(Exception::Structure::EncodingNotSupported);
   ex->add("encoding", name);
   throw ex;
}

} } }

