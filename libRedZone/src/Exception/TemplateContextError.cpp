/*
 * TemplateContextError.cpp
 *
 *  Created on: 2014
 *      Author: jc
 */

#include "TemplateContextError.h"

namespace RedZone {

TemplateContextError::TemplateContextError( std::string const & contextVar )
    : Exception( "Cannot resolve '" + contextVar + "'" ) {
}

TemplateContextError::~TemplateContextError() {
}

} /* namespace RedZone */
