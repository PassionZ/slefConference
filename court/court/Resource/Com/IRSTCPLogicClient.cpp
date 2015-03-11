
#include "stdafx.h"
#include "IRSTCPLogicClient.h"

#include <ASSERT.H>


#define RSIM_COMMAND_NOTIFY				(WM_USER+21520)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//IRSTCPLogicClient*g_pIRSTCPLogicClient=NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(IRSTCPLogicClient, CWnd)
	IRSTCPLogicClient::IRSTCPLogicClient(IRSClientNotify &rNotify):m_pIRSClientNotify(&rNotify)
{

	assert(m_pIRSClientNotify != NULL);

	m_pMcuManager = NULL;
	m_pConf = NULL;

	m_strUserID = "";
	m_iConferenceID = 0;
	m_iSpeakSessionID = 0;
	m_bLogined = false;
	m_bLoginedConference = false;
	m_bLoginFailed = false;

}

IRSTCPLogicClient::~IRSTCPLogicClient()
{
	LogoutSystem();
	//g_pIRSTCPLogicClient=NULL;
}
BEGIN_MESSAGE_MAP(IRSTCPLogicClient, CWnd)
	ON_MESSAGE(RSIM_COMMAND_NOTIFY,OnCommandNotify)
END_MESSAGE_MAP()


