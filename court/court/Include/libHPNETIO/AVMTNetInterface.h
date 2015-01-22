// AVMTNetInterface.h: interface for the AVMTNetInterface class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __AVMTNETINTERFACE_H__
#define __AVMTNETINTERFACE_H__

#include "AVMTSocket.h"
#include <list>
class AVMTNetInterface;

typedef std::list<AVMTNetInterface*>	ListAVMTNetInterface;

class AFX_EXT_CLASS AVMTNetInterface  
{
public:
	AVMTNetInterface(const char*cszDottedDecimal,const char*cszmac="");
	virtual ~AVMTNetInterface(void);
public:
	const char*GetDottedDecimal(void);
	const char*GetMACAddress(void);
	static void Interfaces(ListAVMTNetInterface&rListAVMTNetInterface);
protected:
	char		m_szDottedDecimal[128];
	char		m_szmac[32];

};

#endif 