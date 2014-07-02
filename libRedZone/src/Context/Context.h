/*
 * Context.h
 *
 *  Created on: 21 ���� 2014 �.
 *      Author: jc
 */
#pragma once

#include <string>

#include <Export.h>

#include "json11.hpp"

namespace RedZone {

class RZ_API Context {
public:
	Context( std::string const & json );

	Context( json11::Json const & json );
	Context( json11::Json && json );

	json11::Json json() const;
	void setJson( json11::Json const & json );

	json11::Json resolve( std::string const & name ) const;

	virtual ~Context();

protected:
	json11::Json m_json;
};

} /* namespace RedZone */
