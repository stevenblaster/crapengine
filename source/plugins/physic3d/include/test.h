
#include "config/crap_types.h"

class b3Vector3;

struct physictest
{
//btHashMap<uint32_t, uint32_t> my_map;
    b3Vector3* my_vec;

    physictest( void );

    ~physictest( void )
    {
        //my_map.remove(1);
    }
};
