
//========================================================================================
//版权所有: 版权所有(C) 2008
//系统名称: 
//作　　者: 
//创建日期: 
//功能说明: DTS所有命令解析头定义及模块共用参数定义
//

#pragma once


#define LOCAL_DEBUG
#undef	LOCAL_DEBUG


#define FILE_TRANS_MAXLENGTH 8*1024	  //每个包的大小
#define FILE_TRANS_PACKETCOUNT 3      //第一次请求的个数

#define LOCAL_SESSIONID 1		  //本地SessionID
#define DEFNET_SESSIONID 2		  //默认网络SessionID

//文件传输结构体定义
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

//标注，白板对象结构体定义
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
	POINT			ptFile;			//共享文件的大小
	POINT			ptClient;		//显示区域的大小
	UINT			nFlashStatus;	//flash 播放状态
	UINT			nFlashPosition;	//flash 播放位置
	UINT			nDocZoomSize;	//文档共享缩放比例
	UINT			nDocLeft;		//文档共享移动后位置
	UINT			nDocTop;		//文档共享移动后位置

}DTS_TEM_DATA,*PDTS_TEM_DATA;

//文件处理状态
enum enumFILESTATUS
{
	FILESTATUS_PAUSE = 0,			//暂停
	FILESTATUS_DONEUP,				//上传完成
	FILESTATUS_DONELOAD,			//下载完成
	FILESTATUS_WAIT,				//等待
	FILESTATUS_TRANSMIT,			//传输中
};

//DTS处理命令
enum enumDTSCOMMAND
{	
	WB_COMMAND_DATA = 0,			//白板数据

	/*－－文件传输界面发送命令－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－*/
	FILE_SEND_ADDFILE,				//发送添加文件
	FILE_SEND_DELETEFILE,			//发送删除命令
	FILE_REQUEST_DOWNLOAD,			//发送下载文件请求	
	FILE_PAUSE_DOWNLOAD,			//暂停下载文件
	FILE_CONTINUE_DOWNLOAD,			//继续下载文件
	FILE_PAUSE_UPLOAD,				//暂停上传文件
	FILE_CONTINUE_UPLOAD,			//继续上传文件	
	FILE_GET_FILEINFO,				//获取文件信息
	FILE_GET_POSITION,				//得到文件传输位置
	FILE_REQUEST_FILELIST,			//请求所有文件列表
	/*－－文件传输界面回调命令－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－*/
	FILE_INSERT_FILE,				//新增文件信息
	FILE_DELETE_FILE,				//删除文件信息
	FILE_UPDATE_STATUS,				//更新文件状态	
	FILE_UPLOAD_ERROR,				//上传文件错误
	FILE_DOWNLOAD_ERROR,			//下载文件错误
	FILE_ONGET_FILEINFO,			//回调文件信息
	FILE_ONGET_POSITION,			//回调文件传输位置

	/*－－文件传输内部处理命令－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－*/
	FILE_GET_FILELIST,				//获取所有文件列表
	FILE_ONGET_FILELIST,			//回调所有文件列表
	FILE_AUTO_DOWNLOAD,				//自动继续下载文件
	FILE_ONREQUEST_DOWNLOAD,		//收到下载文件请求
	FILE_ONDOWNLOAD_DATA,			//收到下载文件数据

	/*－－文档共享标注相关－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－*/
	FS_ADD_OBJ,						//添加对象
	FS_DELETE_OBJ,					//删除对象	
	FS_REQUEST_ALLOBJ,				//请求所有对象	
	FS_CHANGE_PAGE,					//Page改变
	FS_GETCUR_PAGEOBJ,				//得到当前Page对象
	FS_DELCUR_PAGEOBJ,				//删除当前Page对象
	FS_SET_FILERECT,				//设置文件及区域大小

	/*－－Flash共享相关－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－*/
	FLASH_SHARE_PLAY,				//开始播放Flash	
	FLASH_SHARE_STOP,				//停止播放Flash	
	FLASH_SHARE_PAUSE,				//暂停播放Flash
	FLASH_SHARE_POSITION,			//更新Flash播放位置
	FLASH_SHARE_SEEK,				//SeekFlash播放位置
	FLASH_SHARE_REQUEST,			//请求Flash播放位置
	
	/*－－2008.6.4 新加 文档共享相关－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－*/
	FS_SET_ZOOM,					//缩放	
	FS_MOVE_POS,					//移动位置	
	FS_GET_POS,						//获取位置	
	FS_ON_CURPAGEOBJ,				//回调当前页数据
};




