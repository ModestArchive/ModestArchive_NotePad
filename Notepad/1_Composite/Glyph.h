//Glyph.h

#ifndef _GLYPH_H
#define _GLYPH_H
#include<string>
using namespace std;

typedef signed long int Long;
template <typename T> class Iterator; // !!!!!!!!!! �Ʒ��� ������ ���� �����ؾߵǴϱ�  �ּ� ���漱��
class Glyph{
public:
	Glyph();
	virtual ~Glyph() = 0;
	virtual Iterator<Glyph*>* CreateIterator() { return  0; }; //�̰� �����ָ� doublebytecharacter�ҋ��� �� createIterator�� ������Ѵ�.
	virtual Long Add(Glyph* glyph) { return -1; }; //�̰� composite���� �Ȱ��� �޼ҵ��ε� ���⼭ �ϴ� ���Ǹ� �� �Ҽ������ϱ� �̷����Ѱ�
	virtual Long Put(Long index, Glyph* glyph ) { return -1; };
	virtual Long Change(Long index,Glyph* glyph) { return -1; };
	virtual Glyph* GetAt(Long index) { return 0; }; //���� ����
	virtual string GetContents() = 0; //���⼭ �����Ҽ������ϱ� �׳� ���� �س�����.
	virtual Glyph* Clone() = 0; //���� ����
	virtual Long Remove(Long Index) { return 0; };
	virtual Long First() { return 0; };
	virtual Long Last() { return 0; };
	virtual Long Previous() { return 0; };
	virtual Long Next() { return 0; };
	virtual Long GetLength() const { return 0; };
	virtual Long GetCurrent() const { return 0; };
	

	

	};
#endif // _GLYPH_H

