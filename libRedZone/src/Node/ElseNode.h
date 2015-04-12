/*
 * ElseNode.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include "Node.h"

namespace RedZone {

class Writer;

class RZ_API ElseNode: public Node {
public:
    ElseNode();

    virtual void render( Writer * stream, Context * context ) const;

    virtual std::string name() const;

    virtual ~ElseNode();
};

} /* namespace RedZone */
