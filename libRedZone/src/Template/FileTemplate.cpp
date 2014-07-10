/*
 * FileTemplate.cpp
 *
 *  Created on: 2014
 *      Author: jc
 */

#include <fstream>

#include <Exception/IOError.h>
#include <IO/FileReader.h>

#include "FileTemplate.h"

namespace RedZone {

FileTemplate::FileTemplate( std::string const & filePath )
	: m_filePath( filePath ) {
   FileReader in( filePath );
   loadFromStream( &in );
}

FileTemplate::~FileTemplate() {
}

} /* namespace RedZone */
