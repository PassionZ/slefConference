//IWBDTS.h
#ifndef __IWBDTS_H__
#define __IWBDTS_H__


class AFX_EXT_CLASS IWbDTSNotify
{
public:
	IWbDTSNotify(void){};
	virtual~IWbDTSNotify(void){};
public:
	virtual void onWbData(unsigned long channelId,char* data,int len)=0;
};

class AFX_EXT_CLASS IWbDTS
{
public:
	IWbDTS(void){};
	virtual~IWbDTS(void){};
public:
	virtual void processWbData(unsigned long channelId,char * data,int len)=0;
	virtual void addChannel(unsigned long channelId)=0;
	virtual void removeChannel(unsigned long channelId)=0;
};

AFX_EXT_CLASS IWbDTS*CreateIWbDTS(IWbDTSNotify&rIWbDTSNotify);

#endif