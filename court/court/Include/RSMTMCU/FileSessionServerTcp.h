#ifndef FileSESSIONSERVERTCP_H_
#define FileSESSIONSERVERTCP_H_

#include "FileSession.h"
#include "../libHPNETIO/AVMTSConnection.h"


class CFileSessionServerTcp 
	: public CFileSession
	, public AVMTSConnection
{
public:
	CFileSessionServerTcp(CFileChannel&rChannel, SOCKET hSocket);
	virtual ~CFileSessionServerTcp(void);

public:
	virtual void ReleaseConnections(void);
	
	virtual void OnReceivedFrame(const char*pFrameData,int nLen);  // inout data

	virtual void OnReceivedDataFromChannel(const char*pData,int nLen); // outin data
	virtual bool IsDisconnected(void);

protected:
	unsigned char	m_ucBufferEmptyCount;
};

#endif
