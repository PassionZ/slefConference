#ifndef TOPMCUDATASTORE_H_
#define TOPMCUDATASTORE_H_

#include "DataStore.h"


//typedef std::list<UINT32> ListMcuID;
//typedef std::map<UINT32,ListMcuID*> MapListMcuID;

typedef std::map</*std::string*/UINT32, ListtConferenceUserInfo*> MapListtConferenceUserInfo;

class CTopMcuDataStore : public CDataStore  
{
public:
	CTopMcuDataStore();
	virtual ~CTopMcuDataStore();

protected:
	//AVCritSec					m_AVCritSecListtConferenceUserInfo;
	ListtConferenceUserInfo		m_ListtConferenceUserInfo;				// 会议用户信息列表

	// 各会议基本人列表
	MapListtConferenceUserInfo		m_MapListtConferenceUserInfo;

	// 各人会议基本列表
	MapListtConferenceUserInfo		m_MapListtConferenceUserInfoConference;

	//AVCritSec					m_AVCritSecMapListMcuIDPath;
	MapListMcuID				m_MapListMcuIDPath;

	//AVCritSec					m_AVCritSecMapListSessionIDofMcuID;
	//MapListMcuID				m_MapListSessionIDofMcuID;

	//AVCritSec					m_AVCritSecMapListMcuIDUser;			// all user info of all mcu
	//MapListMcuID				m_MapListMcuIDUser;

public:
	// ListtMCUInfo MCU分组排序
	void GenOrderListTMCUInfo();
	void RecursionOrderMcuID(ListtMCUInfo *pOldList,UINT32 sMcuID,ListtMCUInfo* pNewList);

	void GetMcuMap(UINT32 iMcuID,ListMcuID& mapMcu);
	void RecursionOrderMcuMap(ListtMCUInfo *pOldList,UINT32 iMcuID,ListMcuID* pNewList);
	
	// MapListMcuIDPath MCU下传搜索路径
	AVCritSec* GetAVCritSecMapListMcuIDPath() { return &/*m_AVCritSecMapListMcuIDPath*/m_AVCritSecListTMCUInfo; }
	MapListMcuID* GetMapListMcuID() { return &m_MapListMcuIDPath; };
	void ClearMapListMcuIDPath();
	void ClearListMcuID(ListMcuID* pListMcuID); // temp
	void GenSessionIDPath();
	void RecursionSessionIDPath(UINT32 iMcuID,ListMcuID* pStackMcuID);
	void AddSessionIDPath(tMCUInfo* pTMCUInfo);
	void DelSessionIDPath(UINT32 iSessionID);
	void PrintfSessionIDPath(UINT32 iSessinID);

	// ListTConferenceUserInfo 每个会议的所有用户列表
	AVCritSec* GetAVCritSecListTConferenceUserInfo() { return &/*m_AVCritSecListtConferenceUserInfo*/m_AVCritSecMapListTConferenceBaseInfo; }
	ListtConferenceUserInfo* GetListTConferenceUserInfo() { return &m_ListtConferenceUserInfo; };
	void AddListTConferenceUserInfo(tConferenceUserInfo*);
	void ClearListTConferenceUserInfo();
	void ReSort();
	void PrintfListtConferenceUserInfo();

	void GenMapListtConferenceBaseInfo();

	// MCU所负责管辖的用户列表(已经废弃，使用下面一组函数)
	//AVCritSec* GetAVCritSecMapListSessionIDofMcuID() { return &/*m_AVCritSecMapListSessionIDofMcuID*/m_AVCritSecListTMCUInfo; }
	//MapListMcuID* GetMapListSessionIDofMcuID() { return &m_MapListSessionIDofMcuID; };
	//void ClearMapListSessionIDofMcuID();
	////void ClearListSessionID(ListMcuID* pListMcuID); // temp
	//void GenMapListSessionIDofMcuID();
	//void RecursionSessionID(UINT32 iMcuID,ListMcuID* pStackMcuID);
	////void AddMapListSessionIDofMcuID(UINT32 iMcuID, UINT32 iSessionID);
	////void DelMapListSessionIDofMcuID(UINT32 iMcuID, UINT32 iSessionID);
	//void PrintfMapListSessionIDofMcuID();

	//// MCU所负责管辖的用户列表
	//void AddMapListMcuIDUser(UINT32 iMcuID, UINT32 iSessionID);
	//void DelMapListMcuIDUser(UINT32 iMcuID, UINT32 iSessionID);
	//void ClearMapListMcuIDUser();
	//AVCritSec* GetAVCritSecMapListMcuIDUser() { return &m_AVCritSecMapListMcuIDUser; }
	//ListMcuID* GetMapListMcuIDUser(UINT32 iMcuID) { return m_MapListMcuIDUser[iMcuID]; }

	UINT32 GetSessionID(const char* cUserID, UINT32 iUpMcuID);
	char* GetUserName(UINT32 iSessionID);
	UINT32  GetConferenceID(UINT32 iSessionID);
	byte  GetUserDegreeFlag(UINT32 iSessionID, UINT32 iConferenceID);

	bool IsOnline(UINT32 iSessionID);
	bool IsAllowEnterConference(UINT32 iSessionID, UINT32 iConferenceID);

	// 各会议基本人列表
	AVCritSec* GetAVCritSecMapListtConferenceUserInfo() { return &/*m_AVCritSecListtConferenceUserInfo*/m_AVCritSecMapListTConferenceBaseInfo;}
	MapListtConferenceUserInfo* GetMapListtConferenceUserInfo() { return &m_MapListtConferenceUserInfo; };
	void AddMapListtConferenceUserInfo(/*std::string*/UINT32 iConferenceID, tConferenceUserInfo* pInfo);
	void ClearMapListtConferenceUserInfo();
	void ClearListtConferenceUserInfo(ListtConferenceUserInfo* pListInfo);
	void DelMapListtConferenceUserInfo(/*std::string*/UINT32 iConferenceID, UINT32 iSessionID);
	void DelMapListtConferenceUserInfo(UINT32 iConferenceID);

	// 各人会议基本列表
	AVCritSec* GetAVCritSecMapListtConferenceUserInfoConference() { return &/*m_AVCritSecListtConferenceUserInfo*/m_AVCritSecMapListTConferenceBaseInfo;}
	MapListtConferenceUserInfo* GetMapListtConferenceUserInfoConference() { return &m_MapListtConferenceUserInfoConference; };
	void AddMapListtConferenceUserInfoConference(/*std::string*/UINT32 iSessionID, tConferenceUserInfo* pInfo);
	void ClearMapListtConferenceUserInfoConference();
	//void ClearListtConferenceUserInfo(ListtConferenceUserInfo* pListInfo);
	void DelMapListtConferenceUserInfoConference(/*std::string*/UINT32 iConferenceID, UINT32 iSessionID);
	void DelMapListtConferenceUserInfoConference(UINT32 iSessionID);
	void DelMapListtConferenceUserInfoConference1(UINT32 iConferenceID);

};

#endif
