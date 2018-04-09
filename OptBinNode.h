#ifndef __OPTBINNODE_H__
#define __OPTBINNODE_H__

#include <iostream>

template<class T>
class OptBinNode
{
protected:
  T fact;
  OptBinNode< T > *left_ptr;
  OptBinNode< T > *rigth_ptr;

public:
  OptBinNode();
  OptBinNode( T );
  OptBinNode( T, T, T );

  T getFact();
  OptBinNode< T >* getLeft();
  OptBinNode< T >* getRigth();

  void setLeft( T );
  void setRigth( T );
};

#include "OptBinNode.hxx"

#endif
