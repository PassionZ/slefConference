#ifndef SONMCUDATASTORE_H_
#define SONMCUDATASTORE_H_

#include "DataStore.h"


typedef std::map</*std::string*/UINT32, ListtUserInfo*> MapListtUserInfo;

class CSonMcuDataStore : public CDataStore
{
public:
	CSonMcuDataStore();
	virtual ~CSonMcuDataStore();

protected:
	AVCritSec					m_AVCritSecListtUserInfo;
	ListtUserInfo				m_ListtUserInfo;			// 基本用户信息列表

	MapListtUserInfo		m_MapListtUserInfo;
	MapListtUserInfo		m_MapListtUserInfoConference;
	
public:
	// ListtUserInfo 每个会议的所有用户列表
	AVCritSec* GetAVCritSecListtUserInfo() { return &m_AVCritSecListtUserInfo; }
	ListtUserInfo* GetListtUserInfo() { return &m_ListtUserInfo; };
	void AddListtUserInfo(tUserInfo*);
	void ClearListtUserInfo();
	void ReSort();
	void PrintfListtUserInfo();

	UINT32 GetSessionID(const char* cUserID, UINT32 iUpMcuID);
	char* GetUserName(UINT32 iSessionID);
	UINT32  GetConferenceID(UINT32 iSessionID);
	byte  GetUserDegreeFlag(UINT32 iSessionID, UINT32 iConferenceID);

	bool IsOnline(UINT32 iSessionID);
	bool IsAllowEnterConference(UINT32 iSessionID, UINT32 iConferenceID);

	// 各会议基本人列表
	AVCritSec* GetAVCritSecMapListtUserInfo() { return &m_AVCritSecListtUserInfo; }
	MapListtUserInfo* GetMapListtUserInfo() { return &m_MapListtUserInfo; };
	void AddMapListtUserInfo(/*std::string*/UINT32 iConferenceID, tUserInfo* pInfo);
	void ClearMapListtUserInfo();
	void ClearListtUserInfo(ListtUserInfo* pListInfo);
	void DelMapListtUserInfo(/*std::string*/UINT32 iConferenceID, UINT32 iSessionID);
	void DelMapListtUserInfo(UINT32 iConferenceID);

	// 各人会议基本列表
	AVCritSec* GetAVCritSecMapListtUserInfoConference() { return &m_AVCritSecListtUserInfo; }
	MapListtUserInfo* GetMapListtUserInfoConference() { return &m_MapListtUserInfoConference; };
	void AddMapListtUserInfoConference(/*std::string*/UINT32 iSessionID, tUserInfo* pInfo);
	void ClearMapListtUserInfoConference();
	//void ClearListtUserInfo(ListtUserInfo* pListInfo);
	void DelMapListtUserInfoConference(/*std::string*/UINT32 iConferenceID, UINT32 iSessionID);
	void DelMapListtUserInfoConference(UINT32 iSessionID);
	void DelMapListtUserInfoConference1(UINT32 iConferenceID);

	void GenMapListtConferenceBaseInfo();

};

#endif
