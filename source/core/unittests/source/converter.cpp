#include "UnitTest++.h"

//lib includes
#include "convert.h"
#include "logger.h"

namespace
{

TEST( AnnounceTestConverter )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"converter.h\"" );
}

TEST(ConverterC8C8)
{
    char test = 0;
    CHECK_EQUAL( 0, (crap::convert<char, char>( test )) );

	test = 25;
    CHECK_EQUAL( 25, (crap::convert<char, char>( test )) );

	test = -25;
    CHECK_EQUAL( -25, (crap::convert<char, char>( test )) );

	test = -128;
    CHECK_EQUAL( -128, (crap::convert<char, char>( test )) );

	test = 127;
    CHECK_EQUAL( 127, (crap::convert<char, char>( test )) );
}

TEST(ConverterC8I8)
{
        char test = 0;
        CHECK_EQUAL( 0, (crap::convert<char, int8_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<char, int8_t>( test )) );

        test = -25;
        CHECK_EQUAL( -25, (crap::convert<char, int8_t>( test )) );

        test = -128;
        CHECK_EQUAL( -128, (crap::convert<char, int8_t>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<char, int8_t>( test )) );
}

TEST(ConverterC8U8)
{
        char test = 0;
        CHECK_EQUAL( 0, (crap::convert<char, uint8_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<char, uint8_t>( test )) );

        test = -25;
        CHECK_EQUAL( 0, (crap::convert<char, uint8_t>( test )) );

        test = -128;
        CHECK_EQUAL( 0, (crap::convert<char, uint8_t>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<char, uint8_t>( test )) );
}

TEST(ConverterC8I16)
{
        char test = 0;
        CHECK_EQUAL( 0, (crap::convert<char, int16_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<char, int16_t>( test )) );

        test = -25;
        CHECK_EQUAL( -25, (crap::convert<char, int16_t>( test )) );

        test = -128;
        CHECK_EQUAL( -128, (crap::convert<char, int16_t>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<char, int16_t>( test )) );
}

TEST(ConverterC8U16)
{
        char test = 0;
        CHECK_EQUAL( 0, (crap::convert<char, uint16_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<char, uint16_t>( test )) );

        test = -25;
        CHECK_EQUAL( 0, (crap::convert<char, uint16_t>( test )) );

        test = -128;
        CHECK_EQUAL( 0, (crap::convert<char, uint16_t>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<char, uint16_t>( test )) );
}

TEST(ConverterC8I32)
{
        char test = 0;
        CHECK_EQUAL( 0, (crap::convert<char, int32_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<char, int32_t>( test )) );

        test = -25;
        CHECK_EQUAL( -25, (crap::convert<char, int32_t>( test )) );

        test = -128;
        CHECK_EQUAL( -128, (crap::convert<char, int32_t>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<char, int32_t>( test )) );
}

TEST(ConverterC8U32)
{
        char test = 0;
        CHECK_EQUAL( (uint32_t)0, (crap::convert<char, uint32_t>( test )) );

        test = 25;
        CHECK_EQUAL( (uint32_t)25, (crap::convert<char, uint32_t>( test )) );

        test = -25;
        CHECK_EQUAL( (uint32_t)0, (crap::convert<char, uint32_t>( test )) );

        test = -128;
        CHECK_EQUAL( (uint32_t)0, (crap::convert<char, uint32_t>( test )) );

        test = 127;
        CHECK_EQUAL( (uint32_t)127, (crap::convert<char, uint32_t>( test )) );
}

TEST(ConverterC8I64)
{
        char test = 0;
        CHECK_EQUAL( 0, (crap::convert<char, int64_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<char, int64_t>( test )) );

        test = -25;
        CHECK_EQUAL( -25, (crap::convert<char, int64_t>( test )) );

        test = -128;
        CHECK_EQUAL( -128, (crap::convert<char, int64_t>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<char, int64_t>( test )) );
}

TEST(ConverterC8U64)
{
        char test = 0;
        CHECK_EQUAL( (uint64_t)0, (crap::convert<char, uint64_t>( test )) );

        test = 25;
        CHECK_EQUAL( (uint64_t)25, (crap::convert<char, uint64_t>( test )) );

        test = -25;
        CHECK_EQUAL( (uint64_t)0, (crap::convert<char, uint64_t>( -25 )) );

        test = -128;
        CHECK_EQUAL( (uint64_t)0, (crap::convert<char, uint64_t>( test )) );

        test = 127;
        CHECK_EQUAL( (uint64_t)127, (crap::convert<char, uint64_t>( test )) );
}

TEST(ConverterC8F32)
{
        char test = 0;
        CHECK_EQUAL( 0.0f, (crap::convert<char, float32_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25.0f, (crap::convert<char, float32_t>( test )) );

        test = -25;
        CHECK_EQUAL( -25.0f, (crap::convert<char, float32_t>( test )) );

        test = -128;
        CHECK_EQUAL( -128.0f, (crap::convert<char, float32_t>( test )) );

        test = 127;
        CHECK_EQUAL( 127.0f, (crap::convert<char, float32_t>( test )) );
}

TEST(ConverterC8F64)
{
        char test = 0;
        CHECK_EQUAL( 0.0, (crap::convert<char, float64_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25.0, (crap::convert<char, float64_t>( test )) );

        test = -25;
        CHECK_EQUAL( -25.0, (crap::convert<char, float64_t>( test )) );

        test = -128;
        CHECK_EQUAL( -128.0, (crap::convert<char, float64_t>( test )) );

        test = 127;
        CHECK_EQUAL( 127.0, (crap::convert<char, uint64_t>( test )) );
}

//I8
TEST(ConverterI8C8)
{
        int8_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int8_t, char>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<int8_t, char>( test )) );

        test = -25;
        CHECK_EQUAL( -25, (crap::convert<int8_t, char>( test )) );

        test = -128;
        CHECK_EQUAL( -128, (crap::convert<int8_t, char>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<int8_t, char>( test )) );
}

TEST(ConverterI8I8)
{
        int8_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int8_t, int8_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<int8_t, int8_t>( test )) );

        test = -25;
        CHECK_EQUAL( -25, (crap::convert<int8_t, int8_t>( test )) );

        test = -128;
        CHECK_EQUAL( -128, (crap::convert<int8_t, int8_t>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<int8_t, int8_t>( test )) );
}

TEST(ConverterI8U8)
{
        int8_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int8_t, uint8_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<int8_t, uint8_t>( test )) );

        test = -25;
        CHECK_EQUAL( 0, (crap::convert<int8_t, uint8_t>( test )) );

        test = -128;
        CHECK_EQUAL( 0, (crap::convert<int8_t, uint8_t>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<int8_t, uint8_t>( test )) );
}

TEST(ConverterI8I16)
{
        int8_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int8_t, int16_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<int8_t, int16_t>( test )) );

        test = -25;
        CHECK_EQUAL( -25, (crap::convert<int8_t, int16_t>( test )) );

        test = -128;
        CHECK_EQUAL( -128, (crap::convert<int8_t, int16_t>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<int8_t, int16_t>( test )) );
}

TEST(ConverterI8U16)
{
        int8_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int8_t, uint16_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<int8_t, uint16_t>( test )) );

        test = -25;
        CHECK_EQUAL( 0, (crap::convert<int8_t, uint16_t>( test )) );

        test = -128;
        CHECK_EQUAL( 0, (crap::convert<int8_t, uint16_t>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<int8_t, uint16_t>( test )) );
}

TEST(ConverterI8I32)
{
        int8_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int8_t, int32_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<int8_t, int32_t>( test )) );

        test = -25;
        CHECK_EQUAL( -25, (crap::convert<int8_t, int32_t>( test )) );

        test = -128;
        CHECK_EQUAL( -128, (crap::convert<int8_t, int32_t>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<int8_t, int32_t>( test )) );
}

TEST(ConverterI8U32)
{
        int8_t test = 0;
        CHECK_EQUAL( (uint32_t)0, (crap::convert<int8_t, uint32_t>( test )) );

        test = 25;
        CHECK_EQUAL( (uint32_t)25, (crap::convert<int8_t, uint32_t>( test )) );

        test = -25;
        CHECK_EQUAL( (uint32_t)0, (crap::convert<int8_t, uint32_t>( test )) );

        test = -128;
        CHECK_EQUAL( (uint32_t)0, (crap::convert<int8_t, uint32_t>( test )) );

        test = 127;
        CHECK_EQUAL( (uint32_t)127, (crap::convert<int8_t, uint32_t>( test )) );
}

TEST(ConverterI8I64)
{
        int8_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int8_t, int64_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<int8_t, int64_t>( test )) );

        test = -25;
        CHECK_EQUAL( -25, (crap::convert<int8_t, int64_t>( test )) );

        test = -128;
        CHECK_EQUAL( -128, (crap::convert<int8_t, int64_t>( test )) );

        test = 127;
        CHECK_EQUAL( 127, (crap::convert<int8_t, int64_t>( test )) );
}

