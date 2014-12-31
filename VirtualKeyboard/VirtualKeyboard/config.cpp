#include "stdafx.h"
#include "config.h"

#define ELEM_COUNT(a) (sizeof(a)/sizeof(a[0]))
//zyb       
//0��
LPCSTR AlphaTable1[] = {
//  0   1   2   3   4   5   6   7   8   9
    "q","w","e","r","t","y","u","i","o","p",
//  10  11  12  13  14  15  16  17  18
    "a","s","d","f","g","h","j","k","l",
//  19  20  21  22  23  24  25
    "z","x","c","v","b","n","m",
//    26
    "pau"
};
LPCSTR AlphaTable2[] = {
    "Q","W","E","R","T","Y","U","I","O","P",
    "A","S","D","F","G","H","J","K","L",
    "Z","X","C","V","B","N","M",
    "brk"
};
const int AlphaTableSize = ELEM_COUNT(AlphaTable1); //27

//1��
LPCSTR SymbolTable1[] = {
//  0   1   2   3   4   5   6   7   8   9   10  11  12
    "`","1","2","3","4","5","6","7","8","9","0","-","=",
//  13  14  15
    "[","]","\\",
//  16  17
    ";","'",
//  18  19  20
    ".",",","/"
};
LPCSTR SymbolTable2[] = {
    "~","!","@","#","$","%","^","&","*","(",")","-","+",
    "[","]","\\",
    ";","'",
    "<",">","?"
};
const int SymbolTableSize = ELEM_COUNT(SymbolTable1);   //21

//2��
LPCSTR NumPadTable1[] = {
    "7","8","9",
    "4","5","6",
    "1","2","3",
    "0","."
};
LPCSTR NumPadTable2[] = {
    "hm","��","pup",
    "��","  ","��",
    "end","��","pdn",
    "ins","del"
};
const int NumPadTableSize = ELEM_COUNT(NumPadTable1);   //11

//3��
LPCSTR MainTable[] = {
//  0      1       2      3     4
    "lock","shift","ctrl","win","alt",
//  5     6    7    8    9    10   11   12   13   14   15    16    17    18    19
    "esc","F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12","psc","slk",
//  20     21    22    23
    "bksp","ins","hm","pup",
//  24    25    26    27
    "tab","del","end","pdn",
//  28    29   30   31   32   33  34
    "ent","��","��","��","��"," ","app"
};
const int MainTableSize = ELEM_COUNT(MainTable);    //35

//4��
LPCSTR HelpTable[] = {
//  0     1   2   3   4   5
    "nlk","/","*","-","+","ent"
};
const int HelpTableSize = ELEM_COUNT(HelpTable);    //6

