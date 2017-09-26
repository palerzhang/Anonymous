#ifndef _ANONYMOUS_PLANE_H_
#define _ANONYMOUS_PLANE_H_

#include "AsMath.h"
#include "AsVector3.h"

class AsPlane
{
public:

	AsVector3 n; //!< The normal to the plane
	float d;  //!< The distance from the origin

	inline AsPlane()
	{
	}

	inline AsPlane(float nx, float ny, float nz, float distance) : n(nx, ny, nz), d(distance)
	{
	}

	inline AsPlane(const AsVector3& normal, float distance) : n(normal), d(distance)
	{
	}

	inline AsPlane(const AsVector3& point, const AsVector3& normal)
		: n(normal), d(-point.dot(n)) // p satisfies normal.dot(p) + d = 0
	{
	}

	inline AsPlane(const AsVector3& p0, const AsVector3& p1, const AsVector3& p2)
	{
		n = (p1 - p0).cross(p2 - p0).getNormalized();
		d = -p0.dot(n);
	}

	/**
	\brief returns true if the two planes are exactly equal
	*/
	inline bool operator==(const AsPlane& p) const
	{
		return n == p.n && d == p.d;
	}

	inline float distance(const AsVector3& p) const
	{
		return p.dot(n) + d;
	}

	inline bool contains(const AsVector3& p) const
	{
		return AsAbs(distance(p)) < (1.0e-7f);
	}

	/**
	\brief projects p into the plane
	*/
	inline AsVector3 project(const AsVector3& p) const
	{
		return p - n * distance(p);
	}

	/**
	\brief find an arbitrary point in the plane
	*/
	inline AsVector3 pointInPlane() const
	{
		return -n * d;
	}

	/**
	\brief equivalent plane with unit normal
	*/

	inline void normalize()
	{
		float denom = 1.0f / n.magnitude();
		n *= denom;
		d *= denom;
	}

};

#endif