TEST(ConverterI8U64)
{
        int8_t test = 0;
        CHECK_EQUAL( (uint64_t)0, (crap::convert<int8_t, uint64_t>( test )) );

        test = 25;
        CHECK_EQUAL( (uint64_t)25, (crap::convert<int8_t, uint64_t>( test )) );

        test = -25;
        CHECK_EQUAL( (uint64_t)0, (crap::convert<int8_t, uint64_t>( test )) );

        test = -128;
        CHECK_EQUAL( (uint64_t)0, (crap::convert<int8_t, uint64_t>( test )) );

        test = 127;
        CHECK_EQUAL( (uint64_t)127, (crap::convert<int8_t, uint64_t>( test )) );
}

TEST(ConverterI8F32)
{
        int8_t test = 0;
        CHECK_EQUAL( 0.0f, (crap::convert<int8_t, float32_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25.0f, (crap::convert<int8_t, float32_t>( test )) );

        test = -25;
        CHECK_EQUAL( -25.0f, (crap::convert<int8_t, float32_t>( test )) );

        test = -128;
        CHECK_EQUAL( -128.0f, (crap::convert<int8_t, float32_t>( test )) );

        test = 127;
        CHECK_EQUAL( 127.0f, (crap::convert<int8_t, float32_t>( test )) );
}

TEST(ConverterI8F64)
{
        int8_t test = 0;
        CHECK_EQUAL( 0.0, (crap::convert<int8_t, float64_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25.0, (crap::convert<int8_t, float64_t>( test )) );

        test = -25;
        CHECK_EQUAL( -25.0, (crap::convert<int8_t, float64_t>( test )) );

        test = -128;
        CHECK_EQUAL( -128.0, (crap::convert<int8_t, float64_t>( test )) );

        test = 127;
        CHECK_EQUAL( 127.0, (crap::convert<int8_t, uint64_t>( test )) );
}

//uint8_t
TEST(ConverterU8C8)
{
        uint8_t test = 0;
        CHECK_EQUAL( (int32_t)0, (int32_t)(crap::convert<uint8_t, char>( test )) );

        test = 25;
        CHECK_EQUAL( (int32_t)25, (int32_t)(crap::convert<uint8_t, char>( test )) );

        test = 255;
        CHECK_EQUAL( (int32_t)127, (int32_t)(crap::convert<uint8_t, char>( test )) );
}

TEST(ConverterU8I8)
{
        uint8_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<uint8_t, int8_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<uint8_t, int8_t>( test )) );

        test = 255;
        CHECK_EQUAL( 127, (crap::convert<uint8_t, int8_t>( test )) );
}

TEST(ConverterU8U8)
{
        uint8_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<uint8_t, uint8_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<uint8_t, uint8_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<uint8_t, uint8_t>( test )) );
}

TEST(ConverterU8I16)
{
        uint8_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<uint8_t, int16_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<uint8_t, int16_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<uint8_t, int16_t>( test )) );
}

TEST(ConverterU8U16)
{
        uint8_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<uint8_t, uint16_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<uint8_t, uint16_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<uint8_t, uint16_t>( test )) );
}

TEST(ConverterU8I32)
{
        uint8_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<uint8_t, int32_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<uint8_t, int32_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<uint8_t, int32_t>( test )) );
}

TEST(ConverterU8U32)
{
        uint8_t test = 0;
        CHECK_EQUAL( (uint32_t)0, (crap::convert<uint8_t, uint32_t>( test )) );

        test = 25;
        CHECK_EQUAL( (uint32_t)25, (crap::convert<uint8_t, uint32_t>( test )) );

        test = 255;
        CHECK_EQUAL( (uint32_t)255, (crap::convert<uint8_t, uint32_t>( test )) );
}

TEST(ConverterU8I64)
{
        uint8_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<uint8_t, int64_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25, (crap::convert<uint8_t, int64_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<uint8_t, int64_t>( test )) );
}

TEST(ConverterU8U64)
{
        uint8_t test = 0;
        CHECK_EQUAL( (uint64_t)0, (crap::convert<uint8_t, uint64_t>( test )) );

        test = 25;
        CHECK_EQUAL( (uint64_t)25, (crap::convert<uint8_t, uint64_t>( test )) );

        test = 255;
        CHECK_EQUAL( (uint64_t)255, (crap::convert<uint8_t, uint64_t>( test )) );
}

TEST(ConverterU8F32)
{
        uint8_t test = 0;
        CHECK_EQUAL( 0.0f, (crap::convert<uint8_t, float32_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25.0f, (crap::convert<uint8_t, float32_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255.0f, (crap::convert<uint8_t, float32_t>( test )) );
}

TEST(ConverterU8F64)
{
        uint8_t test = 0;
        CHECK_EQUAL( 0.0, (crap::convert<uint8_t, float64_t>( test )) );

        test = 25;
        CHECK_EQUAL( 25.0, (crap::convert<uint8_t, float64_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255.0, (crap::convert<uint8_t, uint64_t>( test )) );
}

//int16_t
TEST(ConverterI16C8)
{
        int16_t test = 0;
        CHECK_EQUAL( (int32_t)0, (int32_t)(crap::convert<int16_t, char>( test )) );

        test = 255;
        CHECK_EQUAL( (int32_t)127, (int32_t)(crap::convert<int16_t, char>( test )) );

        test = -255;
        CHECK_EQUAL( (int32_t)-128, (int32_t)(crap::convert<int16_t, char>( test )) );

        test = crap::limits<int16_t>::MAX;
        CHECK_EQUAL( (int32_t)127, (int32_t)(crap::convert<int16_t, char>( test )) );

        test = crap::limits<int16_t>::MIN;
        CHECK_EQUAL( (int32_t)-128, (int32_t)(crap::convert<int16_t, char>( test )) );
}

TEST(ConverterI16I8)
{
        int16_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int16_t, int8_t>( test )) );

        test = 255;
        CHECK_EQUAL( 127, (crap::convert<int16_t, int8_t>( test )) );

        test = -255;
        CHECK_EQUAL( -128, (crap::convert<int16_t, int8_t>( test )) );

        test = crap::limits<int16_t>::MAX;
        CHECK_EQUAL( 127, (crap::convert<int16_t, int8_t>( test )) );

        test = crap::limits<int16_t>::MIN;
        CHECK_EQUAL( -128, (crap::convert<int16_t, int8_t>( test )) );
}

TEST(ConverterI16U8)
{
        int16_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int16_t, uint8_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<int16_t, uint8_t>( test )) );

        test = -255;
        CHECK_EQUAL( 0, (crap::convert<int16_t, uint8_t>( test )) );

        test = crap::limits<int16_t>::MAX;
        CHECK_EQUAL( 255, (crap::convert<int16_t, uint8_t>( test )) );

        test = crap::limits<int16_t>::MIN;
        CHECK_EQUAL( 0, (crap::convert<int16_t, uint8_t>( test )) );
}

TEST(ConverterI16I16)
{
        int16_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int16_t, int16_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<int16_t, int16_t>( test )) );

        test = -255;
        CHECK_EQUAL( -255, (crap::convert<int16_t, int16_t>( test )) );

        test = crap::limits<int16_t>::MAX;
        CHECK_EQUAL( crap::limits<int16_t>::MAX, (crap::convert<int16_t, int16_t>( test )) );

        test = crap::limits<int16_t>::MIN;
        CHECK_EQUAL( crap::limits<int16_t>::MIN, (crap::convert<int16_t, int16_t>( test )) );
}

TEST(ConverterI16U16)
{
        int16_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int16_t, uint16_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<int16_t, uint16_t>( test )) );

        test = -255;
        CHECK_EQUAL( 0, (crap::convert<int16_t, uint16_t>( test )) );

        test = crap::limits<int16_t>::MAX;
        CHECK_EQUAL( crap::limits<int16_t>::MAX, (crap::convert<int16_t, uint16_t>( test )) );

        test = crap::limits<int16_t>::MIN;
        CHECK_EQUAL( 0, (crap::convert<int16_t, uint16_t>( test )) );
}

TEST(ConverterI16I32)
{
        int16_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int16_t, int32_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<int16_t, int32_t>( test )) );

        test = -255;
        CHECK_EQUAL( -255, (crap::convert<int16_t, int32_t>( test )) );

        test = crap::limits<int16_t>::MAX;
        CHECK_EQUAL( crap::limits<int16_t>::MAX, (crap::convert<int16_t, int32_t>( test )) );

        test = crap::limits<int16_t>::MIN;
        CHECK_EQUAL( crap::limits<int16_t>::MIN, (crap::convert<int16_t, int32_t>( test )) );
}

