/*!
 * @file node.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 14, 2015
 */
#pragma once

#ifndef ENGINE_INCLUDE_NODE_H_
#define ENGINE_INCLUDE_NODE_H_

#include "container/intrusivelist.h"
#include "strings.h"

namespace crap
{
class Component;
class ComponentSystem;

class Node
{
public:

	friend class ComponentSystem;

	Node( ComponentSystem* system, uint32_t id = 0 );
	~Node( void );

	void initChildren( void );

	CRAP_INLINE intrusive_list<Component>* getComponents( void ) { return &_components; }

	void sendChidren( string_hash name, pointer_t<void> );

	CRAP_INLINE string_hash getName( void ) const { return _name; }

	CRAP_INLINE uint32_t getID( void ) const { return _id; }

	CRAP_INLINE bool operator==( const uint32_t id )
	{
		return id == _id;
	}

	CRAP_INLINE bool operator==( const Node& other )
	{
		return other._id == _id;
	}

private:

	CRAP_INLINE void setId( uint32_t id ) { _id = id; }
	CRAP_INLINE void setName( string_hash name ) { _name = name; }

	ComponentSystem*			_system;
	intrusive_list<Component>	_components;
	uint32_t					_id;
	string_hash					_name;
};

} /* namespace crap */

#endif /* ENGINE_INCLUDE_NODE_H_ */
