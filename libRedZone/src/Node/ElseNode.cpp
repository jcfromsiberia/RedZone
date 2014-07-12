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

void ElseNode::render( Writer *, Context * ) const {

}

std::string ElseNode::name() const {
   return "Else";
}

ElseNode::~ElseNode() {
}

} /* namespace RedZone */
