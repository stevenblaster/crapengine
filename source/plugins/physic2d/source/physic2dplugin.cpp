
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
#include "../../default/include/attributes2d.h"
#include "system.h"
#include "plugin.h"
#include "components/rectangle2dphysic.h"
#include "components/circle2dphysic.h"
#include "components/collision2d.h"
#include "physicsystem2d.h"
#include "taskmanager.h"

namespace crap
{

CRAP_DECLARE_PLUGIN( Physic2DPlugin )
{
public:
	Physic2DPlugin( System* system ) :
		_physic2drectangle("Rectangle2DPhysic", system->getSubSystem<ComponentSystem>("ComponentSystem"),10),
		_physic2dcircle("Circle2DPhysic", system->getSubSystem<ComponentSystem>("ComponentSystem"),10),
		_collision2d("Collision2D", system->getSubSystem<ComponentSystem>("ComponentSystem"),10)
	{
	}

	~Physic2DPlugin( void )
	{

	}

    virtual void init( System* system )
    {
    	_sys = new PhysicSystem2D( 1000, 0.f, 10.f, 8, 2, 1.f/200.f );
    	_sub = new SubSystem( "PhysicSystem2D", _sys, system );
    	system->getSubSystem<TaskManager>("TaskManager")->addTask< crap::PhysicSystem2D, &crap::PhysicSystem2D::update>( "Physic2DUpdate", _sys, 20, true, false );
    }

    virtual void deinit( System* system )
    {
    	_sub->~SubSystem();
    }

    uint32_t id( void )
    {
    	return string_hash("Physic2DPlugin").hash();
    }

private:

    crap::ComponentType<Rectangle2DPhysic> _physic2drectangle;
    crap::ComponentType<Circle2DPhysic>  _physic2dcircle;
    crap::ComponentType<Collision2D>  _collision2d;
    crap::PhysicSystem2D*	_sys;
    crap::SubSystem* _sub;
};

CRAP_PLUGIN_FACTORY( Physic2DPlugin )

} /* namespace crap */
