#ifndef __WBCHANNEL_H__
#define __WBCHANNEL_H__

#include "../HPDTS/IHPDTS.h"
#include "WbSession.h"
#include "../libHPBaseclass/AVAutoLock.h"
#include <map>


typedef std::map<unsigned long,CWbSession*>	MapWbSession;

class AFX_EXT_CLASS CWbChannel
	: public IHPDTSNotify
{
public:
	CWbChannel(unsigned long ulChannelID,bool bUI=false);
	virtual ~CWbChannel(void);

public:
	virtual bool Connect(void);
	virtual void ReleaseConnections(void);

	//unsigned long GetSessionCount(void);
	//bool IsDirty(void);
	//bool IsEmpty(void);
	//void SetChannelID(unsigned long ulChannelID);
	unsigned long GetChannelID(void);
	void OnDataFromSession(unsigned long ulSessionID,char*pData,int nLen); //
	virtual void onWbData(unsigned long ulSessionID,char* data,int len);
	void AddSession(CWbSession*pSession);
	void RemoveSession(CWbSession*pSession);

	void ClearSession(void);

	bool IsFree() { return m_bFree;}
	void SetFree(bool bFree) { m_bFree = bFree;}
	bool IsMatch(unsigned long ulConferenceID) {
		return (m_ulConferenceID == ulConferenceID);
	}
	void SetConference(unsigned long ulConferenceID) {
		m_ulConferenceID = ulConferenceID;
	}

	void SetDelete() {
		m_bDelete = true;
	}
	bool IsDelete() {
		return m_bDelete;
	}

	void print()
	{
#ifdef _DEBUG
		cout << "CWbChannel:" << m_ulConferenceID << endl;
#endif
	}

protected:
	virtual void onDTSNetDataNotify(unsigned long ulSessionID,const char* pData,int nLen);  //回调网络数据
	virtual void onDTSUIDataNotify(const char* pData,int nLen){};							//回调界面数据

protected:
	unsigned long		m_ulChannelID;
	MapWbSession		m_MapSession;
	AVCritSec			m_AVCritSecMapSession;
	//bool				m_bDirty;
	IHPDTS*				m_pIWbDTS;

	bool				m_bFree;
	unsigned long		m_ulConferenceID;

	bool				m_bDelete;

	bool				m_bUI;
};

#endif
