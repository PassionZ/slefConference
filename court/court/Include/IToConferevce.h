// ITOCONFERENCE.h

#if !defined(_TOCONFERENCE_H_)
#define _TOCONFERENCE_H_

#ifdef _TOCONFERENCE_
#define DllExport_TO_CONFERENCE __declspec(dllexport)
#else
#define DllExport_TO_CONFERENCE __declspec(dllimport) 
#endif

// 创建视频会议系统调用接口
DllExport_TO_CONFERENCE int CreateToConference();
#endif