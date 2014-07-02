/*
 * Root.cpp
 *
 *  Created on: 2014
 *      Author: jc
 */

#include "Root.h"

namespace RedZone {

Root::Root()
    : Node() {

}

void Root::render( std::ostream & stream, Context * context ) const {
    renderChildren( stream, context );
}

Root::~Root() {
}

} /* namespace RedZone */
