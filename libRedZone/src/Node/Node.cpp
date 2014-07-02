/*
 * Node.cpp
 *
 *  Created on: 2014
 *      Author: jc
 */

#include "Node.h"

#include <algorithm>
#include <functional>
#include <iostream>

#include <Context/Context.h>

namespace RedZone {

Node::Node( bool createsScope )
    : m_createsScope( createsScope ) {

}

void Node::render( std::ostream & stream, Context * context ) const {
    stream << "*** NOT IMPLEMENTED ***";
}

void Node::renderChildren( std::ostream & stream, Context * context,
        std::vector< std::shared_ptr< Node > > children ) const {
    if( !children.size() )
        children = m_children;
    std::for_each( children.begin(), children.end(),
            std::bind( &Node::render,
                    std::placeholders::_1,
                    std::ref( stream ), context ) );
}

void Node::addChild( Node * child ) {
    m_children.push_back( std::shared_ptr< Node >( child ) );
}

bool Node::createsScope() const {
    return m_createsScope;
}

json11::Json Node::resolveInContext( std::string const & name, Context const * context ) const {
    return context->resolve( name );
}

void Node::processFragment( Fragment const * fragment ) {
}

void Node::enterScope() {

}

void Node::exitScope() {

}

Node::~Node() {

}

} /* namespace RedZone */
