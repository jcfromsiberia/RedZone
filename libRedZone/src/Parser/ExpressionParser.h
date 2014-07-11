/*
 * ExpressionParser.h
 *
 *      Author: jc
 */

#pragma once

#include <functional>
#include <set>
#include <string>

#include <Context/json11.hpp>
#include <Export.h>

namespace RedZone
{

class Context;

class RZ_API ExpressionParser
{
public:
   typedef std::set< char > charset;

   ExpressionParser( Context const * context );

   json11::Json parse( std::string expression ) const;

   virtual ~ExpressionParser();

protected:
   json11::Json parseRecursive( std::string expression ) const;

protected:
   Context const * m_context;
   charset m_binaryOperatorChars;
};

} /* namespace RedZone */
