#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <regex>
#include <set>
#include <streambuf>
#include <string>

#include "Build_OptBinTree.h"

std::vector< std::string > tokenize(
  const std::string&, std::string&
  );
int init_PQ(
  std::string, std::vector<float>&, std::vector<float>&, std::vector<std::string>&
  );
int init_dicc( std::vector< std::string >& );
std::chrono::duration< double > test_rn_tree(
  const std::vector< std::string >&, const int&, const std::set< std::string >&
  );
std::chrono::duration< double > test_opt_bin_tree(
   std::vector< std::string >&, const int&, OptBinTree< std::string >&
  );

int main(int argc, char *argv[])
{
  if( argc != 3 )
  {
    std::cerr << "Usage: " << argv[ 0 ] << " input_file time_to_find(seconds)" << std::endl;
    return( 1 );
  }

  int n;

  std::vector<float> P;
  std::vector<float> Q;
  std::vector<std::string> datos, dicc;

  OptBinTree< std::string > opt_tree;
  std::set< std::string > rn_tree;

  std::chrono::duration< double > d, t;
  std::chrono::high_resolution_clock::time_point start;
  std::chrono::seconds m = std::chrono::seconds( std::stoi( argv[ 2 ] ) );

  init_PQ(argv[1], P, Q, datos);

  std::cout << "Filling rn_tree..." << std::endl;
  for( int i = 0; i < datos.size(); i++ )
    rn_tree.insert(datos[i]);

  std::cout << "Calculating R..." << std::endl;
  std::vector< std::vector< int > > R = Build_OptBinTree(P, Q);

  std::cout << "Filling opt_bin_tree..." << std::endl;
  opt_tree = BruteForceBackTracking(R, datos);

  std::list< OptBinNode < std::string >* > lista = opt_tree.nivelOrden();

  std::cout << datos.size() << " " << rn_tree.size() << " " << lista.size() << std::endl;

  init_dicc(dicc);

  std::cout << "Start rn_tree tests" << std::endl;
  start = std::chrono::high_resolution_clock::now();
  d = std::chrono::duration< double >();
  n = 0;

  while( d.count() <= m.count() )
  {
    d = std::chrono::duration_cast< std::chrono::duration< double > >(
      std::chrono::high_resolution_clock::now() - start
      );

    t = test_rn_tree( dicc, n, rn_tree );
    n += 100;

    std::cout << n << " " << t.count() << std::endl;
  }

  std::cout << "Start opt_bin_tree tests" << std::endl;
  start = std::chrono::high_resolution_clock::now();
  d = std::chrono::duration< double >();
  n = 0;

  while( d.count() <= m.count() )
  {
    d = std::chrono::duration_cast< std::chrono::duration< double > >(
      std::chrono::high_resolution_clock::now() - start
      );

    t = test_opt_bin_tree( dicc, n, opt_tree );
    n += 100;

    std::cout << n << " " << t.count() << std::endl;
  }

  return 0;
}

std::vector< std::string > tokenize(
  const std::string& input, const std::string& regex
  )
{
  std::regex re( regex );
  std::sregex_token_iterator first{ input.begin( ), input.end( ), re, -1 }, last;
  return{ first, last };
}

int init_PQ(
  std::string file_path, std::vector<float> &P, std::vector<float> &Q,
  std::vector<std::string> &datos
  )
{
  // Read file into a buffer
  std::ifstream input_file( file_path );
  if( !input_file.is_open( ) )
  {
    std::cerr << "Invalid input file." << std::endl;
    return 1;

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
  tokens.erase(tokens.begin());

  for( int i = 0; i < tokens.size(); i+=2 )
  {
    datos.push_back(tokens[i]);
    P.push_back(std::stof(tokens[i + 1]) / (num_words * 2.0));
  }

  Q = std::vector<float>(P.size() + 1, 0.5 / (static_cast<float>(P.size()) + 1.0));

  input_file.close();

  return 0;
}

int init_dicc( std::vector< std::string >& dicc )
{
  std::ifstream input_file( "diccionario.txt" );
  if( !input_file.is_open( ) )
  {
          std::cerr << "Invalid input file." << std::endl;
          return 1;
  } // fi
  std::string buffer;
  input_file.seekg( 0, std::ios::end );
  buffer.reserve(input_file.tellg( ));
  input_file.seekg( 0, std::ios::beg );
  buffer.assign(( std::istreambuf_iterator< char >( input_file ) ),std::istreambuf_iterator< char >( ));

  dicc = tokenize( buffer, "[^a-zA-Z]+" );

  input_file.close();

  return 0;
}

std::chrono::duration< double > test_rn_tree(
  const std::vector< std::string >& dicc, const int& n,
  const std::set< std::string >& rn_tree
  )
{
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> dist(0, dicc.size());

  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

  for( int i = 0; i < n; i++)
    rn_tree.find( dicc[ dist( mt ) ] );

  std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration< double > time_span = std::chrono::duration_cast< std::chrono::duration < double > >(t2 - t1);

  return time_span;
}

std::chrono::duration< double > test_opt_bin_tree(
  std::vector< std::string >& dicc, const int& n,
  OptBinTree< std::string >& opt_bin_tree
  )
{
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> dist(0, dicc.size());

  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

  for( int i = 0; i < n; i++)
    opt_bin_tree.find( dicc[ dist( mt ) ] );

  std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration< double > time_span = std::chrono::duration_cast< std::chrono::duration < double > >(t2 - t1);

  return time_span;
}
