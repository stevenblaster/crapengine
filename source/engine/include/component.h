/*!
 * @file component.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 28, 2014
 */
#pragma once

#ifndef ENGINE_INCLUDE_COMPONENT_H_
#define ENGINE_INCLUDE_COMPONENT_H_

#include "utilities.h"
#include "convert.h"

namespace crap
{
class System;

class Component
{
public:

	friend class ComponentFactory;

	CRAP_INLINE Component( uint32_t type ) : _typeID(type) {}
	virtual ~Component( void ) {}

	uint64_t getGlobalID( void ) const { return _globalID; }
	uint32_t getTypeID( void ) const { return _typeID; }
	uint32_t getComponentID( void ) const { return _componentID; }

	virtual void init( System* system ) {}
	virtual void deinit( System* system ) {}

	void setComponentID( uint64_t cid ) { _componentID = cid; }

protected:

	union
	{
		uint64_t _globalID;
		struct
		{
			uint32_t _typeID;
			uint32_t _componentID;
		};
	};
};

#define DECLARE_COMPONENT_MEMBER( classname, varname, vartype )					\
	private: vartype _##varname;										\
	public:	CRAP_INLINE vartype* get##varname( void ) { return &_##varname; }	\
	public: static void set##varname( classname* instance, const string64& data )	\
	{ instance->_##varname = crap::convert<string64, vartype>(data); }

} /* namespace crap */

#endif /* ENGINE_INCLUDE_COMPONENT_H_ */
