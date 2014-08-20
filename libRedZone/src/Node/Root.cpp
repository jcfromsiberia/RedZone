/*
 * Root.cpp
 *
 *  Created on: 2014
 *      Author: jc
 */

#include "Root.h"

namespace RedZone {

Root::Root( std::string id )
    : Node(), m_id( id ) {

}

void Root::render( Writer * stream, Context * context ) const {
    renderChildren( stream, context );
}

std::string Root::name() const {
   return "Root";
}

Root::~Root() {
}

} /* namespace RedZone */
