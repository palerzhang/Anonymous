#ifndef _ANONYMOUS_VERTEX_DATA_H_
#define _ANONYMOUS_VERTEX_DATA_H_

typedef unsigned int AsVertexFlag;
typedef unsigned int AsUint;

// Position of vertex
#define AS_POSITION		1 << 0
// Normal of vertex
#define AS_NORMAL		1 << 1

class AsVertexData
{
	/*
	\ @mFlag shows that which part of values is stored
	\ This must be specified while create the instance
	\ Note that this cannot be changed
	*/
	AsVertexFlag mFlag;

public:
	/*
	\ Array that store the position, color and normal of a vertex information
	\ The position, color and normal of a vertex are stored one by one
	\ i.e. 3d position, rgba color and normal
	\ |x|y|z|nx|ny|nz|
	\ | pos | normal |
	\ |    vertex    |
	*/
	float * mData;
	/*
	\ Count of the vertices
	*/
	AsUint mCount;
	/*
	\ Constructor of @AsVertexData, must specified data flag
	*/
	AsVertexData(AsVertexFlag flag);
	/*
	\ Deconstructor
	*/
	~AsVertexData();
	/*
	\ Allocate memory of @mData and @mSingleColor
	\ according to @num and @mFlag
	*/
	void Allocate(int num);
	/*
	\ Load data
	\ @position: the position of vertices
	\ @normal: the normal of vertices
	\ Note that position must be specified.
	*/
	void LoadData(float * position, float * normal);
	/*
	\ Free the memory
	*/
	void Release();	
};

#endif