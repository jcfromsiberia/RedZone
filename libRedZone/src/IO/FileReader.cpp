/*
 * FileReader.cpp
 *
 *      Author: jc
 */
#include "FileReader.h"

#include <Exception/IOError.h>

namespace RedZone {

FileReader::FileReader( std::string const & fileName )
   : m_file( fileName ) {
   if( !m_file.good() ) {
      throw IOError( "Can not open " + fileName + " file." );
   }
}

std::string FileReader::read( size_t nBytes ) {
   std::string result( nBytes, '\0' );
   m_file.read( &result[ 0 ], nBytes );
   return result;
}

std::string FileReader::readAll() {
   return std::string( std::istreambuf_iterator< char >( m_file ), std::istreambuf_iterator< char >() );
}

FileReader::~FileReader() {
}

} /* namespace RedZone */
