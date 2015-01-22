#ifndef __DESKTOPSESSION_H__
#define __DESKTOPSESSION_H__

#include "../DataDefine/AVMTMCUClient.h"


class AFX_EXT_CLASS CDesktopChannel;
class AFX_EXT_CLASS CDesktopSession
{
public:
	CDesktopSession(CDesktopChannel&rChannel, bool bClient);
	virtual ~CDesktopSession(void);

public:
	virtual bool Connect(void);
	virtual void ReleaseConnections(void);

	virtual void OnReceivedDataFromChannel(const char*pData,int nLen)=0;
	virtual bool IsDisconnected(void)=0;
	virtual unsigned long GetBufferingFrameCount(void)=0;

	virtual void SendDataToChannel(const char*pData,int nLen);

	unsigned long GetChannelID(void);
	unsigned long GetSessionID(void);

	bool IsClient() { return m_bClient; }
	bool IsSource() { return m_bSource; }
	void SetSource(bool bSource) { m_bSource = bSource; }

	// sink
	bool IsEnable(void);
	//bool IsRequestKeyFrame(void);

	virtual void Reset() = 0;
	void OnReceivedDirectionAck(void);
	bool GetSource() {
		return m_bSource;
	}
	bool GetDirectionAck() {
		return m_bDirectionAck;
	}
	bool GetEnable() {
		return m_bEnable;
	}
	CDesktopChannel& GetChannel() {
		return m_rChannel;
	}

protected:
	CDesktopChannel&			m_rChannel;
	unsigned long				m_ulSessionID;

	bool						m_bClient; //
	bool						m_bSource; // true is source,or is sink

	unsigned char				m_ucKeepAliveCount;

	// sink
	bool						m_bEnable;
	bool						m_bDirectionAck;
	//bool						m_bRequestKeyFrame;

	// source
	//bool						m_bIsEnable;
};

#endif
