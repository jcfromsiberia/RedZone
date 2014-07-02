/*
 * ElseNode.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include "Node.h"

namespace RedZone {

class ElseNode: public Node {
public:
    ElseNode();

    virtual void render( std::ostream & stream, Context * context ) const;

    virtual ~ElseNode();
};

} /* namespace RedZone */