KeyConfig kcs[] = {
    3,5,{1,1,9,9},VK_ESCAPE,
    3,6,{19,1,27,9},VK_F1,
    3,7,{28,1,36,9},VK_F2,
    3,8,{37,1,45,9},VK_F3,
    3,9,{46,1,54,9},VK_F4,
    3,10,{60,1,68,9},VK_F5,
    3,11,{69,1,77,9},VK_F6,
    3,12,{78,1,86,9},VK_F7,
    3,13,{87,1,95,9},VK_F8,
    3,14,{101,1,109,9},VK_F9,
    3,15,{110,1,118,9},VK_F10,
    3,16,{119,1,127,9},VK_F11,
    3,17,{128,1,136,9},VK_F12,
    3,18,{137,1,145,9},VK_SNAPSHOT,
    3,19,{146,1,154,9},VK_SCROLL,
    0,26,{155,1,163,9},VK_PAUSE,

    1,0,{1,10,9,18},0xC0,
    1,1,{10,10,18,18},'1',
    1,2,{19,10,27,18},'2',
    1,3,{28,10,36,18},'3',
    1,4,{37,10,45,18},'4',
    1,5,{46,10,54,18},'5',
    1,6,{55,10,63,18},'6',
    1,7,{64,10,72,18},'7',
    1,8,{73,10,81,18},'8',
    1,9,{82,10,90,18},'9',
    1,10,{91,10,99,18},'0',
    1,11,{100,10,108,18},0xBD,
    1,12,{109,10,117,18},0xBB,
    3,20,{118,10,136,18},VK_BACK,
    3,21,{137,10,145,18},VK_INSERT,
    3,22,{146,10,154,18},VK_HOME,
    3,23,{155,10,163,18},VK_PRIOR,

    3,24,{1,19,14,27},VK_TAB,
    0,0,{15,19,23,27},'Q',
    0,1,{24,19,32,27},'W',
    0,2,{33,19,41,27},'E',
    0,3,{42,19,50,27},'R',
    0,4,{51,19,59,27},'T',
    0,5,{60,19,68,27},'Y',
    0,6,{69,19,77,27},'U',
    0,7,{78,19,86,27},'I',
    0,8,{87,19,95,27},'O',
    0,9,{96,19,104,27},'P',
    1,13,{105,19,113,27},0xDB,
    1,14,{114,19,122,27},0xDD,
    1,15,{123,19,136,27},0xDC,
    3,25,{137,19,145,27},VK_DELETE,
    3,26,{146,19,154,27},VK_END,
    3,27,{155,19,163,27},VK_NEXT,

    3,0,{1,28,18,36},VK_CAPITAL,
    0,10,{19,28,27,36},'A',
    0,11,{28,28,36,36},'S',
    0,12,{37,28,45,36},'D',
    0,13,{46,28,54,36},'F',
    0,14,{55,28,63,36},'G',
    0,15,{64,28,72,36},'H',
    0,16,{73,28,81,36},'J',
    0,17,{82,28,90,36},'K',
    0,18,{91,28,99,36},'L',
    1,16,{100,28,108,36},0xBA,
    1,17,{109,28,117,36},0xDE,
    3,28,{118,28,136,36},VK_RETURN,

    3,1,{1,37,23,45},VK_LSHIFT,
    0,19,{24,37,32,45},'Z',
    0,20,{33,37,41,45},'X',
    0,21,{42,37,50,45},'C',
    0,22,{51,37,59,45},'V',
    0,23,{60,37,68,45},'B',
    0,24,{69,37,77,45},'N',
    0,25,{78,37,86,45},'M',
    1,18,{87,37,95,45},0xBC,
    1,19,{96,37,104,45},0xBE,
    1,20,{105,37,113,45},0xBF,
    3,1,{114,37,136,45},VK_RSHIFT,
    3,29,{146,37,154,45},VK_UP,

    3,2,{1,46,14,54},VK_LCONTROL,
    3,3,{15,46,23,54},VK_LWIN,
    3,4,{24,46,35,54},VK_LMENU,
    3,33,{36,46,92,54},VK_SPACE,
    3,4,{93,46,104,54},VK_RMENU,
    3,3,{105,46,113,54},VK_RWIN,
    3,34,{114,46,122,54},VK_APPS,
    3,2,{123,46,136,54},VK_RCONTROL,
    3,30,{137,46,145,54},VK_LEFT,
    3,31,{146,46,154,54},VK_DOWN,
    3,32,{155,46,163,54},VK_RIGHT,

    //----------
    4,0,{164,10,172,18},VK_NUMLOCK,
    4,1,{173,10,181,18},VK_DIVIDE,
    4,2,{182,10,190,18},VK_MULTIPLY,
    4,3,{191,10,199,18},VK_SUBTRACT,

    2,0,{164,19,172,27},VK_NUMPAD7,
    2,1,{173,19,181,27},VK_NUMPAD8,
    2,2,{182,19,190,27},VK_NUMPAD9,
    4,4,{191,19,199,36},VK_ADD,

    2,3,{164,28,172,36},VK_NUMPAD4,
    2,4,{173,28,181,36},VK_NUMPAD5,
    2,5,{182,28,190,36},VK_NUMPAD6,

    2,6,{164,37,172,45},VK_NUMPAD1,
    2,7,{173,37,181,45},VK_NUMPAD2,
    2,8,{182,37,190,45},VK_NUMPAD3,
    4,5,{191,37,199,54},VK_RETURN,

    2,9,{164,46,181,54},VK_NUMPAD0,
    2,10,{182,46,190,54},VK_DECIMAL
};
const int kcSize = ELEM_COUNT(kcs);
const SIZE kbSize = {199,54};