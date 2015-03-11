#ifndef DBMANAGER_H_
#define DBMANAGER_H_

#include "../libHPBaseclass/AVThread.h"
#include "../libHPBaseclass/AVBufferPool.h"
#include "../libHPBaseclass/AVUtil.h"
#include "MySqlDBConnection.h"
#include "AVDataPacket.h"


class AFX_EXT_CLASS RSMTMCUManager;

class CDbManager
	: public AVBufferPool
	, public AVThread
{
public:
	CDbManager(RSMTMCUManager& rAVMTMCUManager);
	virtual ~CDbManager(void);

	bool Connect(const char* host, const char* name);
	void ReleaseConnections(void);

	void SendPacket(unsigned char* pData,int nLen);

protected:
	void ThreadProcMain(void);
	void OnDispatchReceivedData(char* pData,int nLen);
	void OnDispatchTopMcuLogin(AVDataInPacket& in);
	void OnDispatchTopMcuLogout(AVDataInPacket& in);
	void OnDispatchMcuLogin(AVDataInPacket& in);
	void OnDispatchMcuLogout(AVDataInPacket& in);
	void OnDispatchUserLogin(AVDataInPacket& in);
	void OnDispatchUserLogout(AVDataInPacket& in);
	void OnDispatchChangeName(AVDataInPacket& in);
	void OnDispatchChangePass(AVDataInPacket& in);
	void OnDispatchChangeBandwidth(AVDataInPacket& in);
	void OnDispatchLoginConference(AVDataInPacket& in);
	void OnDispatchLogoutConference(AVDataInPacket& in);
	void OnDispatchChangeTemplete(AVDataInPacket& in);

	//////////////////////////////////////////////////////////////////////////

	void CheckDb(bool bfirst);

	//////////////////////////////////////////////////////////////////////////
	
	void		DeleteMcu(UINT32 iMcuID);
	void		UpdateMcu(tMCUInfo *ptMCUInfo);
	void		InsertMcu(tMCUInfo *ptMCUInfo);

	void		DeleteConference(UINT32 iConferenceID);
	void		UpdateConference(tConferenceInfo *ptConferenceInfo);
	void		InsertConference(tConferenceInfo *ptConferenceInfo);

	void		DeleteConferenceUser(UINT32 iConferenceID, UINT32 iSessionID);
	void		UpdateConferenceUser(tConferenceUserInfo *ptConferenceUserInfo);
	void		InsertConferenceUser(tConferenceUserInfo *ptConferenceUserInfo);

	void		DeleteTemplet(tTempletInfo *ptInfo);
	void		UpdateTemplet(tTempletInfo *ptInfo);
	void		InsertTemplet(tTempletInfo *ptInfo);

	void		SetTos(unsigned char ucTos);

	void		GenOrderListTMCUInfo();
	void		GenMapListSessionIDofMcuID();
	void		GenMapListtConferenceBaseInfo();

	void		DeleteChannel(tChannelInfo *ptInfo);
	void		UpdateChannel(tChannelInfo *ptInfo);
	void		InsertChannel(tChannelInfo *ptInfo);

	void		UpdateConferenceAll();

protected:
	bool m_bWantToStop;
	RSMTMCUManager&				m_rAVMTMCUManager;
	AVCritSec					m_AVCritSecMySqlDb;
	CMySqlDBConnection*			m_pMySqlDb;

	unsigned long m_ulLastCheckTimestamp;
	unsigned long m_ulLastCheckTimestampDb;

	unsigned char				m_ucTos;

	friend class CMySqlDBConnection;

private:
	unsigned long m_ulLastCheckTimeStamp;

};

#endif