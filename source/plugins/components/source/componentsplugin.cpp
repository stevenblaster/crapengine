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
#include "rectangle.h"
#include "roundedrectangle.h"
#include "text2d.h"
#include "system.h"
#include "plugin.h"
#include "physic2drectangle.h"
#include "physic2dcircle.h"

namespace crap
{

CRAP_DECLARE_PLUGIN( ComponentsPlugin )
{
public:
	ComponentsPlugin( System* system ) :
		_trans2d("Transformation2D", system->getSubSystem<ComponentSystem>("ComponentSystem"),10),
		_circle2d("Circle", system->getSubSystem<ComponentSystem>("ComponentSystem"),10),
		_rectangle2d("Rectangle", system->getSubSystem<ComponentSystem>("ComponentSystem"),10),
		_roundedRectangle2d("RoundedRectangle", system->getSubSystem<ComponentSystem>("ComponentSystem"),10),
		_text2d("Text2D", system->getSubSystem<ComponentSystem>("ComponentSystem"),10),
		_physic2drectangle("Physic2DRectangle", system->getSubSystem<ComponentSystem>("ComponentSystem"),10),
		_physic2dcircle("Physic2DCircle", system->getSubSystem<ComponentSystem>("ComponentSystem"),10)
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

    crap::ComponentType<Transformation2D>	_trans2d;
    crap::ComponentType<Circle>	_circle2d;
    crap::ComponentType<Rectangle>	_rectangle2d;
    crap::ComponentType<RoundedRectangle> _roundedRectangle2d;
    crap::ComponentType<Text2D> _text2d;
    crap::ComponentType<Physic2DRectangle> _physic2drectangle;
    crap::ComponentType<Physic2DCircle>  _physic2dcircle;
};

CRAP_PLUGIN_FACTORY( ComponentsPlugin )

} /* namespace crap */
