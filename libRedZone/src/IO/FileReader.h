/*
 * FileReader.h
 *
 *      Author: jc
 */

#pragma once

#include <fstream>
#include <iterator>

#include "Reader.h"

namespace RedZone {

class FileReader : public Reader {
public:
   FileReader( std::string const & fileName );

   virtual std::string read( size_t nBytes );
   virtual std::string readAll();

   virtual ~FileReader();

protected:
   std::ifstream m_file;

private:
   FileReader( FileReader const & ) { }
};

} /* namespace RedZone */
