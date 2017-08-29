#ifndef _ANONYMOUS_MATRIX33_H_
#define _ANONYMOUS_MATRIX33_H_

#include "AsVector3.h"
#include "AsQuaternion.h"

/*!
\brief 3x3 matrix class

Some clarifications, as there have been much confusion about matrix formats etc in the past.

Short:
- Matrix have base vectors in columns (vectors are column matrices, 3x1 matrices).
- Matrix is physically stored in column major format
- Matrices are concaternated from left

Long:
Given three base vectors a, b and c the matrix is stored as

|a.x b.x c.x|
|a.y b.y c.y|
|a.z b.z c.z|

Vectors are treated as columns, so the vector v is

|x|
|y|
|z|

And matrices are applied _before_ the vector (pre-multiplication)
v' = M*v

|x'|   |a.x b.x c.x|   |x|   |a.x*x + b.x*y + c.x*z|
|y'| = |a.y b.y c.y| * |y| = |a.y*x + b.y*y + c.y*z|
|z'|   |a.z b.z c.z|   |z|   |a.z*x + b.z*y + c.z*z|


Physical storage and indexing:
To be compatible with popular 3d rendering APIs (read D3d and OpenGL)
the physical indexing is

|0 3 6|
|1 4 7|
|2 5 8|

index = column*3 + row

which in C++ translates to M[column][row]

The mathematical indexing is M_row,column and this is what is used for _-notation
so _12 is 1st row, second column and operator(row, column)!

*/

class AsMatrix33
{
public:
	// Data, see above for format!
	AsVector3 column0, column1, column2; // the three base vectors

	//! Default constructor
	inline AsMatrix33()
	{
	}

	//! identity constructor
	inline AsMatrix33(AsIDENTITY r)
		: column0(1.0f, 0.0f, 0.0f), column1(0.0f, 1.0f, 0.0f), column2(0.0f, 0.0f, 1.0f)
	{
		AS_UNUSED(r);
	}

	//! zero constructor
	inline AsMatrix33(AsZERO r) : column0(0.0f), column1(0.0f), column2(0.0f)
	{
		AS_UNUSED(r);
	}

	//! Construct from three base vectors
	AsMatrix33(const AsVector3& col0, const AsVector3& col1, const AsVector3& col2)
		: column0(col0), column1(col1), column2(col2)
	{
	}

	//! constructor from a scalar, which generates a multiple of the identity matrix
	explicit inline AsMatrix33(float r)
		: column0(r, 0.0f, 0.0f), column1(0.0f, r, 0.0f), column2(0.0f, 0.0f, r)
	{
	}

	//! Construct from float[9]
	explicit inline AsMatrix33(float values[])
		: column0(values[0], values[1], values[2])
		, column1(values[3], values[4], values[5])
		, column2(values[6], values[7], values[8])
	{
	}

	//! Construct from a quaternion
	explicit inline AsMatrix33(const AsQuaternion& q)
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

