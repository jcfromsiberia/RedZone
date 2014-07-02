/*
 * TemplateSyntaxError.cpp
 *
 *  Created on: 2014
 *      Author: jc
 */

#include "TemplateSyntaxError.h"

namespace RedZone {

TemplateSyntaxError::TemplateSyntaxError( std::string const & wrongSyntax )
    : Exception( "'" + wrongSyntax + "' seems like invalid syntax." ) {

}

TemplateSyntaxError::~TemplateSyntaxError() {
}

} /* namespace RedZone */
