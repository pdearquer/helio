/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

#ifdef __HELIO_STORAGE_STRUCTURE_XML_READER
using namespace Storage::Structure::XML;
using namespace Storage::FileSystem;
#endif

namespace Component {
namespace Error {

Messages *Messages::msgs = null;

Messages::Messages()
{
   lang = "en";
   country = "gb";

#ifdef __HELIO_STORAGE_STRUCTURE_XML_READER
   Storage::FileSystem::Simulation::FileSystem *fs = new Storage::FileSystem::Simulation::FileSystem("./");
   
   FileHandle *file;
   try
   {
      file = fs->file("/Messages.xml");
   }
   catch(Exception *ex)
   {
      delete fs;
      
      Exception *ex2 = RE_MAKE_ERROR("Component.Error.NoMessages", ex);
      ex2->add("database", "/Messages.xml");
      throw ex2;
   }
   
   try
   {
      Reader r;
      r.comments(false);
      xml = r.read(file);
   }
   catch(Exception *ex)
   {
      delete file;
      delete fs;
      
      Exception *ex2 = RE_MAKE_ERROR("Component.Error.BadMessages", ex);
      ex2->add("database", "/Messages.xml");
      throw ex2;
   }

   delete file;
   delete fs;
#endif
}
   
Messages::~Messages()
{
#ifdef __HELIO_STORAGE_STRUCTURE_XML_READER
   delete xml;
#endif
}
   
   
String Messages::getMsg(String id)
{
#ifdef __HELIO_STORAGE_STRUCTURE_XML_READER
   Tag *tag = xml->root();
   
   Element *el = tag->children();
   while(el != null)
   {
      if(el->type() == Element::ELEMENT_TAG)
      {
         tag = el->as<Tag>();
         if(tag->name() == "lang")
         {
            Attribute *at = tag->attributes()->get("id");
            if(at != null && at->value() == lang)
            {
               at = tag->attributes()->get("country");
               if(at != null && at->value() == country)
               {
                  // Language found, get message
                  return getMsg(id, tag);
               }
            }
         }
      }
      
      el = el->next();
   }
   
   Exception *ex = MAKE_ERROR("Component.Error.NoLanguage");
   ex->add("id", id);
   ex->add("lang", lang);
   ex->add("country", country);
   throw ex;
#else
   return id;
#endif   
}

#ifdef __HELIO_STORAGE_STRUCTURE_XML_READER
String Messages::getMsg(String id, Storage::Structure::XML::Tag *tag)
{
   Element *el = tag->children();
   while(el != null)
   {
      if(el->type() == Element::ELEMENT_TAG)
      {
         Tag *msg = el->as<Tag>();
         if(msg->name() == "msg")
         {
            Attribute *at = msg->attributes()->get("id");
            if(at != null && at->value() == id)
            {
               try
               {
                  return msg->read();
               }
               catch(Exception *ex)
               {
                  Exception *ex2 = RE_MAKE_ERROR("Component.Error.NotFound", ex);
                  ex2->add("id", id);
                  ex2->add("lang", lang);
                  ex2->add("country", country);
                  throw ex2;
               }                  
            }
         }
      }
      
      el = el->next();
   }
   
   Exception *ex = MAKE_ERROR("Component.Error.NotFound");
   ex->add("id", id);
   ex->add("lang", lang);
   ex->add("country", country);
   throw ex;
}
#endif

String Messages::get(String id)
{
   if(msgs == null)
   {
      msgs = new Messages();
   }
   
   return msgs->getMsg(id);
}


void Messages::destroy()
{
   if(msgs != null)
   {
      delete msgs;
      msgs = null;
   }
}

} }

