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
	AVCritSec					m_AVCritSecMapListTConferenceBaseInfo;	// 会议基本信息列表
	MapListtConferenceBaseInfo	m_MapListTConferenceBaseInfo;
	
	AVCritSec			        m_AVCritSecListtConferenceInfo;
	ListtConferenceInfo			m_ListtConferenceInfo;					// 会议信息列表

	AVCritSec					m_AVCritSecListTMCUInfo;
	ListtMCUInfo				m_ListTMCUInfo;							// MCU信息列表

	AVCritSec					m_AVCritSecListtTempletInfo;
	ListtTempletInfo			m_ListtTempletInfo;						// 会议模板信息列表
	
	MapListtTalkOverDataInfo	m_MapListtTalkOverDataInfo;				// 会议讨论信息内容

	//AVCritSec					m_AVCritSecMapListMcuIDUser;			// all user info of all mcu
	MapListMcuID				m_MapListMcuIDUser;

#ifdef NETTVANDBROADCAST
	AVCritSec					m_AVCritSecListtChannelInfo;
	ListtChannelInfo			m_ListtChannelInfo;
#endif

public:
	// ListtMCUInfo MCU所有信息列表
	AVCritSec* GetAVCritSecListTMCUInfo() { return &m_AVCritSecListTMCUInfo; }
	ListtMCUInfo* GetListTMCUInfo() { return &m_ListTMCUInfo; };
	void AddListTMCUInfo(tMCUInfo*);
	void DelListTMCUInfo(UINT32 iMcuID);
	void ClearListTMCUInfo();

	bool GetListMcuID(UINT32 iMcuID, /*ListUINT32*/ListMcuID*& listMcuID);

	// ListtTempletInfo 会议模板信息列表
	AVCritSec* GetAVCritSecListtTempletInfo() { return &m_AVCritSecListtTempletInfo; }
	ListtTempletInfo* GetListtTempletInfo() { return &m_ListtTempletInfo; };
	void AddListtTempletInfo(tTempletInfo*);
	void ClearListtTempletInfo();

	// MapListtConferenceBaseInfo 各人基本会议列表
	AVCritSec* GetAVCritSecMapListTConferenceBaseInfo() { return &m_AVCritSecMapListTConferenceBaseInfo; }
	MapListtConferenceBaseInfo* GetMapListTConferenceBaseInfo() { return &m_MapListTConferenceBaseInfo; };
	void AddMapListTConferenceBaseInfo(/*std::string*/UINT32 strUserID, tConferenceBaseInfo* pTConferenceBaseInfo);
	void ClearMapListTConferenceBaseInfo();
	void ClearListTConferenceBaseInfo(ListtConferenceBaseInfo* pListTConferenceBaseInfo); // temp

	// ListtConferenceInfo 会议所有信息列表
	AVCritSec* GetAVCritSecListtConferenceInfo() { return &m_AVCritSecListtConferenceInfo; }
	ListtConferenceInfo* GetListtConferenceInfo() { return &m_ListtConferenceInfo; };
	void AddListtConferenceInfo(tConferenceInfo*);
	void ClearListtConferenceInfo();

	tConferenceInfo* GettConferenceInfo(UINT32 iConferenceID);
	void DelMapListTConferenceBaseInfo(/*std::string*/UINT32 strUserID, UINT32 iConferenceID);
	void DelMapListTConferenceBaseInfo(UINT32 iConferenceID);

	byte GetTempletInfoWinNumber(tTempletInfo *pInfo);
	void PrintDataInfo();

	// MCU所负责管辖的用户列表
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
	// ListtChannelInfo 频道信息列表
	AVCritSec* GetAVCritSecListtChannelInfo() { return &m_AVCritSecListtChannelInfo; }
	ListtChannelInfo* GetListtChannelInfo() { return &m_ListtChannelInfo; };
	void AddListtChannelInfo(tChannelInfo*);
	void ClearListtChannelInfo();
#endif

};

#endif