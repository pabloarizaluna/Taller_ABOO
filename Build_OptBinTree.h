#ifndef __BUILD_OPTBINTREE_H__
#define __BUILD_OPTBINTREE_H__

#include <vector>
#include <limits>

#include "OptBinTree.h"

std::vector< std::vector< int > > Build_OptBinTree(
  std::vector< float > P, std::vector< float > Q
  );
OptBinTree< std::string > BruteForceBackTracking( 
  std::vector< std::vector< int > > &R, std::vector< std::string > &datos
  );

#endif
