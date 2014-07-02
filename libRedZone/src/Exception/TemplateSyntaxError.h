/*
 * TemplateSyntaxError.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include "Exception.h"

namespace RedZone {

class TemplateSyntaxError: public Exception {
public:
    TemplateSyntaxError( std::string const & wrongSyntax );
    virtual ~TemplateSyntaxError();
};

} /* namespace RedZone */
