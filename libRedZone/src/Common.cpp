/*
 * Common.cpp
 *
 *      Author: jc
 */
#include "Common.h"

#include <algorithm>
#include <ctype.h>
#include <functional>

#if defined( __linux__ ) || defined( __APPLE__ )
#  include <unistd.h>
#elif defined( _WIN32 ) || defined( _WIN64 )
#  error "Not implemented yet"
#else
#  error "Unknown OS"
#endif

namespace RedZone {

std::string dbl2str( double d ) {
    size_t len = std::snprintf( 0, 0, "%.10f", d );
    std::string s( len + 1, 0) ;
    std::snprintf( &s[ 0 ], len + 1, "%.10f", d );
    s.pop_back();
    s.erase( s.find_last_not_of( '0' ) + 1, std::string::npos );
    if( s.back() == '.' ) {
        s.pop_back();
    }
    return s;
}

void trimString( std::string & str ) {
   str.erase( str.begin(), std::find_if( str.begin(), str.end(),
           std::not1( std::ptr_fun< int, int >( std::isspace ) ) ) );
   str.erase( std::find_if( str.rbegin(), str.rend(),
           std::not1( std::ptr_fun< int, int >( std::isspace ) ) ).base(), str.end() );
}

std::string replaceString( std::string subject, const std::string & search, const std::string & replace ) {
   size_t pos = 0;
   while ( ( pos = subject.find( search, pos ) ) != std::string::npos ) {
       subject.replace( pos, search.length(), replace );
       pos += replace.length();
   }
   return subject;
}

bool isReadableFile( std::string const & filePath ) {
   return access( filePath.c_str(), R_OK ) != -1;
}

} /* namespace RedZone */
