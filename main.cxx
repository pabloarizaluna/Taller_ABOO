#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <streambuf>
#include <string>

#include "Build_OptBinTree.h"

std::vector< std::string > tokenize(
  const std::string& input, const std::string& regex
  )
{
  std::regex re( regex );
  std::sregex_token_iterator first{ input.begin( ), input.end( ), re, -1 }, last;
  return{ first, last };
}

int init_PQ(std::string file_path, std::vector<float>&, std::vector<float>&,
  std::vector<std::string>&);

int main(int argc, char *argv[])
{
  if( argc != 2 )
  {
    std::cerr << "Usage: " << argv[ 0 ] << " input_file" << std::endl;
    return( 1 );

  }

  std::vector<float> P;
  std::vector<float> Q;
  std::vector<std::string> datos;

  init_PQ(argv[1], P, Q, datos);

  std::cout << "Datos" << std::endl;
  std::ostream_iterator< std::string > outputs( std::cout, " " );
  std::copy( datos.begin(), datos.end(), outputs );

  std::cout << std::endl << std::endl;

  std::cout << "Ps" << std::endl;
  std::ostream_iterator< float > outputs_1( std::cout, " " );
  std::copy( P.begin(), P.end(), outputs_1 );

  std::cout << std::endl << std::endl;

  std::cout << "Qs" << std::endl;
  std::ostream_iterator< float > outputs_2( std::cout, " " );
  std::copy( Q.begin(), Q.end(), outputs_2 );

  std::vector<std::vector<int>> R = Build_OptBinTree(P, Q);

  std::cout << std::endl << std::endl;

  /*std::cout << "Rs" << std::endl;
  std::ostream_iterator< int > outputs_3( std::cout, " " );
  std::copy( R.begin(), R.end(), outputs_3 );*/

  std::cout << std::endl << std::endl;

  return 0;
}

int init_PQ(std::string file_path, std::vector<float> &P, std::vector<float> &Q,
  std::vector<std::string> &datos)
{
  // Read file into a buffer
  std::ifstream input_file( file_path );
  if( !input_file.is_open( ) )
  {
    std::cerr << "Invalid input file." << std::endl;
    return( 1 );

  } // fi
  std::string buffer;
  input_file.seekg( 0, std::ios::end );
  buffer.reserve( input_file.tellg( ) );
  input_file.seekg( 0, std::ios::beg );
  buffer.assign(
    ( std::istreambuf_iterator< char >( input_file ) ),
    std::istreambuf_iterator< char >( )
    );

  // Tokenize
  std::vector< std::string > tokens = tokenize( buffer, "[^a-zA-Z0-9]+" );

  int num_words = std::stoi(tokens.front());
  float acum_p = 0, acum_q = 0;
  tokens.erase(tokens.begin());

  for( int i = 0; i < tokens.size(); i+=2 )
  {
    datos.push_back(tokens[i]);
    P.push_back(std::stof(tokens[i + 1]) / (num_words * 2.0));
    acum_p += P.back();
  }

  Q = std::vector<float>(P.size() + 1, 0.5 / (static_cast<float>(P.size()) + 1.0));
  for( float i : Q )
    acum_q += i;
  
  std::cout << "Acum P: " << acum_p << std::endl;
  std::cout << "Acum Q: " << acum_q << std::endl;
  input_file.close();
}
