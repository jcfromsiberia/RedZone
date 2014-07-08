/*
 * ExpressionException.h
 *
 *      Author: jc
 */

#pragma once

#include "Exception.h"

namespace RedZone
{

class ExpressionException : public Exception
{
public:
   using Exception::Exception;

   ExpressionException( std::string const & expr, std::string const & err );

   virtual ~ExpressionException();
};

} /* namespace RedZone */
