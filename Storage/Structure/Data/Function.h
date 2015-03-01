/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Function handler and invoker
 * Keeps reference to a function and allow it to be invoked or executed.
 *
 * The template admit up to 8 type arguments. The first is the return
 * type of the function and the other 7 are function arguments. Do not
 * define those arguments that you don't need.
 *
 * This class is abstract, see MemberFunction or StaticFunction for
 * actual handlers.
 *
 * // Let a method be as:
 * // int MyClass::myFunc(String input);
 * Function<_int, String> *fun = new MemberFunction<_int, MyClass, String>(myObj, &MyClass::myFunc);
 * _int ret = fun->invoke("example");   // Execute the method
 * delete fun;
 */
// Return and 7 arguments implementation
template<typename Tret = void,
      typename Targ1 = void, typename Targ2 = void, typename Targ3 = void,
      typename Targ4 = void, typename Targ5 = void, typename Targ6 = void,
      typename Targ7 = void>
class Function :
      public virtual Object
{
public:
   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke(Targ1 a1, Targ2 a2, Targ3 a3, Targ4 a4, Targ5 a5, Targ6 a6, Targ7 a7) = 0;
};

// Return and 6 arguments implementation
template<typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4, typename Targ5, typename Targ6>
class Function<Tret, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, void> :
      public virtual Object
{
public:
   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke(Targ1 a1, Targ2 a2, Targ3 a3, Targ4 a4, Targ5 a5, Targ6 a6) = 0;
};

// Return and 5 arguments implementation
template<typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4, typename Targ5>
class Function<Tret, Targ1, Targ2, Targ3, Targ4, Targ5, void, void> :
      public virtual Object
{
public:
   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke(Targ1 a1, Targ2 a2, Targ3 a3, Targ4 a4, Targ5 a5) = 0;
};

// Return and 4 arguments implementation
template<typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4>
class Function<Tret, Targ1, Targ2, Targ3, Targ4, void, void, void> :
      public virtual Object
{
public:
   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke(Targ1 a1, Targ2 a2, Targ3 a3, Targ4 a4) = 0;
};

// Return and 3 arguments implementation
template<typename Tret,
      typename Targ1, typename Targ2, typename Targ3>
class Function<Tret, Targ1, Targ2, Targ3, void, void, void, void> :
      public virtual Object
{
public:
   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke(Targ1 a1, Targ2 a2, Targ3 a3) = 0;
};

// Return and 2 arguments implementation
template<typename Tret,
      typename Targ1, typename Targ2>
class Function<Tret, Targ1, Targ2, void, void, void, void, void> :
      public virtual Object
{
public:
   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke(Targ1 a1, Targ2 a2) = 0;
};

// Return and 1 argument implementation
template<typename Tret,
      typename Targ1>
class Function<Tret, Targ1, void, void, void, void, void, void> :
      public virtual Object
{
public:
   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke(Targ1 a1) = 0;
};

// Only return implementation
template<typename Tret>
class Function<Tret, void, void, void, void, void, void, void> :
      public virtual Object
{
public:
   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke() = 0;
};

// Void return implementation
template<>
class Function<void, void, void, void, void, void, void, void> :
      public virtual Object
{
public:
   /**
    * Invokes or executes the function.
    */
   virtual void invoke() = 0;
};

