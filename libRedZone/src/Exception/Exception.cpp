/*
 * Exception.cpp
 *
 *  Created on: 2014
 *      Author: jc
 */

#include "Exception.h"

namespace RedZone {

Exception::Exception( std::string const & message )
    : m_message( message ) {

}

const char * Exception::what() const throw() {
    return m_message.c_str();
}

Exception::~Exception() {
}

} /* namespace RedZone */