LRESULT IRSTCPLogicClient::OnCommandNotify(WPARAM wParam, LPARAM lParam)
{
	if (m_pIRSClientNotify == NULL)
	{
		TRACE("IRSTCPLogicClient::m_pIRSClientNotify == NULL\n");
	}

	/*while*/if (CWnd::GetSafeHwnd())
	{
		while(GetCount())
		{
			AVDataBuffer*pAVCommandDataBuffer=(AVDataBuffer*)GetDataBuffer();
			if (pAVCommandDataBuffer==NULL)
			{
				return	1;
			}
			else
			{
				AVDataInPacket inPacket((char*)pAVCommandDataBuffer->GetData(),pAVCommandDataBuffer->GetLen());
				_tMessageHeader msgHeader;
				UINT32 iType;
				inPacket >> (UINT32)iType >> msgHeader._iCommandID >> msgHeader._iMcuID;
				msgHeader._eDirectionType = (EDirectionType)iType;

				ProcessCommand(msgHeader._iCommandID, msgHeader._iMcuID, (char*)pAVCommandDataBuffer->GetData()+sizeof(_tMessageHeader), pAVCommandDataBuffer->GetLen()-sizeof(_tMessageHeader));
				delete pAVCommandDataBuffer;
				pAVCommandDataBuffer=NULL;
			}

			if (m_bLoginFailed)
				break;
		}
	}

	return 0;

}
void IRSTCPLogicClient::ProcessCommand(UINT32 iCmdID, UINT32 iMcuID, char*pData,int nLen)
{
	if (!m_bLoginedConference && iCmdID > 0x00001008)
	{
		if (iCmdID != CONF_COMMAND_INVITEUSER_REP && iCmdID != CONF_COMMAND_TESTMCUBANDWIDTH_REP && iCmdID != CONF_COMMAND_TESTMCUBANDWIDTHDATA && iCmdID != CONF_COMMAND_TESTMCUBANDWIDTHEND && iCmdID != CONF_COMMAND_BROADCAST_INSERTCONFERENCEUSER)
			return;
	}
	TRACE(" IRSTCPLogicClient::ProcessCommand %d  %d\n",iCmdID,iMcuID);
	switch(iCmdID) {
	case CONF_COMMAND_USERLOGIN:
		{
			OnUserLogin(iMcuID, pData, nLen);
		}
		break;

	case CONF_COMMAND_FETCHMCUINFO:
		{
			OnFetchMcuInfo(iMcuID, pData, nLen);
		}
		break;
	case CONF_COMMAND_FETCHMCUINFOEND:
		{
			OnFetchMcuInfoEnd(iMcuID, pData, nLen);
		}
		break;
	case CONF_COMMAND_FETCHCONFERENCEBASEINFO:
		{
			OnFetchConferenceBaseInfo(iMcuID, pData, nLen);
		}
		break;
	case CONF_COMMAND_FETCHCONFERENCEBASEINFOEND:
		{
			OnFetchConferenceBaseInfoEnd(iMcuID, pData, nLen);
		}
		break;
			case CONF_COMMAND_FETCHCONFERENCEUSERINFO:
		{
			OnFetchConferenceUserInfo(iMcuID, pData, nLen);
		}
		break;
			case CONF_COMMAND_BROADCAST_USERLOGIN:
		{
			//OnBroadcastUserLogin(iMcuID, pData, nLen);
		}
		break;
	case CONF_COMMAND_BROADCAST_USERLOGOUT:
		{
			//OnBroadcastUserLogout(iMcuID, pData, nLen);
		}
		break;
	case CONF_COMMAND_BROADCAST_CONFERENCELOGIN:
		{
			//OnBroadcastConferenceLogin(iMcuID, pData, nLen);
		}
		break;
	case CONF_COMMAND_BROADCAST_CONFERENCELOGOUT:
		{
			//OnBroadcastConferenceLogout(iMcuID, pData, nLen);
		}
		break;
		case CONF_COMMAND_BROADCAST_P2PDATA:
		{
			//OnBroadcastP2P(iMcuID, pData, nLen);
		}
		break;
	case CONF_COMMAND_BROADCAST_OPENTALKOVER:
		{
			//OnOpenTalkOver(iMcuID, pData, nLen);
		}
		break;
	case CONF_COMMAND_BROADCAST_CLOSETALKOVER:
		{
			//OnCloseTalkOver(iMcuID, pData, nLen);
		}
		break;
	case CONF_COMMAND_BROADCAST_TALKOVERDATA:
		{
			//OnUserTalk(iMcuID, pData, nLen);
		}
		break;
	case CONF_COMMAND_SENDCONFERENCETEMPLET:
		{
			OnSendConferenceTemplet(iMcuID, pData, nLen);
		}
		break;
	case CONF_COMMAND_SENDCONFERENCEMEMBER:
		{
			OnSendConferenceMember(iMcuID, pData, nLen);
		}
		break;
	case CONF_COMMAND_SENDCONFERENCEMEMBERPRESENCE:
		{
			//OnSendConferenceMemberPresence(iMcuID, pData, nLen);
		}
		break;
	case CONF_COMMAND_SENDCONFERENCEMEMBERENTER:
		{
			//OnSendConferenceMemberEnter(iMcuID, pData, nLen);
		}
		break;
	case CONF_COMMAND_SENDTALKOVER:
		{
			//OnSendTalkOver(iMcuID, pData, nLen);
		}
		break;
	case CONF_COMMAND_SENDTALKOVERDATA:
		{
			//OnSendTalkOverData(iMcuID, pData, nLen);
		}
		break;
			case CONF_COMMAND_P2PDATA_REP:
		{
			OnP2PData(iMcuID, pData, nLen);
		}
		break;
		case CONF_COMMAND_BROADCAST_CHANGUSERMICVIDEOINFO:
		{
			//OnBroadcastChangUserMicVideoInfo(iMcuID, pData, nLen);
		}
		break;
		case CONF_COMMAND_BROADCAST_FRAMENO:
		{
						OnBroadcastSelectMainFrame(iMcuID, pData, nLen);
		}
		break;
	default:
		break;
	}
}

