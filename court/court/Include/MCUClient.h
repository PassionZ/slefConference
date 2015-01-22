#ifndef __IMCUCLIENT_H__
#define __IMCUCLIENT_H__

#include <string>

// video tcp&udp
class IAVVideoReceiverNotify
{
public:
	IAVVideoReceiverNotify(void){};
	virtual~IAVVideoReceiverNotify(void){};
public:
	virtual void OnIAVVideoReceiverNotifyReceivedVideoFrame(const char*pData,int nLen)=0;
};

class IAVVideoReceiver
{
public:
	IAVVideoReceiver(void){};
	virtual ~IAVVideoReceiver(void){};
};

class IAVVideoSenderNotify
{
public:
	IAVVideoSenderNotify(void){};
	virtual~IAVVideoSenderNotify(void){};
};

class IAVVideoSender
{
public:
	IAVVideoSender(void){};
	virtual ~IAVVideoSender(void){};
public:
	virtual void SendVideoFrame(const char*pData,int nLen)=0;
};

// audio udp
class IAVAudioReceiverNotify
{ 
public:
	IAVAudioReceiverNotify(void){};
	virtual~IAVAudioReceiverNotify(void){};
public:
	virtual void OnIAVAudioReceiverNotifyReceivedAudioFrame(const char*pData,int nLen)=0;
};

class IAVAudioReceiver
{
public:
	IAVAudioReceiver(void){};
	virtual ~IAVAudioReceiver(void){};
};

class IAVAudioSenderNotify
{
public:
	IAVAudioSenderNotify(void){};
	virtual~IAVAudioSenderNotify(void){};
};

class IAVAudioSender
{
public:
	IAVAudioSender(void){};
	virtual ~IAVAudioSender(void){};
public:
	virtual void SendAudioFrame(const char*pData,int nLen)=0;
};
#endif
