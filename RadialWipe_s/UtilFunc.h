#ifndef _RADIALWIPE_S_UTILFUNC_H_
#define _RADIALWIPE_S_UTILFUNC_H_
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "CustomType.h"

inline float toRadian(float deg){
	return deg * M_PI / 180.f;
}

inline float clamp(float v, float mi, float ma) {
	return min(max(v, mi), ma);
}

void getpixeldata(lua_State *L, Pixel_RGBA **out_Pixels, Size_2D *out_Size){
	lua_getglobal(L, "obj");
	lua_getfield(L, -1, "getpixeldata");
	lua_call(L, 0, 3);
	out_Size->h = lua_tointeger(L, -1);
	lua_pop(L, 1);
	out_Size->w = lua_tointeger(L, -1);
	lua_pop(L, 1);
	*out_Pixels = (Pixel_RGBA*)lua_touserdata(L, -1);
	lua_pop(L, 1);

}

void calcWipeAngles(float startAngle, float wipeAngle, bool fan, float *out_StartAngle, float *out_EndAngle){
	float a1, a2;
	if (fan) {
		startAngle -= wipeAngle / 2;
	}
	startAngle = std::fmodf(startAngle, 360);
	if (std::fmodf(std::abs(wipeAngle), 720)<360) {
		a1 = startAngle;
		a2 = std::fmodf(wipeAngle, 360) + startAngle;
	}
	else
	{
		a1 = std::fmodf(wipeAngle, 360) + startAngle;
		a2 = startAngle;
	}
	*out_StartAngle = (wipeAngle >= 0) ? a1 : a2;
	*out_EndAngle = (wipeAngle >= 0) ? a2 : a1;
	if (*out_StartAngle < 0)*out_StartAngle += 360;
	while (*out_StartAngle > *out_EndAngle)*out_EndAngle += 360;
}

#endif