/*!
 * @file directorylistener.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 26, 2014
 */


#ifndef ENGINE_INCLUDE_DIRECTORYLISTENER_H_
#define ENGINE_INCLUDE_DIRECTORYLISTENER_H_

#include "strings.h"
#include "container/array.h"
#include "container/arraymap.h"
#include "delegates.h"
#include "directory.h"

#include "memory.h"

#ifdef CRAP_NO_DEBUG
#define DIRECTORY_MEMORY SimpleGeneralMemory
#else
#define DIRECTORY_MEMORY BoundGeneralMemory
#endif

namespace crap
{


class DirectoryListener
{
public:

	typedef crap::delegate< void (const char*) > DirectoryFunction;
	typedef array<DirectoryFunction> FunctionArray;
	typedef array_map< string_hash, uint64_t > FileMap;

	DirectoryListener( uint32_t max_functions, uint32_t max_files, const string256& path, bool recursive = false );

	~DirectoryListener( void );

	template< class C, void (C::*F)( const char* ) >
	void addCallback( C* instance );

	template< void (*F)( const char* ) >
	void addCallback( void );

	template< class C, void (C::*F)( const char* ) >
	void removeCallback( C* instance );

	template< void (*F)( const char* ) >
	void removeCallback( void );

	CRAP_INLINE void init( void ){ update(0); }
	bool update( uint32_t deltatime );

private:

	void scanDirectory( const string256& path );

	DIRECTORY_MEMORY	_allocator;

	FunctionArray 	_functions;
	FileMap			_fileMap;
	string256		_path;
	bool			_recursive;
};


template< class C, void (C::*F)( const char* ) >
void DirectoryListener::addCallback( C* instance )
{
	DirectoryFunction function;
	function.bind<C,F>(instance);
	_functions.push_back( function );
}

template< void (*F)( const char* ) >
void DirectoryListener::addCallback( void )
{
	DirectoryFunction function;
	function.bind<F>();
	_functions.push_back( function );
}

template< class C, void (C::*F)( const char* ) >
void DirectoryListener::removeCallback( C* instance )
{
	DirectoryFunction function;
	function.bind<C,F>(instance);
	uint32_t index = _functions.find( function );
	if( index != FunctionArray::INVALID )
	{
		_functions.erase_at( index );
	}
}

template< void (*F)( const char* ) >
void DirectoryListener::removeCallback( void )
{
	DirectoryFunction function;
	function.bind<F>();
	uint32_t index = _functions.find( function );
	if( index != FunctionArray::INVALID )
	{
		_functions.erase_at( index );
	}
}

} /* namespace crap */

#endif /* ENGINE_INCLUDE_DIRECTORYLISTENER_H_ */
