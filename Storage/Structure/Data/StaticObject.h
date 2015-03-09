/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Base of every static allocated classes
 * Especial class created to mark the static allocated classes and
 * also prevent other classes to inherit from them.
 */
class StaticObject : 
      public virtual Object
{
friend Storage::Structure::Data::Boolean;
friend Storage::Structure::Data::Character;
friend Storage::Structure::Data::Date;
friend Storage::Structure::Data::Float;
friend Storage::Structure::Data::Integer;
friend Storage::Structure::Data::Pointer;
friend Storage::Structure::Data::String;
template<class T> friend class Storage::Structure::Vector;
template <class K, class V> friend class Storage::Structure::Table;
template<class T> friend class Storage::Structure::Iterator;
friend Storage::Structure::Text::StringBuffer;
friend Storage::Structure::Text::WindowPointer;

private:
   /**
    * Private constructor to prevent any class to inherit from a
    * static object.
    * The classes allowed to be static must be friends of this.
    */
   StaticObject();
};