TEST(ConverterI16U32)
{
        int16_t test = 0;
        CHECK_EQUAL( (uint32_t)0, (crap::convert<int16_t, uint32_t>( test )) );

        test = 255;
        CHECK_EQUAL( (uint32_t)255, (crap::convert<int16_t, uint32_t>( test )) );

        test = -255;
        CHECK_EQUAL( (uint32_t)0, (crap::convert<int16_t, uint32_t>( test )) );

        test = crap::limits<int16_t>::MAX;
        CHECK_EQUAL( (uint32_t)crap::limits<int16_t>::MAX, (crap::convert<int16_t, uint32_t>( test )) );

        test = crap::limits<int16_t>::MIN;
        CHECK_EQUAL( (uint32_t)0, (crap::convert<int16_t, uint32_t>( test )) );
}

TEST(ConverterI16I64)
{
        int16_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int16_t, int64_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<int16_t, int64_t>( test )) );

        test = -255;
        CHECK_EQUAL( -255, (crap::convert<int16_t, int64_t>( test )) );

        test = crap::limits<int16_t>::MAX;
        CHECK_EQUAL( crap::limits<int16_t>::MAX, (crap::convert<int16_t, int64_t>( test )) );

        test = crap::limits<int16_t>::MIN;
        CHECK_EQUAL( crap::limits<int16_t>::MIN, (crap::convert<int16_t, int64_t>( test )) );
}

TEST(ConverterI16U64)
{
        int16_t test = 0;
        CHECK_EQUAL( (uint64_t)0, (crap::convert<int16_t, uint64_t>( test )) );

        test = 255;
        CHECK_EQUAL( (uint64_t)255, (crap::convert<int16_t, uint64_t>( test )) );

        test = -255;
        CHECK_EQUAL( (uint64_t)0, (crap::convert<int16_t, uint64_t>( test )) );

        test = crap::limits<int16_t>::MAX;
        CHECK_EQUAL( (uint64_t)crap::limits<int16_t>::MAX, (crap::convert<int16_t, uint64_t>( test )) );

        test = crap::limits<int16_t>::MIN;
        CHECK_EQUAL( (uint64_t)0, (crap::convert<int16_t, uint64_t>( test )) );
}

TEST(ConverterI16F32)
{
        int16_t test = 0;
        CHECK_EQUAL( 0.0f, (crap::convert<int16_t, float32_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255.0f, (crap::convert<int16_t, float32_t>( test )) );

        test = -255;
        CHECK_EQUAL( -255.0f, (crap::convert<int16_t, float32_t>( test )) );

        test = crap::limits<int16_t>::MAX;
        CHECK_EQUAL( crap::limits<int16_t>::MAX, (crap::convert<int16_t, float32_t>( test )) );

        test = crap::limits<int16_t>::MIN;
        CHECK_EQUAL( crap::limits<int16_t>::MIN, (crap::convert<int16_t, float32_t>( test )) );
}

TEST(Converterint16_tF64)
{
        int16_t test = 0;
        CHECK_EQUAL( 0.0, (crap::convert<int16_t, float64_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255.0, (crap::convert<int16_t, float64_t>( test )) );

        test = -255;
        CHECK_EQUAL( -255.0, (crap::convert<int16_t, float64_t>( test )) );

        test = crap::limits<int16_t>::MAX;
        CHECK_EQUAL( crap::limits<int16_t>::MAX, (crap::convert<int16_t, float64_t>( test )) );

        test = crap::limits<int16_t>::MIN;
        CHECK_EQUAL( crap::limits<int16_t>::MIN, (crap::convert<int16_t, float64_t>( test )) );
}

//U16
TEST(ConverterU16C8)
{
        uint16_t test = 255;
        CHECK_EQUAL( (int32_t)127, (int32_t)(crap::convert<uint16_t, char>( test )) );

        test = crap::limits<uint16_t>::MAX;
        CHECK_EQUAL( (int32_t)127, (int32_t)(crap::convert<uint16_t, char>( test )) );

        test = crap::limits<uint16_t>::MIN;
        CHECK_EQUAL( (int32_t)0, (int32_t)(crap::convert<uint16_t, char>( test )) );
}

TEST(ConverterU16I8)
{
        uint16_t test = 255;
        CHECK_EQUAL( (int32_t)127, (int32_t)(crap::convert<uint16_t, int8_t>( test )) );

        test = crap::limits<uint16_t>::MAX;
        CHECK_EQUAL( (int32_t)127, (int32_t)(crap::convert<uint16_t, int8_t>( test )) );

        test = crap::limits<uint16_t>::MIN;
        CHECK_EQUAL( (int32_t)0, (int32_t)(crap::convert<uint16_t, int8_t>( test )) );
}

TEST(ConverterU16U8)
{
        uint16_t test = 255;
        CHECK_EQUAL( 255, (crap::convert<uint16_t, uint8_t>( test )) );

        test = crap::limits<uint16_t>::MAX;
        CHECK_EQUAL( 255, (crap::convert<uint16_t, uint8_t>( test )) );

        test = crap::limits<uint16_t>::MIN;
        CHECK_EQUAL( 0, (crap::convert<uint16_t, uint8_t>( test )) );
}

TEST(ConverterU16I16)
{
        uint16_t test = 255;
        CHECK_EQUAL( 255, (crap::convert<uint16_t, int16_t>( test )) );

        test = crap::limits<uint16_t>::MAX;
        CHECK_EQUAL( crap::limits<int16_t>::MAX, (crap::convert<uint16_t, int16_t>( test )) );

        test = crap::limits<uint16_t>::MIN;
        CHECK_EQUAL( 0, (crap::convert<uint16_t, int16_t>( test )) );
}

TEST(ConverterU16U16)
{
        uint16_t test = 255;
        CHECK_EQUAL( 255, (crap::convert<uint16_t, uint16_t>( test )) );

        test = crap::limits<uint16_t>::MIN;
        CHECK_EQUAL( crap::limits<uint16_t>::MIN, (crap::convert<uint16_t, uint16_t>( test )) );

        test = crap::limits<uint16_t>::MIN;
        CHECK_EQUAL( 0, (crap::convert<uint16_t, uint16_t>( test )) );
}

TEST(ConverterU16I32)
{
        uint16_t test = 255;
        CHECK_EQUAL( 255, (crap::convert<uint16_t, int32_t>( test )) );

        test = crap::limits<uint16_t>::MIN;
        CHECK_EQUAL( crap::limits<uint16_t>::MIN, (crap::convert<uint16_t, int32_t>( test )) );

        test = crap::limits<uint16_t>::MIN;
        CHECK_EQUAL( crap::limits<uint16_t>::MIN, (crap::convert<uint16_t, int32_t>( test )) );
}

TEST(ConverterU16U32)
{
        uint16_t test = 255;
        CHECK_EQUAL( (uint32_t)255, (crap::convert<uint16_t, uint32_t>( test )) );

        test = crap::limits<uint16_t>::MIN;
        CHECK_EQUAL( (uint32_t)crap::limits<uint16_t>::MIN, (crap::convert<uint16_t, uint32_t>( test )) );

        test = crap::limits<uint16_t>::MIN;
        CHECK_EQUAL( (uint32_t)0, (crap::convert<uint16_t, uint32_t>( test )) );
}

TEST(ConverterU16I64)
{
        uint16_t test = 255;
        CHECK_EQUAL( 255, (crap::convert<uint16_t, int64_t>( test )) );

        test = crap::limits<uint16_t>::MIN;
        CHECK_EQUAL( crap::limits<uint16_t>::MIN, (crap::convert<uint16_t, int64_t>( test )) );

        test = crap::limits<uint16_t>::MIN;
        CHECK_EQUAL( crap::limits<uint16_t>::MIN, (crap::convert<uint16_t, int64_t>( test )) );
}

TEST(ConverterU16U64)
{
        uint16_t test = 255;
        CHECK_EQUAL( (uint64_t)255, (crap::convert<uint16_t, uint64_t>( test )) );

        test = crap::limits<uint16_t>::MIN;
        CHECK_EQUAL( (uint64_t)crap::limits<uint16_t>::MIN, (crap::convert<uint16_t, uint64_t>( test )) );

        test = crap::limits<uint16_t>::MIN;
        CHECK_EQUAL( (uint64_t)0, (crap::convert<uint16_t, uint64_t>( test )) );
}

TEST(ConverterU16F32)
{
        uint16_t test = 255;
        CHECK_EQUAL( 255.0f, (crap::convert<uint16_t, float32_t>( test )) );

        test = crap::limits<uint16_t>::MAX;
        CHECK_EQUAL( 65535.0f, (crap::convert<uint16_t, float32_t>( test )) );

        test = crap::limits<uint16_t>::MIN;
        CHECK_EQUAL( 0.f, (crap::convert<uint16_t, float32_t>( test )) );
}

TEST(ConverterU16F64)
{
        uint16_t test = 255;
        CHECK_EQUAL( 255.0, (crap::convert<uint16_t, float64_t>( test )) );

        test = crap::limits<uint16_t>::MAX;
        CHECK_EQUAL( crap::limits<uint16_t>::MAX, (crap::convert<uint16_t, float64_t>( test )) );

        test = crap::limits<uint16_t>::MIN;
        CHECK_EQUAL( crap::limits<uint16_t>::MIN, (crap::convert<uint16_t, float64_t>( test )) );
}


//int32_t
TEST(ConverterI32C8)
{
        int32_t test = 0;
        CHECK_EQUAL( (int32_t)0, (int32_t)(crap::convert<int32_t, char>( test )) );

        test = 255;
        CHECK_EQUAL( (int32_t)127, (int32_t)(crap::convert<int32_t, char>( test )) );

        test = -255;
        CHECK_EQUAL( (int32_t)-128, (int32_t)(crap::convert<int32_t, char>( test )) );

        test = crap::limits<int32_t>::MAX;
        CHECK_EQUAL( (int32_t)127, (int32_t)(crap::convert<int32_t, char>( test )) );

        test = crap::limits<int32_t>::MIN;
        CHECK_EQUAL( (int32_t)-128, (int32_t)(crap::convert<int32_t, char>( test )) );
}

TEST(ConverterI32I8)
{
        int32_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int32_t, int8_t>( test )) );

        test = 255;
        CHECK_EQUAL( 127, (crap::convert<int32_t, int8_t>( test )) );

        test = -255;
        CHECK_EQUAL( -128, (crap::convert<int32_t, int8_t>( test )) );

        test = crap::limits<int32_t>::MAX;
        CHECK_EQUAL( 127, (crap::convert<int32_t, int8_t>( test )) );

        test = crap::limits<int32_t>::MIN;
        CHECK_EQUAL( -128, (crap::convert<int32_t, int8_t>( test )) );
}

