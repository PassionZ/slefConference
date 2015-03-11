#ifndef __LOG_H
#define __LOG_H

#include <fstream>
#include <string>

//#define VIEW_CHANNEL


class Log:public std::ofstream{
public:
	Log();
	Log(char* cFileName);
};	

extern Log logger;
#ifdef VIEW_CHANNEL
extern Log loggerVideoTcp;
extern Log loggerAudio;
#endif


#endif

