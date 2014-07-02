/*
 * IfNode.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include <Context/json11.hpp>

#include "Node.h"

namespace RedZone {

class IfNode: public Node {
public:

    typedef bool ( json11::Json::*Comparer )( json11::Json const & ) const;

    IfNode();

    virtual void render( std::ostream & stream, Context * context ) const;

    virtual void processFragment( Fragment const * fragment );
    virtual void exitScope();

    virtual ~IfNode();

protected:
    json11::Json operandToJson( std::string const & operand, Context const * context ) const;

protected:
    std::vector< std::string > m_operands;
    static const std::map< std::string, Comparer > m_comparers;
    Comparer m_comparer = nullptr;
    std::vector< std::shared_ptr< Node > > m_ifNodes;
    std::vector< std::shared_ptr< Node > > m_elseNodes;
};

} /* namespace RedZone */
