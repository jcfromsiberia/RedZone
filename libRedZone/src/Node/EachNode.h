/*
 * EachNode.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include "Node.h"

namespace RedZone {

class Writer;

class EachNode: public Node {
public:
    EachNode();

    virtual void render( Writer * stream, Context * context ) const;
    virtual void processFragment( Fragment const * fragment );

    virtual ~EachNode();

protected:
    std::string m_container;
    std::string m_var;
};

} /* namespace RedZone */
