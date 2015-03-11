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
	ListtConferenceUserInfo		m_ListtConferenceUserInfo;				// �����û���Ϣ�б�

	// ������������б�
	MapListtConferenceUserInfo		m_MapListtConferenceUserInfo;

	// ���˻�������б�
	MapListtConferenceUserInfo		m_MapListtConferenceUserInfoConference;

	//AVCritSec					m_AVCritSecMapListMcuIDPath;
	MapListMcuID				m_MapListMcuIDPath;

	//AVCritSec					m_AVCritSecMapListSessionIDofMcuID;
	//MapListMcuID				m_MapListSessionIDofMcuID;

	//AVCritSec					m_AVCritSecMapListMcuIDUser;			// all user info of all mcu
	//MapListMcuID				m_MapListMcuIDUser;

public:
	// ListtMCUInfo MCU��������
	void GenOrderListTMCUInfo();
	void RecursionOrderMcuID(ListtMCUInfo *pOldList,UINT32 sMcuID,ListtMCUInfo* pNewList);

	void GetMcuMap(UINT32 iMcuID,ListMcuID& mapMcu);
	void RecursionOrderMcuMap(ListtMCUInfo *pOldList,UINT32 iMcuID,ListMcuID* pNewList);
	
	// MapListMcuIDPath MCU�´�����·��
	AVCritSec* GetAVCritSecMapListMcuIDPath() { return &/*m_AVCritSecMapListMcuIDPath*/m_AVCritSecListTMCUInfo; }
	MapListMcuID* GetMapListMcuID() { return &m_MapListMcuIDPath; };
	void ClearMapListMcuIDPath();
	void ClearListMcuID(ListMcuID* pListMcuID); // temp
	void GenSessionIDPath();
	void RecursionSessionIDPath(UINT32 iMcuID,ListMcuID* pStackMcuID);
	void AddSessionIDPath(tMCUInfo* pTMCUInfo);
	void DelSessionIDPath(UINT32 iSessionID);
	void PrintfSessionIDPath(UINT32 iSessinID);

	// ListTConferenceUserInfo ÿ������������û��б�
	AVCritSec* GetAVCritSecListTConferenceUserInfo() { return &/*m_AVCritSecListtConferenceUserInfo*/m_AVCritSecMapListTConferenceBaseInfo; }
	ListtConferenceUserInfo* GetListTConferenceUserInfo() { return &m_ListtConferenceUserInfo; };
	void AddListTConferenceUserInfo(tConferenceUserInfo*);
	void ClearListTConferenceUserInfo();
	void ReSort();
	void PrintfListtConferenceUserInfo();

	void GenMapListtConferenceBaseInfo();

	// MCU�������Ͻ���û��б�(�Ѿ�������ʹ������һ�麯��)
	//AVCritSec* GetAVCritSecMapListSessionIDofMcuID() { return &/*m_AVCritSecMapListSessionIDofMcuID*/m_AVCritSecListTMCUInfo; }
	//MapListMcuID* GetMapListSessionIDofMcuID() { return &m_MapListSessionIDofMcuID; };
	//void ClearMapListSessionIDofMcuID();
	////void ClearListSessionID(ListMcuID* pListMcuID); // temp
	//void GenMapListSessionIDofMcuID();
	//void RecursionSessionID(UINT32 iMcuID,ListMcuID* pStackMcuID);
	////void AddMapListSessionIDofMcuID(UINT32 iMcuID, UINT32 iSessionID);
	////void DelMapListSessionIDofMcuID(UINT32 iMcuID, UINT32 iSessionID);
	//void PrintfMapListSessionIDofMcuID();

	//// MCU�������Ͻ���û��б�
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

	// ������������б�
	AVCritSec* GetAVCritSecMapListtConferenceUserInfo() { return &/*m_AVCritSecListtConferenceUserInfo*/m_AVCritSecMapListTConferenceBaseInfo;}
	MapListtConferenceUserInfo* GetMapListtConferenceUserInfo() { return &m_MapListtConferenceUserInfo; };
	void AddMapListtConferenceUserInfo(/*std::string*/UINT32 iConferenceID, tConferenceUserInfo* pInfo);
	void ClearMapListtConferenceUserInfo();
	void ClearListtConferenceUserInfo(ListtConferenceUserInfo* pListInfo);
	void DelMapListtConferenceUserInfo(/*std::string*/UINT32 iConferenceID, UINT32 iSessionID);
	void DelMapListtConferenceUserInfo(UINT32 iConferenceID);

	// ���˻�������б�
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
