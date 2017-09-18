#ifndef _ANONYMOUS_OBJECT_H_
#define _ANONYMOUS_OBJECT_H_

#include <string>
#include "AsObjectFamily.h"
#include "Foundation\AsTransform.h"

using namespace std;

/*
\ Base class of object
*/
class AsObject
{
protected:
	/*
	\ The transform under world space
	\ Always use this @mWorldSpace to transform vertex
	\  Before use @mWorldSpace, always re-calculate it
	\	with @mWorldSpace = parent.@mWorldSpace.transform(@mTransform)
	\ Note that, our render frequency is less than update
	\	So we do re-calculation beform render
	*/
	AsTransform mWorldSpace;
	/*
	\ Manager of this object's parent and children
	*/
	AsObjectFamily * mFamily;

protected:
	/*
	\ Get the unique name in its parent's children with @name
	*/
	virtual string UniqueName(string name);

public:
	/*
	\ Name of this object
	*/
	string mName;
	/*
	\ The transform under its parent
	*/
	AsTransform mTransform;
	/*
	\ The @parent must be specified
	\ The @name can use default
	*/
	AsObject(string name = "New Object", AsObject * parent = nullptr);
	~AsObject();
	/*
	\ Get the @mWorldSpace of this object
	*/
	const AsTransform & GetWorldSpace();
	/*
	\ Get the map of children of this object
	*/
	AsObjectMap & GetChildren();
	/*
	\ Get the object with @name in children
	*/
	AsObject * FindChild(const string & name);
	/*
	\ Get the parent of this object
	*/
	AsObject * GetParent();
	/*
	\ Attach this object to @parent
	\ Besides, change the transform
	\ This object is the child of @parent
	*/
	void Attach(AsObject * parent);
	/*
	\ Un-attach this object from its parent
	\ One important task is to reset its @mTransform and @mWorldSpace
	\ Equally, to the root
	\ @mTransform is set to parent.@mWorldSpace.transform(@mTransform)
	\ @mWorldSpace is the same as @mTransform
	*/
	void Unattach();
	/*
	\ Set the position of this object
	*/
	inline void SetPosition(float x, float y, float z);
	/*
	\ Set the rotation around x-axis, y-axis, z-axis
	*/
	void SetRotation(float x, float y, float z);
	/*
	\ Remove all children objects under this object
	*/
	virtual void RemoveChildren();
	/*
	\ Copy this object to @dst
	*/
	virtual void Copy(AsObject * dst);
	/*
	\ Release the memory of this object, besides its children
	*/
	virtual void Release();
	/*
	\ Update the object's state
	\ i.e. @mTransform
	*/
	virtual void Update(float dt) { AS_UNUSED(dt); };
	/*
	\ Render the object with @interpolation
	\ Note that @interpolation can be unused
	\ Must be specified
	*/
	virtual void Render(float interpolation) = 0;
};

#endif