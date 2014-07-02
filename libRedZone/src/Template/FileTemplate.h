/*
 * FileTemplate.h
 *
 *  Created on: 2014
 *      Author: jc
 */
#pragma once

#include "Template.h"

#include <string>

namespace RedZone {

class RZ_API FileTemplate: public Template {
public:
	FileTemplate( std::string const & filePath );
	virtual ~FileTemplate();

private:
	std::string m_filePath;
};

} /* namespace RedZone */
