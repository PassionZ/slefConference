#ifndef IDBCONNECTION_H_
#define IDBCONNECTION_H_

//#include "../DataDefine/RSMsgdefine.h"


#define USE_TEST

#ifdef USE_TEST

#define DB_USER				"Conference" 		
#define DB_USER_PASSWORD	"Desktop@163.com"
#define DB_NAME				"MyTest" 

#else
#define DB_USER				"Conference" 		
#define DB_USER_PASSWORD	"Desktop@163.com"
#define DB_NAME				"VideoConferenceDB"	

#endif
#define DB_HOST				"192.168.1.3"

typedef enum _EDbRecordStatus {_eNormal, _eInsert, _eModify, _eDelete, _eObsolescence} EDbRecordStatus;

class IDBConnection  
{
public:
	IDBConnection();
	virtual ~IDBConnection();

public:
	virtual bool	Connect(const char* host, const char* name) = 0;
	virtual void	ReleaseConnections(void) = 0;

	virtual UINT16  GetMCUInfoList(/*ListtMCUInfo *pListtMCUInfo, */bool bFirst = false) = 0;
	virtual UINT16  GetConferenceInfoList(/*ListtConferenceInfo *pListtConferenceInfo, */bool bFirst = false) = 0;
	virtual UINT16  GetTempletInfoList(/*ListtTempletInfo *pListInfo, */bool bFirst = false) = 0;

	virtual UINT16	UserLogin(const char *cszUserID, const char *cszPassword, UINT32 iMcuID, UINT32& iSessionID) = 0;
	virtual void	UserLogout(UINT32 iSessionID) = 0;
	virtual bool	LoginConference(UINT32 iSessionID, UINT32 iConfereneID) = 0;
	virtual void	LogoutConference(UINT32 iSessionID) = 0;
};

IDBConnection*CreateDBConnection(void);
#define USE_DB_MYSQL

#endif
