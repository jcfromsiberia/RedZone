/*
 * IOError.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include "Exception.h"

namespace RedZone {

class IOError: public RedZone::Exception {
public:
    IOError( std::string const & message );
    virtual ~IOError();
};

} /* namespace RedZone */
