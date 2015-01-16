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

	Node( uint32_t id = 0 );
	~Node( void );

	CRAP_INLINE intrusive_list<Component>* getComponents( void ) { return &_components; }

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

	intrusive_list<Component>	_components;
	uint32_t					_id;
};

} /* namespace crap */

#endif /* ENGINE_INCLUDE_NODE_H_ */
