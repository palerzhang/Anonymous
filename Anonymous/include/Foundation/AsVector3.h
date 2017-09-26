#ifndef _ANONYMOUS_VECTOR3_H_
#define _ANONYMOUS_VECTOR3_H_

#include "AsMath.h"

enum AsZERO
{
	AsZero = 0
};

class AsVector3
{
public:
	
	float x, y, z;

	inline AsVector3()
	{
	}

	inline AsVector3(AsZERO r) : x(0.0f), y(0.0f), z(0.0f)
	{
		AS_UNUSED(r);
	}

	explicit inline AsVector3(float a) : x(a), y(a), z(a) 
	{
	}

	inline AsVector3(float nx, float ny, float nz) : x(nx), y(ny), z(nz)
	{
	}

	inline AsVector3(const AsVector3& v) : x(v.x), y(v.y), z(v.z)
	{
	}

	/**
	\brief Assignment operator
	*/
	inline AsVector3& operator=(const AsVector3& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
		return *this;
	}

	/**
	\brief element access
	*/
	inline float& operator[](unsigned int index)
	{
		if (index <= 2)
			return reinterpret_cast<float*>(this)[index];
		else
			return reinterpret_cast<float*>(this)[2];
	}

	/**
	\brief returns true if the two vectors are exactly equal.
	*/
	inline bool operator==(const AsVector3& v) const
	{
		return x == v.x && y == v.y && z == v.z;
	}

	/**
	\brief returns true if the two vectors are not exactly equal.
	*/
	inline bool operator!=(const AsVector3& v) const
	{
		return x != v.x || y != v.y || z != v.z;
	}

	/**
	\brief tests for exact zero vector
	*/
	inline bool isZero() const
	{
		return x == 0.0f && y == 0.0f && z == 0.0f;
	}

	/**
	\brief returns true if all 3 elems of the vector are finite (not NAN or INF, etc.)
	*/
	inline bool isFinite() const
	{
		return AsIsFinite(x) && AsIsFinite(y) && AsIsFinite(z);
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
		return x * x + y * y + z * z;
	}

	/**
	\brief returns the magnitude
	*/
	inline float magnitude() const
	{
		return sqrt(magnitudeSquared());
	}

	/**
	\brief negation
	*/
	inline AsVector3 operator-() const
	{
		return AsVector3(-x, -y, -z);
	}

	/**
	\brief vector addition
	*/
	inline AsVector3 operator+(const AsVector3& v) const
	{
		return AsVector3(x + v.x, y + v.y, z + v.z);
	}

	/**
	\brief vector difference
	*/
	inline AsVector3 operator-(const AsVector3& v) const
	{
		return AsVector3(x - v.x, y - v.y, z - v.z);
	}

	/**
	\brief scalar post-multiplication
	*/
	inline AsVector3 operator*(float f) const
	{
		return AsVector3(x * f, y * f, z * f);
	}

	/**
	\brief scalar division
	*/
	inline AsVector3 operator/(float f) const
	{
		f = 1.0f / f;
		return AsVector3(x * f, y * f, z * f);
	}

	/**
	\brief vector addition
	*/
	inline AsVector3& operator+=(const AsVector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	/**
	\brief vector difference
	*/
	inline AsVector3& operator-=(const AsVector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	/**
	\brief scalar multiplication
	*/
	inline AsVector3& operator*=(float f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}
	/**
	\brief scalar division
	*/
	inline AsVector3& operator/=(float f)
	{
		f = 1.0f / f;
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	/**
	\brief returns the scalar product of this and other.
	*/
	inline float dot(const AsVector3& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	/**
	\brief cross product
	*/
	inline AsVector3 cross(const AsVector3& v) const
	{
		return AsVector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	/** return a unit vector */

	inline AsVector3 getNormalized() const
	{
		const float m = magnitudeSquared();
		return m > 0.0f ? *this * AsRecipSqrt(m) : AsVector3(0, 0, 0);
	}

	/**
	\brief normalizes the vector in place
	*/
	inline float normalize()
	{
		const float m = magnitude();
		if (m > 0.0f)
			*this /= m;
		return m;
	}

	/**
	\brief a[i] * b[i], for all i.
	*/
	inline AsVector3 multiply(const AsVector3& a) const
	{
		return AsVector3(x * a.x, y * a.y, z * a.z);
	}

	/**
	\brief element-wise minimum
	*/
	inline AsVector3 minimum(const AsVector3& v) const
	{
		return AsVector3(AsMin(x, v.x), AsMin(y, v.y), AsMin(z, v.z));
	}

	/**
	\brief returns MIN(x, y, z);
	*/
	inline float minElement() const
	{
		return AsMin(x, AsMin(y, z));
	}

	/**
	\brief element-wise maximum
	*/
	inline AsVector3 maximum(const AsVector3& v) const
	{
		return AsVector3(AsMax(x, v.x), AsMax(y, v.y), AsMax(z, v.z));
	}

	/**
	\brief returns MAX(x, y, z);
	*/
	inline float maxElement() const
	{
		return AsMax(x, AsMax(y, z));
	}

	/**
	\brief returns absolute values of components;
	*/
	inline AsVector3 abs() const
	{
		return AsVector3(AsAbs(x), AsAbs(y), AsAbs(z));
	}

	inline const float* valuePtr()
	{
		return reinterpret_cast<float*>(this);
	}
};

static inline AsVector3 operator*(float f, const AsVector3& v)
{
	return AsVector3(f * v.x, f * v.y, f * v.z);
}

#endif