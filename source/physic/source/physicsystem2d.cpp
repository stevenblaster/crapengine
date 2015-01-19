/*!
 * @file physicsystem2d.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 19, 2015
 */

#include <Box2D/Box2D.h>
#include "physicsystem2d.h"

namespace crap
{

PhysicSystem2D::PhysicSystem2D( void )
{
	b2Vec2 gravity(0.0f, -10.0f);
	b2World world(gravity);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	b2Body* groundBody = world.CreateBody(&groundBodyDef);



	b2PolygonShape groundBox;

	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

}

PhysicSystem2D::~PhysicSystem2D( void )
{

}

}/* namespace crap */
