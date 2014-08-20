/*
 * StringReader.cpp
 *
 *      Author: jc
 */
#include "StringReader.h"

namespace RedZone {

StringReader::StringReader( std::string const & string )
   : m_string( string ), m_iter( m_string.begin() ) {
}

std::string StringReader::read( size_t nBytes ) {
   std::string result( m_iter, m_iter + nBytes );
   m_iter += nBytes;
   return result;
}

std::string StringReader::readAll() {
   return m_string;
}

std::string StringReader::id() const {
    return "<string>";
}

StringReader::~StringReader() {
}

} /* namespace RedZone */
