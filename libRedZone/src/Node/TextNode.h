/*
 * TextNode.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include "Node.h"

namespace RedZone {

class TextNode: public Node {
public:
    TextNode();

    virtual void render( std::ostream & stream, Context * context ) const;
    virtual void processFragment( Fragment const * fragment );

    virtual ~TextNode();

protected:
    std::string m_text;
};

} /* namespace RedZone */
