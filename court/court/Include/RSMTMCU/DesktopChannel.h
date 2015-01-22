#ifndef __DESKTOPCHANNEL_H__
#define __DESKTOPCHANNEL_H__

#include "DesktopSession.h"
#include "../libHPBaseclass/AVAutoLock.h"
#include <map>


typedef std::map<unsigned long,CDesktopSession*>	MapDesktopSession;

class AFX_EXT_CLASS CDesktopChannel
	//: public IWbDTSNotify
{
public:
	CDesktopChannel(unsigned long ulChannelID);
	virtual ~CDesktopChannel(void);

public:
	bool Connect(void);
	void ReleaseConnections(void);

	unsigned long GetSessionCount(void);
	//bool IsDirty(void);
	//bool IsEmpty(void);
	//void SetChannelID(unsigned long ulChannelID);
	unsigned long GetChannelID(void);
	void OnDataFromSession(unsigned long ulSessionID,const char*pData,int nLen); //
	//void onWbData(unsigned long channelId,char* data,int len);
	void AddSession(CDesktopSession*pSession);
	void RemoveSession(CDesktopSession*pSession);

	bool IsDesktopSinkEnable(void);
	//bool IsRequestKeyFrame(void);
	void OnDesktopChannelData(const char*pData,int nLen); //
	unsigned long GetBufferingFrameCount(void);

	void ClearSession(void);

	bool IsSingle() { return m_bSingle;}
	void SetSingle(bool bDirection) { m_bSingle = bDirection;}
	bool IsFree() { return m_bFree;}
	void SetFree(bool bFree) { m_bFree = bFree;}
	bool IsMatch(unsigned long ulSessionID) {
		return (ulSessionID == m_ulSessionID);
	}
	void SetSession(unsigned long ulSessionID) {
		m_ulSessionID = ulSessionID;
	}

	void SetDelete() {
		m_bDelete = true;
	}
	bool IsDelete() {
		return m_bDelete;
	}

	bool IsVideoSinkEnable(void);
	void Reset();

	void print()
	{
#ifdef _DEBUG
		cout << "CDesktopChannel:" << m_ulSessionID << endl;
#endif
	}

protected:
	unsigned long		m_ulChannelID;
	MapDesktopSession	m_MapSession;
	AVCritSec			m_AVCritSecMapSession;
	//bool				m_bDirty;
	//IWbDTS*			m_pIWbDTS;

	bool				m_bSingle;
	bool				m_bFree;
	unsigned long		m_ulSessionID;
	//unsigned short		m_usCardNo;

	bool				m_bDelete;

};

#endif