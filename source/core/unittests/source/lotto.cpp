
#include "asserts.h"

#include <cstdio>
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

#include "UnitTest++.h"

#include "logger.h"

namespace
{

TEST( AnnounceTestLotto )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"lotto.cpp xD\"" );
}

/*
struct ziehung
{
    unsigned int number[7];
};
*/

#ifndef CRAP_COMPILER_MSVC
TEST(FunitIsLotto)
{
    uint32_t all_numbers[45];
    uint32_t numbers_votings[45];

    for(uint32_t i=1; i<46; ++i)
    {
        all_numbers[i-1] = i;
        numbers_votings[i-1] = 100;
    }

    srand (time(NULL));

    char filename[] = "../../../data/zahlen-text.csv";
    FILE* fp = fopen(filename, "r");
    if( fp == 0 )
    	fp = fopen("../../data/zahlen-text.csv", "r");
    if( fp == 0 )
    	fp = fopen("../data/zahlen-text.csv", "r");
    CRAP_ASSERT(ASSERT_BREAK, fp!=0,  "Cannot open file %s", filename);

    unsigned int all[3000][7];

    char buffer[100];
    unsigned int c = 0;
    while( fgets(buffer,100,fp) )
    {
        sscanf( buffer, "%i,%i,%i,%i,%i,%i,%i", &all[c][0],&all[c][1],&all[c][2],&all[c][3],&all[c][4],&all[c][5],&all[c][6]);
        //printf("%s", buffer);
        c++;
    }
    //for( unsigned int i=0; i<c; ++i)
    //    printf( "ziehung %i: %i-%i-%i-%i-%i-%i Zz %i\n", i, all[i][0],all[i][1],all[i][2],all[i][3],all[i][4],all[i][5],all[i][6]);

    for(uint32_t i = 1; i<11; ++i)
    {
        //printf( "ziehung %i: %i-%i-%i-%i-%i-%i Zz %i\n", c-i, all[c-i][0],all[c-i][1],all[c-i][2],all[c-i][3],all[c-i][4],all[c-i][5],all[c-i][6]);
        for(uint32_t j=0; j<7;++j)
        {
            const uint32_t number = all[c-i][j] -1;
            if( i == 2  && numbers_votings[number] != 100 )
            {
                numbers_votings[number] = 0;
            }

            if( i == 3 && numbers_votings[number] == 99 )
            {
                numbers_votings[number] = 0;
            }

            if( i == 4 && numbers_votings[number] == 98 )
            {
                numbers_votings[number] = 50;
            }

            if( i == 5 && numbers_votings[number] == 97 )
            {
                numbers_votings[number] = 50;
            }

            else if( numbers_votings[number] > 10 )
                numbers_votings[number] -= (21 - i*2);
        }

    }

    for(uint32_t i=1; i<46; ++i)
    {
        //printf( "%u: %u\n", i, numbers_votings[i-1]);
    }

    uint32_t voted_numbers[45];
    uint32_t sorted_votings[45];
    uint32_t index = 0;

    for( uint32_t i = 100; i>0; --i)
    {
        for(uint32_t j=1; j<46; ++j)
        {
            if( numbers_votings[j-1] == i )
            {
                voted_numbers[index] = j;
                sorted_votings[index++] = i;
            }
        }
    }

    for(uint32_t i=1; i<46; ++i)
    {
        printf("%u,", voted_numbers[i-1]);
    }
    printf("\n");

    bool success = false;
    unsigned int border = 3;
    unsigned int bordercount = 0;
    unsigned int number[6];

    uint32_t draw_numbers = 0;
    const uint32_t draw_numbers_max = 100000;
    uint32_t draw_points[draw_numbers_max];
    //memset( draw_points, 0, draw_numbers_max );
    char drawings[draw_numbers_max][30];


    uint32_t super = 0;

    for( uint32_t a=0; a<40; a++ )
    {
        if( draw_numbers > draw_numbers_max )
            break;

        for( uint32_t b=a+1; b<41; b++ )
        {
            if( draw_numbers > draw_numbers_max && a>=b)
                break;

            for( uint32_t c=b+1; c<42; c++ )
            {
                if( draw_numbers > draw_numbers_max && b>=c )
                    break;

                for( uint32_t d=c+1; d<43; d++ )
                {
                    if( draw_numbers > draw_numbers_max && c>=d )
                        break;

                    for( uint32_t e=d+1; e<44; e++ )
                    {
                        if( draw_numbers > draw_numbers_max && d>=e)
                            break;

                        for( uint32_t f=e+1; f<45; f++ )
                        {
                            if( draw_numbers > draw_numbers_max && e>=f )
                                break;

                            const uint32_t nums[6] = { voted_numbers[a],voted_numbers[b],voted_numbers[c],voted_numbers[d],voted_numbers[e],voted_numbers[f] };

                            for( unsigned int i=0; i<c; ++i)
                            {
                                if( draw_numbers > draw_numbers_max )
                                    break;

                                bordercount = 6;
                                if( nums[0] != all[i][0] && nums[0] != all[i][1] && nums[0] != all[i][2] && nums[0] != all[i][3] && nums[0] != all[i][4] && nums[0] != all[i][5] && nums[0] != all[i][6] )
                                    bordercount--;

                                if( nums[1] != all[i][0] && nums[1] != all[i][1] && nums[1] != all[i][2] && nums[1] != all[i][3] && nums[1] != all[i][4] && nums[1] != all[i][5] && nums[1] != all[i][6] )
                                    bordercount--;

                                if( nums[2] != all[i][0] && nums[2] != all[i][1] && nums[2] != all[i][2] && nums[2] != all[i][3] && nums[2] != all[i][4] && nums[2] != all[i][5] && nums[2] != all[i][6] )
                                    bordercount--;

                                if( nums[3] != all[i][0] && nums[3] != all[i][1] && nums[3] != all[i][2] && nums[3] != all[i][3] && nums[3] != all[i][4] && nums[3] != all[i][5] && nums[3] != all[i][6] )
                                    bordercount--;

                                if( nums[4] != all[i][0] && nums[4] != all[i][1] && nums[4] != all[i][2] && nums[4] != all[i][3] && nums[4] != all[i][4] && nums[4] != all[i][5] && nums[4] != all[i][6] )
                                    bordercount--;

                                if( nums[5] != all[i][0] && nums[5] != all[i][1] && nums[5] != all[i][2] && nums[5] != all[i][3] && nums[5] != all[i][4] && nums[5] != all[i][5] && nums[5] != all[i][6] )
                                    bordercount--;

                                if( bordercount > border )
                                {
                                    sprintf( &(drawings[draw_numbers][0]), "%i-%i-%i-%i-%i-%i\0" , nums[0], nums[1], nums[2], nums[3], nums[4], nums[5] );
                                    draw_points[draw_numbers++] = sorted_votings[a] + sorted_votings[b] + sorted_votings[c] + sorted_votings[d] + sorted_votings[e] + sorted_votings[f];

                                }
                            }
                        }
                    }
                }
            }
        }
    }

    for(uint32_t i=0; i< draw_numbers_max; ++i )
    {
        if( draw_points[i] >= 586 )
        printf( "[%u] = %s\n", draw_points[i], &(drawings[i][0]));
    }

}
#endif
}
