#ifndef _ANONYMOUSE_COLOR_H_
#define _ANONYMOUSE_COLOR_H_

#include "AsVector4.h"

class AsColor
{
public:
	float r, g, b, a;

	AsColor() : r(0), g(0), b(0), a(1.0f){}

	AsColor(float nr, float ng, float nb, float na = 1.0f)
		: r(nr), g(ng), b(nb), a(na){}

	AsColor(AsVector3 vec, float na = 1.0f)
		: r(vec.x), g(vec.y), b(vec.z), a(na){}

	AsColor(AsVector4 vec)
		: r(vec.x), g(vec.y), b(vec.z), a(vec.w){}

	inline AsColor & operator=(const AsColor & c)
	{
		r = c.r; g = c.g; b = c.b; a = c.a;
		return *this;
	}

	// color prefab
	static const AsColor White;
	static const AsColor Black;
};

const AsColor AsColor::White = AsColor(1.0f, 1.0f, 1.0f, 1.0f);
const AsColor AsColor::Black = AsColor(0.0f, 0.0f, 0.0f, 1.0f);

#endif