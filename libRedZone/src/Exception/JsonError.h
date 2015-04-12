/*
 * JsonError.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include "Exception.h"

#include <Common.h>

namespace RedZone {

class RZ_API JsonError: public Exception {
public:
#if defined( RZ_UNIX )
    using Exception::Exception;
#elif defined( RZ_WINDOWS )
#   pragma message( "Stupid M$VC compiler does not support constructor inheritance!" )
	JsonError( std::string const & message ) : Exception( message ) 
	{
	}
#else
#   error( "Not implemented yet" )
#endif
    virtual ~JsonError();
};

} /* namespace RedZone */
