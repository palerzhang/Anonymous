#ifndef _ANONYMOUS_TRANSFORM_H_
#define _ANONYMOUS_TRANSFORM_H_

#include "AsQuaternion.h"
#include "AsPlane.h"
#include "AsMatrix44.h"

class AsTransform
{
public:
	AsQuaternion q;
	AsVector3 p;

	inline AsTransform()
	{
	}

	inline explicit AsTransform(const AsVector3& position) : q(AsIdentity), p(position)
	{
	}

	inline explicit AsTransform(AsIDENTITY r) : q(AsIdentity), p(AsZero)
	{
		AS_UNUSED(r);
	}

	inline explicit AsTransform(const AsQuaternion& orientation) : q(orientation), p(0)
	{
	}

	inline AsTransform(float x, float y, float z, AsQuaternion aQ = AsQuaternion(AsIdentity))
		: q(aQ), p(x, y, z)
	{
	}

	inline AsTransform(const AsVector3& p0, const AsQuaternion& q0) : q(q0), p(p0)
	{
	}

	inline explicit AsTransform(const AsMatrix44& m);

	/**
	\brief returns true if the two transforms are exactly equal
	*/
	inline bool operator==(const AsTransform& t) const
	{
		return p == t.p && q == t.q;
	}

	inline AsTransform operator*(const AsTransform& x) const
	{
		return transform(x);
	}

	//! Equals matrix multiplication
	inline AsTransform& operator*=(AsTransform& other)
	{
		*this = *this * other;
		return *this;
	}

	inline AsTransform getInverse() const
	{
		return AsTransform(q.rotateInv(-p), q.getConjugate());
	}

	inline AsVector3 transform(const AsVector3& input) const
	{
		return q.rotate(input) + p;
	}

	inline AsVector3 transformInv(const AsVector3& input) const
	{
		return q.rotateInv(input - p);
	}

	inline AsVector3 rotate(const AsVector3& input) const
	{
		return q.rotate(input);
	}

	inline AsVector3 rotateInv(const AsVector3& input) const
	{
		return q.rotateInv(input);
	}

	//! Transform transform to parent (returns compound transform: first src, then *this)
	inline AsTransform transform(const AsTransform& src) const
	{
		// src = [srct, srcr] -> [r*srct + t, r*srcr]
		return AsTransform(q.rotate(src.p) + p, q * src.q);
	}

	/**
	\brief returns true if finite and q is a unit quaternion
	*/

	bool isValid() const
	{
		return p.isFinite() && q.isFinite() && q.isUnit();
	}

	/**
	\brief returns true if all elems are finite (not NAN or INF, etc.)
	*/
	inline bool isFinite() const
	{
		return p.isFinite() && q.isFinite();
	}

	//! Transform transform from parent (returns compound transform: first src, then this->inverse)
	inline AsTransform transformInv(const AsTransform& src) const
	{
		// src = [srct, srcr] -> [r^-1*(srct-t), r^-1*srcr]
		AsQuaternion qinv = q.getConjugate();
		return AsTransform(qinv.rotate(src.p - p), qinv * src.q);
	}

	/**
	\brief transform plane
	*/

	inline AsPlane transform(const AsPlane& plane) const
	{
		AsVector3 transformedNormal = rotate(plane.n);
		return AsPlane(transformedNormal, plane.d - p.dot(transformedNormal));
	}

	/**
	\brief inverse-transform plane
	*/

	inline AsPlane inverseTransform(const AsPlane& plane) const
	{
		AsVector3 transformedNormal = rotateInv(plane.n);
		return AsPlane(transformedNormal, plane.d + p.dot(plane.n));
	}

	/**
	\brief return a normalized transform (i.e. one in which the quaternion has unit magnitude)
	*/
	inline AsTransform getNormalized() const
	{
		return AsTransform(p, q.getNormalized());
	}
};

#endif