/*!
 * @file directorylistener.cpp
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

#include "directorylistener.h"

namespace crap
{

DirectoryListener::DirectoryListener( uint32_t max_functions, uint32_t max_files, const string256& path, bool recursive ) :
		_allocator( FunctionArray::size_of_elements( max_functions )+FileMap::size_of_elements( max_files )+1024 ),
		_functions( _allocator.allocate(FunctionArray::size_of_elements( max_functions ), 4), FunctionArray::size_of_elements( max_functions ) ),
		_fileMap( _allocator.allocate(FileMap::size_of_elements( max_files ), 4), FileMap::size_of_elements( max_files ) ),
		_path( path ),
		_recursive( recursive )
{

}

DirectoryListener::~DirectoryListener(void)
{
	while( _functions.size() > 0 )
	{
		_functions.pop_back();
	}

	while(_fileMap.size() > 0 )
	{
		_fileMap.pop_back();
	}

	_allocator.deallocate( _fileMap.memory().as_void );
	_allocator.deallocate( _functions.memory().as_void );
}

void DirectoryListener::scanDirectory( const string256& path )
{
	directory_t dir;
	if( !openDirectory( &dir, path.c_str() ) )
		return;

    do
    {
    	crap::string256 filePath;
    	crap::getAbsolutePath( &dir, &filePath );
    	string256 fileName = crap::directoryName( &dir );

    	if( fileName.size() < 3 )
    		continue;

    	if( isDirectory( &dir ) )
    	{
    		if( _recursive )
    			scanDirectory( filePath );
    	}
    	else
    	{
    		const string_hash hash( filePath.c_str() );
    		const uint64_t timestamp = getLastWriteTime( &dir );

    		uint32_t index = _fileMap.find( hash );
    		if( index == FileMap::INVALID )
    		{
    			_fileMap.push_back( hash, timestamp );
    			for( uint32_t i=0; i<_functions.size(); ++i )
    			{
    				_functions[i].invoke( filePath.c_str() );
    			}
    		}
    		else if( *(_fileMap.get_value(index )) != timestamp )
    		{
    			*( _fileMap.get_value(index) ) = timestamp;
    			for( uint32_t i=0; i<_functions.size(); ++i )
    			{
    				_functions[i].invoke( filePath.c_str() );
    			}
    		}
    	}

    } while( crap::nextDirectory( &dir ) );

    closeDirectory( &dir );
}

bool DirectoryListener::update( uint32_t deltatime )
{
	scanDirectory( _path );
}

} /* namespace crap */
