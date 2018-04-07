#include "OptBinTree.h"

template< class T >
OptBinTree< T >::OptBinTree()
{
  this->root_ptr = nullptr;
}

template< class T >
OptBinTree< T >::OptBinTree( T fact )
{
  this->root_ptr = new OptBinNode< T >( fact );
}

template< class T >
bool OptBinTree< T >::is_empty()
{
  return this->root_ptr == nullptr;
}

template< class T >
OptBinNode< T >* OptBinTree< T >::find( T &fact )
{
  bool found = false;
  OptBinNode< T > *node_ptr = this->root_ptr;

  while( node_ptr != nullptr && !found )
  {
    if( node_ptr->getFact() == fact )
      found = true;
    else
      if( fact < node_ptr->getFact() )
        node_ptr = node_ptr->getLeft();
      else
        node_ptr = node_ptr->getRigth();
  }

  return node_ptr;
}

template< class T >
bool OptBinTree< T >::insert( T &fact )
{

  if( !this->is_empty() )
	{
		if( this->find( fact ) == nullptr )
		{
      bool found = false;
      OptBinNode< T > *father_ptr = this->root_ptr;

      while( father_ptr != nullptr )
      {
        if( fact < father_ptr->getFact() )
          if( father_ptr->getLeft() == nullptr )
          {
            father_ptr->setLeft( fact );
            father_ptr = nullptr;
          }
          else
            father_ptr = father_ptr->getLeft();
        else
          if( father_ptr->getRigth() == nullptr )
          {
            father_ptr->setRigth( fact );
            father_ptr = nullptr;
          }
          else
            father_ptr = father_ptr->getRigth();
      }

      return true;
		}
		return false;
	}

	this->root_ptr = new OptBinNode< T >( fact );
	return true;
}

template< class T >
std::list< OptBinNode< T >* > OptBinTree< T >::nivelOrden()
{
	std::list< OptBinNode< T >* > lista;

	if( !this->is_empty() )
	{
		lista.push_back( this->root_ptr );
		for( typename std::list< OptBinNode< T >* >::iterator it = lista.begin(); it != lista.end(); ++it)
    {
      if( ( *it )->getLeft() != nullptr )
		    lista.push_back( ( *it )->getLeft() );
	    if( ( *it )->getRigth() != nullptr )
		    lista.push_back( ( *it )->getRigth() );
    }
	}

	return lista;
}