void IRSTCPLogicClient::OnBroadcastSelectMainFrame(UINT32 iMcuID, char*pData,int nLen)   
{
		AVDataInPacket inPacket((char*)pData,nLen);
	UINT32 iConferenceID = 0;
	byte cFrameNo;
	inPacket >> iConferenceID;
	inPacket >> cFrameNo;

	TRACE("CONF_COMMAND_BROADCAST_FRAMENO\n");
	m_pIRSClientNotify->OnSelectMainFrame(cFrameNo);
}
void IRSTCPLogicClient::OnP2PData(UINT32 iMcuID, char*pData,int nLen)                 
{
	AVDataInPacket inPacket((char*)pData,nLen);
	UINT32 cJumps = 0;
	inPacket >> cJumps;
	if (cJumps == (UINT32)0) {  // 主持人
		inPacket >> iMcuID;
	} else {
		while (cJumps--) {
			inPacket >> iMcuID;
		}
	}

	UINT32 iConferenceID = 0, iSessionID = 0;
	inPacket >> iConferenceID;
	inPacket >> iSessionID;
	char data[1025] = {0};
	//inPacket >> data;
	int iLen = 0;
	unsigned char* pTemp = inPacket.ReadData(iLen);
	TRACE("CONF_COMMAND_P2PDATA_REP: %d\n");

	m_pIRSClientNotify->OnP2PData(iSessionID, (const char*)pTemp, iLen);
}
void IRSTCPLogicClient::OnSendConferenceTemplet(UINT32 iMcuID, char*pData,int nLen)
{
	AVDataInPacket inPacket((char*)pData,nLen);
	tConferenceInfo msgtUserInfo;
	inPacket >> (UINT32)msgtUserInfo._iConferenceID;
	inPacket >> msgtUserInfo._strConferenceName;
	inPacket >> msgtUserInfo._strConferenceTopic;
	inPacket >> (UINT16)msgtUserInfo._iBandwidth;

	inPacket >> (byte)msgtUserInfo._iOneWinClass;
	byte bTemp;
	inPacket >> (byte)bTemp;
	msgtUserInfo._bOneWinTemplate = (bool)bTemp;
	inPacket >> (byte)msgtUserInfo._iOneWinNumber;
	inPacket >> (byte)msgtUserInfo._iOneWinType;
	inPacket >> (byte)msgtUserInfo._iTwoWinClass;
	inPacket >> (byte)bTemp;
	msgtUserInfo._bTwoWinTemplate = (bool)bTemp;
	inPacket >> (byte)msgtUserInfo._iTwoWinNumber;
	inPacket >> (byte)msgtUserInfo._iTwoWinType;
				
	// ...
	// 还不需要传输 ?

	TRACE("CONF_COMMAND_SENDCONFERENCETEMPLET: iConferenceID = %d\n", msgtUserInfo._iConferenceID);
				
	// 2号屏
	//byte screenType = 0x00;
	//screenType = msgtUserInfo._iTwoWinClass;
	//byte templetType = 0x00;
	//templetType = msgtUserInfo._iTwoWinNumber;
	//byte tTempData;
	//tTempData=(templetType << 4)&0x0F0;
	//templetType = tTempData+msgtUserInfo._iTwoWinType;
	//m_pIRSClientNotify->OnConferenceTemplet(screenType, msgtUserInfo._bTwoWinTemplate, templetType);
	m_pIRSClientNotify->OnConferenceTemplet(0x01, msgtUserInfo._iTwoWinClass, msgtUserInfo._bTwoWinTemplate, msgtUserInfo._iTwoWinNumber, msgtUserInfo._iTwoWinType);
	
	// 1号屏
	//screenType = 0x00;
	//screenType = msgtUserInfo._iOneWinClass;
	//templetType = 0x00;
	//templetType = msgtUserInfo._iOneWinNumber;
	//tTempData=(templetType << 4)&0x0F0;
	//templetType = tTempData+msgtUserInfo._iOneWinType;
	//templetType += msgtUserInfo._iOneWinType;
	//m_pIRSClientNotify->OnConferenceTemplet((screenType << 4)&0x0F0, msgtUserInfo._bOneWinTemplate, templetType);
	m_pIRSClientNotify->OnConferenceTemplet(0x00, msgtUserInfo._iOneWinClass, msgtUserInfo._bOneWinTemplate, msgtUserInfo._iOneWinNumber, msgtUserInfo._iOneWinType);

	m_pIRSClientNotify->OnSetBandwidth(msgtUserInfo._iBandwidth);
	TRACE("CONF_COMMAND_BROADCAST_SETBANDWIDTH: iBandwidth = %d\n", msgtUserInfo._iBandwidth);
}

