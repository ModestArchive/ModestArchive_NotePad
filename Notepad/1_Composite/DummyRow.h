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
	
    //Add도 있어야하지 않을까
	virtual Long Put(Long index, Glyph* glyph);//오버라이딩하고 다른처리를 해줘야하지않을까
	virtual string GetContents();
	virtual Glyph* Clone();//다르게 해줘야 하지않을까
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

