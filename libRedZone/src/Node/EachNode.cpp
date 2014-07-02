/*
 * EachNode.cpp
 *
 *  Created on: 2014
 *      Author: jc
 */

#include "EachNode.h"

#include <regex>
#include <iostream>

#include <Context/Context.h>
#include <Exception/TemplateSyntaxError.h>
#include <Parser/Fragment.h>

using namespace json11;

namespace RedZone {

EachNode::EachNode()
    : Node( true ) {
}

void EachNode::render( std::ostream & stream, Context * context ) const {
    Json container = resolveInContext( m_container, context );
    if( !container.is_array() ) {
        throw Exception( m_container + " is not iterable" );
    }
    Json::array items = container.array_items();

    Json::object prototype = context->json().object_items();

    std::shared_ptr< Context > newContext( new Context( prototype ) );

    for( auto item: items ) {
        prototype[ m_var ] = item;
        newContext->setJson( Json( prototype ) );
        renderChildren( stream, newContext.get() );
    }
}

void EachNode::processFragment( Fragment const * fragment ) {
    static const std::regex splitter( R"(^each\s+([A-Za-z0-9\.]+)\s+as\s+(\w+)$)" );
    std::smatch match;
    if( !std::regex_match( fragment->clean(), match, splitter ) ) {
        throw TemplateSyntaxError( fragment->clean() );
    }
    m_container = match[1];
    m_var = match[2];
}

EachNode::~EachNode() {
}

} /* namespace RedZone */
