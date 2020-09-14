//HistoryModifier.cpp

#include"HistoryModifier.h"
#include"ConstraintSolver.h"
#include"ConstraintSolverMemento.h"
#include"NotePadState.h"
#include"SingleByteCharacter.h"
#include"glyph.h"
#include"NotePadForm.h"
#include"StringMaker.h"


HistoryModifier::HistoryModifier(NotePadHistory* notePadHistory,NotePadForm* notePadForm) {
	this->notePadHistory = notePadHistory;
	this->notePadForm = notePadForm;
}


HistoryModifier::~HistoryModifier() {

}


void HistoryModifier::ModifyWriteStateToRemoveState(NotePadState* notePadState) {
	notePadState->SetIsWritingAction(false);
	notePadState->SetIsRemoveAction(true);
	notePadState->SetIsBackSpaceRemoving(true);
}


void HistoryModifier::ModifyRemoveStateToWriteState(NotePadState* notePadState) {
	notePadState->SetIsRemoveAction(false);
	notePadState->SetIsWritingAction(true);
	if (notePadState->GetIsBackspaceRemoving() == true) {//단어,줄일때 구분해서!! 일단 단어끼리부터 단어도 텝이냐 아니냐
		notePadState->SetIsBackSpaceRemoving(false);
	}
}


void HistoryModifier::ModifyPasteStateToCutOutState(NotePadState* notePadState) {
	notePadState->SetIsPastegAction(false);
	notePadState->SetIsCutOutAction(true);
}


void HistoryModifier::ModifyCutOutStateToPasteState(NotePadState* notePadState) {
	notePadState->SetIsCutOutAction(false);
	notePadState->SetIsPastegAction(true);
}

void HistoryModifier::ModifyRemoveSelectionEraseToPasteState(NotePadState* notePadState) {
	notePadState->SetIsRemoveAction(false);
	notePadState->SetIsSelectionErasedBeforeAction(false);
	notePadState->SetIsPastegAction(true);
}


void HistoryModifier::ModifySelectionErasedBeforeActionToPasteState(NotePadState* notePadState) {
	notePadState->SetIsSelectionErasedBeforeAction(false);
	notePadState->SetIsPastegAction(true);
}


void HistoryModifier::ModifyPasteStateToSelectionErasedBeforeActionState(NotePadState* notePadState) {
	
	notePadState->SetIsSelectionErasedBeforeAction(true);
	notePadState->SetIsPastegAction(false);
}


NotePadState* HistoryModifier::ModifyWriteStateToSelectionErasedBeforeActionState(NotePadState* notePadState) {
	NotePadState* beforeActionNotePadState = 0;
	notePadState->SetIsSelectionErasedBeforeAction(true);
	notePadState->SetIsWritingAction(false);
	if (notePadState->GetGlyph()!=0) {
		notePadState->SetContents(new string(notePadState->GetGlyph()->GetContents()));
		if (notePadState->GetGlyph() != 0) {
			delete notePadState->GetGlyph();
			notePadState->SetGlyph(0);
		}
		beforeActionNotePadState = new NotePadState(*notePadState);
		beforeActionNotePadState->SetColumnIndexRelatedWithAction(notePadState->GetColumnIndexRelatedWithAction() + 1);
	}
	else {
		string* contents = new string("\r\n");
		notePadState->SetContents(contents);
		beforeActionNotePadState = new NotePadState(*notePadState);
		beforeActionNotePadState->SetRowIndexRelatedWithAction(notePadState->GetRowIndexRelatedWithAction()+1);
		beforeActionNotePadState->SetColumnIndexRelatedWithAction(0);
	}
	return beforeActionNotePadState;
}