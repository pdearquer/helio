/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Member function or method handler and invoker
 * Function implementation to handle member functions or methods
 * of a class.
 *
 * NEVER delete the object refered before this handler.
 *
 * Use example:
 *
 * // Let a method be as:
 * // _int MyClass::myFunc(String input);
 * MyClass *myObj = new MyClass();
 * Function<_int, String> *fun = new MemberFunction<MyClass, _int, String>(myObj, &MyClass::myFunc);
 * _int ret = fun->invoke("example");   // Excute the method
 * delete fun;
 *
 * The object modification is not allowed in purpose.
 */
// Return and 7 arguments implementation
template<class C, typename Tret = void,
      typename Targ1 = void, typename Targ2 = void, typename Targ3 = void,
      typename Targ4 = void, typename Targ5 = void, typename Targ6 = void,
      typename Targ7 = void>
class MemberFunction :
      public virtual Function<Tret, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7>
{
public:
   /**
    * Member function prototype
    */
   typedef Tret (C::*proto)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7);

private:
   /**
    * Object refence.
    */
   C *_obj;
   
   /**
    * Function pointer.
    */
   proto _ptr;

public:
   /**
    * Keep the object reference and method.
    * Remenber the indirection:
    *  new MemberFunction<...>(myObj, &MyClass:myMethod);
    */
   MemberFunction(C *obj, proto ptr);

   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke(Targ1 a1, Targ2 a2, Targ3 a3, Targ4 a4, Targ5 a5, Targ6 a6, Targ7 a7);
   
   /**
    * Gets the object instance.
    */
   virtual C *getObject();
};

// Return and 6 arguments implementation
template<class C, typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4, typename Targ5, typename Targ6>
class MemberFunction<C, Tret, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, void> :
      public virtual Function<Tret, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, void>
{
public:
   /**
    * Member function prototype
    */
   typedef Tret (C::*proto)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6);

private:
   /**
    * Object refence.
    */
   C *_obj;

   /**
    * Function pointer.
    */
   proto _ptr;

public:
   /**
    * Keep the object reference and method.
    * Remenber the indirection:
    *  new MemberFunction<...>(myObj, &MyClass:myMethod);
    */
   MemberFunction(C *obj, proto ptr);

   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke(Targ1 a1, Targ2 a2, Targ3 a3, Targ4 a4, Targ5 a5, Targ6 a6);
   
   /**
    * Gets the object instance.
    */
   virtual C *getObject();
};

// Return and 5 arguments implementation
template<class C, typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4, typename Targ5>
class MemberFunction<C, Tret, Targ1, Targ2, Targ3, Targ4, Targ5, void, void> :
      public virtual Function<Tret, Targ1, Targ2, Targ3, Targ4, Targ5, void, void>
{
public:
   /**
    * Member function prototype
    */
   typedef Tret (C::*proto)(Targ1, Targ2, Targ3, Targ4, Targ5);

private:
   /**
    * Object refence.
    */
   C *_obj;

   /**
    * Function pointer.
    */
   proto _ptr;

public:
   /**
    * Keep the object reference and method.
    * Remenber the indirection:
    *  new MemberFunction<...>(myObj, &MyClass:myMethod);
    */
   MemberFunction(C *obj, proto ptr);

   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke(Targ1 a1, Targ2 a2, Targ3 a3, Targ4 a4, Targ5 a5);
   
   /**
    * Gets the object instance.
    */
   virtual C *getObject();
};

// Return and 4 arguments implementation
template<class C, typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4>
class MemberFunction<C, Tret, Targ1, Targ2, Targ3, Targ4, void, void, void> :
      public virtual Function<Tret, Targ1, Targ2, Targ3, Targ4, void, void, void>
{
public:
   /**
    * Member function prototype
    */
   typedef Tret (C::*proto)(Targ1, Targ2, Targ3, Targ4);

private:
   /**
    * Object refence.
    */
   C *_obj;

   /**
    * Function pointer.
    */
   proto _ptr;

public:
   /**
    * Keep the object reference and method.
    * Remenber the indirection:
    *  new MemberFunction<...>(myObj, &MyClass:myMethod);
    */
   MemberFunction(C *obj, proto ptr);

   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke(Targ1 a1, Targ2 a2, Targ3 a3, Targ4 a4);
   
   /**
    * Gets the object instance.
    */
   virtual C *getObject();
};

