/*
 * ExpressionException.cpp
 *
 *      Author: jc
 */
#include "ExpressionException.h"

namespace RedZone
{

ExpressionException::ExpressionException( std::string const & expr, std::string const & err )
   : Exception( "In expression \"" + expr + "\": " + err )
{
}

ExpressionException::~ExpressionException()
{
}

} /* namespace RedZone */
