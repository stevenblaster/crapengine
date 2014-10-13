
#include <iostream>
#include <vector>

//#include "atomic.h"
//#include "container/array.h"

//#include "container/container_index.h"
////#include "container/vector.h"

//#include "UnitTest++.h"

//#define MEM (1024 * 100)
//#define ARR (MEM/4)
//#define THR 1
//#define INSERTIONS 1000000

//struct somevector
//{
//crap::mutex_t a_mutex;
//std::vector<uint32_t> a_vector;
//};


//void* doInsert( void* data )
//{
//    crap::vector<uint32_t>* my_index = (crap::vector3<uint32_t>*)data;
//    static uint32_t some_number = 1;
//    uint32_t my_number = some_number++;

//    uint32_t rondo = rand() % (1000000);

//    for(uint32_t i = 0; i < INSERTIONS; ++i )
////        my_index->push_back( my_number );
//    {
//        (*my_index)[i] = my_number;
//    }
////    {
////        crap::mutex_lock( &my_index->a_mutex );
////        my_index->a_vector[rondo+i] = my_number;
////        crap::mutex_unlock( &my_index->a_mutex );
////    }

////        uint32_t temp = (*my_index)[my_number];
////    (*my_index)[my_number] = 25;

////    printf( "%u exited\n", crap::thread_id() );
////    fflush(stdout);

//    return data;
//}

//namespace
//{

//struct teststruct128
//{
//    uint64_t first;
//    uint64_t second;
//};

//struct teststruct256
//{
//    uint64_t first;
//    uint64_t second;
//    uint64_t third;
//    uint64_t fourth;

//    teststruct256& operator=( const teststruct256& other )
//    {
//        first = other.first;
//        second = other.second;

//        return *this;
//    }

//    bool operator==( const teststruct256& other ) const
//    {
//        return first == other.first;
//    }

//    teststruct256& operator&( const teststruct256& other )
//    {
//        return *this;
//    }

//    teststruct256& operator|( const teststruct256& other )
//    {
//        return *this;
//    }

//    teststruct256& operator+( const teststruct256& other )
//    {
//        return *this;
//    }
//};

//struct teststructUgly
//{
//    char first;
//    uint64_t second;
//    uint64_t third;
//    uint64_t fourth;
//};



//TEST(DoTheThreading)
//{
//    void* mem = malloc( MEM );
//    crap::array<int> arr( mem, MEM );

//    crap::container_index* my_index = new crap::container_index(ARR);
//    crap::vector<uint32_t> my_vector(2000000);
//    crap::vector3<uint32_t> my_other_vector( 1000000 );
//    somevector default_vector;
//    crap::mutex_init( &default_vector.a_mutex );
//    default_vector.a_vector.reserve(1000000);

//    for(int i=0; i<ARR; ++i )
//        arr.push_back(i % 2);

//    crap::thread_t tr[THR];
//    crap::tick_t frequency, ticks_before, ticks_after;
//    crap::timer_frequency( &frequency );
//    crap::timer_get_tick( &ticks_before );

//    for(int i=0; i < THR; ++i )
//    {
//        crap::thread_create(&tr[i], doInsert, &my_other_vector, 8196, 0);
//    }

//    for(int i=0; i < THR; ++i )
//    {
//        crap::thread_join(tr[i], 0);
//    }

//    crap::timer_get_tick( &ticks_after );

//    std::cout << THR * INSERTIONS << " insertions done by " << THR << " threads took " << ticks_after - ticks_before << " ticks." << std::endl;

//    std::cout << "the size is " << my_vector.size() << std::endl;

//    std::cout << "frequency: " << frequency << std::endl;

////    for( crap::vector<uint32_t>::const_iterator it = my_vector.begin(); it != my_vector.end(); ++it )
////        if( *it == 25 )
////        std::cout << "Content at " << it.get_index() << " is " << *it << std::endl;
//}

//TEST(atmoicstuff)
//{
//    crap::atomic_t<uint8_t> testtype;
//    testtype.atomic_store(10);
//    uint8_t temp1 = testtype.atomic_load();
//    bool result = testtype.atomic_cas( temp1, 12 );
//    temp1 = testtype.atomic_add( 12 );
//    temp1 = testtype.atomic_and( 12 );
//    temp1 = testtype.atomic_or( 12 );

//    crap::atomic_t<uint16_t> testtype2;
//    testtype2.atomic_store(10);
//    uint16_t temp2 = testtype2.atomic_load();
//    result = testtype2.atomic_cas( temp2, 12 );
//    temp2 = testtype2.atomic_add( 12 );
//    temp2 = testtype2.atomic_and( 12 );
//    temp2 = testtype2.atomic_or( 12 );

//    crap::atomic_t<uint32_t> testtype3;
//    testtype3.atomic_store(10);
//    uint32_t temp3 = testtype3.atomic_load();
//    result = testtype3.atomic_cas( temp3, 12 );
//    temp3 = testtype3.atomic_add( 12 );
//    temp3 = testtype3.atomic_and( 12 );
//    temp3 = testtype3.atomic_or( 12 );

//    crap::atomic_t<uint64_t> testtype4;
//    testtype4.atomic_store(10);
//    uint64_t temp4 = testtype4.atomic_load();
//    result = testtype4.atomic_cas( temp4, 12 );
//    temp4 = testtype4.atomic_add( 12 );
//    temp4 = testtype4.atomic_and( 12 );
//    temp4 = testtype4.atomic_or( 12 );

//    teststruct256 funny;
//    crap::atomic_t<teststruct256> testtype5;
//    testtype5.atomic_store(funny);
//    funny.first = 4;
//    teststruct256 temp5 = testtype5.atomic_load();
//    result = testtype5.atomic_cas( temp5, funny );
//    temp5 = testtype5.atomic_add( funny );
//    temp5 = testtype5.atomic_and( funny );
//    temp5 = testtype5.atomic_or( funny );
//}

//TEST(atmoicstuff2)
//{
//    bool result;

//    crap::atomic_t<float32_t> testtype3;
//    testtype3.atomic_store(10.f);
//    float32_t temp3 = testtype3.atomic_load();
//    result = testtype3.atomic_cas( temp3, 12.f );
//    temp3 = testtype3.atomic_add( 12.f );
//    temp3 = testtype3.atomic_and( 12.f );
//    temp3 = testtype3.atomic_or( 12.f );

//    crap::atomic_t<float64_t> testtype4;
//    testtype4.atomic_store(10.0);
//    float64_t temp4 = testtype4.atomic_load();
//    result = testtype4.atomic_cas( temp4, 12.0);
//    temp4 = testtype4.atomic_add( 12.0 );
//    temp4 = testtype4.atomic_and( 12.0 );
//    temp4 = testtype4.atomic_or( 12.0 );

//    std::cout << "vectr and stuff done" << std::endl;

//    std::cout << "Alignment of char: " << crap::align_of<char>::value << std::endl;
//    std::cout << "Alignment of int: " << crap::align_of<int>::value << std::endl;

//    uint32_t headerSize = sizeof(uint64_t)/sizeof(uint32_t);

//    if(sizeof(uint64_t)%sizeof(uint32_t) > 0)
//        headerSize += 1;

//    std::cout << "Was kommt da raus? " << headerSize << std::endl;
//}

//}
