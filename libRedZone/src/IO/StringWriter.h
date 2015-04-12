/*
 * StringWriter.h
 *
 *      Author: jc
 */

#pragma once

#include <string>

#include "Writer.h"

namespace RedZone {

class RZ_API StringWriter : public Writer {
public:
   StringWriter( std::string & string );

   virtual void write( std::string const & data );
   virtual void flush();

   virtual ~StringWriter();

protected:
   std::string & m_string;
};

} /* namespace RedZone */
