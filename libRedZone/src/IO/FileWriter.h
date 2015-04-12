/*
 * FileWriter.h
 *
 *      Author: jc
 */

#pragma once

#include <fstream>

#include "Writer.h"

namespace RedZone {

class RZ_API FileWriter : public Writer {
public:
   FileWriter( std::string const & fileName );

   virtual void write( std::string const & data );
   virtual void flush();

   virtual ~FileWriter();

protected:
   std::ofstream m_file;

private:
   FileWriter( FileWriter const & ) { }
};

} /* namespace RedZone */
