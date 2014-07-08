/*
 * ExpressionParser.h
 *
 *      Author: jc
 */

#pragma once

#include <functional>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include <Context/json11.hpp>
#include <Export.h>

namespace RedZone
{

class Context;

class RZ_API ExpressionParser
{
public:
   ExpressionParser( Context const * context );

   json11::Json parse( std::string expression ) const;

   virtual ~ExpressionParser();

protected:
   json11::Json parseRecursive( std::string expression ) const;

protected:
   Context const * m_context;

   // TODO: move operators and functions into context
   static std::vector< std::tuple< std::string, int,
      std::function< json11::Json( json11::Json const &, json11::Json const & ) > > > const s_binaryOperations;
   static std::map< std::string, std::function< json11::Json( std::vector< json11::Json > const & ) > > const s_functions;
};

} /* namespace RedZone */
