
#include "utilities.h"

namespace crap
{

const uint32_t limits<uint32_t>::MIN = UINT32_MIN;
const uint32_t limits<uint32_t>::MAX = UINT32_MAX;

const int64_t limits<int64_t>::MIN = INT64_MIN;
const int64_t limits<int64_t>::MAX = INT64_MAX;

const uint64_t limits<uint64_t>::MIN = UINT64_MIN;
const uint64_t limits<uint64_t>::MAX = UINT64_MAX;

const float32_t limits<float32_t>::MIN = FLOAT32_MAX * -1.f;
const float32_t limits<float32_t>::MAX = FLOAT32_MAX;

const float64_t limits<float64_t>::MIN = FLOAT64_MAX * -1.0;
const float64_t limits<float64_t>::MAX = FLOAT64_MAX;

}
