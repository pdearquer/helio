/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

#include <Helio.h>

namespace Storage {
namespace Structure {

template<class N> void Node<N>::adding(Object *container)
{
   container->as<Graph<N> >();
}

template<class N> void Node<N>::removed(Object *container)
{
   container->as<Graph<N> >();
}

}
}