		column0 = AsVector3(1.0f - yy - zz, xy + zw, xz - yw);
		column1 = AsVector3(xy - zw, 1.0f - xx - zz, yz + xw);
		column2 = AsVector3(xz + yw, yz - xw, 1.0f - xx - yy);
	}

	//! Copy constructor
	inline AsMatrix33(const AsMatrix33& other)
		: column0(other.column0), column1(other.column1), column2(other.column2)
	{
	}

	//! Assignment operator
	inline AsMatrix33& operator=(const AsMatrix33& other)
	{
		column0 = other.column0;
		column1 = other.column1;
		column2 = other.column2;
		return *this;
	}

	//! Construct from diagonal, off-diagonals are zero.
	inline static const AsMatrix33 createDiagonal(const AsVector3& d)
	{
		return AsMatrix33(AsVector3(d.x, 0.0f, 0.0f), AsVector3(0.0f, d.y, 0.0f), AsVector3(0.0f, 0.0f, d.z));
	}

	/**
	\brief returns true if the two matrices are exactly equal
	*/
	inline bool operator==(const AsMatrix33& m) const
	{
		return column0 == m.column0 && column1 == m.column1 && column2 == m.column2;
	}

	//! Get transposed matrix
	inline const AsMatrix33 getTranspose() const
	{
		const AsVector3 v0(column0.x, column1.x, column2.x);
		const AsVector3 v1(column0.y, column1.y, column2.y);
		const AsVector3 v2(column0.z, column1.z, column2.z);

		return AsMatrix33(v0, v1, v2);
	}

	//! Get the real inverse
	inline const AsMatrix33 getInverse() const
	{
		const float det = getDeterminant();
		AsMatrix33 inverse;

		if (det != 0)
		{
			const float invDet = 1.0f / det;

			inverse.column0.x = invDet * (column1.y * column2.z - column2.y * column1.z);
			inverse.column0.y = invDet * -(column0.y * column2.z - column2.y * column0.z);
			inverse.column0.z = invDet * (column0.y * column1.z - column0.z * column1.y);

			inverse.column1.x = invDet * -(column1.x * column2.z - column1.z * column2.x);
			inverse.column1.y = invDet * (column0.x * column2.z - column0.z * column2.x);
			inverse.column1.z = invDet * -(column0.x * column1.z - column0.z * column1.x);

			inverse.column2.x = invDet * (column1.x * column2.y - column1.y * column2.x);
			inverse.column2.y = invDet * -(column0.x * column2.y - column0.y * column2.x);
			inverse.column2.z = invDet * (column0.x * column1.y - column1.x * column0.y);

			return inverse;
		}
		else
		{
			return AsMatrix33(AsIdentity);
		}
	}

	//! Get determinant
	inline float getDeterminant() const
	{
		return column0.dot(column1.cross(column2));
	}

	//! Unary minus
	inline const AsMatrix33 operator-() const
	{
		return AsMatrix33(-column0, -column1, -column2);
	}

	//! Add
	inline const AsMatrix33 operator+(const AsMatrix33& other) const
	{
		return AsMatrix33(column0 + other.column0, column1 + other.column1, column2 + other.column2);
	}

	//! Subtract
	inline const AsMatrix33 operator-(const AsMatrix33& other) const
	{
		return AsMatrix33(column0 - other.column0, column1 - other.column1, column2 - other.column2);
	}

	//! Scalar multiplication
	inline const AsMatrix33 operator*(float scalar) const
	{
		return AsMatrix33(column0 * scalar, column1 * scalar, column2 * scalar);
	}

	friend AsMatrix33 operator*(float, const AsMatrix33&);

	//! Matrix vector multiplication (returns 'this->transform(vec)')
	inline const AsVector3 operator*(const AsVector3& vec) const
	{
		return transform(vec);
	}

	// a <op>= b operators

	//! Matrix multiplication
	inline const AsMatrix33 operator*(const AsMatrix33& other) const
	{
		// Rows from this <dot> columns from other
		// column0 = transform(other.column0) etc
		return AsMatrix33(transform(other.column0), transform(other.column1), transform(other.column2));
	}

	//! Equals-add
	inline AsMatrix33& operator+=(const AsMatrix33& other)
	{
		column0 += other.column0;
		column1 += other.column1;
		column2 += other.column2;
		return *this;
	}

	//! Equals-sub
	inline AsMatrix33& operator-=(const AsMatrix33& other)
	{
		column0 -= other.column0;
		column1 -= other.column1;
		column2 -= other.column2;
		return *this;
	}

	//! Equals scalar multiplication
	inline AsMatrix33& operator*=(float scalar)
	{
		column0 *= scalar;
		column1 *= scalar;
		column2 *= scalar;
		return *this;
	}

	//! Equals matrix multiplication
	inline AsMatrix33& operator*=(const AsMatrix33& other)
	{
		*this = *this * other;
		return *this;
	}

	//! Element access, mathematical way!
	inline float& operator()(unsigned int row, unsigned int col)
	{
		return (*this)[col][row];
	}

	// Transform etc

	//! Transform vector by matrix, equal to v' = M*v
	inline const AsVector3 transform(const AsVector3& other) const
	{
		return column0 * other.x + column1 * other.y + column2 * other.z;
	}

	//! Transform vector by matrix transpose, v' = M^t*v
	inline const AsVector3 transformTranspose(const AsVector3& other) const
	{
		return AsVector3(column0.dot(other), column1.dot(other), column2.dot(other));
	}

	inline const float* front() const
	{
		return &column0.x;
	}

	inline AsVector3& operator[](unsigned int num)
	{
		return (&column0)[num];
	}
	inline const AsVector3& operator[](unsigned int num) const
	{
		return (&column0)[num];
	}
};

inline AsQuaternion::AsQuaternion(const AsMatrix33& m)
{
	if (m.column2.z < 0)
	{
		if (m.column0.x > m.column1.y)
		{
			float t = 1 + m.column0.x - m.column1.y - m.column2.z;
			*this = AsQuaternion(t, m.column0.y + m.column1.x, m.column2.x + m.column0.z, m.column1.z - m.column2.y) *
				(0.5f / AsSqrt(t));
		}
		else
		{
			float t = 1 - m.column0.x + m.column1.y - m.column2.z;
			*this = AsQuaternion(m.column0.y + m.column1.x, t, m.column1.z + m.column2.y, m.column2.x - m.column0.z) *
				(0.5f / AsSqrt(t));
		}
	}
	else
	{
		if (m.column0.x < -m.column1.y)
		{
			float t = 1 - m.column0.x - m.column1.y + m.column2.z;
			*this = AsQuaternion(m.column2.x + m.column0.z, m.column1.z + m.column2.y, t, m.column0.y - m.column1.x) *
				(0.5f / AsSqrt(t));
		}
		else
		{
			float t = 1 + m.column0.x + m.column1.y + m.column2.z;
			*this = AsQuaternion(m.column1.z - m.column2.y, m.column2.x - m.column0.z, m.column0.y - m.column1.x, t) *
				(0.5f / AsSqrt(t));
		}
	}
}

#endif