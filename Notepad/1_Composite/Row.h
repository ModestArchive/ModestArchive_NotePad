//Row.h

#ifndef _ROW_H
#define _ROW_H
#include "Composite.h"



class Row :public Composite {
public:
	Row(Long capacity = 1024);
	Row(const Row& source);
	virtual ~Row();
	virtual Iterator<Glyph*>* CreateIterator();
	virtual Long Add(Glyph* glyph);
	virtual Long Put(Long index, Glyph* glyph);
	virtual string GetContents();
	virtual Glyph* Clone();
	void SearchMatchCharDuplicate(string* findWhatContents,Long* (*indexes),Long *count, int(*compare)(void*,void*));
};
#endif//_ROW_H
