//NotePadMementoMaker.h

#ifndef _NOTEPADMEMENTOMAKER_H
#define _NOTEPADMEMENTOMAKER_H

class Glyph;
class NotePadForm;
class ConstraintSolverMemento;
class NotePadMementoMaker{

public:
	NotePadMementoMaker(NotePadForm* notePadForm);
	~NotePadMementoMaker();
	ConstraintSolverMemento* MakeMemento(bool isWritingAction,
										 bool isRemoveAction,
										 bool isBackspaceRemoving,
										 Glyph* clonGlyph);

	ConstraintSolverMemento* MakeMemento(bool isPasteAction,
										bool isCutOutAction,
										Long designatedRowIndexRelatedWithAction,
										Long designatedColumnIndexRelatedWithAction,
										string* cloneContents);

	ConstraintSolverMemento* MakeNoStandardMemento(bool isSelectionErasedBeforeAction,
													 bool isRemoveAction,
													 Long designatedRowIndexRelatedWithAction,
													 Long designatedColunIndexRealtedWithAction,
													 string* cloneContents);

	ConstraintSolverMemento* MakeReplaceAllMemento(bool isSelectionErasedBeforeAction,
													bool isPasteAction,
													bool isFirstOrLastReplace,
													Long designatedRowIndexRelatedWithAction,
													Long designatedColumnIndexRelatedWithAction,
													string* cloneContents);
	//인라인함수
	NotePadForm* GetNotePadForm() const;
private:
	NotePadForm* notePadForm;
};

inline NotePadForm* NotePadMementoMaker::GetNotePadForm() const {
	return const_cast<NotePadForm*>(this->notePadForm);
}
#endif // !_NOTEPADMEMENTOMAKER_H
