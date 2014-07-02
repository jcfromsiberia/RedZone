/*
 * Context.cpp
 *
 *  Created on: 21 ���� 2014 �.
 *      Author: jc
 */

#include "Context.h"

#include <regex>
#include <iostream>

#include <Exception/JsonError.h>
#include <Exception/TemplateContextError.h>

using namespace json11;

namespace RedZone {

Context::Context( std::string const & json ) {
    std::string err;
    m_json = Json::parse( json, err );
    if( err.size() ) {
        throw JsonError( err );
    }
}

Context::Context( json11::Json const & json )
    : m_json( json ) {

}

Context::Context( json11::Json && json )
    : m_json( json ) {

}

json11::Json Context::json() const {
    return m_json;
}

void Context::setJson( json11::Json const & json ) {
    m_json = json;
}

Json Context::resolve( std::string const & name ) const {
    Json result = m_json;
    static const std::regex splitter( R"(\.)" );
    std::sregex_token_iterator iter( name.begin(), name.end(), splitter, -1 );
    static const std::sregex_token_iterator end;
    for( ; iter != end; ++iter ) {
        Json tmp = result[ *iter ];
        if( tmp.is_null() ) {
            throw TemplateContextError( name );
        }
        result = tmp;
    }
    return result;
}

Context::~Context() {
}

} /* namespace RedZone */
