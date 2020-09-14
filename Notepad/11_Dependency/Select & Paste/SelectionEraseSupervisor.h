//SelectionEraseSupervisor.h

#ifndef _SELECTIONERASESUPERVISOR_H
#define _SELECTIONERASESUPERVISOR_H
#include"NotePadForm.h"

class NotePadForm;
class SelectionEraseSupervisor{
public:

	SelectionEraseSupervisor(NotePadForm* notePadForm);
	~SelectionEraseSupervisor();
	void EraseContents(string* contents,bool isRemoveAction);
	void EraseContentsForReplaceAll(string* contents, bool isFirstReplace);
	void EraseContentsForReplaceNoneAll(string* contents, bool isFirstReplace, bool isLastReplace);
	void EraseContentsForCtrlX(string* contents);
	
private:
	NotePadForm* notePadForm;
};
#endif//!_SELECTIONERASESUPERVISOR_H
