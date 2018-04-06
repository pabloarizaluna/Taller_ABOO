/*
 * Compilation: g++ -std=c++11 build_histogram.cxx -o my_fancy_executable
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <streambuf>
#include <string>
#include <vector>

// -------------------------------------------------------------------------
std::vector< std::string > tokenize(
  const std::string& input, const std::string& regex
  )
{
  std::regex re( regex );
  std::sregex_token_iterator first{ input.begin( ), input.end( ), re, -1 }, last;
  return{ first, last };
}

// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
  if( argc < 3 )
  {
    std::cerr << "Usage: " << argv[ 0 ] << " input_file output_file" << std::endl;
    return( 1 );

  } // fi

  // Read file into a buffer
  std::ifstream input_file( argv[ 1 ] );
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
  std::vector< std::string > tokens = tokenize( buffer, "[^a-zA-Z]+" );

  // Build histogram
  typedef std::map< std::string, unsigned long > THistogram;
  THistogram h;
  for( std::string& tok: tokens )
  {
    std::transform( tok.begin( ), tok.end( ), tok.begin( ), ::tolower );
    h[ tok ]++;

  } // rof

  // Write histogram
  std::stringstream out_str;
  out_str << tokens.size( ) << std::endl;
  for( const THistogram::value_type& e: h )
    out_str
      << e.first << " "
      << e.second << std::endl;
  std::ofstream output_file( argv[ 2 ] );
  if( !output_file.is_open( ) )
  {
    std::cerr << "Invalid output file." << std::endl;
    return( 1 );

  } // fi
  output_file << out_str.str( );
  output_file.close( );

  return( 0 );
}

// eof - $RCSfile$
