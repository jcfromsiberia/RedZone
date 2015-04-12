/*
 * StringReader.h
 *
 *      Author: jc
 */

#pragma once

#include <string>

#include "Reader.h"

namespace RedZone {

class RZ_API StringReader : public Reader {
public:
   StringReader( std::string const & string );

   virtual std::string read( size_t nBytes );
   virtual std::string readAll();
   virtual std::string id() const;

   virtual ~StringReader();

protected:
   std::string const & m_string;
   std::string::const_iterator m_iter;
};

} /* namespace RedZone */
