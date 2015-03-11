#ifndef TCPCLIENT_H_
#define TCPCLIENT_H_

#include "../libHPNETIO/AVMTSConnection.h"


class CTcpClient :
	public AVMTTCPClient
{
public:
	CTcpClient(AVMTTCPClientNotify&rNotify,SOCKET hSocket);
	virtual ~CTcpClient(void);

	bool IsDisconnected() {return m_bDisconnected == true;}
};

#endif
