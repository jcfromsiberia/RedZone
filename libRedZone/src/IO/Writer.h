/*
 * Writer.h
 *
 *      Author: jc
 */

#pragma once

#include <string>

#include <Export.h>

namespace RedZone {

class RZ_API Writer {
public:
   virtual void write( std::string const & data ) = 0;
   virtual void flush() = 0;

   virtual ~Writer();

protected:
   Writer();
};

} /* namespace RedZone */
