/*!
 * @file audioplugin.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 27, 2014
 */
#define CRAP_DL 1

#include "config/crap_platform.h"
#include "config/crap_compiler.h"

#include "componenttype.h"
#include "testcomponent.h"
#include "transformation2d.h"
#include "circle.h"
#include "system.h"
#include "plugin.h"

namespace crap
{

CRAP_DECLARE_PLUGIN( ComponentsPlugin )
{
public:
	ComponentsPlugin( System* system ) :
		_test("TestComponent", system->getSubSystem<ComponentSystem>("ComponentSystem"),10),
		_trans2d("Transformation2D", system->getSubSystem<ComponentSystem>("ComponentSystem"),10),
		_circle2d("Circle", system->getSubSystem<ComponentSystem>("ComponentSystem"),10)
	{
	}

	~ComponentsPlugin( void )
	{
	}

    void init( void )
    {
    }

    void deinit( void )
    {
    }

    uint32_t id( void )
    {
    	return string_hash("ComponentsPlugin").hash();
    }

private:

    crap::ComponentType<TestComponent>	_test;
    crap::ComponentType<Transformation2D>	_trans2d;
    crap::ComponentType<Circle>	_circle2d;
};

CRAP_PLUGIN_FACTORY( ComponentsPlugin )

} /* namespace crap */
