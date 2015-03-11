#ifndef AUDIOCHANNEL_H_
#define AUDIOCHANNEL_H_

#include "AudioSession.h"
#include "../libHPBaseclass/AVAutoLock.h"
#include <map>
#include <iostream>

using namespace std;

typedef std::map<unsigned long,CAudioSession*>	MapAudioSession;

class AFX_EXT_CLASS CAudioChannel
{
public:
	CAudioChannel(unsigned long ulChannelID);
	virtual ~CAudioChannel(void);

public:
	void ReleaseConnections(void);

	unsigned long GetChannelID(void);
	void AddSession(CAudioSession*pSession);
	void RemoveSession(CAudioSession*pSession);

	bool IsAudioSinkEnable(void);
	void ProcessAudioSinkDisable(void);
	void ClearSession(void);

	void OnDataFromSession(unsigned long ulSessionID,const char*pData,int nLen); //
	void OnDataFromSessionDirection(unsigned long ulSessionID,const char*pData,int nLen);
	void OnDataFromSessionEnable(unsigned long ulSessionID,const char*pData,int nLen);
	void OnAudioChannelData(const char*pData,int nLen); //

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

	void print()
	{
#ifdef _DEBUG
		cout << "CAudioChannel:" << m_ulSessionID << endl;
#endif
	}

	void Reset();

	unsigned long GetSessionID() {
		return m_ulSessionID;
	}
	unsigned short GetCardNo() {
		return m_usCardNo;
	}

protected:
	unsigned long		m_ulChannelID;
	MapAudioSession		m_MapSession;
	AVCritSec			m_AVCritSecMapSession;

	bool				m_bSingle;
	bool				m_bFree;
	unsigned long		m_ulSessionID;

	bool				m_bDelete;

	unsigned short		m_usCardNo;
};

#endif

