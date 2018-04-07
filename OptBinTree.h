#ifndef __OPTBINTREE_H__
#define __OPTBINTREE_H__

#include <iterator>
#include <list>

#include "OptBinNode.h"

template< class T >
class OptBinTree
{
private:
  OptBinNode< T > *root_ptr;

  OptBinNode< T >* insert_helper( OptBinNode< T >**, T& );

public:
  OptBinTree();
  OptBinTree( T );

  bool insert( T& );
  bool is_empty();
  OptBinNode< T >* find( T& );

  std::list< OptBinNode< T >* > nivelOrden();
};

#include "OptBinTree.hxx"

#endif
