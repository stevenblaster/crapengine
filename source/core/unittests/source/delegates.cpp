#include "delegates.h"

#include "UnitTest++.h"

#include "logger.h"

namespace
{

TEST( AnnounceTestDelegates )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"delegates.h\"" );
}

int dele_func( void )
{
    return 1;
}

int dele_add( int val )
{
    return 1+val;
}

long dele_add2( int val, long val1 )
{
    return val1 + val;
}

float dele_mul( int base, long fun, float multi )
{
    return ((float)(base*fun)) * multi;
}

float dele_mul2( int base, long fun, float multi, float plus )
{
    return ((float)(base*fun)) * multi + plus;
}

float dele_div( int base, long fun, float multi, float plus, int add )
{
    return ((float)(base*fun)) * multi + plus + add;
}


class dele_test
{
public:

    int dele_func( void )
    {
        return 0;
    }

    int dele_add( int val )
    {
        return 2+val;
    }

    long dele_add2( int val, long val1 )
    {
        return val1 + val;
    }

    float dele_mul( int base, long fun, float multi )
    {
        return ((float)(base*fun)) * multi;
    }

    float dele_mul2( int base, long fun, float multi, float plus )
    {
        return ((float)(base*fun)) * multi + plus;
    }

    float dele_div( int base, long fun, float multi, float plus, int add )
    {
        return ((float)(base*fun)) * multi + plus + add;
    }
};


TEST(TestDelegateZero)
{
    dele_test setest;
    crap::delegate< int (void) > dele;

    dele.bind<dele_func>();

    printf("Se delegate says: %i\n", dele.invoke());

    dele.bind<dele_test, &dele_test::dele_func>( &setest );

    printf("Se delegate says again: %i\n", dele.invoke());

}

TEST(TestDelegateOne)
{
        dele_test setest;
    crap::delegate<int(int)> dele2;

    dele2.bind<dele_add>();

    printf("Se delegate adds: %i\n", dele2.invoke(25));

    dele2.bind<dele_test, &dele_test::dele_add>( &setest );

    printf("Se delegate adds: %i\n", dele2.invoke(125));
}

TEST(TestDelegateTwo)
{
        dele_test setest;
    crap::delegate<long(int, long)> dele3;

    dele3.bind<dele_add2>();

    printf("Se delegate adds: %i\n", dele3.invoke(25, 25));

    dele3.bind<dele_test, &dele_test::dele_add2>( &setest );

    printf("Se delegate adds: %i\n", dele3.invoke(50, 25));
}

TEST(TestDelegateThree)
{
        dele_test setest;
    crap::delegate<float(int, long, float)> dele3;

    dele3.bind<dele_mul>();

    printf("Se delegate adds: %f\n", dele3.invoke(25, 25, 1.3f));

    dele3.bind<dele_test, &dele_test::dele_mul>( &setest );

    printf("Se delegate adds: %f\n", dele3.invoke(50, 25, 2.6f));
}

TEST(TestDelegateFour)
{
        dele_test setest;
    crap::delegate<float(int, long, float, float)> dele3;

    dele3.bind<dele_mul2>();

    printf("Se delegate adds: %f\n", dele3.invoke(25, 25, 1.3f, 2.6f));

    dele3.bind<dele_test, &dele_test::dele_mul2>( &setest );

    printf("Se delegate adds: %f\n", dele3.invoke(50, 25, 2.6f, 4.3f));
}

TEST(TestDelegateFive)
{
    dele_test setest;
    crap::delegate<float(int, long, float, float, int)> dele3;

    dele3.bind<dele_div>();

    printf("Se delegate adds: %f\n", dele3.invoke(25, 25, 1.3f, 2.6f,8));

    dele3.bind<dele_test, &dele_test::dele_div>( &setest );

    printf("Se delegate adds: %f\n", dele3.invoke(50, 25, 2.6f, 4.3f, 7));
}

}
