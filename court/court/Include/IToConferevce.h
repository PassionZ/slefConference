// ITOCONFERENCE.h

#if !defined(_TOCONFERENCE_H_)
#define _TOCONFERENCE_H_

#ifdef _TOCONFERENCE_
#define DllExport_TO_CONFERENCE __declspec(dllexport)
#else
#define DllExport_TO_CONFERENCE __declspec(dllimport) 
#endif

// ������Ƶ����ϵͳ���ýӿ�
DllExport_TO_CONFERENCE int CreateToConference();
#endif