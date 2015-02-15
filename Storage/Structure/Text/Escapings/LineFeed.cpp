/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Text {
namespace Escapings {

LineFeed::LineFeed()
{
   setName("LineFeed");
}


void LineFeed::escape(WritableWindow *w)
{
   WindowPointer start = w->start();
   WindowPointer result = w->result();

   while(w->findAny("\r\n"))
   {
      start = result;
      
      if(w->hasFinished(start))
      {
         w->replace('\n', start, start);
         return;
      }
      else
      {
         result = start + 1;
         Character c1 = w->getChar(start);
         Character c2 = w->getChar(result);
         
         if(c1 == '\r')
         {
            if(c2 == '\n')
            {
               w->replace('\n', start, result);
               start++;
            }
            else
            {
               w->replace('\n', start, start);
            }
         }
         else if(c1 == '\n')
         {
            if(c2 == '\r')
            {
               w->replace('\n', start, result);
               start++;
            }
         }
         
         if(w->hasFinished(start))
            return;
            
         start++;
      }
   }
}
   
void LineFeed::unescape(WritableWindow *w)
{
   WindowPointer start = w->start();
   WindowPointer result = w->result();

   while(w->find('\n'))
   {
      start = result;
      
      w->replace("\r\n", start, start);
      start++;
      
      if(w->hasFinished(start))
         return;
         
      start++;
   }
}

} } } }
