#pragma once

#ifndef CRAP_CORE_RESOURCEMANAGER
#define CRAP_CORE_RESOURCEMANAGER

#include "container/intrusivelist.h"
#include "container/map.h"
#include "memory.h"

#ifdef CRAP_NO_DEBUG
#define RESOURCE_MEMORY crap::SimpleGeneralMemory
#else
#define RESOURCE_MEMORY crap::BoundGeneralMemory
#endif

#include "strings.h"



namespace crap
{

class ResourceFilter;

extern intrusive_list<ResourceFilter> ResourceFilterList;

class ResourceFilter
{
public:
    CRAP_INLINE ResourceFilter( const string_hash& name ) : _node( this, &ResourceFilterList ), _name(name) {}
    virtual ~ResourceFilter( void ) {}

    virtual void use( const string_hash& name, pointer_t<void> data ) = 0;
    virtual void import( pointer_t<void> input_data, pointer_t<void> output_data, uint32_t size ) = 0;
    virtual uint32_t calculateMemory( pointer_t<void> input_data, uint32_t size ) = 0;
    virtual string64 exportFileName( string64 import_name ) = 0;
    virtual string64 exportTypeName( void ) = 0;

    CRAP_INLINE bool operator==( const string_hash& name )
    {
        return _name == name;
    }

protected:
    intrusive_node<ResourceFilter> _node;
    string_hash                 _name;
};

class ResourceManager
{

public:

    typedef crap::string_hash                                   ResourceType;
    typedef crap::string_hash                                   ResourceName;
    typedef crap::string512                                     ResourcePath;

    ResourceManager( uint32_t memory, uint32_t num_resources, const char* resource_path );
    ~ResourceManager( void );

    void loadXML( const char* filename );
    void saveXML( const char* filename );

    void importFile(const char* import_path, const char* type, const char* name );

    void loadPackage( const char* filename );
    void savePackage( const char* filename );

    struct ResourceInfo
    {
#ifndef CRAP_NO_DEBUG
        string64        name;
        string64        type_name;
        string64        file_name;
#endif
        string_hash     type;
        string512       path;
        uint32_t        offset;
        uint32_t        size;
        pointer_t<void> memory;

        ResourceInfo( const string512& pat, uint32_t off, const string_hash& typ, pointer_t<void> mem, uint32_t siz) : path(pat), offset(off), type(typ), memory(mem), size(siz)
        {

        }
    };

    struct PackageContentInfo
    {
        uint32_t type;
        uint32_t name;
        uint32_t size;
    };

    void loadResources( const crap::array<string_hash>& items );


private:

    typedef crap::sorted_map<ResourceName, ResourceInfo>        ResourceMap;

    pointer_t<void> loadToMemory( ResourceMap::handle handle );
    void unloadFromMemory( ResourceMap::handle handle );

    RESOURCE_MEMORY                                     _allocator;

    ResourceMap                                         _resources;
    crap::string512                                     _path;
};

}

#endif //CRAP_CORE_RESOURCEMANAGER
