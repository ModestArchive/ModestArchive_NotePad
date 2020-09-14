//DummyRow.h

#ifndef _DUMMYROW_H
#define _DUMMYROW_H
#include "Row.h"



class DummyRow :public Row{
public:
	DummyRow(Long capacity = 1024);
	DummyRow(const DummyRow& source);
	virtual ~DummyRow();
	virtual Iterator<Glyph*>* CreateIterator();
	
    //Add�� �־������ ������
	virtual Long Put(Long index, Glyph* glyph);//�������̵��ϰ� �ٸ�ó���� ���������������
	virtual string GetContents();
	virtual Glyph* Clone();//�ٸ��� ����� ����������
	void SetIsTabErasedTrue();
	void SetIsTabErasedFalse();
	void SetIsSubjectedHyphenationRuleTrue();
	bool GetIsTabErased() const;
	bool GetIsSubjectedHypenationRule() const;
private:
	bool isSubjectedHyphenationRule;
	bool isTabErased;
};

inline bool DummyRow::GetIsTabErased() const {
	return isTabErased;
}
inline bool DummyRow::GetIsSubjectedHypenationRule() const {
	return isSubjectedHyphenationRule;
}
#endif//_DUMMYROW_H

