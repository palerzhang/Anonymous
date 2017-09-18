#ifndef _ANONYMOUS_EMPTY_OBJECT_H_
#define _ANONYMOUS_EMPTY_OBJECT_H_

#include "AsObject.h"

/*
\ Empty Object, nothing need to render
*/
class AsEmptyObject : public AsObject
{
public:
	AsEmptyObject(string name = "New Object", AsObject * parent = nullptr)
		: AsObject(name, parent){}

protected:
	/*
	\ Render the object with @interpolation
	\ Note that @interpolation can be unused
	*/
	void Render(float interpolation) override
	{
		// Nothing
	}
	/*
	\ Compile the children
	\ Empty object is un-drawable
	*/
	void PrepareAndCompileShaders() override
	{
		// Nothing
	}
};

#endif