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

class RZ_API EachNode: public Node {
public:
    EachNode();

    virtual void render( Writer * stream, Context * context ) const;
    virtual void processFragment( Fragment const * fragment );
    virtual void exitScope( std::string const & endTag );
    virtual std::string name() const;

    virtual ~EachNode();

protected:
    std::string m_container;
    std::vector< std::string > m_vars;
};

} /* namespace RedZone */
