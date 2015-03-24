/*!
 * @file plugintype.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Mar 22, 2015
 */
#pragma once

#ifndef ENGINE_INCLUDE_PLUGINTYPE_H_
#define ENGINE_INCLUDE_PLUGINTYPE_H_

#include "attributes.h"
#include "plugin.h"

namespace crap
{

template<typename T>
class PluginType : public Plugin
{

public:

	PluginType( void ){}

	virtual void setAttribute( Plugin* plugin, string_hash attribute_name, const string64& value )
	{
		intrusive_node< ClassAttribute<T> >* node = ClassAttribute<T>::list.begin();
		for( ; node != ClassAttribute<T>::list.end(); node = ClassAttribute<T>::list.next( node ) )
		{
			if( node->parent()->name == attribute_name )
			{
				node->parent()->setFunction( (T*)plugin, value );
			}
		}
	}
};

} /* namespace crap */

#define CRAP_DECLARE_PLUGIN( type ) class type : public crap::PluginType<type>

#endif /* ENGINE_INCLUDE_PLUGINTYPE_H_ */
