#include <iostream>

#include "geometry/Geometry.h"
#include "geometry/Noise.h"
#include "luatables/luatables.h"
#include "luatables/luatables.cc"

using namespace Geo;
using namespace Noise;

#include "include/Root.h"
#include "include/Configuration.h"


int main()
{
    Root::instance().start();
    return 0;
}
