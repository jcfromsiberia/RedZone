/*
 * StringWriter.cpp
 *
 *      Author: jc
 */
#include "StringWriter.h"

#include <iterator>

namespace RedZone {

StringWriter::StringWriter( std::string & string )
   : m_string( string ) {
}

void StringWriter::write( std::string const & data ) {
   std::copy( data.begin(), data.end(), std::back_inserter( m_string ) );
}

void StringWriter::flush() {

}

StringWriter::~StringWriter() {
}

} /* namespace RedZone */
