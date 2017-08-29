#ifndef _ANONYMOUS_QUATERNION_H_
#define _ANONYMOUS_QUATERNION_H_

#include "AsVector3.h"
#include "AsMatrix33.h"

enum AsIDENTITY
{
	AsIdentity = 0
};

class AsQuaternion
{
public:
	float x, y, z, w;

	inline AsQuaternion()
	{
	}

	inline AsQuaternion(AsIDENTITY r) : x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{
		AS_UNUSED(r);
	}

	explicit inline AsQuaternion(float r) : x(0.0f), y(0.0f), z(0.0f), w(r)
	{
	}

	inline AsQuaternion(float nx, float ny, float nz, float nw) : x(nx), y(ny), z(nz), w(nw)
	{
	}

	/**
	\brief Creates from angle-axis representation.

	Axis must be normalized!

	Angle is in radians!

	<b>Unit:</b> Radians
	*/
	inline AsQuaternion(float angleRadians, const AsVector3& unitAxis)
	{
		const float a = angleRadians * 0.5f;
		const float s = sin(a);
		w = cos(a);
		x = unitAxis.x * s;
		y = unitAxis.y * s;
		z = unitAxis.z * s;
	}

	inline AsQuaternion(const AsQuaternion& v) : x(v.x), y(v.y), z(v.z), w(v.w)
	{
	}

	/**
	\brief Creates from orientation matrix.

	\param[in] m Rotation matrix to extract quaternion from.
	*/
	inline explicit AsQuaternion(const AsMatrix33& m);

	/**
	\brief returns true if quat is identity
	*/
	inline bool isIdentity() const
	{
		return x == 0.0f && y == 0.0f && z == 0.0f && w == 1.0f;
	}

	/**
	\brief returns true if all elements are finite (not NAN or INF, etc.)
	*/
	inline bool isFinite() const
	{
		return AsIsFinite(x) && AsIsFinite(y) && AsIsFinite(z) && AsIsFinite(w);
	}

	/**
	\brief returns true if finite and magnitude is close to unit
	*/
	inline bool isUnit() const
	{
		const float unitTolerance = 1e-4f;
		return isFinite() && AsAbs(magnitude() - 1) < unitTolerance;
	}

	/**
	\brief returns true if the two quaternions are exactly equal
	*/
	inline bool operator==(const AsQuaternion& q) const
	{
		return x == q.x && y == q.y && z == q.z && w == q.w;
	}

	/**
	\brief converts this quaternion to angle-axis representation
	*/
	inline void toRadiansAndUnitAxis(float& angle, AsVector3& axis) const
	{
		const float quatEpsilon = 1.0e-8f;
		const float s2 = x * x + y * y + z * z;
		if (s2 < quatEpsilon * quatEpsilon) // can't extract a sensible axis
		{
			angle = 0.0f;
			axis = AsVector3(1.0f, 0.0f, 0.0f);
		}
		else
		{
			const float s = AsRecipSqrt(s2);
			axis = AsVector3(x, y, z) * s;
			angle = AsAbs(w) < quatEpsilon ? AsPi : atan2(s2 * s, w) * 2.0f;
		}
	}

	/**
	\brief Gets the angle between this quat and the identity quaternion.

	<b>Unit:</b> Radians
	*/
	inline float getAngle() const
	{
		return acos(w) * 2.0f;
	}

	/**
	\brief Gets the angle between this quat and the argument

	<b>Unit:</b> Radians
	*/
	inline float getAngle(const AsQuaternion& q) const
	{
		return acos(dot(q)) * 2.0f;
	}

	/**
	\brief This is the squared 4D vector length, should be 1 for unit quaternions.
	*/
	inline float magnitudeSquared() const
	{
		return x * x + y * y + z * z + w * w;
	}

	/**
	\brief returns the scalar product of this and other.
	*/
	inline float dot(const AsQuaternion& v) const
	{
		return x * v.x + y * v.y + z * v.z + w * v.w;
	}

	inline AsQuaternion getNormalized() const
	{
		const float s = 1.0f / magnitude();
		return AsQuaternion(x * s, y * s, z * s, w * s);
	}

	inline float magnitude() const
	{
		return sqrt(magnitudeSquared());
	}

	// modifiers:
	/**
	\brief maps to the closest unit quaternion.
	*/
	inline float normalize() // convert this AsQuaternion to a unit quaternion
	{
		const float mag = magnitude();
		if (mag != 0.0f)
		{
			const float imag = 1.0f / mag;

			x *= imag;
			y *= imag;
			z *= imag;
			w *= imag;
		}
		return mag;
	}

