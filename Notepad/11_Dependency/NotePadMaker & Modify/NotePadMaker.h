//NotePadMaker.h


#ifndef _NOTEPADMAKER_H
#define _NOTEPADMAKER_H

#include <string.h>
#include<iostream>
#include"NotePadForm.h"

using namespace std;

class NotePadMaker {

public:
	NotePadMaker(NotePadForm *notePadForm);
	~NotePadMaker();
	void MakeNotePad(string contents);

	void PlusRowInNotePad();
	void WriteTabInRow(char(* contents));
	void WriteSingleByteCharacterInRow(char(* contents));
	void WriteDoubleByteCharacterInRow(char(* contents));
	void WriteCompleteDoubleByteCharacterInRow(char(*contents));

	void EraseCurrentRowInNotePad();
	void EraseNextRowInNotePad();
	void ErasePreviousCharacterInRow();
	void EraseCurrentCharactorInRow();
	//언두,리두를 위한연산
	void PlusRowInNotePadForUndoRedo();
	void PlusRowInNotePadNoCurrentMoveForUndoRedo();
	void WriteTabInRowForUndoRedo(Glyph* contents);
	void WriteTabInRowNoCurrentMoveForUndoRedo(Glyph* contents);
	void WriteContentsInRowForUndoRedo(Glyph* contents);
	void WriteContentsInRowNoCurrentMoveForUndoRedo(Glyph* contents);
	void EraseCurrentRowInNotePadForUndoRedo();
	void EraseNextRowInNotePadForUndoRedo(); 
	void ErasePreviousCharacterInRowForUndoRedo();
	void EraseCurrentCharactorInRowForUndoRedo();
	void WriteContentsFromStringForUndoRedo(string* contents);
	void EraseDesignatedAreaForUndoPaste(Long rowIndexRelatedWithAfterAction, Long columnIndexRelatedWithAfterAction);
	void EraseDesignatedAreaForRedoCutOut(Long rowIndexRelatedWithBeforeAction, Long columnIndexRelatedWithBeforeAction);
private:
	NotePadForm *notePadForm;
};
#endif // !_NOTEPADMAKER_H
