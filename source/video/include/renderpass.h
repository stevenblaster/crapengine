/*!
 * @file renderpass.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Mar 15, 2015
 */
#pragma once

#ifndef VIDEO_INCLUDE_RENDERPASS_H_
#define VIDEO_INCLUDE_RENDERPASS_H_

#include "utilities.h"
#include "container/intrusivelist.h"

namespace crap
{

class RenderSystem;

class RenderPass
{
public:
	RenderPass( uint32_t key, RenderSystem* rendererSystem );
	virtual ~RenderPass( void ) {}

	uint32_t getKey( void ) const { return _key; }

	bool operator==( const RenderPass& other ) const { return _key == other._key; }
	bool operator<( const RenderPass& other ) const { return _key < other._key; }

	virtual void prepareRender( void ) {}
	virtual void render( void ) {}
	virtual void finishRender( void ) {}

private:

	uint32_t _key;
	intrusive_node<RenderPass> _node;
};

} /* namespace crap */

#endif /* VIDEO_INCLUDE_RENDERPASS_H_ */
