#include "RadialWipe_s.h"
#include "CustomType.h"
#include "UtilFunc.h"
#include <omp.h>

int RadialWipe_Core(lua_State *L) {
	float sAngle = lua_tonumber(L, 1);
	float wAngle = lua_tonumber(L, 2);
	// 上の二つまでが必須の引数 後はオプション
	int argNum = lua_gettop(L);
	float ox = (argNum >= 3) ? lua_tonumber(L, 3) : 0;
	float oy = (argNum >= 4) ? lua_tonumber(L, 4) : 0;
	bool fan = (argNum >= 5) ? lua_toboolean(L, 5) : false;

	// ワイプの角度が0か720の倍数(偶数周ちょうど)なら何もやることはないのでさっさと抜ける
	if (std::fmodf(wAngle, 720) == 0) {
		return 0;
	}

	// ここでスクリプトの代わりに画像のデータの取得を行う これによってスクリプト側でいちいちgetpixeldataを呼び出す必要がなくなる
	Pixel_RGBA *pixels;
	Size_2D size;
	getpixeldata(L, &pixels, &size);
	vec2 imageCenter(size.w/2.0, size.h/2.0);

	float startAngle, endAngle;
	calcWipeAngles(sAngle, wAngle, fan, &startAngle, &endAngle);
	vec2 wipeCenter(ox+imageCenter.x, oy+imageCenter.y);

	float angleDiff = endAngle - startAngle;
	float halflineAngle = std::fmodf(startAngle + angleDiff * 0.5 + 90, 360);

	endAngle = std::fmodf(endAngle, 360);

	float a1 = (startAngle > 90 && startAngle <= 270) ? 1 : -1;
	float a2 = (endAngle > 90 && endAngle <= 270) ? -1 : 1;
	float a3 = (halflineAngle > 90 && halflineAngle <= 270) ? -1 : 1;
	float t1 = std::tan(toRadian(startAngle));
	float t2 = std::tan(toRadian(endAngle));
	float t3 = std::tan(toRadian(halflineAngle));
	// それぞれの角度が90か270の時に(tanの無限大の代わりに)INFINITEを入れる(これがないとどれかが90か270の時にワイプが効かなくなる)
	if (startAngle == 90 || startAngle == 270) t1 = INFINITE;
	if (endAngle == 90 || endAngle == 270) t2 = INFINITE;
	if (halflineAngle == 90 || halflineAngle == 270) t3 = INFINITE;

	a1 /= std::sqrt(a1*a1*(1 + t1 * t1));
	a2 /= std::sqrt(a2*a2*(1 + t2 * t2));
	a3 /= std::sqrt(a3*a3*(1 + t3 * t3));

	vec3 line1(a1, a1*t1, a1*(-wipeCenter.x - wipeCenter.y*t1));
	vec3 line2(a2, a2*t2, a2*(-wipeCenter.x - wipeCenter.y*t2));
	vec3 line3(a3, a3*t3, a3*(-wipeCenter.x - wipeCenter.y*t3));

	#pragma omp parallel for
	for (int y = 0; y < size.h; y++) {
		for (int x = 0; x < size.w; x++) {
			unsigned long index = x + y * size.w;
			float at = 0;
			if (std::fmodf(wAngle, 360) != 0) {
				vec3 pos((float)x + 0.5, (float)y + 0.5, 1.0);
				if (angleDiff <= 180) {
					if (line3.dot(pos) > 0.5) {
						at = 1.0;
					}
					else {
						float d1 = clamp(line1.dot(pos) + 0.5, 0.0, 1.0);
						float d2 = clamp(line2.dot(pos) + 0.5, 0.0, 1.0);
						at = max(d1, d2);
					}
				}
				else
				{
					if (line3.dot(pos) < -0.5) {
						at = 0.0;
					}
					else {
						float d1 = clamp(line1.dot(pos) + 0.5, 0.0, 1.0);
						float d2 = clamp(line2.dot(pos) + 0.5, 0.0, 1.0);
						at = min(d1, d2);
					}
				}
			} else {
				at = 0;
			}
			pixels[index].a *= at;
		}
	}

	// getpixeldataと同様にputpixeldataもこちら側で処理
	lua_getfield(L, -1, "putpixeldata");
	lua_pushlightuserdata(L, pixels);
	lua_call(L, 1, 0);
	return 0;
}

// 関数の登録
static luaL_Reg RadialWipe_s[] = {
	{ "RadialWipe", RadialWipe },
	{ NULL, NULL }
};

/*
ここでDLLを定義
別のものを作る場合は
RadialWipe_s
の部分を新しい名前に変更
*/
extern "C" {
	__declspec(dllexport) int luaopen_RadialWipe_s(lua_State *L) {
		luaL_register(L, "RadialWipe_s", RadialWipe_s);
		return 1;
	}
}
