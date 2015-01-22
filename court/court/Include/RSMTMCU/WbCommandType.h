#ifndef _WBCOMMANDTYPE_H
#define _WBCOMMANDTYPE_H

//modify by wzf 2006.05.09
/*
typedef struct {	
	unsigned long objId;	
	unsigned char pageId;	
	unsigned char tabId;
	unsigned char type;
}WB_COMMAND_HEAD,*PWB_COMMAND_HEAD;
*/
typedef struct {	
	unsigned long ulObjId;	
	unsigned char byPageId;	
	unsigned char byTabId;
	unsigned char byType;
}WB_COMMAND_HEAD,*LPWB_COMMAND_HEAD, *PWB_COMMAND_HEAD;
//WBDATA

enum TAB_CTRL_FLAG
{
	TAB_CTRL_WHITEBOARD = 0,
	TAB_CTRL_SHAREDOC,
	TAB_CTRL_SHAREVIDEO
};

typedef struct
{
    long    left;
    long    top;
    long    right;
    long    bottom;
}MYRECT;

typedef struct
{
    long  x;
    long  y;
}MYPOINT;

typedef struct {
	MYRECT					rtToolBar;
	MYPOINT					ptWhiteBoard;
	MYPOINT					ptShareDoc;
	unsigned long			dwWhiteBoardPage;
	unsigned long			dwShareDocPage;
	unsigned char			byTabId;
	int						bFullScreen;
}CLIENT_WINDOW_POSITION;

#define DATA_TRANS_ADDOBJECT			1
#define DATA_TRANS_LOADFILE				2
#define DATA_TRANS_MOVEOBJ				3
#define DATA_TRANS_OBJ_RESIZE			4
#define DATA_TRANS_DELETE_ALL			5
#define DATA_TRANS_DELETE_OBJECT		6
#define DATA_TRANS_SCROLL				7
#define DATA_TRANS_COLORREF_CHANGED		8
#define DATA_TRANS_LINE_WIDTH_CHANGED	9
#define DATA_TRANS_FONT_CHANGED			10
#define DATA_TRANS_TEXT_CHANGED			11
#define DATA_TRANS_POINTER_CMD			12
#define DATA_TRANS_LOCK					13
#define DATA_TRANS_PAGE					14
#define DATA_TRANS_SET_BACKBITMAP		15
#define DATA_TRANS_SET_BACKCOLOR		16
#define DATA_TRANS_CLEAR_ALL			17
#define DATA_TRANS_OBJREQUEST			18
#define DATA_TRANS_OBJRESPONSE			19
#define DATA_TRANS_OBJECT_ALL			20
#define DATA_TRANS_DOC_PAGE_CHANGED		21
#define DATA_TRANS_DOC_CLOSE			22
#define DATA_TRANS_DOC_LOADFILE			23
#define DATA_TRANS_TABCTRL_CHANGE		24
#define DATA_TRANS_FULLSCREEN			25
#define DATA_TRANS_TOOLBARMOVE			26
#define DATA_TRANS_WINDOWMOVE			27
#define DATA_TRANS_LASTPOSITION			28

#define DATA_TRANS_REQUESTTOKEN				29      //查询令牌状态  
#define DATA_TRANS_RESPONSETOKENSTATE		30      //反回令牌状态   
#define DATA_TRANS_FILEPRINTFINISH			31		//打印完成消息   
#define DATA_TRANS_FILEPRINTCANCEL			32		//文件打印退出
#define DATA_TRANS_REQUESTLASTPOSITION			33		// 取得当前活动位置 data格式  posx + posy (len=sizeof(int) * 2)
#define DATA_TRANS_RESPONSELASTPOSITION			34		// 取得当前活动位置 data格式  posx + posy (len=sizeof(int) * 2)

#define DATA_TRANS_SHAREFILE_END		37 //add by wzf on 2006.05.16
#define DATA_TRANS_REQUESTSHAREFILE		38
#define DATA_TRANS_RESPONSESHAREFILE	39

#define DATA_TRANS_DTOBJ_LENGTH		40 //add by wzf on 2006.05.25
#define TRANS_REQUESTDTOBJDATA			41 //add by wzf on 2006.05.26
#define TRANS_RESPONSEDTOBJDATA			42 //add by wzf on 2006.05.26
#define TRANS_DTOBJDATA_END				43 //add by wzf on 2006.05.26
#define TRANS_CLEAR_DTOBJDATA			44 //add by wzf on 2006.05.26



//二维绘图对象
#define SHAPE_NULL				0
#define SHAPE_PEN				1
#define SHAPE_COLOR_PEN			2
#define SHAPE_LINE				3
#define SHAPE_EMPTY_RECT		4
#define SHAPE_FILL_RECT			5
#define SHAPE_EMPTY_ELLIPSE		6
#define SHAPE_FILL_ELLIPSE		7
#define SHAPE_TEXT				8
#define SHAPE_BITMAP			9

#endif