#pragma once

//分类id的定义
#define LABEL_SET_ALPHA  0
#define LABEL_SET_SYMBOL 1
#define LABEL_SET_NUMPAD 2
#define LABEL_SET_MAIN   3
#define LABEL_SET_HELP   4

//字母串表
extern LPCSTR AlphaTable1[];	//小写
extern LPCSTR AlphaTable2[];	//大写
extern const int AlphaTableSize;

//符号串表
extern LPCSTR SymbolTable1[];	//下
extern LPCSTR SymbolTable2[];	//上
extern const int SymbolTableSize;

//小键盘数字表
extern LPCSTR NumPadTable1[];	//数字
extern LPCSTR NumPadTable2[];	//光标控制
extern const int NumPadTableSize;

//主键盘单显
extern LPCSTR MainTable[];
extern const int MainTableSize;

//辅助键盘单显
extern LPCSTR HelpTable[];
extern const int HelpTableSize;

struct KeyConfig
{
	short id;		//分类id
	short offset;	//类内偏移
	RECT rt;	//位置
	BYTE vk;	//虚拟码
};

extern KeyConfig kcs[];
extern const int kcSize;
extern const SIZE kbSize;