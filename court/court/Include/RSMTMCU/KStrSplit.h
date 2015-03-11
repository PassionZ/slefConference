#ifndef __KSTRSPLIT_H
#define __KSTRSPLIT_H

#include <string>
#include <map>

typedef std::map<int,std::string> STRING_SPLIT_MAP;

class KStrSplit
{
public:
	KStrSplit(const std::string& data,char token);
	virtual ~KStrSplit(void);
	std::string operator[](int Index);
	int GetCount(void);

private:
	STRING_SPLIT_MAP m_mapStringSplit;
};

#endif