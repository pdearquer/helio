/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Static function handler and invoker
 * Function implementation to handle static functions whether
 * within a class or alone.
 *
 * Use example:
 *
 * // Let a static method be as:
 * // static _int MyClass::myFunc(String input);
 * Function<_int, String> *fun = new StaticFunction<_int, String>(&MyClass::myFunc);
 * _int ret = fun->invoke("example");   // Excute the method
 * delete fun;
 */
// Return and 7 arguments implementation
template<typename Tret = void,
      typename Targ1 = void, typename Targ2 = void, typename Targ3 = void,
      typename Targ4 = void, typename Targ5 = void, typename Targ6 = void,
      typename Targ7 = void>
class StaticFunction :
      public virtual Function<Tret, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7>
{
public:
   /**
    * Static function prototype
    */
   typedef Tret (*proto)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7);

private:
   /**
    * Function pointer.
    */
   proto _ptr;

public:
   /**
    * Keep a pointer to the function for future invokations.
    * Remenber the indirection:
    *  new StaticFunction<...>(&MyClass:staticFun);
    */
   StaticFunction(proto ptr);

   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke(Targ1 a1, Targ2 a2, Targ3 a3, Targ4 a4, Targ5 a5, Targ6 a6, Targ7 a7);
};

// Return and 6 arguments implementation
template<typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4, typename Targ5, typename Targ6>
class StaticFunction<Tret, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, void> :
      public virtual Function<Tret, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, void>
{
public:
   /**
    * Static function prototype
    */
   typedef Tret (*proto)(Targ1, Targ2, Targ3, Targ4, Targ5, Targ6);

private:
   /**
    * Function pointer.
    */
   proto _ptr;

public:
   /**
    * Keep a pointer to the function for future invokations.
    * Remenber the indirection:
    *  new StaticFunction<...>(&MyClass:staticFun);
    */
   StaticFunction(proto ptr);

   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke(Targ1 a1, Targ2 a2, Targ3 a3, Targ4 a4, Targ5 a5, Targ6 a6);
};

// Return and 5 arguments implementation
template<typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4, typename Targ5>
class StaticFunction<Tret, Targ1, Targ2, Targ3, Targ4, Targ5, void, void> :
      public virtual Function<Tret, Targ1, Targ2, Targ3, Targ4, Targ5, void, void>
{
public:
   /**
    * Static function prototype
    */
   typedef Tret (*proto)(Targ1, Targ2, Targ3, Targ4, Targ5);

private:
   /**
    * Function pointer.
    */
   proto _ptr;

public:
   /**
    * Keep a pointer to the function for future invokations.
    * Remenber the indirection:
    *  new StaticFunction<...>(&MyClass:staticFun);
    */
   StaticFunction(proto ptr);

   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke(Targ1 a1, Targ2 a2, Targ3 a3, Targ4 a4, Targ5 a5);
};

// Return and 4 arguments implementation
template<typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4>
class StaticFunction<Tret, Targ1, Targ2, Targ3, Targ4, void, void, void> :
      public virtual Function<Tret, Targ1, Targ2, Targ3, Targ4, void, void, void>
{
public:
   /**
    * Static function prototype
    */
   typedef Tret (*proto)(Targ1, Targ2, Targ3, Targ4);

private:
   /**
    * Function pointer.
    */
   proto _ptr;

public:
   /**
    * Keep a pointer to the function for future invokations.
    * Remenber the indirection:
    *  new StaticFunction<...>(&MyClass:staticFun);
    */
   StaticFunction(proto ptr);

   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke(Targ1 a1, Targ2 a2, Targ3 a3, Targ4 a4);
};

// Return and 3 arguments implementation
template<typename Tret,
      typename Targ1, typename Targ2, typename Targ3>
class StaticFunction<Tret, Targ1, Targ2, Targ3, void, void, void, void> :
      public virtual Function<Tret, Targ1, Targ2, Targ3, void, void, void, void>
{
public:
   /**
    * Static function prototype
    */
   typedef Tret (*proto)(Targ1, Targ2, Targ3);

private:
   /**
    * Function pointer.
    */
   proto _ptr;

public:
   /**
    * Keep a pointer to the function for future invokations.
    * Remenber the indirection:
    *  new StaticFunction<...>(&MyClass:staticFun);
    */
   StaticFunction(proto ptr);

   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke(Targ1 a1, Targ2 a2, Targ3 a3);
};

// Return and 2 arguments implementation
template<typename Tret,
      typename Targ1, typename Targ2>
class StaticFunction<Tret, Targ1, Targ2, void, void, void, void, void> :
      public virtual Function<Tret, Targ1, Targ2, void, void, void, void, void>
{
public:
   /**
    * Static function prototype
    */
   typedef Tret (*proto)(Targ1, Targ2);

private:
   /**
    * Function pointer.
    */
   proto _ptr;

public:
   /**
    * Keep a pointer to the function for future invokations.
    * Remenber the indirection:
    *  new StaticFunction<...>(&MyClass:staticFun);
    */
   StaticFunction(proto ptr);

   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke(Targ1 a1, Targ2 a2);
};

// Return and 1 argument implementation
template<typename Tret,
      typename Targ1>
class StaticFunction<Tret, Targ1, void, void, void, void, void, void> :
      public virtual Function<Tret, Targ1, void, void, void, void, void, void>
{
public:
   /**
    * Static function prototype
    */
   typedef Tret (*proto)(Targ1);

private:
   /**
    * Function pointer.
    */
   proto _ptr;

public:
   /**
    * Keep a pointer to the function for future invokations.
    * Remenber the indirection:
    *  new StaticFunction<...>(&MyClass:staticFun);
    */
   StaticFunction(proto ptr);

   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke(Targ1 a1);
};

// Only return implementation
template<typename Tret>
class StaticFunction<Tret, void, void, void, void, void, void, void> :
      public virtual Function<Tret, void, void, void, void, void, void, void>
{
public:
   /**
    * Static function prototype
    */
   typedef Tret (*proto)();

private:
   /**
    * Function pointer.
    */
   proto _ptr;

public:
   /**
    * Keep a pointer to the function for future invokations.
    * Remenber the indirection:
    *  new StaticFunction<...>(&MyClass:staticFun);
    */
   StaticFunction(proto ptr);

   /**
    * Invokes or executes the function.
    */
   virtual Tret invoke();
};

