/*
 * JsonError.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include "Exception.h"

namespace RedZone {

class JsonError: public Exception {
public:
    using Exception::Exception;

    virtual ~JsonError();
};

} /* namespace RedZone */
