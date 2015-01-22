#ifndef	FileSESSIONCLIENTTCP_H_
#define FileSESSIONCLIENTTCP_H_

#include "FileSession.h"
#include "../libHPNETIO/AVMTConnectTCP.h"
#include "../libHPNETIO/AVMTSocketClient.h"
#include "../libHPNETIO/AVMTSConnection.h"
#include "../DataDefine/AVMTMCUClient.h"

#include "HMTConnectTCP.h"


class CFileSessionClientTcp 
	: public CFileSession
	//, public AVMTConnectTCPNotify
	, public AVMTSocketClientNotify
	, public AVMTTCPClientNotify
	, public ILocalFile

	, public HMTConnectTCPNotify
{
public:
	CFileSessionClientTcp(ILocalFileNotify&rNotify, CFileChannel&rChannel);
	virtual ~CFileSessionClientTcp(void);

public:
	virtual bool Connect(const std::string &/*unsigned long*/ ulPeerMCUIP0,unsigned short usPeerMCUPort);
	virtual void ReleaseConnections(void);

	virtual void OnAVMTConnectTCPNotifyConnected(/*AVMTConnectTCP*/HMTConnectTCP*pAVMTConnectTCP,SOCKET hSocket);
	virtual void OnAVMTConnectTCPNotifyFailed(/*AVMTConnectTCP*/HMTConnectTCP*pAVMTConnectTCP);

	virtual bool OnAVMTSocketClientNotifyConnected(AVMTSocketClient*pAVMTSocketClient,SOCKET hSocket,unsigned long ulType,const void*pData,int nLen);
	virtual void OnAVMTSocketClientNotifyFailed(AVMTSocketClient*pAVMTSocketClient,unsigned long ulType);

	virtual void OnAVMTTCPClientNotifyReceivedFrame(const char*pFrameData,int nLen); // inout data
	virtual void OnAVMTTCPClientNotifyDisconnected(void);

	virtual void OnReceivedDataFromChannel(const char*pData,int nLen); // outin data
	virtual bool IsDisconnected(void);

	//virtual void onFileDataOut(const char*pData,int nLen) {};
	//void processFileData(char * pData,long nLen) {};
	void SetSendFilePath(std::string sFilePath) {};

protected:
	ILocalFileNotify&		m_rNotify;
	/*AVMTConnectTCP*/HMTConnectTCP*				m_pAVMTConnectTCP;
	AVMTSocketClient*			m_pAVMTSocketClient;
	AVCritSec					m_AVCritSecAVMTTCPClient;
	AVMTTCPClient*				m_pAVMTTCPClient;

	bool						m_bDisconnected;

	unsigned char				m_ucKeepAliveCount;
};

#endif
