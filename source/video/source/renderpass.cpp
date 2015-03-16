/*!
 * @file renderpass.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Mar 16, 2015
 */

#include "rendersystem.h"
#include "renderpass.h"

namespace crap
{

RenderPass::RenderPass( uint32_t key, RenderSystem* renderSystem ) :
		_key(key), _node(this, renderSystem->getRenderList())
{

}

} /* namespace crap */
