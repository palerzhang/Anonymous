#ifndef _ANONYMOUS_MATRIX44_H_
#define _ANONYMOUS_MATRIX44_H_

#include "AsQuaternion.h"
#include "AsMatrix44.h"
#include "AsMatrix33.h"
#include "AsTransform.h"

class AsMatrix44
{
public:

	float x, y, z, w;

	inline AsMatrix44()
	{
	}

	AsMatrix44(AsZERO r) : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{
		AS_UNUSED(r);
	}

	explicit inline AsMatrix44(float a) : x(a), y(a), z(a), w(a)
	{
	}

	inline AsMatrix44(float nx, float ny, float nz, float nw) : x(nx), y(ny), z(nz), w(nw)
	{
	}

	inline AsMatrix44(const AsVector3& v, float nw) : x(v.x), y(v.y), z(v.z), w(nw)
	{
	}

	explicit inline AsMatrix44(const float v[]) : x(v[0]), y(v[1]), z(v[2]), w(v[3])
	{
	}

	inline AsMatrix44(const AsMatrix44& v) : x(v.x), y(v.y), z(v.z), w(v.w)
	{
	}

	/**
	\brief Assignment operator
	*/
	inline AsMatrix44& operator=(const AsMatrix44& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
		w = p.w;
		return *this;
	}

	/**
	\brief element access
	*/
	inline float& operator[](unsigned int index)
	{
		return reinterpret_cast<float*>(this)[index];
	}

	/**
	\brief element access
	*/
	inline const float& operator[](unsigned int index) const
	{
		return reinterpret_cast<const float*>(this)[index];
	}

	/**
	\brief returns true if the two vectors are exactly equal.
	*/
	inline bool operator==(const AsMatrix44& v) const
	{
		return x == v.x && y == v.y && z == v.z && w == v.w;
	}

	/**
	\brief returns true if the two vectors are not exactly equal.
	*/
	inline bool operator!=(const AsMatrix44& v) const
	{
		return x != v.x || y != v.y || z != v.z || w != v.w;
	}

	/**
	\brief tests for exact zero vector
	*/
	inline bool isZero() const
	{
		return x == 0 && y == 0 && z == 0 && w == 0;
	}

	/**
	\brief returns true if all 3 elems of the vector are finite (not NAN or INF, etc.)
	*/
	inline bool isFinite() const
	{
		return AsIsFinite(x) && AsIsFinite(y) && AsIsFinite(z) && AsIsFinite(w);
	}

	/**
	\brief is normalized - used by API parameter validation
	*/
	inline bool isNormalized() const
	{
		const float unitTolerance = 1e-4f;
		return isFinite() && AsAbs(magnitude() - 1) < unitTolerance;
	}

	/**
	\brief returns the squared magnitude

	Avoids calling AsSqrt()!
	*/
	inline float magnitudeSquared() const
	{
		return x * x + y * y + z * z + w * w;
	}

	/**
	\brief returns the magnitude
	*/
	inline float magnitude() const
	{
		return AsSqrt(magnitudeSquared());
	}

	/**
	\brief negation
	*/
	inline AsMatrix44 operator-() const
	{
		return AsMatrix44(-x, -y, -z, -w);
	}

	/**
	\brief vector addition
	*/
	inline AsMatrix44 operator+(const AsMatrix44& v) const
	{
		return AsMatrix44(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	/**
	\brief vector difference
	*/
	inline AsMatrix44 operator-(const AsMatrix44& v) const
	{
		return AsMatrix44(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	/**
	\brief scalar post-multiplication
	*/

	inline AsMatrix44 operator*(float f) const
	{
		return AsMatrix44(x * f, y * f, z * f, w * f);
	}

	/**
	\brief scalar division
	*/
	inline AsMatrix44 operator/(float f) const
	{
		f = 1.0f / f;
		return AsMatrix44(x * f, y * f, z * f, w * f);
	}

	/**
	\brief vector addition
	*/
	inline AsMatrix44& operator+=(const AsMatrix44& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}

	/**
	\brief vector difference
	*/
	inline AsMatrix44& operator-=(const AsMatrix44& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}

	/**
	\brief scalar multiplication
	*/
	inline AsMatrix44& operator*=(float f)
	{
		x *= f;
		y *= f;
		z *= f;
		w *= f;
		return *this;
	}
	/**
	\brief scalar division
	*/
	inline AsMatrix44& operator/=(float f)
	{
		f = 1.0f / f;
		x *= f;
		y *= f;
		z *= f;
		w *= f;
		return *this;
	}

	/**
	\brief returns the scalar product of this and other.
	*/
	inline float dot(const AsMatrix44& v) const
	{
		return x * v.x + y * v.y + z * v.z + w * v.w;
	}

	/** return a unit vector */

	inline AsMatrix44 getNormalized() const
	{
		float m = magnitudeSquared();
		return m > 0.0f ? *this * AsRecipSqrt(m) : AsMatrix44(0, 0, 0, 0);
	}

	/**
	\brief normalizes the vector in place
	*/
	inline float normalize()
	{
		float m = magnitude();
		if (m > 0.0f)
			*this /= m;
		return m;
	}

	/**
	\brief a[i] * b[i], for all i.
	*/
	inline AsMatrix44 multiply(const AsMatrix44& a) const
	{
		return AsMatrix44(x * a.x, y * a.y, z * a.z, w * a.w);
	}

	/**
	\brief element-wise minimum
	*/
	inline AsMatrix44 minimum(const AsMatrix44& v) const
	{
		return AsMatrix44(AsMin(x, v.x), AsMin(y, v.y), AsMin(z, v.z), AsMin(w, v.w));
	}

	/**
	\brief element-wise maximum
	*/
	inline AsMatrix44 maximum(const AsMatrix44& v) const
	{
		return AsMatrix44(AsMax(x, v.x), AsMax(y, v.y), AsMax(z, v.z), AsMax(w, v.w));
	}

	inline AsVector3 getXYZ() const
	{
		return AsVector3(x, y, z);
	}

	/**
	\brief set vector elements to zero
	*/
	inline void setZero()
	{
		x = y = z = w = 0.0f;
	}
};

static inline AsMatrix44 operator*(float f, const AsMatrix44& v)
{
	return AsMatrix44(f * v.x, f * v.y, f * v.z, f * v.w);
}

#endif