


#include "componentsystem.h"
#include "componentfactory.h"

namespace crap
{

ComponentFactory::ComponentFactory( crap::string_hash name, ComponentSystem* system ) :
		_node( this, system->factoryList() ), _name( name )
	{}

}