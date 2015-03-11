#ifndef __CONFIG_H
#define __CONFIG_H

#include <map>
#include <string>
#include <iostream>
#include <xfunctional>

class Config{
 private:
	std::string              pathname;
	typedef std::map<std::string, std::string, std::greater<std::string> > Pairs;
	//typedef std::map<std::string, std::string > Pairs;
	Pairs                    pairs;
	std::map<std::string, Pairs, std::greater<std::string> > paragraph;
	
 public:
	static const std::string GROUP_DEFAULT;
	Config(std::string filename);
	
	static void        trimString(std::string &str);
	int                getInt(std::string paragraph, std::string name);
	void               set(std::string, std::string, std::string);
	void               set(std::string, std::string, int);
	std::string        getString(std::string paragraph, std::string name);
	bool               load(int &errLine);
	
	void               dump(std::ostream &);
	void               save();
};
	
#endif
