/*!
 * @file converter.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 25, 2014
 */


/*


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

*/
