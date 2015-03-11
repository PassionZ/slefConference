#ifndef __AVMTSCONNECTION_H__
#define __AVMTSCONNECTION_H__

#include "AVMTSocketTCP.h"
#include "AVMTSFrame.h"
#include "../libHPBaseclass/AVBufferPool.h"
#include "AVIOEvent.h"
#include "VIDEC_Header.h"

class AFX_EXT_CLASS AVMTSConnection
	: public AVIOEvent
	, public AVMTSFrame
	, public AVBufferPool
{
public:
	AVMTSConnection(SOCKET hSocket);
	~AVMTSConnection(void);
public:
	virtual void ReleaseConnections(void);
	virtual bool OnRead(void);
	virtual bool OnWrite(void);
	virtual void OnError(void);

	virtual bool WantReading(void);
	virtual bool WantWriting(void);
	virtual int SendData(const char*pData,int nLen);
	virtual void OnDisconnected(void);
	operator SOCKET(void){return m_AVMTSocketTCP;};

	virtual unsigned long GetLastReadInterval(void);
	virtual bool IsExpired(void);
protected:
	AVMTSocketTCP				m_AVMTSocketTCP;
	bool						m_bDisconnected;
	unsigned long				m_ulWriteTimestamp;
	unsigned long				m_ulReadTimestamp;
};


class AVMTTCPClientNotify
{
public:
	AVMTTCPClientNotify(void){};
	virtual~AVMTTCPClientNotify(void){};
public:
	virtual void OnAVMTTCPClientNotifyReceivedFrame(const char*pFrameData,int nLen)=0;
	virtual void OnAVMTTCPClientNotifyDisconnected(void)=0;
};

class AVMTTCPClient
	: public AVMTSConnection
{
public:
	AVMTTCPClient(AVMTTCPClientNotify&rNotify,SOCKET hSocket)
		: AVMTSConnection(hSocket)
		, m_rNotify(rNotify)
	{
	};
	virtual~AVMTTCPClient(void){};
public:
	virtual void OnReceivedFrame(const char*pFrameData,int nLen)
	{
		m_rNotify.OnAVMTTCPClientNotifyReceivedFrame(pFrameData,nLen);
	}
	virtual void OnDisconnected(void)
	{
		m_rNotify.OnAVMTTCPClientNotifyDisconnected();
		AVMTSConnection::OnDisconnected();
	}

	int FlushToKeyFrame(void)
	{
		int nCount=0;
		AVAutoLock l(&m_AVCritSec);
		while (m_listDataBuffer.size()>0)
		{
			AVDataBuffer*pAVDataBuffer=(AVDataBuffer*)m_listDataBuffer.back();
			void*pData=pAVDataBuffer->GetData();
			bool bKeyFrame=VIDEC_HEADER_EXT_GET_KEYFRAME((void*)pData);
			if (bKeyFrame)
			{
				break;
			}
			else
			{
				m_listDataBuffer.pop_back();
				delete pAVDataBuffer;
				pAVDataBuffer=NULL;

				nCount++;
			}
		}

		return nCount;
	}
	unsigned long GetBufferedTimeMS(void)
	{
		AVAutoLock l(&m_AVCritSec);
		if (m_listDataBuffer.size()>1)
		{
			AVDataBuffer*pAVDataBufferBack=(AVDataBuffer*)m_listDataBuffer.back();
			void*pDataBack=pAVDataBufferBack->GetData();
			unsigned long ulTimestampBack=VIDEC_HEADER_EXT_GET_TIMESTAMP((void*)pDataBack);
			AVDataBuffer*pAVDataBufferFront=(AVDataBuffer*)m_listDataBuffer.front();
			void*pDataFront=pAVDataBufferFront->GetData();
			unsigned long ulTimestampFront=VIDEC_HEADER_EXT_GET_TIMESTAMP((void*)pDataFront);
			return (ulTimestampBack-ulTimestampFront);
		}

		return 0;
	}

protected:
	AVMTTCPClientNotify&	m_rNotify;
};

#endif