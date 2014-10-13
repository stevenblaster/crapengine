#include "UnitTest++.h"
#include "configuration.h"
#include "logger.h"


crap::Configuration* config;


TEST(CreateConfiguration)
{
    config = new crap::Configuration( 2048, 20 );
}

TEST(LoadConfiguration)
{
    config->load("../../../data/test.ini");
}

TEST(GetConfigValue)
{
    crap::string64 str = config->getValue<crap::string64>("SOUND_VOLUME");
    std::cout << str << std::endl;

    float32_t vol = config->getValue<float32_t>("SOUND_VOLUME");
    std::cout << vol << std::endl;
}

TEST(DestroyConfiguration)
{
    delete config;
}
