/*
 * Template.cpp
 *
 *  Created on: 21 ���� 2014 �.
 *      Author: jc
 */
#include <algorithm>
#include <functional>

#include <Node/Root.h>
#include <Parser/Parser.h>

#include "Template.h"

using namespace std::placeholders;

namespace RedZone {

Template::Template() {
}

void Template::render( std::ostream & stream, Context * context ) const {
    m_root->render( stream, context );
}

void Template::loadFromStream( std::istream & stream ) {
    Parser parser;
    m_root.reset( parser.loadFromStream( stream ) );
}

Template::~Template() {
}

} /* namespace RedZone */
