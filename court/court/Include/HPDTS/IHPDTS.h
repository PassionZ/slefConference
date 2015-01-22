
//========================================================================================
//��Ȩ����: ��Ȩ����(C) 2008
//ϵͳ����: 
//��������: 
//��������: 
//����˵��: ���ݴ���������ں˽ӿ��ඨ��
//

#pragma once

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS IHPDTSNotify
{
public:
	IHPDTSNotify(void){};
	virtual~ IHPDTSNotify(void){};
public:
	virtual void onDTSNetDataNotify(unsigned long ulSessionID,const char* pData,int nLen)=0;  //�ص���������
	virtual void onDTSUIDataNotify(const char* pData,int nLen)=0;							  //�ص���������
};


//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS IHPDTS
{
public:
	IHPDTS(void){};
	virtual~IHPDTS(void){};

	virtual void Init(void) = 0;
	virtual void Release(void) = 0;
public:
	virtual void processUIData(const char* pData,int nLen)=0;								//�����������
	virtual void processDTSData(unsigned long ulSessionID,const char* pData,int nLen)=0;	//������������
	virtual void AddDTSSession(unsigned long ulSessionID,bool bHost/*��ulSessionID�Ƿ�ΪHost Server*/)=0; //����DTS����
	virtual void RemoveDTSSession(unsigned long ulSessionID)=0;								//ɾ��DTS����
};

//---------------------------------------------------------------------------------------
AFX_EXT_CLASS IHPDTS*CreateIHPDTS(IHPDTSNotify& rIHPDTSNotify,bool bUI/*�Ƿ���UI*/);

AFX_EXT_CLASS void HPDTSInit(const char* cszTemPath/*�����ļ���ʱĿ¼*/);	
AFX_EXT_CLASS void HPDTSUnInit(void);
AFX_EXT_CLASS void HPDTSSetSavePath(const char* cszSavePath);//�ͻ��������ļ�����Ŀ¼,���ظ�����
AFX_EXT_CLASS const char* GetFileTemPath(void);
AFX_EXT_CLASS const char* GetFileSavePath(void);

