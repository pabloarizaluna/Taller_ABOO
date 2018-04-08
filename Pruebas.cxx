#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <streambuf>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
std::vector< std::string > tokenize(const std::string& input, const std::string& regex);

int main(int argc, char const *argv[]) {

        srand (time(NULL));
        int indice ;

        std::ifstream input_file( "diccionario.txt" );
        if( !input_file.is_open( ) )
        {
                std::cerr << "Invalid input file." << std::endl;
                return( 1 );

        } // fi
        std::string buffer;
        input_file.seekg( 0, std::ios::end );
        buffer.reserve(input_file.tellg( ));
        input_file.seekg( 0, std::ios::beg );
        buffer.assign(( std::istreambuf_iterator< char >( input_file ) ),std::istreambuf_iterator< char >( ));

        std::vector< std::string > tokens = tokenize( buffer, "[^a-zA-Z0-9]+" );
        int size = tokens.size() ;

        indice = rand() % size;
        /*

        std::cout << "Datos" << std::endl;
        std::ostream_iterator< std::string > outputs( std::cout, " " );
        std::copy( tokens.begin(), tokens.end(), outputs );

        */
        std::cout <<  << '\n';
        return 0;
}

std::vector< std::string > tokenize(  const std::string& input, const std::string& regex)
{
        std::regex re( regex );
        std::sregex_token_iterator first{ input.begin( ), input.end( ), re, -1 }, last;
        return { first, last };
}
