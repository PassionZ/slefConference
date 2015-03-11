#include "stdafx.h"
#include "Config.h"
#include <fstream>
#include <ctype.h>
#include <sstream>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

const string Config::GROUP_DEFAULT("default");

Config::Config(string filename)
{
	pathname = filename;
}

void Config::trimString(string &str)
{
	int i = 0;
	for(; i < (int)str.length() && isspace(str[i]); i++);
	
	str = str.substr(i);
	
	for(i = (int)str.length() - 1; i >= 0 && isspace(str[i]); i--);

	str.erase(i + 1);
	
}

bool Config::load(int &errLine)
{
	ifstream in(pathname.c_str());
	
	string value;

	paragraph.clear();
	errLine = 0;

	string currentGroup = GROUP_DEFAULT;
	Pairs pairs;

	while(getline(in, value)){
		errLine++;
		trimString(value);
		if(value[0] == '#')
			continue;
		
		if(value.length() == 0)
			continue;


		string::size_type idx = value.find("=");

		if(idx == string::npos){
			if(value[0] == '[' && value[value.length() - 1] == ']'){
				value.erase(value.length() - 1);
				value.erase(0, 1);
				
				paragraph[currentGroup] = pairs;

				currentGroup = value;
				pairs.clear();
			} else
				return false;
		} else{
			string key = value.substr(0, idx);
			trimString(key);
			
			string val = value.substr(idx + 1);
			trimString(val);
			pairs[key] = val;
		}
	}
	paragraph[currentGroup] = pairs;
	return true;
}	
		
int Config::getInt(string group, string name)
{
	int val = 0;
	istringstream in(getString(group, name));
	in >> val;
	return val;
}

string Config::getString(string para, string name)
{
	string group = para;
	trimString(group);
	if(0 == (int)group.length())
		group = GROUP_DEFAULT;

       	map<string, Pairs, greater<string> >::iterator pos = paragraph.find(group);
	if(pos != paragraph.end()){
		Pairs pairs = pos->second;
		Pairs::iterator p = pairs.find(name);
		if(p != pairs.end())
			return p->second;
	}

	string str;
	return str;
}

void Config::set(string para, string name, string value)
{
	string group = para;
	trimString(group);
	if(group.length() == 0)
		group = GROUP_DEFAULT;

	Pairs &pairs = paragraph[group];
	pairs[name] = value;
}

void Config::set(string paragraph, string name, int value)
{
	ostringstream os;
	os << value;
	set(paragraph, name, os.str());
}

void Config::dump(ostream &os)
{
//dump DEFAULT_GROUP group first
	Pairs pairs = paragraph[GROUP_DEFAULT];

	Pairs::iterator p = pairs.begin();
	for(; p != pairs.end(); ++p){
		os << p->first << '=' << p->second << endl;
	}

       	map<string, Pairs, greater<string> >::iterator pos =  paragraph.begin();
       
	for(; pos != paragraph.end(); ++pos){
		pairs = pos->second;
		if(pos->first == GROUP_DEFAULT)
			continue;

		os << '[' << pos->first << ']' << endl;
		p = pairs.begin();
		for(; p != pairs.end(); ++p){
			os << p->first << '=' << p->second << endl;
		}
	}
}

void Config::save()
{
	ofstream out(pathname.c_str());
	dump(out);
}
			
