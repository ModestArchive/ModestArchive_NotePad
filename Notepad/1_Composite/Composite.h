//Composite.h
#ifndef _COMPOSITE_H
#define _COMPOSITE_H

#include "Glyph.h"
#include "Array.h"
typedef signed long int Long;


class Composite :public Glyph {
public:
	//생성자,소멸자
	Composite(Long capacity = 256);
	Composite(const Composite& source);
	virtual ~Composite();
	
	//메소드
	virtual Long Change(Long index, Glyph* glyph);
	virtual Glyph* GetAt(Long index);
	virtual Long Remove(Long index);
	virtual Long First() ;
	virtual Long Last() ;
	virtual Long Previous() ;
	virtual Long Next() ;
	
	//연산자함수
	Composite& operator=(const Composite& source);
	Glyph* operator[](Long index);
	//인라인함수
	Long GetCapacity() const;
	virtual Long GetLength() const;
	virtual Long GetCurrent() const;

protected:
	Array<Glyph*> glyphs;
	Long capacity;
	Long length;
	Long current;
};

inline Long Composite::GetCapacity() const {
	return this->capacity;

}

inline Long Composite::GetLength() const {
	return this->length;
}
inline Long Composite::GetCurrent() const {
	return this->current;
}
#endif//_COMPOSITE_H