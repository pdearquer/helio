/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
/**
 * Object templates implementation.
 */

namespace Storage {
namespace Structure {
namespace Data {

template <class T> _bool Object::is()
{
   return (dynamic_cast<T*>(this) != null);
}

/**

 * Check if belong to some class (constant object version).
 */
template <class T> _bool Object::is() const
{
   return (dynamic_cast<const T*>(this) != null);
}

/**
 * Soft dynamic casting. If it fails returns null.
 */
template <class T> T *Object::tryAs()
{
   return dynamic_cast<T*>(this);
}

/**
 * Soft dynamic constant casting. If it fails returns null.
 */
template <class T> const T *Object::tryAs() const
{
   return dynamic_cast<const T*>(this);
}

/**
 * Hard dynamic casting. If it fails throw an exception.
 */
template <class T> T *Object::as()
{
   T *obj = dynamic_cast<T*>(this);
   if(obj == null)
   {
      Exception *ex = MAKE_ERROR(Exception::InvalidClass);
      ex->add("class", getClass());
      try
      {
         ex->add("expected", (String) typeid(T).name());
      }
      catch(std::bad_typeid &e)
      { }
      throw ex;
   }

   return obj;
}

/**
 * Hard dynamic constant casting. If it fails throw an exception.
 */
template <class T> const T *Object::as() const
{
   const T *obj = dynamic_cast<const T*>(this);
   if(obj == null)
   {
      Exception *ex = MAKE_ERROR(Exception::InvalidClass);
      ex->add("class", getClass());
      try
      {
         ex->add("expected", (String) typeid(T).name());
      }
      catch(std::bad_typeid &e)
      { }
      throw ex;
   }

   return obj;
}

} } }

