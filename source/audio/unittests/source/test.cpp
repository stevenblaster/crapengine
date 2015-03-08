
//#include "test.h"
#include "audiodevice.h"
#include "audiobuffer.h"
#include "audiosource.h"
#include "audiocontrol.h"
#include "audiofile.h"
#include "file.h"
#include "AudioSystem.h"
//#include <AL/alut.h>

//#if defined (CRAP_COMPILER_VC)
//#pragma pack(1)
//#endif

int main( void )
{
    crap::AudioSystem manager(20, 20);

    uint32_t filesize = crap::fileSize("../../../data/yes.wav");
    crap::file_t* my_file = crap::openFile("../../../data/yes.wav", "r");
    crap::pointer_t<void> buffer( malloc(filesize) );
    crap::readFromFile( my_file, buffer, filesize );
    crap::closeFile( my_file );
    crap::WaveFile wavefile( buffer );
    manager.addBuffer( "Yes", wavefile );

    filesize = crap::fileSize("../../../data/nagut.wav");
    my_file = crap::openFile("../../../data/nagut.wav", "r");
    crap::pointer_t<void> buffer2( malloc(filesize) );
    crap::readFromFile( my_file, buffer2, filesize );
    crap::closeFile( my_file );
    crap::WaveFile wavefile2( buffer2 );
    manager.addBuffer( "Nagut", wavefile2 );


    uint32_t source_id = manager.leaseSource( "Yes" );
    uint32_t source_id2 = manager.leaseSource( "Nagut" );


    float32_t zero[3] = {0.f, 0.f, 0.f};
    float32_t one[3] = {1.f, 1.f, 1.f};
    float32_t dir[6] = {0.f, 0.f, 1.f, 0.f, 1.f, 0.f };

    manager.setListenerData( zero, zero, dir );

    manager.setSourceData( zero, zero,  source_id );
    manager.setSourceVolumes( source_id, 1.f, 1.f, false );

    manager.setSourceData( zero, zero,  source_id2 );
    manager.setSourceVolumes( source_id2, 1.f, 1.f, false );

    manager.playSource( source_id );

    crap::sleep_mil_sec(1000);

    manager.playSource( source_id2 );

    crap::sleep_mil_sec(1000);

    return 0;
}
