
#include <iostream>
#include "system.h"
#include "logger.h"
#include "configuration.h"
#include "resourcemanager.h"
#include "audiomanager.h"
#include "pluginmanager.h"
#include "directorylistener.h"
#include "resourcefilter.h"

int main( void )
{
	//debug:: lets find the path
#ifdef CRAP_COMPILER_MSVC
	crap::string256 data_path("../../../data/");
#else
	crap::string256 data_path("../data/");
#endif

	//logger
    crap::logger< crap::log_time_time, crap::log_channel_core, crap::log_type_debug, crap::log_target_cout, 512 > unit_logger;

	//lets config
	crap::string256 ini_path = data_path + "configuration.ini";
	crap::Configuration config( 1024*10, 100 );

	config.load( ini_path.c_str() );

	//set config as subsystem
	crap::SubSystem config_sys( "Configuration", &config );

	//resourcemanager
	const uint32_t resoureMemory = config.getValue<uint32_t>("RESOURCE_MEMORY");
	const uint32_t resoureNumber = config.getValue<uint32_t>("RESOURCE_NUMBER");
	const crap::string64 resourceFile = config.getValue<crap::string64>("RESOURCE_FILE");
	const bool resourceXML = config.getValue<uint32_t>("RESOURCE_XML") == 1;

	crap::ResourceManager resourceManager( resoureMemory, resoureNumber, data_path );
	if( resourceXML )
		resourceManager.loadXML( resourceFile );
	else
		resourceManager.loadPackage( resourceFile );

	// set resourcemanager as subsystem
	crap::SubSystem resource_sys( "ResourceManager", &resourceManager );

	//audiomanager
	const uint32_t audioBufferNumber = config.getValue<uint32_t>("AUDIO_BUFFER_NUM");
	const uint32_t audioSourceNumber = config.getValue<uint32_t>("AUDIO_SOURCE_NUM");
	crap::AudioManager audioManager(audioBufferNumber, audioSourceNumber);

	//set audiomanager as subsystem
	crap::SubSystem audio_sys( "AudioManager", &audioManager );

	//pluginmanager
	const uint32_t pluginNumber = config.getValue<uint32_t>("PLUGIN_NUMBER");
	const uint32_t pluginMemory = config.getValue<uint32_t>("PLUGIN_MEMORY");
	crap::PluginManager pluginManager(pluginNumber, pluginMemory);

	//set pluginmanager as subsystem
	crap::SubSystem plugin_sys( "PluginManager", &pluginManager );

	//set Directory listener
	const uint32_t pluginFunctionNumber = config.getValue<uint32_t>("PLUGIN_FUNCTION_NUM");
	const uint32_t pluginFileNumber = config.getValue<uint32_t>("PLUGIN_FILES_NUM");
	const crap::string256 pluginDir = data_path + config.getValue<crap::string64>("PLUGIN_SUBDIRECTORY");
	crap::DirectoryListener pluginDirectoryListener( pluginFunctionNumber, pluginFileNumber, pluginDir, false );
	pluginDirectoryListener.addCallback<crap::PluginManager, &crap::PluginManager::callbackFunction>( &pluginManager );

	//init this.. (do that at last)
	pluginDirectoryListener.init();

	crap::Configuration* testconf = crap::CrapSystem.getSubSystem<crap::Configuration>( "Configuration" );
	if( testconf != 0 )
	{
		std::cout << "I've worked! " << testconf->getValue<crap::string64>("SOUND_VOLUME") << std::endl;
	}

	float32_t zero[3] = {0.f, 0.f, 0.f};
	float32_t one[3] = {1.f, 1.f, 1.f};
	float32_t dir[6] = {0.f, 0.f, 1.f, 0.f, 1.f, 0.f };

	crap::AudioManager* am = crap::CrapSystem.getSubSystem<crap::AudioManager>( "AudioManager" );

	resourceManager.loadResource( "Nagut" );
	uint32_t sid = am->leaseSource( "Nagut" );

	am->setListenerData( zero, zero, dir );
	am->playSource( sid );

	while( am->getIsPlaying(sid) )
		crap::sleep_mil_sec(100);

	return 0;
}
