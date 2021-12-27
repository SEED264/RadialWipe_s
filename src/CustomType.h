#ifndef _RADIALWIPE_S_CUSTOMTYPE_H_
#define _RADIALWIPE_S_CUSTOMTYPE_H_

// unsigned longの代わりのメモリ上の配置が同じになる構造体
// メモリの配置順の都合上、内部の変数の順番はBGRAでなくてはならない
struct Pixel_RGBA {
	unsigned char b = 0;
	unsigned char g = 0;
	unsigned char r = 0;
	unsigned char a = 0;
};

// 画像のサイズ等に使う構造体
struct Size_2D{
	unsigned int w, h;
	Size_2D(unsigned int aw, unsigned int ah):w(aw), h(ah) {}
	Size_2D(){
		Size_2D(0, 0);
	}
};

struct vec3 {
	float x, y, z;
	vec3(float ax, float ay, float az) :x(ax), y(ay), z(az) {}
	vec3() {
		vec3(0, 0, 0);
	}
	float dot(vec3 a);
};

struct vec2 {
	float x, y;
	vec2(float ax, float ay) :x(ax), y(ay) {}
	vec2() {
		vec2(0, 0);
	}
};

inline float vec3::dot(vec3 a) {
	return x * a.x + y * a.y + z * a.z;
}

#endif // !_RADIALWIPE_S_CUSTOMTYPE_H_
