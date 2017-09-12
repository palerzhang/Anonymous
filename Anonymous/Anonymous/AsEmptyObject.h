#ifndef _ANONYMOUS_EMPTY_OBJECT_H_
#define _ANONYMOUS_EMPTY_OBJECT_H_

#include "AsObject.h"

/*
\ Empty Object, nothing need to render
*/
class AsEmptyObject : public AsObject
{
public:
	AsEmptyObject(AsObject * parent, string name = "New Object")
		: AsObject(parent, name){}
	~AsEmptyObject(){ Release(); }
	/*
	\ Render the object with @interpolation
	\ Note that @interpolation can be unused
	*/
	virtual void Render(float interpolation) override
	{
		AsObjectMap children = GetChildren();
		AsObjectMapIter iter;
		for (iter = children.begin(); iter != children.end(); iter++)
			iter->second->Render(interpolation);
	}
};

#endif