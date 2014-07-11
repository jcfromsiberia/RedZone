/*
 * Context.h
 *
 *  Created on: 21 ���� 2014 �.
 *      Author: jc
 */
#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>

#include <Export.h>

#include "json11.hpp"

namespace RedZone {

class RZ_API Context {
public:
   typedef std::function< json11::Json( json11::Json const &, json11::Json const & ) > BinaryOperator;
   typedef std::vector< std::tuple< std::string, int, BinaryOperator > > BinaryOperators;

   typedef std::function< json11::Json( std::vector< json11::Json > const & ) > Function;
   typedef std::map< std::string, Function > Functions;

	Context( std::string const & json );

	Context( json11::Json const & json );

	json11::Json json() const;
	void setJson( json11::Json const & json );

	json11::Json resolve( std::string const & name ) const;

	BinaryOperators const & binaryOperators() const;
	Functions const & functions() const;

	virtual ~Context();

protected:
	Context();

protected:
	json11::Json m_json;
	BinaryOperators m_binaryOperations;
	Functions m_functions;
};

} /* namespace RedZone */
