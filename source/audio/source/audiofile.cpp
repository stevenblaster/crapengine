
#include "audiofile.h"

namespace crap
{

WaveFile::WaveFile( pointer_t<void> raw_data )
{
    pointer_t<WaveHeader> pointer = raw_data;
    bool riff_check = pointer.as_char[0] == 'R' && pointer.as_char[1] == 'I' && pointer.as_char[2] == 'F' && pointer.as_char[3] == 'F';

    pointer_t<void> check = &(pointer.as_type->wave);

    bool wavefmt_check = check.as_char[0] == 'W' && check.as_char[1] == 'A' && check.as_char[2] == 'V' && check.as_char[3] == 'E' &&
            check.as_char[4] == 'f' && check.as_char[5] == 'm' && check.as_char[6] == 't' && check.as_char[7] == ' ';

    check = &(pointer.as_type->data);

    bool data_check = check.as_char[0] == 'd' && check.as_char[1] == 'a' && check.as_char[2] == 't' && check.as_char[3] == 'a';

    CRAP_ASSERT( ASSERT_BREAK, riff_check && wavefmt_check && data_check,  "Not a valid Wave-File");

    this->channels = pointer.as_type->channels;
    this->frequency = pointer.as_type->frequency;
    this->bits_per_sample = pointer.as_type->bits_per_sample;
    this->size = pointer.as_type->data_size;
    this->data = pointer.as_type += 1;
}

} //namespace crap