TEST(ConverterI32U8)
{
        int32_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int32_t, uint8_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<int32_t, uint8_t>( test )) );

        test = -255;
        CHECK_EQUAL( 0, (crap::convert<int32_t, uint8_t>( test )) );

        test = crap::limits<int32_t>::MAX;
        CHECK_EQUAL( 255, (crap::convert<int32_t, uint8_t>( test )) );

        test = crap::limits<int32_t>::MIN;
        CHECK_EQUAL( 0, (crap::convert<int32_t, uint8_t>( test )) );
}

TEST(ConverterI32I16)
{
        int32_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int32_t, int16_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<int32_t, int16_t>( test )) );

        test = -255;
        CHECK_EQUAL( -255, (crap::convert<int32_t, int16_t>( test )) );

        test = crap::limits<int32_t>::MAX;
        CHECK_EQUAL( crap::limits<int16_t>::MAX, (crap::convert<int32_t, int16_t>( test )) );

        test = crap::limits<int32_t>::MIN;
        CHECK_EQUAL( crap::limits<int16_t>::MIN, (crap::convert<int32_t, int16_t>( test )) );
}

TEST(ConverterI32U16)
{
        int32_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int32_t, uint16_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<int32_t, uint16_t>( test )) );

        test = -255;
        CHECK_EQUAL( 0, (crap::convert<int32_t, uint16_t>( test )) );

        test = crap::limits<int32_t>::MAX;
        CHECK_EQUAL( crap::limits<uint16_t>::MAX, (crap::convert<int32_t, uint16_t>( test )) );

        test = crap::limits<int32_t>::MIN;
        CHECK_EQUAL( 0, (crap::convert<int32_t, uint16_t>( test )) );
}

TEST(ConverterI32I32)
{
        int32_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int32_t, int32_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<int32_t, int32_t>( test )) );

        test = -255;
        CHECK_EQUAL( -255, (crap::convert<int32_t, int32_t>( test )) );

        test = crap::limits<int32_t>::MAX;
        CHECK_EQUAL( crap::limits<int32_t>::MAX, (crap::convert<int32_t, int32_t>( test )) );

        test = crap::limits<int32_t>::MIN;
        CHECK_EQUAL( crap::limits<int32_t>::MIN, (crap::convert<int32_t, int32_t>( test )) );
}

TEST(ConverterI32U32)
{
        int32_t test = 0;
        CHECK_EQUAL( (uint32_t)0, (crap::convert<int32_t, uint32_t>( test )) );

        test = 255;
        CHECK_EQUAL( (uint32_t)255, (crap::convert<int32_t, uint32_t>( test )) );

        test = -255;
        CHECK_EQUAL( (uint32_t)0, (crap::convert<int32_t, uint32_t>( test )) );

        test = crap::limits<int32_t>::MAX;
        CHECK_EQUAL( (uint32_t)crap::limits<int32_t>::MAX, (crap::convert<int32_t, uint32_t>( test )) );

        test = crap::limits<int32_t>::MIN;
        CHECK_EQUAL( (uint32_t)0, (crap::convert<int32_t, uint32_t>( test )) );
}

TEST(ConverterI32I64)
{
        int32_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int32_t, int64_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<int32_t, int64_t>( test )) );

        test = -255;
        CHECK_EQUAL( -255, (crap::convert<int32_t, int64_t>( test )) );

        test = crap::limits<int32_t>::MAX;
        CHECK_EQUAL( crap::limits<int32_t>::MAX, (crap::convert<int32_t, int64_t>( test )) );

        test = crap::limits<int32_t>::MIN;
        CHECK_EQUAL( crap::limits<int32_t>::MIN, (crap::convert<int32_t, int64_t>( test )) );
}

TEST(ConverterI32U64)
{
        int32_t test = 0;
        CHECK_EQUAL( (uint64_t)0, (crap::convert<int32_t, uint64_t>( test )) );

        test = 255;
        CHECK_EQUAL( (uint64_t)255, (crap::convert<int32_t, uint64_t>( test )) );

        test = -255;
        CHECK_EQUAL( (uint64_t)0, (crap::convert<int32_t, uint64_t>( test )) );

        test = crap::limits<int32_t>::MAX;
        CHECK_EQUAL( (uint64_t)crap::limits<int32_t>::MAX, (crap::convert<int32_t, uint64_t>( test )) );

        test = crap::limits<int32_t>::MIN;
        CHECK_EQUAL( (uint64_t)0, (crap::convert<int32_t, uint64_t>( test )) );
}

