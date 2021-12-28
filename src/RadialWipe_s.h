#ifndef _RADIALWIPE_S_H_
#define _RADIALWIPE_S_H_

#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX

#include <lua.hpp>
#include <Windows.h>
#include "CustomType.h"

int RadialWipe(lua_State *L);

void RadialWipeCore(Pixel_RGBA *pixels, Size_2D size,
                    float sAngle, float wAngle, float ox, float oy, bool fan);

#endif // _RADIALWIPE_S_H_
