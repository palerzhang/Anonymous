#ifndef _ANONYMOUS_POLYGON_H_
#define _ANONYMOUS_POLYGON_H_

#include "AsObject.h"
#include "AsVertexData.h"
#include "AsShader.h"
#include "Foundation\AsColor.h"

/*
\ The polygon class.
\ Polygon is usually used in 2D (3D is ok)
\ Draw polygon along vertices one by one
*/

class AsPolygon : public AsObject
{
public:
	/*
	\ Vertex of the polygon
	\ We do not suggest to change the contents of it
	\	as this may reduce the performance 
	*/
	AsVertexData * mVertex;
	/*
	\ Color
	*/
	AsColor mColor;
	/*
	\ Shader of this polygon
	*/
	AsShader * mShader;
	/*
	\ Constructor
	*/
	AsPolygon(string name = "New Object", AsObject * parent = nullptr);
	/*
	\ Deconstructor
	*/
	~AsPolygon();
	/*
	\ Free the memory
	*/
	void Release() override;
	/*
	\ Render the shape
	*/
	void Render(float interpolation) override;
};

#endif