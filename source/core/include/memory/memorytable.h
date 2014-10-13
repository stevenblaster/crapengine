#pragma once

#ifndef CRAP_MEMORY_MEMORYTABLE_H
#define CRAP_MEMORY_MEMORYTABLE_H


#include "atomic.h"
#include "config/crap_types.h"
#include "asserts.h"

namespace crap
{

class memory_table
{
private:

    friend class memory_manager;

    struct atomic_pair
    {
        atomic32_t key;
        atomic32_t value;
    };

    atomic_pair* _data;
    uint32_t _size;

    CRAP_INLINE uint32_t hash_func( const uint32_t& key ) const
    {
        uint32_t h = key;

        h ^= h >> 16;
        h *= 0x85ebca6b;
        h ^= h >> 13;
        h *= 0xc2b2ae35;
        h ^= h >> 16;

        return h;
    }

    CRAP_INLINE memory_table( const memory_table& )
    {
        CRAP_ASSERT(ASSERT_BREAK, ASSERT_CONSOLE, false, "No copy constructor allowed");
    }

    CRAP_INLINE memory_table& operator=( const memory_table& )
    {
        CRAP_ASSERT(ASSERT_BREAK, ASSERT_CONSOLE, false, "No assignment operator allowed");
    }

public:

    CRAP_INLINE memory_table( void* memory, uint32_t size ) : _data((atomic_pair*)memory), _size(size/sizeof(atomic_pair)) {}
    CRAP_INLINE ~memory_table( void ) {}

    CRAP_INLINE void set(const uint32_t& key, const uint32_t& value)
    {
        for (uint32_t idx = hash_func(key);; idx++)
        {
            idx &= _size - 1;

            uint32_t prevKey = compare_exchange_strong_32_relaxed(&_data[idx].key, 0, key);
            if ((prevKey == 0) || (prevKey == key))
            {
                store_32_relaxed(&_data[idx].value, value);
                return;
            }
        }
    }

    CRAP_INLINE uint32_t get(const uint32_t& key) const
    {
        for (uint32_t idx = hash_func(key);; idx++)
        {
            idx &= _size - 1;

            uint32_t probedKey = load_32_relaxed(&_data[idx].key);
            if (probedKey == key)
                return load_32_relaxed(&_data[idx].value);
            if (probedKey == 0)
                return 0;
        }
    }
};

class memory_table_64
{
private:

    friend class memory_manager;

    struct atomic_pair
    {
        atomic32_t key;
        atomic64_t value;
    };

    atomic_pair* _data;
    uint32_t _size;

    CRAP_INLINE uint32_t hash_func( const uint32_t& key ) const
    {
        uint32_t h = key;

        h ^= h >> 16;
        h *= 0x85ebca6b;
        h ^= h >> 13;
        h *= 0xc2b2ae35;
        h ^= h >> 16;

        return h;
    }

    CRAP_INLINE memory_table_64( const memory_table_64& )
    {
        CRAP_ASSERT(ASSERT_BREAK, false, "No copy constructor allowed");
    }

    CRAP_INLINE memory_table_64& operator=( const memory_table_64& )
    {
        CRAP_ASSERT(ASSERT_BREAK, false, "No assignment operator allowed");
    }

public:

    CRAP_INLINE memory_table_64( void* memory, uint32_t size ) : _data((atomic_pair*)memory), _size(size/sizeof(atomic_pair)) {}
    CRAP_INLINE ~memory_table_64( void ) {}

    CRAP_INLINE void set(const uint32_t& key, const uint64_t& value)
    {
        for (uint32_t idx = hash_func(key);; idx++)
        {
            idx &= _size - 1;

            uint32_t prevKey = compare_exchange_strong_32_relaxed(&_data[idx].key, 0, key);
            if ((prevKey == 0) || (prevKey == key))
            {
                store_64_relaxed(&_data[idx].value, value);
                return;
            }
        }
    }

    CRAP_INLINE uint64_t get(const uint32_t& key) const
    {
        for (uint32_t idx = hash_func(key);; idx++)
        {
            idx &= _size - 1;

            uint32_t probedKey = load_32_relaxed(&_data[idx].key);
            if (probedKey == key)
                return load_64_relaxed(&_data[idx].value);
            if (probedKey == 0)
                return 0;
        }
    }
};

} //namespace crap

#endif //CRAP_MEMORY_MEMORYTABLE_H
