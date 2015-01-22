
//========================================================================================
//��Ȩ����: ��Ȩ����(C) 2008
//ϵͳ����: 
//��������: 
//��������: 
//����˵��: DTS�����������ͷ���弰ģ�鹲�ò�������
//

#pragma once


#define LOCAL_DEBUG
#undef	LOCAL_DEBUG


#define FILE_TRANS_MAXLENGTH 8*1024	  //ÿ�����Ĵ�С
#define FILE_TRANS_PACKETCOUNT 3      //��һ������ĸ���

#define LOCAL_SESSIONID 1		  //����SessionID
#define DEFNET_SESSIONID 2		  //Ĭ������SessionID

//�ļ�����ṹ�嶨��
typedef struct tagDtsFileList
{
	unsigned long	ulFileID;
	unsigned long	ulFileLength;
	unsigned long	ulPosition;		
	unsigned long	ulFromSessionID;
	char			chSendUserID[255];
	char			chFileName[128];
	char			chFilePath[255];
	char			chDescription[255];
	char			chStartTime[30];

}DTS_FILE_LIST,*PDTS_FILE_LIST;

//��ע���װ����ṹ�嶨��
typedef struct tag_ObjDataBuf
{
	char*			pData;
	int				nLen;
	unsigned long	ulObjId;
}OBJ_DATA_BUF, *POBJ_DATA_BUF;

#ifndef _WIN32
typedef unsigned long	DWORD;
typedef unsigned int	UINT;
typedef unsigned long   COLORREF;
typedef struct tagPOINT
{
	long  x;
	long  y;
} POINT, *PPOINT;
typedef struct tagRECT
{
	long    left;
	long    top;
	long    right;
	long    bottom;
} RECT, *PRECT;
#endif

typedef struct tagDtsTemData
{	
	UINT			nCurPage;	
	UINT			nTotalPage;	
	POINT			ptFile;			//�����ļ��Ĵ�С
	POINT			ptClient;		//��ʾ����Ĵ�С
	UINT			nFlashStatus;	//flash ����״̬
	UINT			nFlashPosition;	//flash ����λ��
	UINT			nDocZoomSize;	//�ĵ��������ű���
	UINT			nDocLeft;		//�ĵ������ƶ���λ��
	UINT			nDocTop;		//�ĵ������ƶ���λ��

}DTS_TEM_DATA,*PDTS_TEM_DATA;

//�ļ�����״̬
enum enumFILESTATUS
{
	FILESTATUS_PAUSE = 0,			//��ͣ
	FILESTATUS_DONEUP,				//�ϴ����
	FILESTATUS_DONELOAD,			//�������
	FILESTATUS_WAIT,				//�ȴ�
	FILESTATUS_TRANSMIT,			//������
};

//DTS��������
enum enumDTSCOMMAND
{	
	WB_COMMAND_DATA = 0,			//�װ�����

	/*�����ļ�������淢�������������������������������������������������������������������*/
	FILE_SEND_ADDFILE,				//��������ļ�
	FILE_SEND_DELETEFILE,			//����ɾ������
	FILE_REQUEST_DOWNLOAD,			//���������ļ�����	
	FILE_PAUSE_DOWNLOAD,			//��ͣ�����ļ�
	FILE_CONTINUE_DOWNLOAD,			//���������ļ�
	FILE_PAUSE_UPLOAD,				//��ͣ�ϴ��ļ�
	FILE_CONTINUE_UPLOAD,			//�����ϴ��ļ�	
	FILE_GET_FILEINFO,				//��ȡ�ļ���Ϣ
	FILE_GET_POSITION,				//�õ��ļ�����λ��
	FILE_REQUEST_FILELIST,			//���������ļ��б�
	/*�����ļ��������ص������������������������������������������������������������������*/
	FILE_INSERT_FILE,				//�����ļ���Ϣ
	FILE_DELETE_FILE,				//ɾ���ļ���Ϣ
	FILE_UPDATE_STATUS,				//�����ļ�״̬	
	FILE_UPLOAD_ERROR,				//�ϴ��ļ�����
	FILE_DOWNLOAD_ERROR,			//�����ļ�����
	FILE_ONGET_FILEINFO,			//�ص��ļ���Ϣ
	FILE_ONGET_POSITION,			//�ص��ļ�����λ��

	/*�����ļ������ڲ����������������������������������������������������������������������*/
	FILE_GET_FILELIST,				//��ȡ�����ļ��б�
	FILE_ONGET_FILELIST,			//�ص������ļ��б�
	FILE_AUTO_DOWNLOAD,				//�Զ����������ļ�
	FILE_ONREQUEST_DOWNLOAD,		//�յ������ļ�����
	FILE_ONDOWNLOAD_DATA,			//�յ������ļ�����

	/*�����ĵ������ע��أ���������������������������������������������������������������*/
	FS_ADD_OBJ,						//��Ӷ���
	FS_DELETE_OBJ,					//ɾ������	
	FS_REQUEST_ALLOBJ,				//�������ж���	
	FS_CHANGE_PAGE,					//Page�ı�
	FS_GETCUR_PAGEOBJ,				//�õ���ǰPage����
	FS_DELCUR_PAGEOBJ,				//ɾ����ǰPage����
	FS_SET_FILERECT,				//�����ļ��������С

	/*����Flash������أ�����������������������������������������������������������������������*/
	FLASH_SHARE_PLAY,				//��ʼ����Flash	
	FLASH_SHARE_STOP,				//ֹͣ����Flash	
	FLASH_SHARE_PAUSE,				//��ͣ����Flash
	FLASH_SHARE_POSITION,			//����Flash����λ��
	FLASH_SHARE_SEEK,				//SeekFlash����λ��
	FLASH_SHARE_REQUEST,			//����Flash����λ��
	
	/*����2008.6.4 �¼� �ĵ�������أ���������������������������������������������������������������*/
	FS_SET_ZOOM,					//����	
	FS_MOVE_POS,					//�ƶ�λ��	
	FS_GET_POS,						//��ȡλ��	
	FS_ON_CURPAGEOBJ,				//�ص���ǰҳ����
};