TEST(ConverterI32F32)
{
        int32_t test = 0;
        CHECK_EQUAL( 0.0f, (crap::convert<int32_t, float32_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255.0f, (crap::convert<int32_t, float32_t>( test )) );

        test = -255;
        CHECK_EQUAL( -255.0f, (crap::convert<int32_t, float32_t>( test )) );

        test = crap::limits<int32_t>::MAX;
        CHECK_EQUAL( static_cast<float32_t>(crap::limits<int32_t>::MAX),(crap::convert<int32_t, float32_t>( test )) );

        test = crap::limits<int32_t>::MIN;
        CHECK_EQUAL( crap::limits<int32_t>::MIN, (crap::convert<int32_t, float32_t>( test )) );
}

TEST(ConverterI32F64)
{
        int32_t test = 0;
        CHECK_EQUAL( 0.0, (crap::convert<int32_t, float64_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255.0, (crap::convert<int32_t, float64_t>( test )) );

        test = -255;
        CHECK_EQUAL( -255.0, (crap::convert<int32_t, float64_t>( test )) );

        test = crap::limits<int32_t>::MAX;
        CHECK_EQUAL( (float64_t)crap::limits<int32_t>::MAX, (crap::convert<int32_t, float64_t>( test )) );

        test = crap::limits<int32_t>::MIN;
        CHECK_EQUAL( (float64_t)crap::limits<int32_t>::MIN, (crap::convert<int32_t, float64_t>( test )) );
}


//U32
TEST(ConverterU32C8)
{
        uint32_t test = 255;
        CHECK_EQUAL( (int32_t)127, (int32_t)(crap::convert<uint32_t, char>( test )) );

        test = crap::limits<uint32_t>::MAX;
        CHECK_EQUAL( (int32_t)127, (int32_t)(crap::convert<uint32_t, char>( test )) );

        test = crap::limits<uint32_t>::MIN;
        CHECK_EQUAL( (int32_t)0, (int32_t)(crap::convert<uint32_t, char>( test )) );
}

TEST(ConverterU32I8)
{
        uint32_t test = 255;
        CHECK_EQUAL( (int32_t)127, (int32_t)(crap::convert<uint32_t, int8_t>( test )) );

        test = crap::limits<uint32_t>::MAX;
        CHECK_EQUAL( (int32_t)127, (int32_t)(crap::convert<uint32_t, int8_t>( test )) );

        test = crap::limits<uint32_t>::MIN;
        CHECK_EQUAL( (int32_t)0, (int32_t)(crap::convert<uint32_t, int8_t>( test )) );
}

TEST(ConverterU32U8)
{
        uint32_t test = 255;
        CHECK_EQUAL( 255, (crap::convert<uint32_t, uint8_t>( test )) );

        test = crap::limits<uint32_t>::MAX;
        CHECK_EQUAL( 255, (crap::convert<uint32_t, uint8_t>( test )) );

        test = crap::limits<uint32_t>::MIN;
        CHECK_EQUAL( 0, (crap::convert<uint32_t, uint8_t>( test )) );
}

TEST(ConverterU32I16)
{
        uint32_t test = 255;
        CHECK_EQUAL( 255, (crap::convert<uint32_t, int16_t>( test )) );

        test = crap::limits<uint32_t>::MAX;
        CHECK_EQUAL( crap::limits<int16_t>::MAX, (crap::convert<uint32_t, int16_t>( test )) );

        test = crap::limits<uint32_t>::MIN;
        CHECK_EQUAL( 0, (crap::convert<uint32_t, int16_t>( test )) );
}

TEST(ConverterU32U16)
{
        uint32_t test = 255;
        CHECK_EQUAL( 255, (crap::convert<uint32_t, uint16_t>( test )) );

        test = crap::limits<uint32_t>::MAX;
        CHECK_EQUAL( crap::limits<uint16_t>::MAX, (crap::convert<uint32_t, uint16_t>( test )) );

        test = crap::limits<uint32_t>::MIN;
        CHECK_EQUAL( 0, (crap::convert<uint32_t, uint16_t>( test )) );
}

TEST(ConverterU32I32)
{
        uint32_t test = 255;
        CHECK_EQUAL( 255, (crap::convert<uint32_t, int32_t>( test )) );

        test = crap::limits<uint32_t>::MAX;
        CHECK_EQUAL( crap::limits<int32_t>::MAX, (crap::convert<uint32_t, int32_t>( test )) );

        test = crap::limits<uint32_t>::MIN;
        CHECK_EQUAL( crap::limits<uint32_t>::MIN, (crap::convert<uint32_t, int32_t>( test )) );
}

TEST(ConverterU32U32)
{
        uint32_t test = 255;
        CHECK_EQUAL( (uint32_t)255, (crap::convert<uint32_t, uint32_t>( test )) );

        test = crap::limits<uint32_t>::MAX;
        CHECK_EQUAL( (uint32_t)crap::limits<uint32_t>::MAX, (crap::convert<uint32_t, uint32_t>( test )) );

        test = crap::limits<uint32_t>::MIN;
        CHECK_EQUAL( (uint32_t)0, (crap::convert<uint32_t, uint32_t>( test )) );
}

TEST(ConverterU32I64)
{
        uint32_t test = 255;
        CHECK_EQUAL( 255, (crap::convert<uint32_t, int64_t>( test )) );

        test = crap::limits<uint32_t>::MAX;
        CHECK_EQUAL( crap::limits<uint32_t>::MAX, (crap::convert<uint32_t, int64_t>( test )) );

        test = crap::limits<uint32_t>::MIN;
        CHECK_EQUAL( crap::limits<uint32_t>::MIN, (crap::convert<uint32_t, int64_t>( test )) );
}

TEST(ConverterU32U64)
{
        uint32_t test = 255;
        CHECK_EQUAL( (uint64_t)255, (crap::convert<uint32_t, uint64_t>( test )) );

        test = crap::limits<uint32_t>::MAX;
        CHECK_EQUAL( (uint64_t)crap::limits<uint32_t>::MAX, (crap::convert<uint32_t, uint64_t>( test )) );

        test = crap::limits<uint32_t>::MIN;
        CHECK_EQUAL( (uint64_t)0, (crap::convert<uint32_t, uint64_t>( test )) );
}

TEST(ConverterU32F32)
{
        uint32_t test = 255;
        CHECK_EQUAL( 255.0f, (crap::convert<uint32_t, float32_t>( test )) );

        test = crap::limits<uint32_t>::MAX;
        CHECK_EQUAL( (float32_t)crap::limits<uint32_t>::MAX, (crap::convert<uint32_t, float32_t>( test )) );

        test = crap::limits<uint32_t>::MIN;
        CHECK_EQUAL( 0.f, (crap::convert<uint32_t, float32_t>( test )) );
}

TEST(ConverterU32F64)
{
        uint32_t test = 255;
        CHECK_EQUAL( 255.0, (crap::convert<uint32_t, float64_t>( test )) );

        test = crap::limits<uint32_t>::MAX;
        CHECK_EQUAL( crap::limits<uint32_t>::MAX, (crap::convert<uint32_t, float64_t>( test )) );

        test = crap::limits<uint32_t>::MIN;
        CHECK_EQUAL( crap::limits<uint32_t>::MIN, (crap::convert<uint32_t, float64_t>( test )) );
}


//int64_t
TEST(ConverterI64C8)
{
        int64_t test = 0;
        CHECK_EQUAL( (int32_t)0, (int32_t)(crap::convert<int64_t, char>( test )) );

        test = 255;
        CHECK_EQUAL( (int32_t)127, (int32_t)(crap::convert<int64_t, char>( test )) );

        test = -255;
        CHECK_EQUAL( (int32_t)-128, (int32_t)(crap::convert<int64_t, char>( test )) );

        test = crap::limits<int64_t>::MAX;
        CHECK_EQUAL( (int32_t)127, (int32_t)(crap::convert<int64_t, char>( test )) );

        test = crap::limits<int64_t>::MIN;
        CHECK_EQUAL( (int32_t)-128, (int32_t)(crap::convert<int64_t, char>( test )) );
}

TEST(ConverterI64I8)
{
        int64_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int64_t, int8_t>( test )) );

        test = 255;
        CHECK_EQUAL( 127, (crap::convert<int64_t, int8_t>( test )) );

        test = -255;
        CHECK_EQUAL( -128, (crap::convert<int64_t, int8_t>( test )) );

        test = crap::limits<int64_t>::MAX;
        CHECK_EQUAL( 127, (crap::convert<int64_t, int8_t>( test )) );

        test = crap::limits<int64_t>::MIN;
        CHECK_EQUAL( -128, (crap::convert<int64_t, int8_t>( test )) );
}

TEST(ConverterI64U8)
{
        int64_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int64_t, uint8_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<int64_t, uint8_t>( test )) );

        test = -255;
        CHECK_EQUAL( 0, (crap::convert<int64_t, uint8_t>( test )) );

        test = crap::limits<int64_t>::MAX;
        CHECK_EQUAL( 255, (crap::convert<int64_t, uint8_t>( test )) );

        test = crap::limits<int64_t>::MIN;
        CHECK_EQUAL( 0, (crap::convert<int64_t, uint8_t>( test )) );
}

TEST(ConverterI64I16)
{
        int64_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int64_t, int16_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<int64_t, int16_t>( test )) );

        test = -255;
        CHECK_EQUAL( -255, (crap::convert<int64_t, int16_t>( test )) );

        test = crap::limits<int64_t>::MAX;
        CHECK_EQUAL( crap::limits<int16_t>::MAX, (crap::convert<int64_t, int16_t>( test )) );

        test = crap::limits<int64_t>::MIN;
        CHECK_EQUAL( crap::limits<int16_t>::MIN, (crap::convert<int64_t, int16_t>( test )) );
}

TEST(ConverterI64U16)
{
        int64_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int64_t, uint16_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<int64_t, uint16_t>( test )) );

        test = -255;
        CHECK_EQUAL( 0, (crap::convert<int64_t, uint16_t>( test )) );

        test = crap::limits<int64_t>::MAX;
        CHECK_EQUAL( crap::limits<uint16_t>::MAX, (crap::convert<int64_t, uint16_t>( test )) );

        test = crap::limits<int64_t>::MIN;
        CHECK_EQUAL( 0, (crap::convert<int64_t, uint16_t>( test )) );
}

TEST(ConverterI64I32)
{
        int64_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int64_t, int32_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<int64_t, int32_t>( test )) );

        test = -255;
        CHECK_EQUAL( -255, (crap::convert<int64_t, int32_t>( test )) );

        test = crap::limits<int64_t>::MAX;
        CHECK_EQUAL( crap::limits<int32_t>::MAX, (crap::convert<int64_t, int32_t>( test )) );

        test = crap::limits<int64_t>::MIN;
        CHECK_EQUAL( crap::limits<int32_t>::MIN, (crap::convert<int64_t, int32_t>( test )) );
}

