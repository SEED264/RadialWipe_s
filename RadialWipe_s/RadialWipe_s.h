#ifndef _RADIALWIPE_S_H_
#define _RADIALWIPE_S_H_

#include <lua.hpp>
#include <Windows.h>

int RadialWipe_Core(lua_State *L);

int RadialWipe(lua_State *L) {
	int r = RadialWipe_Core(L);
	return r;
	// Lua 側での戻り値の個数を返す(data だけを返すので 1)
}

#endif // _RADIALWIPE_S_H_
