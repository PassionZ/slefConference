//libHPNETIO.h
#ifndef __libHPNETIO_H__
#define __libHPNETIO_H__

#include "AVMTSocket.h"

class IHPTCPIONotify
{
public:
	IHPTCPIONotify(void){};
	virtual~IHPTCPIONotify(void){};
public:
	virtual bool OnIHPTCPIONotifyConnected(SOCKET hSocket,unsigned long ulType,const void*pData,int nLen)=0;
};

class IHPTCPIO
{
public:
	IHPTCPIO(void){};
	virtual~IHPTCPIO(void){};
public:
	virtual void ReleaseConnections(void)=0;
	virtual unsigned short GetTCPPort(void)=0;
	virtual void DoCheck(void)=0;
};

AFX_EXT_CLASS IHPTCPIO*CreateIHPTCPIO(IHPTCPIONotify&rIHPTCPIONotify,unsigned short usTCPPort);

class IHPUDPIONotify
{
public:
	IHPUDPIONotify(void){};
	virtual~IHPUDPIONotify(void){};
public:
	virtual void OnIHPUDPIONotifyReceivedData(const char*pData,int nLen,SOCKET hSocket,unsigned long ulIP,unsigned short usPort)=0;
};

class IHPUDPIO
{
public:
	IHPUDPIO(void){};
	virtual~IHPUDPIO(void){};
public:
	virtual void ReleaseConnections(void)=0;
	virtual bool IsLocalIP(unsigned long ulIP)=0;
	virtual SOCKET GetSocketHandle(unsigned long ulIP)=0;
	virtual unsigned short GetUDPPort(void)=0;
};

AFX_EXT_CLASS IHPUDPIO*CreateIHPUDPIO(IHPUDPIONotify&rIHPUDPIONotify,unsigned short usUDPPort,unsigned char nTos=160);

typedef bool (*HPNETIOLOOPCALLBACK)(void*pUserData);
AFX_EXT_CLASS void SetHPNETIOLoopCallback(HPNETIOLOOPCALLBACK pHPNETIOLoopCallback,void*pData);


//取网络类型个数
AFX_EXT_CLASS int GetNetworkTypeCount(void);
//根据网络类型的序号取网络类型的名称
AFX_EXT_CLASS int GetNetworkTypeName(int nType,char*szName,int nMaxCount);
//设置网络类型及其带宽
AFX_EXT_CLASS void SetNetworkType(int nType,int nBandwidth);

//根据网络类型的序号取其缺省带宽
AFX_EXT_CLASS int GetDefaultBandwidth(int nType);
//根据网络类型的序号取其带宽取值范围
AFX_EXT_CLASS void GetDefaultBandwidthRange(int nType,int&nMinBandwidth,int&nMaxBandwidth);

#endif