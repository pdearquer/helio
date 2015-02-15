/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Data {

template<typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4, typename Targ5, typename Targ6,
      typename Targ7>
StaticFunction<Tret, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7>::
      StaticFunction(proto ptr)
{
   _ptr = ptr;
}

template<typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4, typename Targ5, typename Targ6,
      typename Targ7>
Tret StaticFunction<Tret, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7>::
      invoke(Targ1 a1, Targ2 a2, Targ3 a3, Targ4 a4, Targ5 a5, Targ6 a6, Targ7 a7)
{
   return _ptr(a1, a2, a3, a4, a5, a6, a7);
}


template<typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4, typename Targ5, typename Targ6>
StaticFunction<Tret, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, void>::
      StaticFunction(proto ptr)
{
   _ptr = ptr;
}

template<typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4, typename Targ5, typename Targ6>
Tret StaticFunction<Tret, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, void>::
      invoke(Targ1 a1, Targ2 a2, Targ3 a3, Targ4 a4, Targ5 a5, Targ6 a6)
{
   return _ptr(a1, a2, a3, a4, a5, a6);
}


template<typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4, typename Targ5>
StaticFunction<Tret, Targ1, Targ2, Targ3, Targ4, Targ5, void, void>::
      StaticFunction(proto ptr)
{
   _ptr = ptr;
}

template<typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4, typename Targ5>
Tret StaticFunction<Tret, Targ1, Targ2, Targ3, Targ4, Targ5, void, void>::
      invoke(Targ1 a1, Targ2 a2, Targ3 a3, Targ4 a4, Targ5 a5)
{
   return _ptr(a1, a2, a3, a4, a5);
}


template<typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4>
StaticFunction<Tret, Targ1, Targ2, Targ3, Targ4, void, void, void>::
      StaticFunction(proto ptr)
{
   _ptr = ptr;
}

template<typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4>
Tret StaticFunction<Tret, Targ1, Targ2, Targ3, Targ4, void, void, void>::
      invoke(Targ1 a1, Targ2 a2, Targ3 a3, Targ4 a4)
{
   return _ptr(a1, a2, a3, a4);
}


template<typename Tret,
      typename Targ1, typename Targ2, typename Targ3>
StaticFunction<Tret, Targ1, Targ2, Targ3, void, void, void, void>::
      StaticFunction(proto ptr)
{
   _ptr = ptr;
}

template<typename Tret,
      typename Targ1, typename Targ2, typename Targ3>
Tret StaticFunction<Tret, Targ1, Targ2, Targ3, void, void, void, void>::
      invoke(Targ1 a1, Targ2 a2, Targ3 a3)
{
   return _ptr(a1, a2, a3);
}


template<typename Tret,
      typename Targ1, typename Targ2>
StaticFunction<Tret, Targ1, Targ2, void, void, void, void, void>::
      StaticFunction(proto ptr)
{
   _ptr = ptr;
}

template<typename Tret,
      typename Targ1, typename Targ2>
Tret StaticFunction<Tret, Targ1, Targ2, void, void, void, void, void>::
      invoke(Targ1 a1, Targ2 a2)
{
   return _ptr(a1, a2);
}


template<typename Tret,
      typename Targ1>
StaticFunction<Tret, Targ1, void, void, void, void, void, void>::
      StaticFunction(proto ptr)
{
   _ptr = ptr;
}

template<typename Tret,
      typename Targ1>
Tret StaticFunction<Tret, Targ1, void, void, void, void, void, void>::
      invoke(Targ1 a1)
{
   return _ptr(a1);
}


template<typename Tret>
StaticFunction<Tret, void, void, void, void, void, void, void>::
      StaticFunction(proto ptr)
{
   _ptr = ptr;
}

template<typename Tret>
Tret StaticFunction<Tret, void, void, void, void, void, void, void>::
      invoke()
{
   return _ptr();
}

} } }

