/*
 * TemplateContextError.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include "Exception.h"

namespace RedZone {

class RZ_API TemplateContextError: public Exception {
public:
    TemplateContextError( std::string const & contextVar );
    virtual ~TemplateContextError();
};

} /* namespace RedZone */
