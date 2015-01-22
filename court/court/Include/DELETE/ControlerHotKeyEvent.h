#pragma once
#include <string>
using namespace std;
class IControlerHotKey
{
public:
	IControlerHotKey() {};
	virtual ~IControlerHotKey() {};
	virtual void Release() = 0;
};

class IControlerHotKeyEvent
{
public:
	IControlerHotKeyEvent(){};
	virtual~IControlerHotKeyEvent(){};
};
AFX_EXT_CLASS IControlerHotKey* CreateControlHotKey(IControlerHotKeyEvent *pControlerHotKeyEvent);
