#ifndef __HPP2PCONNECTION_H__
#define __HPP2PCONNECTION_H__

#include <map>
#include <string>

#include "AVMTSocketUDP.h"
#include "HPP2PCMD.h"
#include "../libHPBaseclass/AVUtil.h"

class HPP2PSocket;
class HPP2PConnection
{
public:
	HPP2PConnection(HPP2PSocket&rHPP2PSocket,unsigned long ulP2PID,SOCKET hSocket,unsigned long ulIP,unsigned short usPort);
	virtual ~HPP2PConnection(void);
public:
	virtual unsigned long GetP2PID(void);
	virtual SOCKET GetSocketHandle(void);
	virtual unsigned long GetPeerIP(void);
	virtual unsigned short GetPeerPort(void);
	virtual bool IsExpired(void);
	virtual bool IsWritable(void);
	virtual int SendData(const void*pData,int nLen);
	virtual void OnReceivedSTT(unsigned short usSTTID,unsigned long ulCID);
	virtual void OnReceivedSTTAck(unsigned short usSTTID,unsigned long ulCID);
	virtual void OnReceivedRTT(unsigned short usRTTID);
	virtual void OnReceivedRTTAck(unsigned short usRTTID);
	virtual void OnReceivedData(const void*pData,int nLen);
	virtual unsigned long GetRTT(void);
	virtual unsigned short GetSTTID(void);
	virtual unsigned long GetCID(void);
	virtual unsigned long GetSTTTimestamp(void);
	virtual void SendSTTAck(unsigned short usSTTID,unsigned long ulCID);
	virtual void SendSTT(unsigned short usSTTID);
	virtual void SendRTTAck(unsigned short usRTTID);
	virtual void SendRTT(unsigned long ulTimestamp);
	virtual void Update(void);
protected:
	void Dump(const char*cszHeader);
protected:
	HPP2PSocket&				m_rHPP2PSocket;
	struct sockaddr_in			m_saPeer;
	AVMTSocketUDP				m_AVMTSocketUDP;
	unsigned long				m_ulP2PID;

	unsigned long				m_ulRTT;
	unsigned short				m_usRTTID;
	unsigned long				m_ulRTTTimestamp;

	unsigned short				m_usSTTID;
	unsigned long				m_ulCID;
	unsigned long				m_ulSTTTimestamp;
	unsigned long				m_ulUpdateTimestamp;
	unsigned long				m_ulWritableTimestamp;
	bool						m_bWritable;
};

typedef std::map<std::string,HPP2PConnection*>	MapHPP2PConnection;

#endif