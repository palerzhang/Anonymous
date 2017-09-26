#include "AsObject.h"
#include "Foundation\AsString.h"

string AsObject::UniqueName(string name)
{
	if (nullptr == mFamily)
		return name;
	AsObjectMap brothers = GetParent()->GetChildren();
	AsObjectMapIter iter;
	int cnt = 0;
	for (iter = brothers.begin(); iter != brothers.end(); ++iter)
	{
		if (iter->first == name)
			cnt++;
	}
	if (cnt > 0)
		name = name + "(" + AsParse(cnt) + ")";
	return name;
}

AsObject::AsObject(string name, AsObject * parent)
{
	mTransform = AsTransform(AsIdentity);
	mWorldSpace = AsTransform(AsIdentity);
	mFamily = new AsObjectFamily(parent);;
	mName = name;
	// If the parent is specified, then attach it
	if (nullptr != parent)
		Attach(parent);
}

AsObject::~AsObject()
{
	Release();
}

const AsTransform & AsObject::GetWorldSpace()
{
	return mWorldSpace;
}

AsObjectMap & AsObject::GetChildren()
{
	return mFamily->GetChildren();
}

AsObject * AsObject::FindChild(const string & name)
{
	return mFamily->FindChild(name);
}

AsObject * AsObject::GetParent()
{
	return mFamily->GetParent();
}

void AsObject::Attach(AsObject * parent)
{
	// If no @parent is specified, attach abort
	if (nullptr == parent)
		return;
	// If this object has a family, that is, not a new object
	//	un-attach this object from its parent, and set the @parent
	//		to @mFamily
	// Otherwise, create a new AsObjectFamily instance
	if (nullptr != mFamily)
	{
		Unattach();
		mFamily->Attach(parent);
	}
	else
		mFamily = new AsObjectFamily(parent);
	// unique the name when attach
	mName = UniqueName(mName);

	// add this object ot parent's children list
	parent->GetChildren().insert(AsObjectMapPair(mName, this));
	// set transform into parent transform
	mTransform = parent->GetWorldSpace().transformInv(mTransform);
}

void AsObject::Unattach()
{
	AsObject * parent = GetParent();
	// If no parent, need not un-attach
	if (nullptr == parent)
		return;
	// Erase this object from its parent
	parent->GetChildren().erase(mName);
	// Reset the transform
	mTransform = parent->GetWorldSpace().transform(mTransform);
	mWorldSpace = mTransform;
}

void AsObject::SetPosition(float x, float y, float z)
{
	mTransform.p = AsVector3(x, y, z);
}

void AsObject::SetRotation(float x, float y, float z)
{
	mTransform.q = AsQuaternion(AsVector3(x, y, z));
}

void AsObject::RemoveChildren()
{
	// Release @mFamily
	if (nullptr != mFamily)
		delete mFamily;
}

void AsObject::Copy(AsObject * dst)
{
	// TODO
}

void AsObject::Release()
{
	// Release @mFamily
	if (nullptr != mFamily)
	{
		delete mFamily;
		mFamily = nullptr;
	}
}

void AsObject::_Update(float dt) 
{ 
	Update(dt);

	AsObjectMap children = GetChildren();
	AsObjectMapIter iter;
	for (iter = children.begin(); iter != children.end(); iter++)
		iter->second->_Update(dt);
}

void AsObject::_Render(float interpolation)
{
	Render(interpolation);

	AsObjectMap children = GetChildren();
	AsObjectMapIter iter;
	for (iter = children.begin(); iter != children.end(); iter++)
		iter->second->_Render(interpolation);
}

void AsObject::_PrepareAndCompileShaders()
{
	PrepareAndCompileShaders();

	AsObjectMap children = GetChildren();
	AsObjectMapIter iter;
	for (iter = children.begin(); iter != children.end(); iter++)
		iter->second->_PrepareAndCompileShaders();
}