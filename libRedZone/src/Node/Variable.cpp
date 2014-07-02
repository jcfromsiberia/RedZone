/*
 * Variable.cpp
 *
 *  Created on: 2014
 *      Author: jc
 */

#include "Variable.h"

#include <Parser/Fragment.h>

namespace RedZone {

Variable::Variable()
    : Node() {

}

void Variable::render( std::ostream & stream, Context * context ) const {
    stream << resolveInContext( m_name, context ).string_value();
}

void Variable::processFragment( Fragment const * fragment ) {
    m_name = fragment->clean();
}

Variable::~Variable() {
}

} /* namespace RedZone */
