#pragma once

//����id�Ķ���
#define LABEL_SET_ALPHA  0
#define LABEL_SET_SYMBOL 1
#define LABEL_SET_NUMPAD 2
#define LABEL_SET_MAIN   3
#define LABEL_SET_HELP   4

//��ĸ����
extern LPCSTR AlphaTable1[];	//Сд
extern LPCSTR AlphaTable2[];	//��д
extern const int AlphaTableSize;

//���Ŵ���
extern LPCSTR SymbolTable1[];	//��
extern LPCSTR SymbolTable2[];	//��
extern const int SymbolTableSize;

//С�������ֱ�
extern LPCSTR NumPadTable1[];	//����
extern LPCSTR NumPadTable2[];	//������
extern const int NumPadTableSize;

//�����̵���
extern LPCSTR MainTable[];
extern const int MainTableSize;

//�������̵���
extern LPCSTR HelpTable[];
extern const int HelpTableSize;

struct KeyConfig
{
	short id;		//����id
	short offset;	//����ƫ��
	RECT rt;	//λ��
	BYTE vk;	//������
};

extern KeyConfig kcs[];
extern const int kcSize;
extern const SIZE kbSize;