// Return and 3 arguments implementation
template<class C, typename Tret,
      typename Targ1, typename Targ2, typename Targ3>
class MemberFunction<C, Tret, Targ1, Targ2, Targ3, void, void, void, void> :
      public virtual Function<Tret, Targ1, Targ2, Targ3, void, void, void, void>
{
public:
   /**
    * Member function prototype
    */
   typedef Tret (C::*proto)(Targ1, Targ2, Targ3);

private:
   /**
    * Object refence.
    */
   C *_obj;

   /**
    * Function pointer.
    */
   proto _ptr;

public:
   /**
    * Keep the object reference and method.
    * Remenber the indirection:
    *  new MemberFunction<...>(myObj, &MyClass:myMethod);
    */
   MemberFunction(C *obj, proto ptr);

   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke(Targ1 a1, Targ2 a2, Targ3 a3);
   
   /**
    * Gets the object instance.
    */
   virtual C *getObject();
};

// Return and 2 arguments implementation
template<class C, typename Tret,
      typename Targ1, typename Targ2>
class MemberFunction<C, Tret, Targ1, Targ2, void, void, void, void, void> :
      public virtual Function<Tret, Targ1, Targ2, void, void, void, void, void>
{
public:
   /**
    * Member function prototype
    */
   typedef Tret (C::*proto)(Targ1, Targ2);

private:
   /**
    * Object refence.
    */
   C *_obj;

   /**
    * Function pointer.
    */
   proto _ptr;

public:
   /**
    * Keep the object reference and method.
    * Remenber the indirection:
    *  new MemberFunction<...>(myObj, &MyClass:myMethod);
    */
   MemberFunction(C *obj, proto ptr);

   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke(Targ1 a1, Targ2 a2);
   
   /**
    * Gets the object instance.
    */
   virtual C *getObject();
};

// Return and 1 argument implementation
template<class C, typename Tret,
      typename Targ1>
class MemberFunction<C, Tret, Targ1, void, void, void, void, void, void> :
      public virtual Function<Tret, Targ1, void, void, void, void, void, void>
{
public:
   /**
    * Member function prototype
    */
   typedef Tret (C::*proto)(Targ1);

private:
   /**
    * Object refence.
    */
   C *_obj;

   /**
    * Function pointer.
    */
   proto _ptr;

public:
   /**
    * Keep the object reference and method.
    * Remenber the indirection:
    *  new MemberFunction<...>(myObj, &MyClass:myMethod);
    */
   MemberFunction(C *obj, proto ptr);

   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke(Targ1 a1);
   
   /**
    * Gets the object instance.
    */
   virtual C *getObject();
};

// Only return implementation
template<class C, typename Tret>
class MemberFunction<C, Tret, void, void, void, void, void, void, void> :
      public virtual Function<Tret, void, void, void, void, void, void, void>
{
public:
   /**
    * Member function prototype
    */
   typedef Tret (C::*proto)();

private:
   /**
    * Object refence.
    */
   C *_obj;

   /**
    * Function pointer.
    */
   proto _ptr;

public:
   /**
    * Keep the object reference and method.
    * Remenber the indirection:
    *  new MemberFunction<...>(myObj, &MyClass:myMethod);
    */
   MemberFunction(C *obj, proto ptr);

   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke();
   
   /**
    * Gets the object instance.
    */
   virtual C *getObject();
};

// Void return implementation
template<class C>
class MemberFunction<C, void, void, void, void, void, void, void, void> :
      public virtual Function<void, void, void, void, void, void, void, void>
{
public:
   /**
    * Member function prototype
    */
   typedef void (C::*proto)();

private:
   /**
    * Object refence.
    */
   C *_obj;

   /**
    * Function pointer.
    */
   proto _ptr;

public:
   /**
    * Keep the object reference and method.
    * Remenber the indirection:
    *  new MemberFunction<...>(myObj, &MyClass:myMethod);
    */
   MemberFunction(C *obj, proto ptr);

   /**
    * Invokes or executes the function.
    */
   virtual void invoke();
   
   /**
    * Gets the object instance.
    */
   virtual C *getObject();
};

