#include "UnitTest++.h"
#include "resourcemanager.h"
#include "logger.h"

RESOURCE_MEMORY* rmm;
crap::ResourceManager* rm;

namespace
{

class FunFilter : public crap::ResourceFilter
{
public:
    FunFilter(const char* funname ) : crap::ResourceFilter( funname ), _name(funname)
    {

    }

    ~FunFilter( void ) {}

    void use( const crap::string_hash& name, crap::pointer_void ptr )
    {
        CRAP_DEBUG_LOG( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "My name is %s", _name.c_str());
    }

    void import(crap::pointer_t<void> input_data, crap::pointer_t<void> output_data, uint32_t size )
    {

    }

    uint32_t calculateMemory(crap::pointer_t<void> input_data, uint32_t import_memory)
    {
        return import_memory;
    }

    crap::string64 exportFileName(crap::string64 import_name)
    {
        uint32_t pos = import_name.search('.');
        import_name.cut(pos);
        import_name += ".fun";
        return import_name;
    }

    crap::string64 exportTypeName( void )
    {
        return "Music";
    }

private:
    crap::string64 _name;
};

TEST(ConstructRM)
{
    //crap::logger< crap::log_time_time, crap::log_channel_core, crap::log_type_info, crap::log_target_cout, 512 > logme;
    rm = new crap::ResourceManager( 1024*1024, 30, "../../../data" );
}

TEST(LoadXML)
{
    char filename[] = "resources.xml";
    rm->loadXML( filename );
}

TEST(SaveXML)
{
    char filename[] = "resources_test.xml";
    rm->saveXML( filename );
}

TEST(SavePackage)
{
    char filename[] = "package_test.pack";
    rm->savePackage( filename );
}

TEST(LoadPackage)
{
    char filename[] = "package_test.pack";
    rm->loadPackage( filename );
}

TEST(LoadFilter)
{
    FunFilter filter("Audio");
    void* mem = malloc(1024);
    crap::array<crap::string_hash> arr( mem, 1024);
    arr.push_back("Yes");
    rm->loadResources(arr);
    free(mem);

    rm->importFile("/home/steffen/Programming/crapengine2/data/yes.wav", "Audio", "Yessir");
}

TEST(DeleteRM)
{
    delete rm;
   // delete rmm;
}

}
