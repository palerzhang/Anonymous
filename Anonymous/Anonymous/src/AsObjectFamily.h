#ifndef _ANONYMOUS_OBJECT_FAMILY_H_
#define _ANONYMOUS_OBJECT_FAMILY_H_

#include <unordered_map>

using namespace std;

class AsObject;

typedef unordered_map<string, AsObject *> AsObjectMap;
typedef unordered_map<string, AsObject *>::iterator AsObjectMapIter;	
typedef pair<string, AsObject *> AsObjectMapPair;

/*
\ An object's family is to manage its children and parent
\ Note that programmer can not access this instance directly
\	from the object. 
\ But programmer can access @mChildren and @mParent in this.
*/
class AsObjectFamily
{
	/*
	\ Children of this object
	*/
	AsObjectMap mChildren;
	/*
	\ Parent of this object
	*/
	AsObject * mParent;

public:
	/*
	\ Constructor
	*/
	AsObjectFamily(AsObject * parent = nullptr);
	~AsObjectFamily();
	/*
	\ Get the map of children of the object
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
	\ Attach the object to @parent
	*/
	void Attach(AsObject * parent);
	/*
	\ Release this instance
	*/
	void Release();
};

#endif