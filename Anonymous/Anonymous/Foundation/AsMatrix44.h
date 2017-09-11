#ifndef _ANONYMOUS_MATRIX44_H_
#define _ANONYMOUS_MATRIX44_H_

#include "AsVector4.h"
#include "AsMatrix33.h"
#include "AsTransform.h"

class AsMatrix44
{
public:
	AsVector4 column0, column1, column2, column3; // the four base vectors

	//! Default constructor
	inline AsMatrix44()
	{
	}

	//! identity constructor
	inline AsMatrix44(AsIDENTITY r)
		: column0(1.0f, 0.0f, 0.0f, 0.0f)
		, column1(0.0f, 1.0f, 0.0f, 0.0f)
		, column2(0.0f, 0.0f, 1.0f, 0.0f)
		, column3(0.0f, 0.0f, 0.0f, 1.0f)
	{
		AS_UNUSED(r);
	}

	//! zero constructor
	inline AsMatrix44(AsZERO r) : column0(AsZero), column1(AsZero), column2(AsZero), column3(AsZero)
	{
		AS_UNUSED(r);
	}

	//! Construct from four 4-vectors
	AsMatrix44(const AsVector4& col0, const AsVector4& col1, const AsVector4& col2, const AsVector4& col3)
		: column0(col0), column1(col1), column2(col2), column3(col3)
	{
	}

	//! constructor that generates a multiple of the identity matrix
	explicit inline AsMatrix44(float r)
		: column0(r, 0.0f, 0.0f, 0.0f)
		, column1(0.0f, r, 0.0f, 0.0f)
		, column2(0.0f, 0.0f, r, 0.0f)
		, column3(0.0f, 0.0f, 0.0f, r)
	{
	}

	//! Construct from three base vectors and a translation
	AsMatrix44(const AsVector3& col0, const AsVector3& col1, const AsVector3& col2, const AsVector3& col3)
		: column0(col0, 0), column1(col1, 0), column2(col2, 0), column3(col3, 1.0f)
	{
	}

	//! Construct from float[16]
	explicit inline AsMatrix44(float values[])
		: column0(values[0], values[1], values[2], values[3])
		, column1(values[4], values[5], values[6], values[7])
		, column2(values[8], values[9], values[10], values[11])
		, column3(values[12], values[13], values[14], values[15])
	{
	}

