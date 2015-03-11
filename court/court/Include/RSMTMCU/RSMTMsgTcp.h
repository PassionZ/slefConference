// RSMTMsgTCP.h: interface for the RSMTMsgTCP class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __RSMTMSGTCP_H__
#define __RSMTMSGTCP_H__

#include "../libHPNETIO/AVMTSConnection.h"
#include "../libHPBaseclass/AVUtil.h"


class AFX_EXT_CLASS RSMTMCUMsg;
class AFX_EXT_CLASS RSMTMsgTCP 
	:public AVMTSConnection
{
public:
	RSMTMsgTCP(RSMTMCUMsg&rAVMTMCUFile,UINT32 ulFileChannelID,SOCKET hSocket);
	virtual ~RSMTMsgTCP(void);

public:
	void	ReleaseConnections(void);
	void	OnReceivedFrame(const char*pFrameData,int nLen);
	bool	IsDisconnected(void);
	int		OnSendOutMsg(const void*pData,int nLen);

	bool IsFine() {return m_bFine;}
	void SetFine(bool bFine) {m_bFine = bFine;}
	byte GetDegreeFlag() {return m_iDegreeFlag;}
	void SetDegreeFlag(byte iDegreeFlag) {m_iDegreeFlag = iDegreeFlag;}

	void TestMcuBandwidthStart(UINT32 iDataLen) {m_iStartTime = AVGetTimestamp(), m_iTotalDataLen = iDataLen;}
	void TestMcuBandwidthData(UINT32 iDataLen) {m_iTotalDataLen += iDataLen;}
	UINT32 TestMcuBandwidthEnd(UINT32 iDataLen) {
		UINT32 iTmp = AVGetTimestamp() - m_iStartTime;
		if (iTmp <= 0)
			return 0;
		UINT32 iRate = ((m_iTotalDataLen + iDataLen)*8) / (iTmp);
		m_iStartTime =0, m_iTotalDataLen=0;
		return iRate;
	}

	void SetTDOver(bool bTDOver) { m_bTDOver = bTDOver; }
	bool GetTDOver() { return m_bTDOver; }
	void SetDisconnectOver(bool bDisconnectOver) { m_bDisconnectOver = bDisconnectOver; }
	bool GetDisconnectOver() { return m_bDisconnectOver; }
	
protected:
	unsigned char	m_ucBufferEmptyCount;
	RSMTMCUMsg&		m_rAVMTMCUFile;
	UINT32			m_iMcuID;
	EInfoType		m_eInfoType;
	byte			m_iDegreeFlag;
	bool			m_bFine;

	UINT32			m_iStartTime;
	UINT32			m_iTotalDataLen;

	bool			m_bTDOver;
	bool			m_bDisconnectOver;

	UINT32			m_iConferenceID;

public:
	UINT32		GetMcuID() { return m_iMcuID; }
	void		SetMcuID(UINT32 iMcuID) { m_iMcuID = iMcuID; }
	void		SetInfoType(EInfoType eInfoType) { m_eInfoType = eInfoType; }
	EInfoType	GetInfoType() { return m_eInfoType; }

	void		SetConferenceID(UINT32 iConferenceID) { m_iConferenceID = iConferenceID; }
	UINT32		GetConferenceID() { return m_iConferenceID; }


//public:
//	virtual void OnError(void)
//	{
//		AVMTSConnection::OnError();
//		printf("RSMTMsgTCP OnError\n");
//	}
//	virtual void OnDisconnected(void)
//	{
//		AVMTSConnection::OnDisconnected();
//		printf("RSMTMsgTCP OnDisconnected\n");
//	}
};

#endif 
