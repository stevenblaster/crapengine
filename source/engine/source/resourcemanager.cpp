
#include "resourcemanager.h"
#include "file.h"
#include "logger.h"
#include "xml/tinyxml2.h"
#include "system.h"

namespace crap
{

//intrusive_list<ResourceFilter> ResourceFilterList;

ResourceManager::ResourceManager( uint32_t bufferMemory, uint32_t resourceNumber, const string256& path, System* system ) :
    _allocator( bufferMemory + ResourceMap::size_of_elements( resourceNumber ) ),
    _resources( _allocator.allocate( ResourceMap::size_of_elements(resourceNumber), 4 ),
    		ResourceMap::size_of_elements(resourceNumber) ),
    _path( path ),
	_system(system)
{
	if( _path[ _path.size()-1 ] != '/')
	        _path.concat('/');

    crap::log( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "Resourcemanager with %i bytes memory, max. %i resources with path %s created", bufferMemory + ResourceMap::size_of_elements( resourceNumber ), resourceNumber, path.c_str() );
}

ResourceManager::~ResourceManager( void )
{
	clearInfo();
    _allocator.deallocate( _resources.memory().as_void );
}

void ResourceManager::clearInfo( void )
{
	while( _resources.size() != 0 )
	{
		_resources.erase_at( _resources.size()-1 );
	}
}

void ResourceManager::loadXML( const string64& filename )
{
    crap::log( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "Loading XML Resourceinfo from file %s", filename.c_str() );

    const string256 file_path = _path + filename;
    const uint32_t buffer_size = crap::fileSize( file_path.c_str() );

    file_t* handle = openFile( file_path.c_str() , CRAP_FILE_READ );

    CRAP_ASSERT( ASSERT_BREAK, handle != 0, "Could not open file %s", file_path.c_str() );

    pointer_t<void> buffer(_allocator.allocate(buffer_size, 4) );
	memset( buffer.as_void, 0, buffer_size ); //windows fix...
    readFromFile( handle, buffer, buffer_size );

    tinyxml2::XMLDocument doc;
    uint32_t errorId = doc.Parse( buffer.as_const_char, buffer_size );
    CRAP_ASSERT( ASSERT_BREAK, errorId == 0, doc.ErrorName() );

    tinyxml2::XMLNode* xmlNode = doc.FirstChild();
    CRAP_ASSERT( ASSERT_BREAK, string64(xmlNode->Value()) == string64("RESOURCES"), "Wrong XML tag" );

    tinyxml2::XMLElement* element = xmlNode->FirstChildElement();
    while( element != 0 )
    {
    	const string256			full_path = _path + element->GetText();

    	const string64          resource_filename( element->GetText() );
    	const uint32_t          resource_size( fileSize( full_path.c_str() ) );

    	CRAP_ASSERT( ASSERT_BREAK, resource_size != 0, "Cannot get filesize" );

        const string_hash       resource_type( element->Value() );
        const string_hash       resource_name( element->Attribute("name") );
        const uint32_t          resource_offset( 0 );

        ResourceInfo      resource_info( resource_type, resource_filename, resource_offset, resource_size );

        crap::log( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "Resource \"%s\", type \"%s\", size %i bytes, path \"%s\"", element->Attribute("name"), element->Value(), resource_size, resource_filename.c_str() );

        _resources.insert( resource_name.hash(), resource_info );

        element = element->NextSiblingElement();
    }

    _allocator.deallocate( buffer.as_void );
    closeFile( handle );
}



void ResourceManager::loadPackage( const string64& filename )
{
    crap::log( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "Loading Packed Resourceinfo from file %s", filename.c_str() );

    const string256 file_path = _path + filename;
    const uint32_t buffer_size = crap::fileSize( file_path.c_str() );

    file_t* handle = openFile( file_path.c_str() , CRAP_FILE_READ );

    CRAP_ASSERT( ASSERT_BREAK, handle != 0, "Could not open file %s", file_path.c_str() );

    pointer_t<void> buffer(_allocator.allocate(buffer_size, 4) );
    readFromFile( handle, buffer, buffer_size );

    pointer_t<PackageContentInfo> package_pointer = buffer.as_void;
    uint32_t offset = 0;
    while( offset < buffer_size )
    {
        const string_hash       resource_type( package_pointer.as_type->type );
        const string_hash       resource_name( package_pointer.as_type->name );
        const string64          resource_filename( filename );
        const uint32_t          resource_size( package_pointer.as_type->size );
        const uint32_t          resource_offset( offset + sizeof(PackageContentInfo) );

        ResourceInfo      resource_info( resource_type, resource_filename, resource_offset, resource_size );

        crap::log( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "Resource \"%u\", type \"%u\", size %i bytes, path \"%s\"", resource_name.hash(), resource_type.hash(), resource_size, resource_filename.c_str() );

        _resources.insert( resource_name.hash(), resource_info );

        offset += sizeof(PackageContentInfo) + resource_size;
        package_pointer.as_char += offset;
    }

    _allocator.deallocate(buffer.as_void);
}



void ResourceManager::loadResource( string_hash resourceId )
{
	const uint32_t index = _resources.find( resourceId.hash() );

	CRAP_ASSERT( ASSERT_BREAK, index != ResourceMap::INVALID, "Resource not known" );

	const string_hash typeId = _resources.get_value( index )->typeId;

	intrusive_node<ResourceFilter>* node = _filters.begin();
    for( ; node != _filters.end(); node = node->next() )
    {
        if( *(node->parent()) == typeId )
        {
        	const string256 filePath = _path + _resources.get_value(index)->filename;
        	const uint32_t resourceSize  = crap::fileSize( filePath.c_str() );


        	file_t* resourceFile = openFile( filePath.c_str(), CRAP_FILE_READ );

        	CRAP_ASSERT( ASSERT_BREAK, resourceFile != 0, "Resourcefile not found" );

        	pointer_t<void> memory = _allocator.allocate( resourceSize, 4 );

        	readFromFile( resourceFile, memory, resourceSize );
        	node->parent()->import( resourceId, memory, resourceSize, _system );

        	_allocator.deallocate( memory.as_void );
        	closeFile( resourceFile );
        }
    }
}

} //namespace crap