	//! Construct from a quaternion
	explicit inline AsMatrix44(const AsQuaternion& q)
	{
		const float x = q.x;
		const float y = q.y;
		const float z = q.z;
		const float w = q.w;

		const float x2 = x + x;
		const float y2 = y + y;
		const float z2 = z + z;

		const float xx = x2 * x;
		const float yy = y2 * y;
		const float zz = z2 * z;

		const float xy = x2 * y;
		const float xz = x2 * z;
		const float xw = x2 * w;

		const float yz = y2 * z;
		const float yw = y2 * w;
		const float zw = z2 * w;

		column0 = AsVector4(1.0f - yy - zz, xy + zw, xz - yw, 0.0f);
		column1 = AsVector4(xy - zw, 1.0f - xx - zz, yz + xw, 0.0f);
		column2 = AsVector4(xz + yw, yz - xw, 1.0f - xx - yy, 0.0f);
		column3 = AsVector4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	//! Construct from a diagonal vector
	explicit inline AsMatrix44(const AsVector4& diagonal)
		: column0(diagonal.x, 0.0f, 0.0f, 0.0f)
		, column1(0.0f, diagonal.y, 0.0f, 0.0f)
		, column2(0.0f, 0.0f, diagonal.z, 0.0f)
		, column3(0.0f, 0.0f, 0.0f, diagonal.w)
	{
	}

	//! Construct from Mat33 and a translation
	AsMatrix44(const AsMatrix33& axes, const AsVector3& position)
		: column0(axes.column0, 0.0f), column1(axes.column1, 0.0f), column2(axes.column2, 0.0f), column3(position, 1.0f)
	{
	}

	AsMatrix44(const AsTransform& t)
	{
		*this = AsMatrix44(AsMatrix33(t.q), t.p);
	}

	/**
	\brief returns true if the two matrices are exactly equal
	*/
	inline bool operator==(const AsMatrix44& m) const
	{
		return column0 == m.column0 && column1 == m.column1 && column2 == m.column2 && column3 == m.column3;
	}

	//! Copy constructor
	inline AsMatrix44(const AsMatrix44& other)
		: column0(other.column0), column1(other.column1), column2(other.column2), column3(other.column3)
	{
	}

	//! Assignment operator
	inline AsMatrix44& operator=(const AsMatrix44& other)
	{
		column0 = other.column0;
		column1 = other.column1;
		column2 = other.column2;
		column3 = other.column3;
		return *this;
	}

	//! Get transposed matrix
	inline const AsMatrix44 getTranspose() const
	{
		return AsMatrix44(
			AsVector4(column0.x, column1.x, column2.x, column3.x), AsVector4(column0.y, column1.y, column2.y, column3.y),
			AsVector4(column0.z, column1.z, column2.z, column3.z), AsVector4(column0.w, column1.w, column2.w, column3.w));
	}

	//! Unary minus
	inline const AsMatrix44 operator-() const
	{
		return AsMatrix44(-column0, -column1, -column2, -column3);
	}

	//! Add
	inline const AsMatrix44 operator+(const AsMatrix44& other) const
	{
		return AsMatrix44(column0 + other.column0, column1 + other.column1, column2 + other.column2,
			column3 + other.column3);
	}

	//! Subtract
	inline const AsMatrix44 operator-(const AsMatrix44& other) const
	{
		return AsMatrix44(column0 - other.column0, column1 - other.column1, column2 - other.column2,
			column3 - other.column3);
	}

	//! Scalar multiplication
	inline const AsMatrix44 operator*(float scalar) const
	{
		return AsMatrix44(column0 * scalar, column1 * scalar, column2 * scalar, column3 * scalar);
	}

	friend AsMatrix44 operator*(float, const AsMatrix44&);

	//! Matrix multiplication
	inline const AsMatrix44 operator*(const AsMatrix44& other) const
	{
		// Rows from this <dot> columns from other
		// column0 = transform(other.column0) etc
		return AsMatrix44(transform(other.column0), transform(other.column1), transform(other.column2),
			transform(other.column3));
	}

	// a <op>= b operators

	//! Equals-add
	inline AsMatrix44& operator+=(const AsMatrix44& other)
	{
		column0 += other.column0;
		column1 += other.column1;
		column2 += other.column2;
		column3 += other.column3;
		return *this;
	}

	//! Equals-sub
	inline AsMatrix44& operator-=(const AsMatrix44& other)
	{
		column0 -= other.column0;
		column1 -= other.column1;
		column2 -= other.column2;
		column3 -= other.column3;
		return *this;
	}

	//! Equals scalar multiplication
	inline AsMatrix44& operator*=(float scalar)
	{
		column0 *= scalar;
		column1 *= scalar;
		column2 *= scalar;
		column3 *= scalar;
		return *this;
	}

	//! Equals matrix multiplication
	inline AsMatrix44& operator*=(const AsMatrix44& other)
	{
		*this = *this * other;
		return *this;
	}

	//! Element access, mathematical way!
	inline float operator()(unsigned int row, unsigned int col) const
	{
		return (*this)[col][row];
	}

	//! Element access, mathematical way!
	inline float& operator()(unsigned int row, unsigned int col)
	{
		return (*this)[col][row];
	}

	//! Transform vector by matrix, equal to v' = M*v
	inline const AsVector4 transform(const AsVector4& other) const
	{
		return column0 * other.x + column1 * other.y + column2 * other.z + column3 * other.w;
	}

	//! Transform vector by matrix, equal to v' = M*v
	inline const AsVector3 transform(const AsVector3& other) const
	{
		return transform(AsVector4(other, 1.0f)).getXYZ();
	}

	//! Rotate vector by matrix, equal to v' = M*v
	inline const AsVector4 rotate(const AsVector4& other) const
	{
		return column0 * other.x + column1 * other.y + column2 * other.z; // + column3*0;
	}

	//! Rotate vector by matrix, equal to v' = M*v
	inline const AsVector3 rotate(const AsVector3& other) const
	{
		return rotate(AsVector4(other, 1.0f)).getXYZ();
	}

	inline const AsVector3 getBasis(int num) const
	{
		return (&column0)[num].getXYZ();
	}

	inline const AsVector3 getPosition() const
	{
		return column3.getXYZ();
	}

	inline void setPosition(const AsVector3& position)
	{
		column3.x = position.x;
		column3.y = position.y;
		column3.z = position.z;
	}

	inline const float* front() const
	{
		return &column0.x;
	}

	inline AsVector4& operator[](unsigned int num)
	{
		return (&column0)[num];
	}
	inline const AsVector4& operator[](unsigned int num) const
	{
		return (&column0)[num];
	}

	inline void scale(const AsVector4& p)
	{
		column0 *= p.x;
		column1 *= p.y;
		column2 *= p.z;
		column3 *= p.w;
	}

	inline const AsMatrix44 inverseRT(void) const
	{
		AsVector3 r0(column0.x, column1.x, column2.x), r1(column0.y, column1.y, column2.y),
			r2(column0.z, column1.z, column2.z);

		return AsMatrix44(r0, r1, r2, -(r0 * column3.x + r1 * column3.y + r2 * column3.z));
	}

	inline bool isFinite() const
	{
		return column0.isFinite() && column1.isFinite() && column2.isFinite() && column3.isFinite();
	}

	inline AsTransform toTransform()
	{
		AsTransform transform;

		AsVector3 column3_0 = AsVector3(column0.x, column0.y, column0.z);
		AsVector3 column3_1 = AsVector3(column1.x, column1.y, column1.z);
		AsVector3 column3_2 = AsVector3(column2.x, column2.y, column2.z);

		transform.q = AsMatrix33(column3_0, column3_1, column3_2).toQuaternion();
		transform.p = AsVector3(column3.x, column3.y, column3.z);

		return transform;
	}
};

#endif