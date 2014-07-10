/*
 * FileWriter.cpp
 *
 *      Author: jc
 */
#include "FileWriter.h"

#include <algorithm>
#include <iterator>

#include <Exception/IOError.h>

namespace RedZone {

FileWriter::FileWriter( std::string const & fileName )
   : m_file( fileName ) {
   if( !m_file.good() ) {
      throw IOError( "Can not create " + fileName + " file." );
   }
}

void FileWriter::write( std::string const & data ) {
   std::copy( data.begin(), data.end(), std::ostream_iterator< char >( m_file ) );
}

void FileWriter::flush() {
   m_file.flush();
}

FileWriter::~FileWriter() {
}

} /* namespace RedZone */
