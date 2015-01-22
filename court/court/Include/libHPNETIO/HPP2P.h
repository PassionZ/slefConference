#ifndef __HPP2PH_H__
#define __HPP2PH_H__

#include "IHPP2P.h"
#include "../libHPBaseclass/AVUtil.h"
#include "../libHPBaseclass/AVAutoLock.h"
#include <map>

class HPP2P 
	: public IHPP2P
{
public:
	HPP2P(IHPP2PNotify&rIHPP2PNotify);
	virtual~HPP2P(void);
public:
	bool Connect(void);
	void ReleaseConnections(void);
	
	bool SendP2PCommand(unsigned long ulP2PID,unsigned long ulIP,unsigned short usPort);
	bool IsP2PConnected(unsigned long ulP2PID,unsigned short&usPort);
	void DoCheck(void);
	void OnReceivedP2PData(char*pData,int nLen,unsigned long ulIP,unsigned short usPort);
	void OnReceivedACKData(char*pData,int nLen,unsigned long ulIP,unsigned short usPort);
	unsigned long GetP2PID(void);


	class HPP2PItem
	{
	public:
		HPP2PItem(unsigned long ulID,unsigned long ulIP,unsigned short usPort)
			: m_ulID(ulID)
			, m_ulIP(ulIP)
			, m_usPort(usPort)
			, m_usConnectedPort(0)
			, m_ulUpdateTimestamp(0)
			, m_ulTryCount(0)
		{

		}
		virtual~HPP2PItem(void)
		{

		}
	public:
		void SetConnectedPort(unsigned short usPort)
		{
			m_usConnectedPort=usPort;
			m_ulUpdateTimestamp=AVGetTimestamp();
		};
		unsigned short GetConnectedPort(void)
		{
			return m_usConnectedPort;
		};
		unsigned long GetIP(void)
		{
			return m_ulIP;
		}
		unsigned short GetPort(void)
		{
			return m_usPort;
		}
		unsigned long GetID(void)
		{
			return m_ulID;
		}
		void IncreaseTryCount(void)
		{
			m_ulTryCount++;
		}
		unsigned long GetTryCount(void)
		{
			return m_ulTryCount;
		}
		bool IsExpired(void)
		{
			if (m_usConnectedPort)
			{
				unsigned long ulCurrentTimestamp=AVGetTimestamp();
				if (ulCurrentTimestamp<m_ulUpdateTimestamp)
				{
					m_ulUpdateTimestamp=ulCurrentTimestamp;
				}
				else if(ulCurrentTimestamp-m_ulUpdateTimestamp>60000)
				{
					return true;
				}
			}
			return false;
		}
	protected:
		unsigned long	m_ulID;
		unsigned long	m_ulIP;
		unsigned short	m_usPort;
		unsigned short	m_usConnectedPort;
		unsigned long	m_ulUpdateTimestamp;
		unsigned long	m_ulTryCount;
	};

	typedef std::map<unsigned long,HPP2PItem*>	MapHPP2PItem;
protected:
	IHPP2PNotify&	m_rIHPP2PNotify;
	unsigned long	m_ulP2PID;
	MapHPP2PItem	m_MapHPP2PItem;
	AVCritSec		m_AVCritSecMapHPP2PItem;

	unsigned long	m_ulLastCheckTimestamp;
};

#endif