#ifndef __VIDEOCHANNEL_H__
#define __VIDEOCHANNEL_H__

#include "VideoSession.h"
#include "../libHPBaseclass/AVAutoLock.h"
#include <map>
#include <iostream>

using namespace std;

typedef std::map<unsigned long,CVideoSession*>	MapVideoSession;

class AFX_EXT_CLASS CVideoChannel
	//: public IWbDTSNotify
{
public:
	CVideoChannel(unsigned long ulChannelID);
	virtual ~CVideoChannel(void);

public:
	bool Connect(void);
	void ReleaseConnections(void);

	unsigned long GetSessionCount(void);
	//bool IsDirty(void);
	//bool IsEmpty(void);
	//void SetChannelID(unsigned long ulChannelID);
	unsigned long GetChannelID(void);
	void OnDataFromSession(bool bTcp,unsigned long ulSessionID,const char*pData,int nLen); //
	void OnDataFromSessionDirection(bool bTcp,unsigned long ulSessionID,const char*pData,int nLen);
	void OnDataFromSessionEnable(bool bTcp,unsigned long ulSessionID,const char*pData,int nLen);
	//void onWbData(unsigned long channelId,char* data,int len);
	void AddSession(CVideoSession*pSession);
	void RemoveSession(CVideoSession*pSession);

	bool IsVideoSinkEnable(void);
	void ProcessVideoSinkDisable(void);
	bool IsRequestKeyFrame(void);
	void OnVideoChannelData(bool bTcp,const char*pData,int nLen); //
	unsigned long GetBufferingFrameCount(void);

	void ClearSession(void);

	bool IsSingle() { return m_bSingle;}
	void SetSingle(bool bDirection) { m_bSingle = bDirection;}
	bool IsFree() { return m_bFree;}
	void SetFree(bool bFree) { m_bFree = bFree;}
	bool IsMatch(unsigned long ulSessionID, unsigned short usCardNo) {
		return (ulSessionID == m_ulSessionID && usCardNo == m_usCardNo);
	}
	void SetSessionCard(unsigned long ulSessionID, unsigned short usCardNo) {
		m_ulSessionID = ulSessionID;
		m_usCardNo = usCardNo;
	}
	bool IsLike(unsigned long ulSessionID) {
		return (ulSessionID == m_ulSessionID);
	}

	void SetDelete() {
		m_bDelete = true;
	}
	bool IsDelete() {
		return m_bDelete;
	}

	void Reset();

	void print()
	{
#ifdef _DEBUG
		cout << "CVideoChannel:" << m_ulSessionID << "," << m_usCardNo << endl;
#endif
	}

	unsigned long GetSessionID() {
		return m_ulSessionID;
	}
	unsigned short GetCardNo() {
		return m_usCardNo;
	}

protected:
	unsigned long		m_ulChannelID;
	MapVideoSession		m_MapSession;
	AVCritSec			m_AVCritSecMapSession;
	//bool				m_bDirty;
	//IWbDTS*			m_pIWbDTS;

	bool				m_bSingle;
	bool				m_bFree;
	unsigned long		m_ulSessionID;
	unsigned short		m_usCardNo;

	bool				m_bDelete;

};

#endif
