
#include "resourcemanager.h"
#include "file.h"
#include "logger.h"
#include "xml/tinyxml2.h"

namespace crap
{

intrusive_list<ResourceFilter> ResourceFilterList;

ResourceManager::ResourceManager( uint32_t memory, uint32_t num_resources, const char* resource_path ) :
    _allocator( memory ),
    _resources( _allocator.allocate( sorted_array_map<ResourceName, ResourceInfo>::size_of_elements(num_resources), 4 ),
    		sorted_array_map<ResourceName, ResourceInfo>::size_of_elements(num_resources) ),
    _path( resource_path )
{
    const char lastletter = *(resource_path+strlen(resource_path)-1);
    if( lastletter != '/' )
        _path += ("/");

    crap::log( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "Resourcemanager with %i bytes memory, max. %i resources with path %s created", memory, num_resources, resource_path );
}

ResourceManager::~ResourceManager( void )
{
    for( uint32_t it = _resources.begin(); it != _resources.end(); it = _resources.next(it) )
    {
        if( _resources[it].memory.as_type != 0 )
            unloadFromMemory( it );
    }
    _allocator.deallocate( _resources.memory().as_void );
}

void ResourceManager::loadXML( const char* filename )
{
    crap::log( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "Loading XML Resourceinfo from file %s", filename );

    const string512 file_path = _path + filename;
    const uint32_t buffer_size = crap::fileSize( file_path.c_str() );
    file_t* handle = openFile( file_path.c_str() , CRAP_FILE_READ );

    CRAP_ASSERT( ASSERT_BREAK, handle != 0, "Could not open file %s", file_path.c_str() );

    pointer_t<void> buffer(_allocator.allocate(buffer_size, 4) );
    readFromFile( handle, buffer, buffer_size );

    tinyxml2::XMLDocument doc;
    doc.Parse( buffer.as_const_char, buffer_size );

    _allocator.deallocate( buffer.as_void );
    closeFile( handle );

    tinyxml2::XMLNode* xmlNode = doc.FirstChild();
    CRAP_ASSERT( ASSERT_BREAK, string64(xmlNode->Value()) == string64("RESOURCES"), "Wrong XML tag" );

    tinyxml2::XMLElement* element = xmlNode->FirstChildElement();
    while( element != 0 )
    {
        const string_hash       resource_type( element->Value() );
        const string_hash       resource_name( element->Attribute("name") );
        const string512         resource_path( _path + element->GetText() );
        const uint32_t          resource_size( fileSize( resource_path.c_str() ) );
        const uint32_t          resource_offs( 0 );
        const pointer_t<void>   resource_pntr( 0 );
        ResourceInfo      resource_info( resource_path, resource_offs, resource_type, resource_pntr, resource_size );
#ifndef CRAP_NO_DEBUG
        resource_info.name = element->Attribute("name");
        resource_info.type_name = element->Value();
        resource_info.file_name = element->GetText();
#endif

        crap::log( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "Resource \"%s\", type \"%s\", size %i bytes, path \"%s\"", element->Attribute("name"), element->Value(), resource_size, resource_path.c_str() );

        _resources.insert( resource_name, resource_info );

        element = element->NextSiblingElement();
    }
}

void ResourceManager::saveXML( const char* filename )
{
#ifndef CRAP_NO_DEBUG
    const string512 file_path = _path + filename;

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLNode* resources_node = doc.NewElement("RESOURCES");

    for( uint32_t it = _resources.begin(); it != _resources.end(); it = _resources.next(it) )
    {
        const string64  resource_name = _resources[it].name;
        const string64  resource_type = _resources[it].type_name;
        const string64  resource_path = _resources[it].file_name;

        tinyxml2::XMLElement* new_element = doc.NewElement(resource_type.c_str());
        new_element->SetAttribute("name", resource_name.c_str() );
        new_element->SetText(resource_path.c_str());

        resources_node->InsertEndChild( new_element );
    }
    doc.InsertEndChild(resources_node);

    file_t* handle = openFile( file_path.c_str() , CRAP_FILE_WRITE );
    doc.SaveFile( handle );
    closeFile(handle);

    crap::log( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "Saving XML Resourceinfo to file %s", filename );

#endif
}

void ResourceManager::loadPackage( const char* filename )
{
    crap::log( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "Loading Packed Resourceinfo from file %s", filename );

    const string512 file_path = _path + filename;
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
        const string512         resource_path( file_path );
        const uint32_t          resource_size( package_pointer.as_type->size );
        const uint32_t          resource_offs( offset + sizeof(PackageContentInfo) );
        const pointer_t<void>   resource_pntr( 0 );
        ResourceInfo      resource_info( resource_path, resource_offs, resource_type, resource_pntr, resource_size );

        crap::log( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "Resource \"%u\", type \"%u\", size %i bytes, path \"%s\"", resource_name.hash(), resource_type.hash(), resource_size, resource_path.c_str() );

        _resources.insert( resource_name, resource_info );

        offset += sizeof(PackageContentInfo) + resource_size;
        package_pointer.as_char += offset;
    }