void IRSTCPLogicClient::OnSendConferenceMember(UINT32 iMcuID, char*pData,int nLen)
{
	AVDataInPacket inPacket((char*)pData,nLen);
	//UINT16 iType = 0;
	//inPacket >> (UINT16)iType;
	//while (iType--) 
	{
		tUserInfo msgtUserInfo;
		inPacket >> (UINT32)msgtUserInfo._iSessionID;
		inPacket >> msgtUserInfo._iUserID;
		inPacket >> msgtUserInfo._strUserName;
		inPacket >> msgtUserInfo._iDegreeFlag;
		inPacket >> msgtUserInfo._iMCUID;

		TRACE("CONF_COMMAND_SENDCONFERENCEMEMBER: %d, '%s', '%s'\n", msgtUserInfo._iSessionID,msgtUserInfo._iUserID,msgtUserInfo._strUserName);
		m_pIRSClientNotify->OnConferenceMember(msgtUserInfo._iSessionID,msgtUserInfo._iUserID,msgtUserInfo._iDegreeFlag,msgtUserInfo._strUserName,msgtUserInfo._iMCUID);
	}
}
void IRSTCPLogicClient::OnFetchMcuInfo(UINT32 iMcuID, char*pData,int nLen)
{
	USES_CONVERSION;
	AVDataInPacket inPacket((char*)pData,nLen);
	tMCUInfo msgTMCUInfo;
	UINT32 iType;

	//UINT16 iCount = 0;
	//inPacket >> (UINT16&)iCount;
	//while (iCount--)
	{
		inPacket >> (UINT32)msgTMCUInfo._iUPMCUid;
		inPacket >> (UINT32)msgTMCUInfo._iMCUID;
		inPacket >> (UINT32)iType;
		inPacket >> msgTMCUInfo._strMCUName;
		inPacket >> msgTMCUInfo._strMCUIPAddress;
		msgTMCUInfo._InfoType = (EInfoType)iType;

		TMCUInfo tInfo;
		tInfo._iMCUID = msgTMCUInfo._iMCUID;
		tInfo._iUPMCUid = msgTMCUInfo._iUPMCUid;
		_tcscpy(tInfo._strMCUIPAddress, A2W(msgTMCUInfo._strMCUIPAddress));
		_tcscpy(tInfo._strMCUName, A2W(msgTMCUInfo._strMCUName));

		TRACE("CONF_COMMAND_FETCHMCUINFO: MCUName = '%s', MCUIPAddress = '%s', MCUID = %d\n", msgTMCUInfo._strMCUName, msgTMCUInfo._strMCUIPAddress, msgTMCUInfo._iMCUID);	
		m_pIRSClientNotify->OnMCUItem(&tInfo);
	}
}

void IRSTCPLogicClient::OnFetchMcuInfoEnd(UINT32 iMcuID, char*pData,int nLen)
{	
	TRACE("CONF_COMMAND_FETCHMCUINFOEND\n");
	m_pIRSClientNotify->OnMCUEnd();
}

