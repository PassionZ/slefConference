#ifndef IRSTCPCLIENTMSGNOTIFY_H_
#define IRSTCPCLIENTMSGNOTIFY_H_


class IRSTcpClientMsgNotify  
{
public:
	IRSTcpClientMsgNotify() {};
	virtual ~IRSTcpClientMsgNotify() {};

	virtual void OnRSTcpClientMsgNotifyException(void)=0;
	virtual void OnRSTcpClientMsgNotifyConnected(/*unsigned long ulIP*/)=0;
	virtual void OnRSTcpClientMsgNotifyConnectFailed(void)=0;
	virtual void OnRSTcpClientMsgNotifyInitialized(UINT32 iMcuID)=0;
	virtual void OnRSTcpClientMsgNotifyInitFailed(void)=0;
	virtual void OnRSTcpClientMsgNotifyDisconnected(void)=0;
	virtual void OnRSTcpClientMsgNotifyReceivedData(const void*pData,int nLen)=0;

	virtual void OnRSTcpClientCreateChannelNotifyException(UINT32 iConferenceID, UINT32 iScreen, UINT32 iFrame)=0;
	virtual void OnRSTcpClientCreateChannelNotifyConnected(UINT32 iConferenceID, UINT32 iScreen, UINT32 iFrame)=0;
	virtual void OnRSTcpClientCreateChannelNotifyConnectFailed(UINT32 iConferenceID, UINT32 iScreen, UINT32 iFrame)=0;
	virtual void OnRSTcpClientCreateChannelNotifyInitialized(UINT32 iConferenceID, UINT32 iScreen, UINT32 iFrame)=0;
	virtual void OnRSTcpClientCreateChannelNotifyInitFailed(UINT32 iConferenceID, UINT32 iScreen, UINT32 iFrame)=0;
	virtual void OnRSTcpClientCreateChannelNotifyDisconnected(UINT32 iConferenceID, UINT32 iScreen, UINT32 iFrame)=0;
};

#endif
