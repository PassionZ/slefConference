#ifndef DATASTORE_H_
#define DATASTORE_H_

#ifdef NETTVANDBROADCAST
#include "./DataDefine/RSMsgdefine.h"
#else
#include "../DataDefine/RSMsgdefine.h"
#endif
#include "../libHPBaseclass/AVAutoLock.h"
#include <algorithm>
#include <functional>
#include <list>
#include <map>
#include "../libHPBaseclass/ListPtr.h"


typedef /*std::list<UINT32>*/ListPtr /*ListUINT32*/ListMcuID;

typedef /*std::list<UINT32>*/ListPtr ListMcuID;
typedef std::map<UINT32,ListMcuID*> MapListMcuID;

typedef std::map</*std::string*/UINT32, ListtConferenceBaseInfo*> MapListtConferenceBaseInfo;
typedef std::map<UINT32, ListtTalkOverDataInfo*> MapListtTalkOverDataInfo;

class CDataStore  
{
public:
	CDataStore();
	virtual ~CDataStore();

protected:
	AVCritSec					m_AVCritSecMapListTConferenceBaseInfo;	// ���������Ϣ�б�
	MapListtConferenceBaseInfo	m_MapListTConferenceBaseInfo;
	
	AVCritSec			        m_AVCritSecListtConferenceInfo;
	ListtConferenceInfo			m_ListtConferenceInfo;					// ������Ϣ�б�

	AVCritSec					m_AVCritSecListTMCUInfo;
	ListtMCUInfo				m_ListTMCUInfo;							// MCU��Ϣ�б�

	AVCritSec					m_AVCritSecListtTempletInfo;
	ListtTempletInfo			m_ListtTempletInfo;						// ����ģ����Ϣ�б�
	
	MapListtTalkOverDataInfo	m_MapListtTalkOverDataInfo;				// ����������Ϣ����

	//AVCritSec					m_AVCritSecMapListMcuIDUser;			// all user info of all mcu
	MapListMcuID				m_MapListMcuIDUser;

#ifdef NETTVANDBROADCAST
	AVCritSec					m_AVCritSecListtChannelInfo;
	ListtChannelInfo			m_ListtChannelInfo;
#endif

public:
	// ListtMCUInfo MCU������Ϣ�б�
	AVCritSec* GetAVCritSecListTMCUInfo() { return &m_AVCritSecListTMCUInfo; }
	ListtMCUInfo* GetListTMCUInfo() { return &m_ListTMCUInfo; };
	void AddListTMCUInfo(tMCUInfo*);
	void DelListTMCUInfo(UINT32 iMcuID);
	void ClearListTMCUInfo();

	bool GetListMcuID(UINT32 iMcuID, /*ListUINT32*/ListMcuID*& listMcuID);

	// ListtTempletInfo ����ģ����Ϣ�б�
	AVCritSec* GetAVCritSecListtTempletInfo() { return &m_AVCritSecListtTempletInfo; }
	ListtTempletInfo* GetListtTempletInfo() { return &m_ListtTempletInfo; };
	void AddListtTempletInfo(tTempletInfo*);
	void ClearListtTempletInfo();

	// MapListtConferenceBaseInfo ���˻��������б�
	AVCritSec* GetAVCritSecMapListTConferenceBaseInfo() { return &m_AVCritSecMapListTConferenceBaseInfo; }
	MapListtConferenceBaseInfo* GetMapListTConferenceBaseInfo() { return &m_MapListTConferenceBaseInfo; };
	void AddMapListTConferenceBaseInfo(/*std::string*/UINT32 strUserID, tConferenceBaseInfo* pTConferenceBaseInfo);
	void ClearMapListTConferenceBaseInfo();
	void ClearListTConferenceBaseInfo(ListtConferenceBaseInfo* pListTConferenceBaseInfo); // temp

	// ListtConferenceInfo ����������Ϣ�б�
	AVCritSec* GetAVCritSecListtConferenceInfo() { return &m_AVCritSecListtConferenceInfo; }
	ListtConferenceInfo* GetListtConferenceInfo() { return &m_ListtConferenceInfo; };
	void AddListtConferenceInfo(tConferenceInfo*);
	void ClearListtConferenceInfo();

	tConferenceInfo* GettConferenceInfo(UINT32 iConferenceID);
	void DelMapListTConferenceBaseInfo(/*std::string*/UINT32 strUserID, UINT32 iConferenceID);
	void DelMapListTConferenceBaseInfo(UINT32 iConferenceID);

	byte GetTempletInfoWinNumber(tTempletInfo *pInfo);
	void PrintDataInfo();

	// MCU�������Ͻ���û��б�
	void AddMapListMcuIDUser(UINT32 iMcuID, UINT32 iSessionID);
	void DelMapListMcuIDUser(UINT32 iMcuID, UINT32 iSessionID);
	void ClearMapListMcuIDUser();
	AVCritSec* GetAVCritSecMapListMcuIDUser() { return &m_AVCritSecListTMCUInfo/*m_AVCritSecMapListMcuIDUser*/; }
	ListMcuID* GetMapListMcuIDUser(UINT32 iMcuID)
	{ 
		AVAutoLock l(&m_AVCritSecListTMCUInfo/*m_AVCritSecMapListMcuIDUser*/);
		ListMcuID* pListInfo = NULL;
		MapListMcuID::iterator it = m_MapListMcuIDUser.find(iMcuID);
		while (it != m_MapListMcuIDUser.end())
		{
			pListInfo = (*it).second;
			return pListInfo;
		}
		return NULL; 
	}
	void GenMapListMcuIDUser();
	void RecursionMcuIDUser(UINT32 iMcuID,ListMcuID* pStackMcuID);
	void PrintfMapListMcuIDUser();


#ifdef NETTVANDBROADCAST
	// ListtChannelInfo Ƶ����Ϣ�б�
	AVCritSec* GetAVCritSecListtChannelInfo() { return &m_AVCritSecListtChannelInfo; }
	ListtChannelInfo* GetListtChannelInfo() { return &m_ListtChannelInfo; };
	void AddListtChannelInfo(tChannelInfo*);
	void ClearListtChannelInfo();
#endif

};

#endif