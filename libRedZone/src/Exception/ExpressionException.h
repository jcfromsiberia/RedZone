/*
 * ExpressionException.h
 *
 *      Author: jc
 */

#pragma once

#include "Exception.h"

namespace RedZone
{

class RZ_API ExpressionException : public Exception
{
public:
   using Exception::Exception;

   ExpressionException( std::string const & expr, std::string const & err );

   virtual ~ExpressionException();
};

} /* namespace RedZone */
