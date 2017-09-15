#ifndef _ANONYMOUS_POLYGON_H_
#define _ANONYMOUS_POLYGON_H_

#include "AsObject.h"
#include "AsVertexData.h"
#include "AsShader.h"

/*
\ The polygon class.
\ Polygon is usually used in 2D (3D is ok)
\ Draw polygon along vertices one by one
\ 1. Use constructor to create an instance
		But the memory of arrays is not allocated yet
\ 2. Allocate memory
\ 3. Set elements in arrays
\ 4. Free the memory
*/

class AsPolygon : public AsObject
{
protected:
	/*
	\ Vertex of the polygon
	*/
	AsVertexData * mVertex;
	/*
	\ Shader of this polygon
	*/
	AsShader * mShader;
};

#endif