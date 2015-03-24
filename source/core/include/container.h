/*!
 * @file container.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Mar 21, 2015
 */
#pragma once

#ifndef CORE_INCLUDE_CONTAINER_H_
#define CORE_INCLUDE_CONTAINER_H_

#include "utilities.h"
#include "assert.h"
#include "container/array.h"

namespace crap
{

template<typename T, typename M, typename C>
class Container
{
private:

	M			_memory;
	C			_container;

public:

	Container( uint32_t size ) { CRAP_STATIC_ASSERT( false , "Please specialize this class." ); }

	~Container( void ) {}
};

template<typename T, typename M>
class Container< T, M, array<T> >
{

};

}

#endif /* CORE_INCLUDE_CONTAINER_H_ */