	/*
	\brief returns the conjugate.

	\note for unit quaternions, this is the inverse.
	*/
	inline AsQuaternion getConjugate() const
	{
		return AsQuaternion(-x, -y, -z, w);
	}

	/*
	\brief returns imaginary part.
	*/
	inline AsVector3 getImaginaryPart() const
	{
		return AsVector3(x, y, z);
	}

	/** brief computes rotation of x-axis */
	inline AsVector3 getBasisVector0() const
	{
		const float x2 = x * 2.0f;
		const float w2 = w * 2.0f;
		return AsVector3((w * w2) - 1.0f + x * x2, (z * w2) + y * x2, (-y * w2) + z * x2);
	}

	/** brief computes rotation of y-axis */
	inline AsVector3 getBasisVector1() const
	{
		const float y2 = y * 2.0f;
		const float w2 = w * 2.0f;
		return AsVector3((-z * w2) + x * y2, (w * w2) - 1.0f + y * y2, (x * w2) + z * y2);
	}

	/** brief computes rotation of z-axis */
	inline AsVector3 getBasisVector2() const
	{
		const float z2 = z * 2.0f;
		const float w2 = w * 2.0f;
		return AsVector3((y * w2) + x * z2, (-x * w2) + y * z2, (w * w2) - 1.0f + z * z2);
	}

	/**
	rotates passed vec by this (assumed unitary)
	*/
	inline const AsVector3 rotate(const AsVector3& v) const
	{
		const float vx = 2.0f * v.x;
		const float vy = 2.0f * v.y;
		const float vz = 2.0f * v.z;
		const float w2 = w * w - 0.5f;
		const float dot2 = (x * vx + y * vy + z * vz);
		return AsVector3((vx * w2 + (y * vz - z * vy) * w + x * dot2), (vy * w2 + (z * vx - x * vz) * w + y * dot2),
			(vz * w2 + (x * vy - y * vx) * w + z * dot2));
	}

	/**
	inverse rotates passed vec by this (assumed unitary)
	*/
	inline const AsVector3 rotateInv(const AsVector3& v) const
	{
		const float vx = 2.0f * v.x;
		const float vy = 2.0f * v.y;
		const float vz = 2.0f * v.z;
		const float w2 = w * w - 0.5f;
		const float dot2 = (x * vx + y * vy + z * vz);
		return AsVector3((vx * w2 - (y * vz - z * vy) * w + x * dot2), (vy * w2 - (z * vx - x * vz) * w + y * dot2),
			(vz * w2 - (x * vy - y * vx) * w + z * dot2));
	}

	/**
	\brief Assignment operator
	*/
	inline AsQuaternion& operator=(const AsQuaternion& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
		w = p.w;
		return *this;
	}

	inline AsQuaternion& operator*=(const AsQuaternion& q)
	{
		const float tx = w * q.x + q.w * x + y * q.z - q.y * z;
		const float ty = w * q.y + q.w * y + z * q.x - q.z * x;
		const float tz = w * q.z + q.w * z + x * q.y - q.x * y;

		w = w * q.w - q.x * x - y * q.y - q.z * z;
		x = tx;
		y = ty;
		z = tz;

		return *this;
	}

	inline AsQuaternion& operator+=(const AsQuaternion& q)
	{
		x += q.x;
		y += q.y;
		z += q.z;
		w += q.w;
		return *this;
	}

	inline AsQuaternion& operator-=(const AsQuaternion& q)
	{
		x -= q.x;
		y -= q.y;
		z -= q.z;
		w -= q.w;
		return *this;
	}

	inline AsQuaternion& operator*=(const float s)
	{
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}

	/** quaternion multiplication */
	inline AsQuaternion operator*(const AsQuaternion& q) const
	{
		return AsQuaternion(w * q.x + q.w * x + y * q.z - q.y * z, w * q.y + q.w * y + z * q.x - q.z * x,
			w * q.z + q.w * z + x * q.y - q.x * y, w * q.w - x * q.x - y * q.y - z * q.z);
	}

	/** quaternion addition */
	inline AsQuaternion operator+(const AsQuaternion& q) const
	{
		return AsQuaternion(x + q.x, y + q.y, z + q.z, w + q.w);
	}

	/** quaternion subtraction */
	inline AsQuaternion operator-() const
	{
		return AsQuaternion(-x, -y, -z, -w);
	}

	inline AsQuaternion operator-(const AsQuaternion& q) const
	{
		return AsQuaternion(x - q.x, y - q.y, z - q.z, w - q.w);
	}

	inline AsQuaternion operator*(float r) const
	{
		return AsQuaternion(x * r, y * r, z * r, w * r);
	}

};

#endif