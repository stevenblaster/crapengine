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

#include "attributes.h"


namespace crap
{
class Node;
class System;

class Component
{
public:

	struct TypeList
	{
		Component* components[10];
		TypeList( void ) { memset(components, 0, sizeof(components)); }
	};

	friend class ComponentFactory;
	template<typename t> friend class ComponentType;

	Component( uint32_t type, Node* node );
	virtual ~Component( void ) {}

	CRAP_INLINE uint64_t getGlobalID( void ) const { return _globalID; }
	CRAP_INLINE uint32_t getTypeID( void ) const { return _typeID; }
	CRAP_INLINE uint32_t getComponentID( void ) const { return _componentID; }

	Node*	getNode( void );
	Component* getNeighbour( string_hash type );

	TypeList getNeighboursOfType( string_hash type );

	virtual void init( System* system ) {}
	virtual void deinit( System* system ) {}

	virtual void receiveMessage( string_hash name, pointer_t<void> ) {}

	void setNode( Node* node );

	CRAP_INLINE
	bool operator<( const Component& other ) const { return _globalID < other._globalID; }

protected:

	Component( void );

	CRAP_INLINE void setGlobalID( uint64_t id ) { _globalID = id; }
	CRAP_INLINE void setTypeID( uint32_t id ) { _typeID = id; }
	CRAP_INLINE void setComponentID( uint32_t id ) { _componentID = id; }

	union
	{
		uint64_t _globalID;
		struct
		{
			uint32_t _typeID;
			uint32_t _componentID;
		};
	};

	Node*						_node;
	intrusive_node<Component> 	_listnode;
};

#define DECLARE_COMPONENT_MEMBER( classname, varname, vartype )					\
	private: vartype _##varname;										\
	public:	CRAP_INLINE const vartype& get##varname( void ) const { return _##varname; }	\
	public: static void set##varname( classname* instance, const string64& data )	\
	{ instance->_##varname = crap::convert<string64, vartype>(data); }

} /* namespace crap */

#endif /* ENGINE_INCLUDE_COMPONENT_H_ */
