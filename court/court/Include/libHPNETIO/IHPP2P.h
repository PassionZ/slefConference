//IHPP2P.h
#ifndef __IHPP2P_H__
#define __IHPP2P_H__


class IHPP2PNotify
{
public:
	IHPP2PNotify(void){};
	virtual~IHPP2PNotify(void){};
public:
	virtual void OnIHPP2PNotifySendData(char*pData,int nLen,unsigned long ulIP,unsigned short usPort)=0;
};

class IHPP2P
{
public:
	IHPP2P(void){};
	virtual~IHPP2P(void){};
public:
	virtual void ReleaseConnections(void)=0;
	virtual bool SendP2PCommand(unsigned long ulP2PID,unsigned long ulIP,unsigned short usPort)=0;
	virtual bool IsP2PConnected(unsigned long ulP2PID,unsigned short&usPort)=0;
	virtual void DoCheck(void)=0;
	virtual void OnReceivedP2PData(char*pData,int nLen,unsigned long ulIP,unsigned short usPort)=0;
	virtual void OnReceivedACKData(char*pData,int nLen,unsigned long ulIP,unsigned short usPort)=0;
	virtual unsigned long GetP2PID(void)=0;
};

AFX_EXT_CLASS IHPP2P*CreateIHPP2P(IHPP2PNotify&rIHPP2PNotify);

#endif