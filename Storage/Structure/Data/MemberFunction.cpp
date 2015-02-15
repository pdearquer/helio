/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */
 
#include <Helio.h>

namespace Storage {
namespace Structure {
namespace Data {

template<class C, typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4, typename Targ5, typename Targ6,
      typename Targ7>
MemberFunction<C, Tret, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7>::
      MemberFunction(C *obj, proto ptr)
{
   _obj = obj;
   _ptr = ptr;
}

template<class C, typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4, typename Targ5, typename Targ6,
      typename Targ7>
Tret MemberFunction<C, Tret, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7>::
      invoke(Targ1 a1, Targ2 a2, Targ3 a3, Targ4 a4, Targ5 a5, Targ6 a6, Targ7 a7)
{
   return (_obj->*_ptr)(a1, a2, a3, a4, a5, a6, a7);
}

template<class C, typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4, typename Targ5, typename Targ6,
      typename Targ7>
C *MemberFunction<C, Tret, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, Targ7>::
      getObject()
{
   return _obj;
}


template<class C, typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4, typename Targ5, typename Targ6>
MemberFunction<C, Tret, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, void>::
      MemberFunction(C *obj, proto ptr)
{
   _obj = obj;
   _ptr = ptr;
}

template<class C, typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4, typename Targ5, typename Targ6>
Tret MemberFunction<C, Tret, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, void>::
      invoke(Targ1 a1, Targ2 a2, Targ3 a3, Targ4 a4, Targ5 a5, Targ6 a6)
{
   return (_obj->*_ptr)(a1, a2, a3, a4, a5, a6);
}

template<class C, typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4, typename Targ5, typename Targ6>
C *MemberFunction<C, Tret, Targ1, Targ2, Targ3, Targ4, Targ5, Targ6, void>::
      getObject()
{
   return _obj;
}


template<class C, typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4, typename Targ5>
MemberFunction<C, Tret, Targ1, Targ2, Targ3, Targ4, Targ5, void, void>::
      MemberFunction(C *obj, proto ptr)
{
   _obj = obj;
   _ptr = ptr;
}

template<class C, typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4, typename Targ5>
Tret MemberFunction<C, Tret, Targ1, Targ2, Targ3, Targ4, Targ5, void, void>::
      invoke(Targ1 a1, Targ2 a2, Targ3 a3, Targ4 a4, Targ5 a5)
{
   return (_obj->*_ptr)(a1, a2, a3, a4, a5);
}

template<class C, typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4, typename Targ5>
C *MemberFunction<C, Tret, Targ1, Targ2, Targ3, Targ4, Targ5, void, void>::
      getObject()
{
   return _obj;
}


template<class C, typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4>
MemberFunction<C, Tret, Targ1, Targ2, Targ3, Targ4, void, void, void>::
      MemberFunction(C *obj, proto ptr)
{
   _obj = obj;
   _ptr = ptr;
}

template<class C, typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4>
Tret MemberFunction<C, Tret, Targ1, Targ2, Targ3, Targ4, void, void, void>::
      invoke(Targ1 a1, Targ2 a2, Targ3 a3, Targ4 a4)
{
   return (_obj->*_ptr)(a1, a2, a3, a4);
}

template<class C, typename Tret,
      typename Targ1, typename Targ2, typename Targ3,
      typename Targ4>
C *MemberFunction<C, Tret, Targ1, Targ2, Targ3, Targ4, void, void, void>::
      getObject()
{
   return _obj;
}


template<class C, typename Tret,
      typename Targ1, typename Targ2, typename Targ3>
MemberFunction<C, Tret, Targ1, Targ2, Targ3, void, void, void, void>::
      MemberFunction(C *obj, proto ptr)
{
   _obj = obj;
   _ptr = ptr;
}

template<class C, typename Tret,
      typename Targ1, typename Targ2, typename Targ3>
Tret MemberFunction<C, Tret, Targ1, Targ2, Targ3, void, void, void, void>::
      invoke(Targ1 a1, Targ2 a2, Targ3 a3)
{
   return (_obj->*_ptr)(a1, a2, a3);
}

template<class C, typename Tret,
      typename Targ1, typename Targ2, typename Targ3>
C *MemberFunction<C, Tret, Targ1, Targ2, Targ3, void, void, void, void>::
      getObject()
{
   return _obj;
}


template<class C, typename Tret,
      typename Targ1, typename Targ2>
MemberFunction<C, Tret, Targ1, Targ2, void, void, void, void, void>::
      MemberFunction(C *obj, proto ptr)
{
   _obj = obj;
   _ptr = ptr;
}

template<class C, typename Tret,
      typename Targ1, typename Targ2>
Tret MemberFunction<C, Tret, Targ1, Targ2, void, void, void, void, void>::
      invoke(Targ1 a1, Targ2 a2)
{
   return (_obj->*_ptr)(a1, a2);
}

template<class C, typename Tret,
      typename Targ1, typename Targ2>
C *MemberFunction<C, Tret, Targ1, Targ2, void, void, void, void, void>::
      getObject()
{
   return _obj;
}


template<class C, typename Tret,
      typename Targ1>
MemberFunction<C, Tret, Targ1, void, void, void, void, void, void>::
      MemberFunction(C *obj, proto ptr)
{
   _obj = obj;
   _ptr = ptr;
}

template<class C, typename Tret,
      typename Targ1>
Tret MemberFunction<C, Tret, Targ1, void, void, void, void, void, void>::
      invoke(Targ1 a1)
{
   return (_obj->*_ptr)(a1);
}

template<class C, typename Tret,
      typename Targ1>
C *MemberFunction<C, Tret, Targ1, void, void, void, void, void, void>::
      getObject()
{
   return _obj;
}


template<class C, typename Tret>
MemberFunction<C, Tret, void, void, void, void, void, void, void>::
      MemberFunction(C *obj, proto ptr)
{
   _obj = obj;
   _ptr = ptr;
}

template<class C, typename Tret>
Tret MemberFunction<C, Tret, void, void, void, void, void, void, void>::
      invoke()
{
   return (_obj->*_ptr)();
}

template<class C, typename Tret>
C *MemberFunction<C, Tret, void, void, void, void, void, void, void>::
      getObject()
{
   return _obj;
}


template<class C>
MemberFunction<C, void, void, void, void, void, void, void, void>::
      MemberFunction(C *obj, proto ptr)
{
   _obj = obj;
   _ptr = ptr;
}

template<class C>
void MemberFunction<C, void, void, void, void, void, void, void, void>::
      invoke()
{
   (_obj->*_ptr)();
}

template<class C>
C *MemberFunction<C, void, void, void, void, void, void, void, void>::
      getObject()
{
   return _obj;
}

} } }

