#ifndef RSTCPCLIENT_H_
#define RSTCPCLIENT_H_

#include "../libHPNETIO/AVMTConnectTCP.h"
#include "../libHPNETIO/AVMTSocketClient.h"
#include "../libHPNETIO/AVMTSConnection.h"
#include "RSMTMCUManager.h"
#include "TcpClient.h"

#include "HMTConnectTCP.h"


class AFX_EXT_CLASS CRSTcpClient : 
	//public AVMTConnectTCPNotify, 
	public AVMTSocketClientNotify, 
	public AVMTTCPClientNotify  

	, public HMTConnectTCPNotify
{
public:
	CRSTcpClient(RSMTMCUManager &rNotify);
	virtual ~CRSTcpClient();

	virtual bool Connect(const std::string&/*unsigned long*/ ulIP,unsigned short usPort,const std::string &/*unsigned long*/  ulInterface);
	virtual void ReleaseConnections(void);

	void OnAVMTConnectTCPNotifyConnected(/*AVMTConnectTCP*/HMTConnectTCP*pAVMTConnectTCP,SOCKET hSocket);
	void OnAVMTConnectTCPNotifyFailed(/*AVMTConnectTCP*/HMTConnectTCP*pAVMTConnectTCP);
	
	bool OnAVMTSocketClientNotifyConnected(AVMTSocketClient*pAVMTSocketClient,SOCKET hSocket,unsigned long ulType,const void*pData,int nLen);
	void OnAVMTSocketClientNotifyFailed(AVMTSocketClient*pAVMTSocketClient,unsigned long ulType);

	void OnAVMTTCPClientNotifyReceivedFrame(const char*pFrameData,int nLen);
	void OnAVMTTCPClientNotifyDisconnected(void);

	bool IsDisconnected(void);
	int SendData(const void*pData,int nLen);

protected:
	unsigned char			m_ucBufferEmptyCount;
	RSMTMCUManager&			m_rNotify;
	/*AVMTConnectTCP*/HMTConnectTCP*			m_pAVMTConnectTCP;
	AVMTSocketClient*		m_pAVMTSocketClient;
	/*AVMTTCPClient*/CTcpClient*			m_pAVMTTCPClient;
	bool					m_bDisconnected;
};

#endif
