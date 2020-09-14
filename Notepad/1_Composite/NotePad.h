//NotePad.h

#ifndef _NOTEPAD_H
#define _NOTEPAD_H
#include "Composite.h"

class NotePadForm;
class NotePad :public Composite {
public:
	NotePad(Long capacity = 1024);
	NotePad(const NotePad& source);
	virtual ~NotePad();
	virtual Iterator<Glyph*>* CreateIterator();
	virtual Long Add(Glyph* glyph);
	virtual Long Put(Long index, Glyph* glyph);
	virtual string GetContents();
	string SaveModeGetContents();
	string GetContentsForString();
	virtual Glyph* Clone();
	virtual Long Last();
	};
#endif//_NOTEPAD_H
