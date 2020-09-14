//SelectionEraser.h

#ifndef _SELECTIONERASER_H
#define _SELECTIONERASER_H


class NotePadForm;
class SelectionEraser{
public:

	SelectionEraser(NotePadForm* notePadForm);
	~SelectionEraser();
	void EraseSelectionContents();

private:
	NotePadForm* notePadForm;
};
#endif//!_SELECTIONERASER_H