void IRSTCPLogicClient::OnFetchConferenceBaseInfo(UINT32 iMcuID, char*pData,int nLen)
{
	USES_CONVERSION;
	AVDataInPacket inPacket((char*)pData,nLen);
	tConferenceBaseInfo msgTConferenceBaseInfo;
	UINT32 iUserID;

	//UINT16 iCount = 0;
	//inPacket >> (UINT16)iCount;

	//while (iCount--)
	//{
	inPacket >> (UINT32)iUserID;

	inPacket >> (UINT32)msgTConferenceBaseInfo._iConferenceID;
	inPacket >> msgTConferenceBaseInfo._strConferenceName;
	inPacket >> msgTConferenceBaseInfo._strConferenceTopic;

	TConferenceBaseInfo tInfo;
	tInfo._iConferenceID = msgTConferenceBaseInfo._iConferenceID;
	_tcscpy(tInfo._strConferenceName, A2W(msgTConferenceBaseInfo._strConferenceName));
	_tcscpy(tInfo._strConferenceTopic, A2W(msgTConferenceBaseInfo._strConferenceTopic));

	TRACE("CONF_COMMAND_FETCHCONFERENCEBASEINFO: _strConferenceName = '%s', _strConferenceTopic = '%s', _iConferenceID = %d\n", msgTConferenceBaseInfo._strConferenceName, msgTConferenceBaseInfo._strConferenceTopic, msgTConferenceBaseInfo._iConferenceID);
	m_pIRSClientNotify->OnConferenceListItem(&tInfo);
	//}
}
void IRSTCPLogicClient::OnFetchConferenceUserInfo(UINT32 iMcuID, char*pData,int nLen)
{
	AVDataInPacket inPacket((char*)pData,nLen);
	UINT32 cJumps = 0;
	inPacket >> cJumps;
	if (cJumps == (UINT32)0) {  // 主持人
		inPacket >> iMcuID;
	} else {
		while (cJumps--) {
			inPacket >> iMcuID;
		}
	}
	
	tConferenceUserInfo conferenceUserInfo;
	
	UINT32 iType;
	inPacket >> (UINT32)iType;
	conferenceUserInfo._InfoType = (EInfoType)iType;
	
	byte bValue;
	inPacket >> conferenceUserInfo._strUserName;
	inPacket >> conferenceUserInfo._iUserID;
	inPacket >> (UINT32)conferenceUserInfo._iSessionID;
	inPacket >> (UINT32)conferenceUserInfo._iConferenceID;
	inPacket >> (byte)bValue;
	conferenceUserInfo._bPresentFlag = (bool)bValue;
	inPacket >> (byte)conferenceUserInfo._iOnlineFlag;
	inPacket >> (UINT32)conferenceUserInfo._iMCUID;
	inPacket >> conferenceUserInfo._strOnlineTime;
	inPacket >> (byte)conferenceUserInfo._iDegreeFlag;
	//HTREEITEM	*_phRoot;
	
	TRACE("CONF_COMMAND_FETCHCONFERENCEUSERINFO: _strUserName = '%s', _iUserID = '%s', _iSessionID = %d, _iConferenceID = %d\n", conferenceUserInfo._strUserName, conferenceUserInfo._iUserID, conferenceUserInfo._iSessionID, conferenceUserInfo._iConferenceID);
	
//	m_pIRSClientNotify->OnConferenceMember(conferenceUserInfo._iSessionID,conferenceUserInfo._iUserID,conferenceUserInfo._iDegreeFlag,conferenceUserInfo._strUserName);
	m_pIRSClientNotify->OnSendLoginConference(conferenceUserInfo._iDegreeFlag);

	if (conferenceUserInfo._iDegreeFlag != (byte)0xff)
		m_bLoginedConference = true;
}
void IRSTCPLogicClient::OnFetchConferenceBaseInfoEnd(UINT32 iMcuID, char*pData,int nLen)
{
	TRACE("CONF_COMMAND_FETCHCONFERENCEBASEINFOEND\n"); 
	m_pIRSClientNotify->OnConferenceListEnd();
}
bool IRSTCPLogicClient::FetchConferenceList()
{
	if (m_pMcuManager == NULL) {
		return false;
	}

	AVDataOutPacket outPacket;
	_tMessageHeader msg;
	msg._eDirectionType = _eSingle;
	msg._iCommandID = CONF_COMMAND_FETCHCONFERENCEBASEINFO;
	msg._iMcuID = m_pMcuManager->GetSelfMcuID();
	outPacket << (UINT32)msg._eDirectionType;
	outPacket << msg._iCommandID;
	outPacket << msg._iMcuID;

	UINT16 iLen = m_pMcuManager->SendData(outPacket.GetData(),outPacket.GetLength());

	return (iLen >= (UINT16)sizeof(_tMessageHeader));
}
//////////////////////////////////////////////////////////////////////////

void IRSTCPLogicClient::OnRSTcpClientMsgNotifyConnected(void)
{
	TRACE("success to Connect!\n");
}

void IRSTCPLogicClient::OnRSTcpClientMsgNotifyException(void)
{
	TRACE("Exception to server!\n");
} 
void IRSTCPLogicClient::OnRSTcpClientCreateChannelNotifyException(UINT32 iConferenceID, UINT32 iScreen, UINT32 iFrame)
{
	TRACE("Exception to channel: %u, %u, %u\n", iConferenceID, iScreen, iFrame);
}
void IRSTCPLogicClient::OnRSTcpClientCreateChannelNotifyConnected(UINT32 iConferenceID, UINT32 iScreen, UINT32 iFrame)
{
	TRACE("Connected to channel: %u, %u, %u\n", iConferenceID, iScreen, iFrame);
}
void IRSTCPLogicClient::OnRSTcpClientCreateChannelNotifyConnectFailed(UINT32 iConferenceID, UINT32 iScreen, UINT32 iFrame)
{
	TRACE("ConnectFailed to channel: %u, %u, %u\n", iConferenceID, iScreen, iFrame);
}
void IRSTCPLogicClient::OnRSTcpClientCreateChannelNotifyInitialized(UINT32 iConferenceID, UINT32 iScreen, UINT32 iFrame)
{
	TRACE("Initialized to channel: %u, %u, %u\n", iConferenceID, iScreen, iFrame);
}
void IRSTCPLogicClient::OnRSTcpClientCreateChannelNotifyInitFailed(UINT32 iConferenceID, UINT32 iScreen, UINT32 iFrame)
{
	TRACE("InitFailed to channel: %u, %u, %u\n", iConferenceID, iScreen, iFrame);
}
void IRSTCPLogicClient::OnRSTcpClientCreateChannelNotifyDisconnected(UINT32 iConferenceID, UINT32 iScreen, UINT32 iFrame)
{
	TRACE("Disconnected to channel: %u, %u, %u\n", iConferenceID, iScreen, iFrame);
}


