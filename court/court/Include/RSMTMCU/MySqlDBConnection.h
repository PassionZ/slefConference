#ifndef MYSQLDBCONNECTION_H_
#define MYSQLDBCONNECTION_H_

#include "IDBConnection.h"
#include "MysqlDB.h"


class AFX_EXT_CLASS /*RSMTMCUManager*/CDbManager;
class CMySqlDBConnection : public IDBConnection  
{
public:
	CMySqlDBConnection(/*RSMTMCUManager*/CDbManager& rAVMTMCUManager);
	virtual ~CMySqlDBConnection();

	bool	Connect(const char* host, const char* name);
	void	ReleaseConnections(void);

	UINT16  GetMCUInfoList(/*ListtMCUInfo *pListtMCUInfo, */bool bFirst = false);
	UINT16  GetConferenceInfoList(/*ListtConferenceInfo *pListtConferenceInfo, */bool bFirst = false);
	UINT16  GetConferenceUserInfoList(/*ListtConferenceUserInfo *pListtConferenceUserInfo, */bool bFirst = false);
	UINT16  GetTempletInfoList(/*ListtTempletInfo *pListInfo, */bool bFirst = false);
	unsigned char  GetTos();

	void	McuLogin(UINT32 iMcuID);
	void	McuLogout(UINT32 iMcuID);
	UINT16	UserLogin(const char *cszUserID, const char *cszPassword, UINT32 iMcuID, UINT32& iSessionID);
	void	UserLogout(UINT32 iSessionID);
	bool	LoginConference(UINT32 iSessionID, UINT32 iConfereneID);
	void	LogoutConference(UINT32 iSessionID);
	void	ChangeConferenceTemplete(UINT32 iConferenceID,byte WinNo,byte iWinClass,bool bWinTemplate,byte iWinNumber,byte iWinType);
	void	ChangeConferenceBandwidth(UINT32 iConferenceID,UINT16 iBandwidth);

	UINT16 ChangeName(UINT32 iSessionID, const char*cszName);
	UINT16 ChangePassword(UINT32 iSessionID, const char*cszPassword);

	void	TopMcuLogin();
	void	TopMcuLogout();
	void	TopMcuTimer();

	bool   IsConnected() { return m_dbMySQL.Connected; }

	UINT16  GetChannelInfoList(/*ListtChannelInfo *pListInfo, */bool bFirst = false);

	void  ResetUpdateConference() {
		m_bUpdateConference = false;
	}
	bool GetUpdateConference() {
		return m_bUpdateConference;
	}

protected:
	/*RSMTMCUManager*/CDbManager&		m_rAVMTMCUManager;
	CMysqlDB			m_dbMySQL;

	bool m_bUpdateConference;
};

#endif
