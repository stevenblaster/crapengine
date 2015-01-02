/*!
 * @file componentsystem.h
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

#ifndef ENGINE_INCLUDE_COMPONENTSYSTEM_H_
#define ENGINE_INCLUDE_COMPONENTSYSTEM_H_

#include "utilities.h"
#include "container/intrusivelist.h"

namespace crap
{
class ComponentFactory;

class ComponentSystem
{
public:
	ComponentSystem( void );
	~ComponentSystem( void );

	intrusive_list<ComponentFactory>* factoryList( void ) { return &_factoryList; }

private:

	intrusive_list<ComponentFactory> _factoryList;
};

} /* namespace crap */

#endif /* ENGINE_INCLUDE_COMPONENTSYSTEM_H_ */
