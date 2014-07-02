/*
 * IOError.cpp
 *
 *  Created on: 2014
 *      Author: jc
 */

#include "IOError.h"

namespace RedZone {

IOError::IOError( std::string const & message )
    : Exception( message ) {

}

IOError::~IOError() {
}

} /* namespace RedZone */
