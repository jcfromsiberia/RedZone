/*
 * FileReader.h
 *
 *      Author: jc
 */

#pragma once

#include <fstream>
#include <iterator>
#include <string>

#include "Reader.h"

namespace RedZone {

class RZ_API FileReader : public Reader {
public:
   FileReader( std::string const & fileName );

   virtual std::string read( size_t nBytes );
   virtual std::string readAll();
   virtual std::string id() const;

   virtual ~FileReader();

protected:
   std::ifstream m_file;
   std::string m_path;

private:
   FileReader( FileReader const & ) { }
};

} /* namespace RedZone */
