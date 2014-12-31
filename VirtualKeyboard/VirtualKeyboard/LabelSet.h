#pragma once


//��ĸ��ǩ����
class LabelSet
{
public:
	LabelSet(LPCSTR* _pTable,int _n);
	LPCSTR getLabel(int _id) const;

	~LabelSet();

protected:
	LabelSet(){}

private:
	LPCSTR* pTable;
	int n;
};

//�൱�ڵ���˫��������
class LabelSetEx
{
protected:
	struct Switch
	{
		LabelSet* s[2];
		int at;
	};

public:
	LabelSetEx(int _n);
	bool addSets(int id,LPCSTR* s1,LPCSTR* s2,int n,int at = 0);
	LPCSTR getLable(int id,int off) const;
    void turn(int id);

	~LabelSetEx();

private:
	int n;	//�������ܸ���
	Switch* pGroup;	//������
};