void IRSTCPLogicClient::OnRSTcpClientMsgNotifyConnectFailed(void)
{
	m_pIRSClientNotify->OnConnectTimeout();
}

void IRSTCPLogicClient::OnRSTcpClientMsgNotifyDisconnected(void)
{
	m_pIRSClientNotify->OnDisconnected();
}

void IRSTCPLogicClient::OnRSTcpClientMsgNotifyInitialized(UINT32 iMcuID)
{
	m_pIRSClientNotify->OnConnected(iMcuID);
}

void IRSTCPLogicClient::OnRSTcpClientMsgNotifyInitFailed(void)
{
	TRACE("failure to Init!\n");
	m_pIRSClientNotify->OnConnected(NULL);
}

void IRSTCPLogicClient::OnRSTcpClientMsgNotifyReceivedData(const void*pData,int nLen)
{
	if (CWnd::GetSafeHwnd())
	{
		AVDataInPacket inPacket((char*)pData,nLen);
		_tMessageHeader msgHeader;
		UINT32 iType;
		inPacket >> (UINT32)iType >> msgHeader._iCommandID >> msgHeader._iMcuID;
		msgHeader._eDirectionType = (EDirectionType)iType;

		AVDataBuffer*pAVCommandDataBuffer=new AVDataBuffer();
		if (pAVCommandDataBuffer->StoreData((char*)pData,nLen)==false)
		{
			delete pAVCommandDataBuffer;
			pAVCommandDataBuffer=NULL;
		}
		else
		{
			//AVBufferPool
			SetDataBuffer(pAVCommandDataBuffer);
		}

		PostMessage(RSIM_COMMAND_NOTIFY);
	}
}