TEST(ConverterI64U32)
{
        int64_t test = 0;
        CHECK_EQUAL( (uint32_t)0, (crap::convert<int64_t, uint32_t>( test )) );

        test = 255;
        CHECK_EQUAL( (uint32_t)255, (crap::convert<int64_t, uint32_t>( test )) );

        test = -255;
        CHECK_EQUAL( (uint32_t)0, (crap::convert<int64_t, uint32_t>( test )) );

        test = crap::limits<int64_t>::MAX;
        CHECK_EQUAL( (uint32_t)crap::limits<int64_t>::MAX, (crap::convert<int64_t, uint32_t>( test )) );

        test = crap::limits<int64_t>::MIN;
        CHECK_EQUAL( (uint32_t)0, (crap::convert<int64_t, uint32_t>( test )) );
}

TEST(ConverterI64I64)
{
        int64_t test = 0;
        CHECK_EQUAL( 0, (crap::convert<int64_t, int64_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255, (crap::convert<int64_t, int64_t>( test )) );

        test = -255;
        CHECK_EQUAL( -255, (crap::convert<int64_t, int64_t>( test )) );

        test = crap::limits<int64_t>::MAX;
        CHECK_EQUAL( crap::limits<int64_t>::MAX, (crap::convert<int64_t, int64_t>( test )) );

        test = crap::limits<int64_t>::MIN;
        CHECK_EQUAL( crap::limits<int64_t>::MIN, (crap::convert<int64_t, int64_t>( test )) );
}

TEST(ConverterI64U64)
{
        int64_t test = 0;
        CHECK_EQUAL( (uint64_t)0, (crap::convert<int64_t, uint64_t>( test )) );

        test = 255;
        CHECK_EQUAL( (uint64_t)255, (crap::convert<int64_t, uint64_t>( test )) );

        test = -255;
        CHECK_EQUAL( (uint64_t)0, (crap::convert<int64_t, uint64_t>( test )) );

        test = crap::limits<int64_t>::MAX;
        CHECK_EQUAL( (uint64_t)crap::limits<int64_t>::MAX, (crap::convert<int64_t, uint64_t>( test )) );

        test = crap::limits<int64_t>::MIN;
        CHECK_EQUAL( (uint64_t)0, (crap::convert<int64_t, uint64_t>( test )) );
}

TEST(ConverterI64F32)
{
        int64_t test = 0;
        CHECK_EQUAL( 0.0f, (crap::convert<int64_t, float32_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255.0f, (crap::convert<int64_t, float32_t>( test )) );

        test = -255;
        //CHECK_EQUAL( -255.0f, (crap::convert<int64_t, float32_t>( test )) );

        test = crap::limits<int64_t>::MAX;
        CHECK_EQUAL( static_cast<float32_t>(crap::limits<int64_t>::MAX),(crap::convert<int64_t, float32_t>( test )) );

        test = crap::limits<int64_t>::MIN;
        //CHECK_EQUAL( crap::limits<int64_t>::MIN, (crap::convert<int64_t, float32_t>( test )) );
}

TEST(ConverterI64F64)
{
        int64_t test = 0;
        CHECK_EQUAL( 0.0, (crap::convert<int64_t, float64_t>( test )) );

        test = 255;
        CHECK_EQUAL( 255.0, (crap::convert<int64_t, float64_t>( test )) );

        test = -255;
        CHECK_EQUAL( -255.0, (crap::convert<int64_t, float64_t>( test )) );

        test = crap::limits<int64_t>::MAX;
        CHECK_EQUAL( (float64_t)crap::limits<int64_t>::MAX, (crap::convert<int64_t, float64_t>( test )) );

        test = crap::limits<int64_t>::MIN;
        CHECK_EQUAL( (float64_t)crap::limits<int64_t>::MIN, (crap::convert<int64_t, float64_t>( test )) );
}



//U64
TEST(ConverterU64C8)
{
        uint64_t test = 255;
        CHECK_EQUAL( (int32_t)127, (int32_t)(crap::convert<uint64_t, char>( test )) );

        test = crap::limits<uint64_t>::MAX;
        CHECK_EQUAL( (int32_t)127, (int32_t)(crap::convert<uint64_t, char>( test )) );

        test = crap::limits<uint64_t>::MIN;
        CHECK_EQUAL( (int32_t)0, (int32_t)(crap::convert<uint64_t, char>( test )) );
}

TEST(ConverterU64I8)
{
        uint64_t test = 255;
        CHECK_EQUAL( (int32_t)127, (int32_t)(crap::convert<uint64_t, int8_t>( test )) );

        test = crap::limits<uint64_t>::MAX;
        CHECK_EQUAL( (int32_t)127, (int32_t)(crap::convert<uint64_t, int8_t>( test )) );

        test = crap::limits<uint64_t>::MIN;
        CHECK_EQUAL( (int32_t)0, (int32_t)(crap::convert<uint64_t, int8_t>( test )) );
}

TEST(ConverterU64U8)
{
        uint64_t test = 255;
        CHECK_EQUAL( 255, (crap::convert<uint64_t, uint8_t>( test )) );

        test = crap::limits<uint64_t>::MAX;
        CHECK_EQUAL( 255, (crap::convert<uint64_t, uint8_t>( test )) );

        test = crap::limits<uint64_t>::MIN;
        CHECK_EQUAL( 0, (crap::convert<uint64_t, uint8_t>( test )) );
}

TEST(ConverterU64I16)
{
        uint64_t test = 255;
        CHECK_EQUAL( 255, (crap::convert<uint64_t, int16_t>( test )) );

        test = crap::limits<uint64_t>::MAX;
        CHECK_EQUAL( crap::limits<int16_t>::MAX, (crap::convert<uint64_t, int16_t>( test )) );

        test = crap::limits<uint64_t>::MIN;
        CHECK_EQUAL( 0, (crap::convert<uint64_t, int16_t>( test )) );
}

TEST(ConverterU64U16)
{
        uint64_t test = 255;
        CHECK_EQUAL( 255, (crap::convert<uint64_t, uint16_t>( test )) );

        test = crap::limits<uint64_t>::MAX;
        CHECK_EQUAL( crap::limits<uint16_t>::MAX, (crap::convert<uint64_t, uint16_t>( test )) );

        test = crap::limits<uint64_t>::MIN;
        CHECK_EQUAL( 0, (crap::convert<uint64_t, uint16_t>( test )) );
}

TEST(ConverterU64I32)
{
        uint64_t test = 255;
        CHECK_EQUAL( 255, (crap::convert<uint64_t, int32_t>( test )) );

        test = crap::limits<uint64_t>::MAX;
        CHECK_EQUAL( crap::limits<int32_t>::MAX, (crap::convert<uint64_t, int32_t>( test )) );

        test = crap::limits<uint64_t>::MIN;
        CHECK_EQUAL( crap::limits<uint64_t>::MIN, (crap::convert<uint64_t, int32_t>( test )) );
}

TEST(ConverterU64U32)
{
        uint64_t test = 255;
        CHECK_EQUAL( (uint32_t)255, (crap::convert<uint64_t, uint32_t>( test )) );

        test = crap::limits<uint64_t>::MAX;
        CHECK_EQUAL( (uint32_t)crap::limits<uint32_t>::MAX, (crap::convert<uint64_t, uint32_t>( test )) );

        test = crap::limits<uint64_t>::MIN;
        CHECK_EQUAL( (uint32_t)0, (crap::convert<uint64_t, uint32_t>( test )) );
}

TEST(ConverterU64I64)
{
        uint64_t test = 255;
        CHECK_EQUAL( 255, (crap::convert<uint64_t, int64_t>( test )) );

        test = crap::limits<uint64_t>::MAX;
        CHECK_EQUAL( crap::limits<int64_t>::MAX, (crap::convert<uint64_t, int64_t>( test )) );

        test = crap::limits<uint64_t>::MIN;
        CHECK_EQUAL( crap::limits<uint64_t>::MIN, (crap::convert<uint64_t, int64_t>( test )) );
}

TEST(ConverterU64U64)
{
        uint64_t test = 255;
        CHECK_EQUAL( (uint64_t)255, (crap::convert<uint64_t, uint64_t>( test )) );

        test = crap::limits<uint64_t>::MAX;
        CHECK_EQUAL( (uint64_t)crap::limits<uint64_t>::MAX, (crap::convert<uint64_t, uint64_t>( test )) );

        test = crap::limits<uint64_t>::MIN;
        CHECK_EQUAL( (uint64_t)0, (crap::convert<uint64_t, uint64_t>( test )) );
}

TEST(ConverterU64F32)
{
        uint64_t test = 255;
        CHECK_EQUAL( 255.0f, (crap::convert<uint64_t, float32_t>( test )) );

        test = crap::limits<uint64_t>::MAX;
        CHECK_EQUAL( (float32_t)crap::limits<uint64_t>::MAX, (crap::convert<uint64_t, float32_t>( test )) );

        test = crap::limits<uint64_t>::MIN;
        CHECK_EQUAL( 0.f, (crap::convert<uint64_t, float32_t>( test )) );
}

TEST(ConverterU64F64)
{
        uint64_t test = 255;
        CHECK_EQUAL( 255.0, (crap::convert<uint64_t, float64_t>( test )) );

        test = crap::limits<uint64_t>::MAX;
        CHECK_EQUAL( crap::limits<uint64_t>::MAX, (crap::convert<uint64_t, float64_t>( test )) );

        test = crap::limits<uint64_t>::MIN;
        CHECK_EQUAL( crap::limits<uint64_t>::MIN, (crap::convert<uint64_t, float64_t>( test )) );
}


//float32_t
TEST(ConverterF32C8)
{
    float32_t test = 0.0f;
    CHECK_EQUAL( (int32_t)0, (int32_t)(crap::convert<float32_t, char>( test )) );

	test = 255.f;
    CHECK_EQUAL( (int32_t)127, (int32_t)(crap::convert<float32_t, char>( test )) );

	test = -255.f;
    CHECK_EQUAL( (int32_t)-128, (int32_t)(crap::convert<float32_t, char>( test )) );

    test = crap::limits<float32_t>::MAX;
    CHECK_EQUAL( (int32_t)127, (int32_t)(crap::convert<float32_t, char>( test )) );

    test = crap::limits<float32_t>::MIN;
    CHECK_EQUAL( CHAR_MIN, (int32_t)(crap::convert<float32_t, char>( test )) );
}

TEST(ConverterF32I8)
{
    float32_t test = 0;
    CHECK_EQUAL( 0, (crap::convert<float32_t, int8_t>( test )) );

	test = 255;
    CHECK_EQUAL( 127, (crap::convert<float32_t, int8_t>( test )) );

	test = -255;
    CHECK_EQUAL( -128, (crap::convert<float32_t, int8_t>( test )) );

    test = crap::limits<float32_t>::MAX;
    CHECK_EQUAL( 127, (crap::convert<float32_t, int8_t>( test )) );

    test = crap::limits<float32_t>::MIN;
    CHECK_EQUAL( (int32_t)-128, (int32_t)(crap::convert<float32_t, int8_t>( test )) );
}

TEST(ConverterF32U8)
{
    float32_t test = 0;
    CHECK_EQUAL( 0, (crap::convert<float32_t, uint8_t>( test )) );

	test = 255;
    CHECK_EQUAL( 255, (crap::convert<float32_t, uint8_t>( test )) );

	test = -255;
    CHECK_EQUAL( 0, (crap::convert<float32_t, uint8_t>( test )) );

    test = crap::limits<float32_t>::MAX;
    CHECK_EQUAL( 255, (crap::convert<float32_t, uint8_t>( test )) );

    test = crap::limits<float32_t>::MIN;
    CHECK_EQUAL( 0, (crap::convert<float32_t, uint8_t>( test )) );
}

TEST(ConverterF32I16)
{
    float32_t test = 0;
    CHECK_EQUAL( 0, (crap::convert<float32_t, int16_t>( test )) );

	test = 255;
    CHECK_EQUAL( 255, (crap::convert<float32_t, int16_t>( test )) );

	test = -255;
    CHECK_EQUAL( -255, (crap::convert<float32_t, int16_t>( test )) );

    test = crap::limits<float32_t>::MAX;
    CHECK_EQUAL( crap::limits<int16_t>::MAX, (crap::convert<float32_t, int16_t>( test )) );

    test = crap::limits<float32_t>::MIN;
    CHECK_EQUAL( crap::limits<int16_t>::MIN, (crap::convert<float32_t, int16_t>( test )) );
}

TEST(ConverterF32U16)
{
    float32_t test = 0;
    CHECK_EQUAL( 0, (crap::convert<float32_t, uint16_t>( test )) );

	test = 255;
    CHECK_EQUAL( 255, (crap::convert<float32_t, uint16_t>( test )) );

	test = -255;
    CHECK_EQUAL( 0, (crap::convert<float32_t, uint16_t>( test )) );

    test = crap::limits<float32_t>::MAX;
    CHECK_EQUAL( crap::limits<uint16_t>::MAX, (crap::convert<float32_t, uint16_t>( test )) );

    test = crap::limits<float32_t>::MIN;
    CHECK_EQUAL( 0, (crap::convert<float32_t, uint16_t>( test )) );
}

TEST(ConverterF32I32)
{
    float32_t test = 0;
    CHECK_EQUAL( 0, (crap::convert<float32_t, int32_t>( test )) );

	test = 255;
    CHECK_EQUAL( 255, (crap::convert<float32_t, int32_t>( test )) );

	test = -255;
    CHECK_EQUAL( -255, (crap::convert<float32_t, int32_t>( test )) );

    test = crap::limits<float32_t>::MAX;
    CHECK_EQUAL( crap::limits<int32_t>::MAX, (crap::convert<float32_t, int32_t>( test )) );

    test = crap::limits<float32_t>::MIN;
    CHECK_EQUAL( crap::limits<int32_t>::MIN, (crap::convert<float32_t, int32_t>( test )) );
}

TEST(ConverterF32U32)
{
    float32_t test = 0;
    CHECK_EQUAL( (uint32_t)0, (crap::convert<float32_t, uint32_t>( test )) );

	test = 255;
    CHECK_EQUAL( (uint32_t)255, (crap::convert<float32_t, uint32_t>( test )) );

	test = -255;
    CHECK_EQUAL( (uint32_t)0, (crap::convert<float32_t, uint32_t>( test )) );

    test = crap::limits<float32_t>::MAX;
    CHECK_EQUAL( crap::limits<uint32_t>::MAX, (crap::convert<float32_t, uint32_t>( test )) );

    test = crap::limits<float32_t>::MIN;
    CHECK_EQUAL( (uint32_t)0, (crap::convert<float32_t, uint32_t>( test )) );
}

TEST(ConverterF32I64)
{
    float32_t test = 0;
    CHECK_EQUAL( 0, (crap::convert<float32_t, int64_t>( test )) );

	test = 255;
    CHECK_EQUAL( 255, (crap::convert<float32_t, int64_t>( test )) );

	test = -255;
    CHECK_EQUAL( -255, (crap::convert<float32_t, int64_t>( test )) );

    test = crap::limits<float32_t>::MAX;
    CHECK_EQUAL( crap::limits<int64_t>::MAX, (crap::convert<float32_t, int64_t>( test )) );

    test = crap::limits<float32_t>::MIN;
    CHECK_EQUAL( crap::limits<int64_t>::MIN, (crap::convert<float32_t, int64_t>( test )) );
}

TEST(ConverterF32U64)
{
    float32_t test = 0;
    CHECK_EQUAL( (uint64_t)0, (crap::convert<float32_t, uint64_t>( test )) );

	test = 255;
    CHECK_EQUAL( (uint64_t)255, (crap::convert<float32_t, uint64_t>( test )) );

	test = -255;
    CHECK_EQUAL( (uint64_t)0, (crap::convert<float32_t, uint64_t>( test )) );

    test = crap::limits<float32_t>::MAX;
    CHECK_EQUAL( crap::limits<uint64_t>::MAX, (crap::convert<float32_t, uint64_t>( test )) );

    test = crap::limits<float32_t>::MIN;
    CHECK_EQUAL( (uint64_t)0, (crap::convert<float32_t, uint64_t>( test )) );
}

TEST(ConverterF32F32)
{
    float32_t test = 0;
    CHECK_EQUAL( 0.0f, (crap::convert<float32_t, float32_t>( test )) );

	test = 255;
    CHECK_EQUAL( 255.0f, (crap::convert<float32_t, float32_t>( test )) );

	test = -255;
    CHECK_EQUAL( -255.0f, (crap::convert<float32_t, float32_t>( test )) );

    test = crap::limits<float32_t>::MAX;
    CHECK_EQUAL( crap::limits<float32_t>::MAX,(crap::convert<float32_t, float32_t>( test )) );

    test = crap::limits<float32_t>::MIN;
    CHECK_EQUAL( crap::limits<float32_t>::MIN, (crap::convert<float32_t, float32_t>( test )) );
}

TEST(ConverterF32F64)
{
    float32_t test = 0;
    CHECK_EQUAL( 0.0, (crap::convert<float32_t, float64_t>( test )) );

	test = 255;
    CHECK_EQUAL( 255.0, (crap::convert<float32_t, float64_t>( test )) );

	test = -255;
    CHECK_EQUAL( -255.0, (crap::convert<float32_t, float64_t>( test )) );

    test = crap::limits<float32_t>::MAX;
    CHECK_EQUAL( (float64_t)crap::limits<float32_t>::MAX, (crap::convert<float32_t, float64_t>( test )) );

    test = crap::limits<float32_t>::MIN;
    CHECK_EQUAL( (float64_t)crap::limits<float32_t>::MIN, (crap::convert<float32_t, float64_t>( test )) );
}


//float64_t
TEST(ConverterF64C8)
{
    float64_t test = 0.0f;
    CHECK_EQUAL( (int32_t)0, (int32_t)(crap::convert<float64_t, char>( test )) );

	test = 255.f;
    CHECK_EQUAL( (int32_t)127, (int32_t)(crap::convert<float64_t, char>( test )) );

	test = -255.f;
    CHECK_EQUAL( (int32_t)-128, (int32_t)(crap::convert<float64_t, char>( test )) );

    test = crap::limits<float64_t>::MAX;
    CHECK_EQUAL( (int32_t)127, (int32_t)(crap::convert<float64_t, char>( test )) );

    test = crap::limits<float64_t>::MIN;
    CHECK_EQUAL( (int32_t)-128, (int32_t)(crap::convert<float64_t, char>( test-1.f )) );
}

TEST(ConverterF64I8)
{
    float64_t test = 0;
    CHECK_EQUAL( 0, (crap::convert<float64_t, int8_t>( test )) );

	test = 255;
    CHECK_EQUAL( 127, (crap::convert<float64_t, int8_t>( test )) );

	test = -255;
    CHECK_EQUAL( -128, (crap::convert<float64_t, int8_t>( test )) );

    test = crap::limits<float64_t>::MAX;
    CHECK_EQUAL( 127, (crap::convert<float64_t, int8_t>( test )) );

    test = crap::limits<float64_t>::MIN;
    CHECK_EQUAL( -128, (crap::convert<float64_t, int8_t>( test )) );
}

TEST(ConverterF64U8)
{
    float64_t test = 0;
    CHECK_EQUAL( 0, (crap::convert<float64_t, uint8_t>( test )) );

	test = 255;
    CHECK_EQUAL( 255, (crap::convert<float64_t, uint8_t>( test )) );

	test = -255;
    CHECK_EQUAL( 0, (crap::convert<float64_t, uint8_t>( test )) );

    test = crap::limits<float64_t>::MAX;
    CHECK_EQUAL( 255, (crap::convert<float64_t, uint8_t>( test )) );

    test = crap::limits<float64_t>::MIN;
    CHECK_EQUAL( 0, (crap::convert<float64_t, uint8_t>( test )) );
}

TEST(ConverterF64I16)
{
    float64_t test = 0;
    CHECK_EQUAL( 0, (crap::convert<float64_t, int16_t>( test )) );

	test = 255;
    CHECK_EQUAL( 255, (crap::convert<float64_t, int16_t>( test )) );

	test = -255;
    CHECK_EQUAL( -255, (crap::convert<float64_t, int16_t>( test )) );

    test = crap::limits<float64_t>::MAX;
    CHECK_EQUAL( crap::limits<int16_t>::MAX, (crap::convert<float64_t, int16_t>( test )) );

    test = crap::limits<float64_t>::MIN;
    CHECK_EQUAL( crap::limits<int16_t>::MIN, (crap::convert<float64_t, int16_t>( test )) );
}

TEST(ConverterF64U16)
{
    float64_t test = 0;
    CHECK_EQUAL( 0, (crap::convert<float64_t, uint16_t>( test )) );

	test = 255;
    CHECK_EQUAL( 255, (crap::convert<float64_t, uint16_t>( test )) );

	test = -255;
    CHECK_EQUAL( 0, (crap::convert<float64_t, uint16_t>( test )) );

    test = crap::limits<float64_t>::MAX;
    CHECK_EQUAL( crap::limits<uint16_t>::MAX, (crap::convert<float64_t, uint16_t>( test )) );

    test = crap::limits<float64_t>::MIN;
    CHECK_EQUAL( 0, (crap::convert<float64_t, uint16_t>( test )) );
}

TEST(ConverterF64I32)
{
    float64_t test = 0;
    CHECK_EQUAL( 0, (crap::convert<float64_t, int32_t>( test )) );

	test = 255;
    CHECK_EQUAL( 255, (crap::convert<float64_t, int32_t>( test )) );

	test = -255;
    CHECK_EQUAL( -255, (crap::convert<float64_t, int32_t>( test )) );

    test = crap::limits<float64_t>::MAX;
    CHECK_EQUAL( crap::limits<int32_t>::MAX, (crap::convert<float64_t, int32_t>( test )) );

    test = crap::limits<float64_t>::MIN;
    CHECK_EQUAL( crap::limits<int32_t>::MIN, (crap::convert<float64_t, int32_t>( test )) );
}

TEST(ConverterF64U32)
{
    float64_t test = 0;
    CHECK_EQUAL( (uint32_t)0, (crap::convert<float64_t, uint32_t>( test )) );

	test = 255;
    CHECK_EQUAL( (uint32_t)255, (crap::convert<float64_t, uint32_t>( test )) );

	test = -255;
    CHECK_EQUAL( (uint32_t)0, (crap::convert<float64_t, uint32_t>( test )) );

    test = crap::limits<float64_t>::MAX;
    CHECK_EQUAL( (uint32_t)crap::limits<uint32_t>::MAX, (crap::convert<float64_t, uint32_t>( test )) );

    test = crap::limits<float64_t>::MIN;
    CHECK_EQUAL( (uint32_t)0, (crap::convert<float64_t, uint32_t>( test )) );
}

TEST(ConverterF64I64)
{
    float64_t test = 0;
    CHECK_EQUAL( 0, (crap::convert<float64_t, int64_t>( test )) );

	test = 255;
    CHECK_EQUAL( 255, (crap::convert<float64_t, int64_t>( test )) );

	test = -255;
    CHECK_EQUAL( -255, (crap::convert<float64_t, int64_t>( test )) );

    test = crap::limits<float64_t>::MAX;
    CHECK_EQUAL( crap::limits<int64_t>::MAX, (crap::convert<float64_t, int64_t>( test )) );

    test = crap::limits<float64_t>::MIN;
    CHECK_EQUAL( crap::limits<int64_t>::MIN, (crap::convert<float64_t, int64_t>( test )) );
}

TEST(ConverterF64U64)
{
    float64_t test = 0;
    CHECK_EQUAL( (uint64_t)0, (crap::convert<float64_t, uint64_t>( test )) );

	test = 255;
    CHECK_EQUAL( (uint64_t)255, (crap::convert<float64_t, uint64_t>( test )) );

	test = -255;
    CHECK_EQUAL( (uint64_t)0, (crap::convert<float64_t, uint64_t>( test )) );

    test = crap::limits<float64_t>::MAX;
    CHECK_EQUAL( crap::limits<uint64_t>::MAX, (crap::convert<float64_t, uint64_t>( test )) );

    test = crap::limits<float64_t>::MIN;
    CHECK_EQUAL( (uint64_t)0, (crap::convert<float64_t, uint64_t>( test )) );
}

TEST(ConverterF64F32)
{
    float64_t test = 0.0;
    CHECK_EQUAL( 0.0f, (crap::convert<float64_t, float32_t>( test )) );

	test = 255;
    CHECK_EQUAL( 255.0f, (crap::convert<float64_t, float32_t>( test )) );

	test = -255;
    CHECK_EQUAL( -255.0f, (crap::convert<float64_t, float32_t>( test )) );

    test = crap::limits<float64_t>::MAX;
    CHECK_EQUAL( crap::limits<float32_t>::MAX,(crap::convert<float64_t, float32_t>( test )) );

    test = crap::limits<float64_t>::MIN;
    CHECK_EQUAL( crap::limits<float32_t>::MIN, (crap::convert<float64_t, float32_t>( test )) );
}

TEST(ConverterF64F64)
{
    float64_t test = 0.0;
    CHECK_EQUAL( 0.0, (crap::convert<float64_t, float64_t>( test )) );

	test = 255;
    CHECK_EQUAL( 255.0, (crap::convert<float64_t, float64_t>( test )) );

	test = -255;
    CHECK_EQUAL( -255.0, (crap::convert<float64_t, float64_t>( test )) );

    test = crap::limits<float64_t>::MAX;
    CHECK_EQUAL( (float64_t)crap::limits<float64_t>::MAX, (crap::convert<float64_t, float64_t>( test )) );

    test = crap::limits<float64_t>::MIN;
    CHECK_EQUAL( (float64_t)crap::limits<float64_t>::MIN, (crap::convert<float64_t, float64_t>( test )) );
}


}   // namespace
