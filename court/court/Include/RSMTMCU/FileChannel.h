#ifndef __FileCHANNEL_H__
#define __FileCHANNEL_H__

#include "IFileDTS.h"
#include "FileSession.h"
#include "../libHPBaseclass/AVAutoLock.h"
#include <map>


typedef std::map<unsigned long,CFileSession*>	MapFileSession;

class AFX_EXT_CLASS CFileChannel
	: public IFileDTSNotify
{
public:
	CFileChannel(unsigned long ulChannelID);
	virtual ~CFileChannel(void);

public:
	virtual bool Connect(bool bMcu);
	virtual void ReleaseConnections(void);

	//unsigned long GetSessionCount(void);
	//bool IsDirty(void);
	//bool IsEmpty(void);
	//void SetChannelID(unsigned long ulChannelID);
	unsigned long GetChannelID(void);
	void OnDataFromSession(unsigned long ulSessionID,const char*pData,int nLen); //
	virtual void onFileData(unsigned long ulSessionID,char* data,int len);
	void AddSession(CFileSession*pSession);
	void RemoveSession(CFileSession*pSession);

	void ClearSession(void);

	bool IsSingle() { return m_bSingle;}
	void SetSingle(bool bDirection) { m_bSingle = bDirection;}
	bool IsFree() { return m_bFree;}
	void SetFree(bool bFree) { m_bFree = bFree;}
	bool IsMatch(/*unsigned long ulConferenceID, */const char* cFileName) {
		return (!m_strFileName.compare(cFileName)); //(m_ulConferenceID == ulConferenceID);
	}
	bool IsMatch(unsigned long ulConferenceID/*, const char* cFileName*/) {
		return m_ulConferenceID == ulConferenceID;
	}
	void SetConference(unsigned long ulConferenceID, const char* cFileName) {
		m_ulConferenceID = ulConferenceID;
		m_strFileName = cFileName;
	}

	void SetDelete() {
		m_bDelete = true;
	}
	bool IsDelete() {
		return m_bDelete;
	}

	UINT32 GetConferenceID()  { return m_ulConferenceID; }
	const char* GetFileName() { return m_strFileName.c_str(); }

	void onFileEnd(const char* cFileName) {};
	void onFileProcess(double iProcess) {};
	void processFDTRequest(unsigned long ulSessionID,char * data,int len) {};

	void print()
	{
#ifdef _DEBUG
		cout << "CFileChannel:" << m_ulConferenceID << "," << m_strFileName << endl;
#endif
	}

protected:
	unsigned long		m_ulChannelID;
	MapFileSession		m_MapSession;
	AVCritSec			m_AVCritSecMapSession;
	//bool				m_bDirty;
	IFileDTS*			m_pIFileDTS;

	bool				m_bSingle;
	bool				m_bFree;
	unsigned long		m_ulConferenceID;
	std::string			m_strFileName;

	bool				m_bDelete;
};

#endif
