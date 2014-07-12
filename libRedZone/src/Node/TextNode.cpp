/*
 * TextNode.cpp
 *
 *  Created on: 2014
 *      Author: jc
 */
#include "TextNode.h"

#include <IO/Writer.h>
#include <Parser/Fragment.h>

namespace RedZone {

TextNode::TextNode()
    : Node() {

}

void TextNode::render( Writer * stream, Context * context ) const {
    (void)context;
    stream->write( m_text );
}

void TextNode::processFragment( Fragment const * fragment ) {
    m_text = fragment->raw();
}

std::string TextNode::name() const {
   return "Text";
}

TextNode::~TextNode() {
}

} /* namespace RedZone */
