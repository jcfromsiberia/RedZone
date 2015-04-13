/*
 * Common.cpp
 *
 *      Author: jc
 */
#include "Common.h"

#include <algorithm>
#include <ctype.h>
#include <functional>

#if defined( RZ_UNIX )
#  include <unistd.h>
#elif defined( RZ_WINDOWS )
#  include <Windows.h>
#  include <locale>
#  define snprintf _snprintf
#else
#  error "Unknown OS"
#endif

using namespace std;

namespace RedZone {

std::string dbl2str( double d ) {
    size_t len = snprintf( 0, 0, "%.10f", d );
    std::string s( len + 1, 0) ;
    snprintf( &s[ 0 ], len + 1, "%.10f", d );
    s.pop_back();
    s.erase( s.find_last_not_of( '0' ) + 1, std::string::npos );
    if( s.back() == '.' ) {
        s.pop_back();
    }
	
    return s;
}

void trimString( std::string & str ) {
   str.erase( str.begin(), std::find_if( str.begin(), str.end(),
           std::not1( std::function< int( int ) >( isspace ) ) ) );
   str.erase( std::find_if( str.rbegin(), str.rend(),
           std::not1( std::function< int( int ) >( isspace ) ) ).base(), str.end() );
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
#if defined( RZ_UNIX )
   return access( filePath.c_str(), R_OK ) != -1;
#elif defined( RZ_WINDOWS )
	DWORD attrs = GetFileAttributes( filePath.c_str() );
	return ( attrs != INVALID_FILE_ATTRIBUTES && 
         ! ( attrs & FILE_ATTRIBUTE_DIRECTORY ) );
#else
#  error( "Not implemented yet" ) 
#endif
}

} /* namespace RedZone */
