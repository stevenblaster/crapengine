#pragma once

#ifndef CRAP_CORE_RESOURCEMANAGER
#define CRAP_CORE_RESOURCEMANAGER

#include "memory.h"

#ifdef CRAP_NO_DEBUG
#define RESOURCE_MEMORY crap::SimpleGeneralMemory
#else
#define RESOURCE_MEMORY crap::BoundGeneralMemory
#endif

#include "container/sortedarraymap.h"
#include "resourcefilter.h"


namespace crap
{

class ResourceManager
{

public:

    ResourceManager( uint32_t bufferMemory, uint32_t resourceNumber, const string256& path );
    ~ResourceManager( void );

    void addContent( string_hash typeId, const string64& filename, uint32_t offset, uint32_t size );
    void loadXML( const string64& filename );
    void loadPackage( const string64& filename );
    void clearInfo( void );

    void loadResource( string_hash resourceId );

    struct ResourceInfo
    {
        uint32_t     	typeId;
        string64      	filename;
        uint32_t        offset;
        uint32_t        size;

        ResourceInfo( const string_hash& type, const string64& file, uint32_t off, uint32_t siz ) :
        	typeId(type.hash()), filename(file), offset(off), size(siz)
        {

        }
    };

    struct PackageContentInfo
    {
        uint32_t type;
        uint32_t name;
        uint32_t size;
    };

private:

    typedef crap::sorted_array_map<uint32_t, ResourceInfo> ResourceMap;

    RESOURCE_MEMORY                                     _allocator;

    ResourceMap                                         _resources;
    crap::string256                                     _path;
};

}

#endif //CRAP_CORE_RESOURCEMANAGER
