#ifndef _ANONYMOUS_VERTEX_DATA_H_
#define _ANONYMOUS_VERTEX_DATA_H_

#include <Foundation\AsTypes.h>

enum AsLoadFlag
{
	FLAG_POSITION_ONLY = 0,
	FLAG_POSITION_NORMAL,
	FLAG_NORMAL_POSITION,
	FLAG_POSITION_UV,
	FLAG_POSITION_NORMAL_UV
};

#define ATTRIBUTE_POSITION_POSITION 0
#define ATTRIBUTE_POSITION_NORMAL	1
#define ATTRIBUTE_POSITION_UV		2

class AsVertexData
{
	/*
	\ Vertex Array Object
	*/
	AsUint mVAO;
	/*
	\ Vertex Buffer Object
	*/
	AsUint mVBO;
	/*
	\ Element Buffer Object
	*/
	AsUint mEBO;
	/*
	\ Data loaded
	*/
	bool mLoaded;

public:
	/*
	\ Count of the vertices to draw (using indices)
	*/
	AsUint mCount;
	/*
	\ Constructor of @AsVertexData, must specified data flag
	*/
	AsVertexData();
	/*
	\ Deconstructor
	*/
	~AsVertexData();
	/*
	\ Load data
	\ @data: the data of vertex
	\ @flag: flag tells the function how to read the data
	\ @vsize: the size of vertices (note that not equal to size of @data)
	\ @indices: indices of rendering order (nullptr then use default)
	\ @isize: size of indices
	\ @usage: how to render
	*/
	void LoadData(const float * data, AsLoadFlag flag, AsUint vsize, const AsUint * indices, AsUint isize, AsUint usage);
	/*
	\ Free the memory
	*/
	void Release();	
	/*
	\ Render vertex
	*/
	void RenderSelf(AsUint mode);
};

#endif