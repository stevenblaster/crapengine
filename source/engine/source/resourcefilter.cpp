/*!
 * @file resourcefilter.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 25, 2014
 */

#include "resourcemanager.h"
#include "resourcefilter.h"

namespace crap
{

ResourceFilter::ResourceFilter( string_hash name, ResourceManager* manager ) :
	_node( this, manager->filters() ), _id(name.hash()) {}

} /* namespace crap */
