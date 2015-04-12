/*
 * TextNode.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include "Node.h"

namespace RedZone {

class Writer;

class RZ_API TextNode: public Node {
public:
    TextNode();

    virtual void render( Writer * stream, Context * context ) const;
    virtual void processFragment( Fragment const * fragment );

    virtual std::string name() const;

    virtual ~TextNode();

protected:
    std::string m_text;
};

} /* namespace RedZone */