//////////////////////////////////////////////////////////////////////////
bool IRSTCPLogicClient::Connect(const char*cszMCUHost,unsigned __int16 iMCUPort)	//连接MCU
{
	if (m_pMcuManager != NULL) {
		m_pMcuManager->ReleaseConnections();
		delete m_pMcuManager;
		m_pMcuManager = NULL;
	}
	m_pMcuManager = new RSMTMCUManager(*this);
	assert(m_pMcuManager != NULL);

	if (m_pConf != NULL) {
		delete m_pConf;
		m_pConf = NULL;
	}
	//////////////////////////////////////////////////////////////////////////
	USES_CONVERSION;

	char strFilePath[256] = {0};
	CString strTemp=_T("\\Client.ini");
	TCHAR sztemp[SZTEMP_LENTH],sztemp2[SZTEMP_LENTH];
	GetModuleFileName(NULL,sztemp2,sizeof(sztemp2));
	GetFilePath(sztemp2,sztemp);
	_tcscat(sztemp,strTemp);
	sprintf(strFilePath,"%s",W2A(sztemp));
	////////////////////////////////////////////////////////////////////////
	m_pConf = new Config(/*"Client.ini"*/strFilePath);
	int line;
	if(!m_pConf->load(line))
		assert(0);

	string mcu = "LOCAL", strip = "ip", iport = "port";
	string ip = m_pConf->getString(mcu, strip);
	unsigned short port = m_pConf->getInt(mcu, iport);
	unsigned short listenPort = port;
	if ("" == ip) 
		assert(0);

	string protocol = m_pConf->getString("CONFIG", "vAgreement");
	bool bTcp = true;
	if (protocol.compare("tcp"))
		bTcp = false;
	m_bTcp = bTcp;

	bool bRet = 0;
	bRet = m_pMcuManager->Connect(ip/*AVMTSocket::GetIPAddress(ip.c_str())*/,/*port,*/0,true/*(bool)!port*/, /*true*/m_bTcp); // temp
	if (!bRet) {
		m_pMcuManager->ReleaseConnections();
		delete m_pMcuManager;
		m_pMcuManager = NULL;
		delete m_pConf;
		m_pConf = NULL;
		return false;
	}

	mcu = "UP";
	ip = cszMCUHost/*g_Conf.getString(mcu, strip)*/;
	port = m_pConf->getInt(mcu, iport);

	if ((ip != "") && (port != 0)) {
		m_pMcuManager->SetInfoType(_eUser);
		bRet = m_pMcuManager->RSTcpClientConnect(ip/*AVMTSocket::GetIPAddress(ip.c_str())*/,/*port*/iMCUPort,/*0*/AVMTSocket::GetDottedDecimal(0));
		if (!bRet) {
			m_pMcuManager->ReleaseConnections();
			delete m_pMcuManager;
			m_pMcuManager = NULL;
			delete m_pConf;
			m_pConf = NULL;
			return false;
		}
	} else { // temp
		TRACE("top mcu\n");
		m_pMcuManager->SetInfoType(_eTopMcu);
		//m_pMcuManager->SetSelfMcuID((UINT32)listenPort);
	}		 // end

	if (!m_pMcuManager->InitMcuInfo())
	{
		m_pMcuManager->ReleaseConnections();
		delete m_pMcuManager;
		m_pMcuManager = NULL;
		delete m_pConf;
		m_pConf = NULL;
		return false;
	}

	if (!Start())
		return false;

	return true;
}

bool IRSTCPLogicClient::SendLogin(const char*cszUserID,const char*cszPassword,byte iOnlineFlag)
{
	if (m_pMcuManager == NULL) {
		return false;
	}

	AVDataOutPacket outPacket;
	_tMessageHeader msg;
	msg._eDirectionType = _eSingle;
	msg._iCommandID = CONF_COMMAND_USERLOGIN;
	msg._iMcuID = m_pMcuManager->GetSelfMcuID(); // 无效ID
	outPacket << (UINT32)msg._eDirectionType;
	outPacket << msg._iCommandID;
	outPacket << msg._iMcuID;

	outPacket << cszUserID;		
	outPacket << cszPassword;

	outPacket << m_pMcuManager->GetUpMcuID();
	outPacket << iOnlineFlag;

	UINT16 iLen = m_pMcuManager->SendData(outPacket.GetData(),outPacket.GetLength());

	m_strUserID = cszUserID;

	return (iLen > (UINT16)(sizeof(_tMessageHeader)));
}

void IRSTCPLogicClient::OnUserLogin(UINT32 iMcuID, char*pData,int nLen)
{
	AVDataInPacket inPacket((char*)pData,nLen);
	UINT32 cJumps = 0;
	inPacket >> cJumps;
	if (cJumps == (UINT32)0) {  // 主持人
		inPacket >> iMcuID;
	} else {
		while (cJumps--) {
			inPacket >> iMcuID;
		}
	}

	char cName[90] = {0};
	UINT32 iSessionID = 0;
	inPacket >> cName;
	inPacket >> iSessionID;
	UINT16 iRet = 0;
	inPacket >> iRet;

	TRACE("CONF_COMMAND_USERLOGIN: cName = '%s', iSessionID = %d\n", cName, iSessionID);
	if ((!strcmp(cName, m_strUserID.c_str())) && ((UINT32)0 == iSessionID)) { // 验证不成功
		m_bLoginFailed = true;
		m_pIRSClientNotify->OnLogin(iRet, iSessionID, cName);
	} else
	{
		m_pIRSClientNotify->OnLogin(NULL, iSessionID, cName);
		m_bLogined = true;
	}
}
void IRSTCPLogicClient::LogoutSystem()
{
	if (m_bLogined && m_pMcuManager != NULL)
	{

		AVDataOutPacket outPacket;
		_tMessageHeader msg;
		msg._eDirectionType = _eBroadcast;
		msg._iCommandID = CONF_COMMAND_BROADCAST_USERLOGOUT;
		msg._iMcuID = m_pMcuManager->GetSelfMcuID();
		outPacket << (UINT32)msg._eDirectionType;
		outPacket << msg._iCommandID;
		outPacket << msg._iMcuID;

		UINT16 iLen = m_pMcuManager->SendData(outPacket.GetData(),outPacket.GetLength());
	}

	if (m_pMcuManager != NULL) {
		m_pMcuManager->ReleaseConnections();
		delete m_pMcuManager;
		m_pMcuManager = NULL;
	}

	if (m_pConf != NULL) {
		delete m_pConf;
		m_pConf = NULL;
	}

	//Stop();
}