    _allocator.deallocate(buffer.as_void);
}

void ResourceManager::savePackage( const char* filename )
{
    const string512 file_path = _path + filename;

    file_t* handle = openFile( file_path.c_str() , CRAP_FILE_WRITE );

    for( uint32_t it = _resources.begin(); it != _resources.end(); it = _resources.next(it) )
    {
        PackageContentInfo info;
        info.name = _resources.get_key(it)->hash();
        info.type = _resources[it].type.hash();
        info.size = _resources[it].size;

        loadToMemory( it );

        writeToFile( handle, &info, sizeof(PackageContentInfo) );
        writeToFile( handle, _resources[it].memory.as_void, info.size );

        unloadFromMemory( it );

    }

    closeFile(handle);

    crap::log( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "Saving Packed Resourceinfo to file %s", filename );
}


void ResourceManager::loadResources( const crap::array<string_hash>& items )
{
    for( uint32_t i= 0; i<items.size(); ++i )
    {
        uint32_t res_handle = _resources.find( items[i] );
        CRAP_ASSERT( ASSERT_BREAK, res_handle != ResourceMap::INVALID, "Resource not found!" );

        const ResourceType type = _resources[res_handle].type;
        const pointer_t<void> ptr = loadToMemory( res_handle );

        intrusive_node<ResourceFilter>* node = ResourceFilterList.begin();
        for( ; node != ResourceFilterList.end(); node = node->next() )
        {
            if( *(node->parent()) == type )
                node->parent()->use( items[i], ptr );
        }

        unloadFromMemory( res_handle );
    }
}

pointer_t<void> ResourceManager::loadToMemory( uint32_t handle )
{
    if( _resources[handle].memory.as_void == 0 )
    {
        const uint32_t resource_size = _resources[handle].size;
        const char*    resource_path = _resources[handle].path.c_str();

        _resources[handle].memory = _allocator.allocate( resource_size, 4 );
        file_t* file = openFile( resource_path, CRAP_FILE_READ );
        CRAP_ASSERT( ASSERT_BREAK, file != 0, "Resource not found in filesystem!" );
        readFromFile(file, _resources[handle].memory, resource_size );

        closeFile( file );
    }

    return _resources[handle].memory;
}

void ResourceManager::unloadFromMemory( uint32_t handle )
{
    if( _resources[handle].memory.as_void != 0 )
    {
        _allocator.deallocate( _resources[handle].memory.as_void );
        _resources[handle].memory = 0;
    }
}

void ResourceManager::importFile(const char* import_path, const char* type, const char* name )
{
    const string_hash name_hash( name );
    const string_hash type_hash( type );

    file_t* import_file = openFile( import_path, CRAP_FILE_READBINARY );
    CRAP_ASSERT( ASSERT_BREAK, import_file != 0, "Cannot open import file!" );

    const uint32_t import_size = fileSize( import_path );
    pointer_void import_memory = _allocator.allocate( import_size, 4 );
    readFromFile( import_file, import_memory, import_size );

    intrusive_node<ResourceFilter>* node = ResourceFilterList.begin();
    for( ; node != ResourceFilterList.end(); node = node->next() )
    {
        if( *(node->parent()) == type_hash )
        {
            const uint32_t export_size = node->parent()->calculateMemory( import_memory, import_size );
            pointer_void export_memory = _allocator.allocate( export_size, 4 );

            node->parent()->import( import_memory, export_memory, import_size );

            const string64  export_filename = node->parent()->exportFileName( PATH_TO_FILE(import_path) );
            const string512 export_path = _path + export_filename;
            file_t* export_file = openFile( export_path.c_str(), CRAP_FILE_WRITEBINARY );
            CRAP_ASSERT( ASSERT_BREAK, export_file != 0, "Cannot open export file!" );

            writeToFile( export_file, export_memory, export_size );

            const string_hash       resource_type( node->parent()->exportTypeName().c_str() );
            const string_hash       resource_name( name_hash );
            const string512         resource_path( export_path );
            const uint32_t          resource_size( export_size );
            const uint32_t          resource_offs( 0 );
            const pointer_t<void>   resource_pntr( 0 );
            ResourceInfo      resource_info( resource_path, resource_offs, resource_type, resource_pntr, resource_size );
    #ifndef CRAP_NO_DEBUG
            resource_info.name = name;
            resource_info.type_name = node->parent()->exportTypeName();
            resource_info.file_name = export_filename;
    #endif

            crap::log( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "Imported resource \"%s\", type \"%s\", size %i bytes, path \"%s\"", name, type, export_size, export_path.c_str() );

            _resources.insert( resource_name, resource_info );
            _allocator.deallocate( export_memory.as_void );
            closeFile( export_file );
        }
    }

    _allocator.deallocate( import_memory.as_void );
}

} //namespace crap
