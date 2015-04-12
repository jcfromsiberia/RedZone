/*
 * Template.h
 *
 *  Created on: 21 ���� 2014 �.
 *      Author: jc
 */
#pragma once

#include <memory>
#include <string>
#include <vector>

#include <Export.h>

namespace RedZone {

class Context;
class Reader;
class Root;
class Writer;

class RZ_API Template {
public:
	virtual ~Template();

	void renderToStream( Writer * stream, Context * context ) const;
	std::string render( Context * context ) const;

protected:
	Template();
	void loadFromStream( Reader * stream );

protected:
	std::shared_ptr< Root const > m_root;
};

} /* namespace RedZone */