bool IRSTCPLogicClient::FecthMCU()
{
	if (m_pMcuManager == NULL) {
		return false;
	}

	AVDataOutPacket outPacket;
	_tMessageHeader msg;
	msg._eDirectionType = _eSingle;
	msg._iCommandID = CONF_COMMAND_FETCHMCUINFO;
	msg._iMcuID = m_pMcuManager->GetSelfMcuID();
	outPacket << (UINT32)msg._eDirectionType;
	outPacket << msg._iCommandID;
	outPacket << msg._iMcuID;

	UINT16 iLen = m_pMcuManager->SendData(outPacket.GetData(),outPacket.GetLength());

	return (iLen >= (UINT16)sizeof(_tMessageHeader));
}
bool IRSTCPLogicClient::SendLoginConference(unsigned __int32 iConferenceID,byte iFrameResource/*,byte iUserMicType,CTVideoCardInfoArray *aVideoCardInfoArray*/)	//登陆会议
{
	if (m_pMcuManager == NULL) {
		return false;
	}
	//	assert(aVideoCardInfoArray != NULL);

	m_iConferenceID = iConferenceID; // 当前会议ID	

	AVDataOutPacket outPacket;
	_tMessageHeader msg;
	msg._eDirectionType = _eSingle;
	msg._iCommandID = CONF_COMMAND_FETCHCONFERENCEUSERINFO;
	msg._iMcuID = m_pMcuManager->GetSelfMcuID();
	outPacket << (UINT32)msg._eDirectionType;
	outPacket << msg._iCommandID;
	outPacket << msg._iMcuID;

	outPacket << (UINT32)iConferenceID;

	// TODO: send iUserMicType, *aVideoCardInfoArray info
	//	outPacket << iUserMicType;
	//	outPacket << (UINT16)aVideoCardInfoArray->GetSize();
	//	TVideoCardInfo* ptVideoCardInfo = NULL;
	//	int i=0;for ( i=0; i<aVideoCardInfoArray->GetSize(); ++i)
	//	{
	//		ptVideoCardInfo = aVideoCardInfoArray->GetAt(i);
	//		outPacket << ptVideoCardInfo->_iUserCardNo;
	//		outPacket << ptVideoCardInfo->_iUserCodeType;
	//		outPacket << ptVideoCardInfo->_iUserDisplayType;
	//		outPacket << ptVideoCardInfo->_iUserFrame;
	//		outPacket << (byte)ptVideoCardInfo->_bUserPreventInterleaved;
	//		outPacket << ptVideoCardInfo->_iUserMaxStream;
	//		outPacket << ptVideoCardInfo->_iUserPicQuality;
	//	}

	UINT16 iLen = m_pMcuManager->SendData(outPacket.GetData(),outPacket.GetLength());

	return (iLen >= (UINT16)sizeof(_tMessageHeader));
}
TCHAR *IRSTCPLogicClient::GetFilePath(TCHAR *file, TCHAR *path)
{
	int i, len =_tcslen((LPTSTR)file);

	for(i =len-1; i >-1; i--)
		if(file[i] =='\\' || file[i] =='/' || file[i] ==':') break;
	if(i ==0) _tcscpy(path, _T("."));
	else
	{
		_tcscpy(path, file);
		path[i] =0;
	}
	return path;
}
bool IRSTCPLogicClient::Start(void)
{
	if (!CreateEx(WS_EX_CLIENTEDGE,AfxRegisterWndClass(CS_CLASSDC), _T("RSIMCommandParser"),WS_POPUP,0,0,1,1,NULL,NULL))
	{
		return false;
	}	

	return true;
}
