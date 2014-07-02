/*
 * ElseNode.cpp
 *
 *  Created on: 2014
 *      Author: jc
 */

#include "ElseNode.h"

#include <Context/Context.h>
#include <Parser/Fragment.h>

namespace RedZone {

ElseNode::ElseNode()
    : Node() {

}

void ElseNode::render( std::ostream &, Context * ) const {

}

ElseNode::~ElseNode() {
}

} /* namespace RedZone */
