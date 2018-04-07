#include "OptBinNode.h"

template< class T >
OptBinNode< T >::OptBinNode()
{
  this->fact = T();
  this->left_ptr = nullptr;
  this->rigth_ptr = nullptr;
}

template< class T >
OptBinNode< T >::OptBinNode( T fact )
{
  this->fact = fact;
  this->left_ptr = nullptr;
  this->rigth_ptr = nullptr;
}

template< class T >
OptBinNode< T >::OptBinNode( T fact, T fact_left, T fact_rigth )
{
  this->fact = fact;
  this->left_ptr = new OptBinNode< T >(fact_left);
  this->rigth_ptr = new OptBinNode< T >(fact_left);
}

template< class T >
T OptBinNode< T >::getFact()
{
  return this->fact;
}

template< class T >
OptBinNode< T >* OptBinNode< T >::getLeft()
{
  return this->left_ptr;
}

template< class T >
OptBinNode< T >* OptBinNode< T >::getRigth()
{
  return this->rigth_ptr;
}

template< class T >
void OptBinNode< T >::setLeft( T fact )
{
  this->left_ptr = new OptBinNode< T >( fact );
}

template< class T >
void OptBinNode< T >::setRigth( T fact )
{
  this->rigth_ptr = new OptBinNode< T >( fact );
}
