/*!
 * @file physic2d.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 20, 2015
 */
#pragma once

#ifndef PLUGINS_COMPONENTS_INCLUDE_RECTANGLE2DPHYSIC_H_
#define PLUGINS_COMPONENTS_INCLUDE_RECTANGLE2DPHYSIC_H_


#include "component.h"

/**
 * @namespace crap
 */
namespace crap
{

class Attributes2D;

class Rectangle2DPhysic : public Component
{
public:
	Rectangle2DPhysic( void );
	virtual ~Rectangle2DPhysic( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_CLASS_ATTRIBUTE( Rectangle2DPhysic, width, float32_t )
	DECLARE_CLASS_ATTRIBUTE( Rectangle2DPhysic, height, float32_t )
	DECLARE_CLASS_ATTRIBUTE( Rectangle2DPhysic, density, float32_t )
	DECLARE_CLASS_ATTRIBUTE( Rectangle2DPhysic, dynamic, uint32_t )

	CRAP_INLINE
	bool operator<( const Rectangle2DPhysic& other ) const { return _globalID < other._globalID; }

private:

	uint32_t				_bodyID;
	Attributes2D*			_attributes;
};

} /* namespace crap */



#endif /* PLUGINS_COMPONENTS_INCLUDE_RECTANGLE2DPHYSIC_H_ */
