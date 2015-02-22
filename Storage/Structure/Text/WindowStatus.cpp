/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Text {

WindowStatus::WindowStatus()
{
   _line = 1;
   _column = 1;
}
   
WindowStatus::WindowStatus(WindowStatus *other)
{
   _line = other->_line;
   _column = other->_column;
}


_int WindowStatus::line()
{
   return _line;
}
   
_int WindowStatus::column()
{
   return _column;
}
   
   
void WindowStatus::update(_char c)
{
   if(c == '\n')
   {
      _line++;
      _column = 1;
   }
   else
   {
      _column++;
   }
}

void WindowStatus::update(const Buffer *text)
{
   for(_int i = 0; i < text->length(); i++)
      update(text->get(i));
}
   
void WindowStatus::update(const String &text)
{
   for(_int i = 0; i < text.length(); i++)
      update(text.get(i));
}

} } }

