#include"NotePadRestorer.h"
#include"NotePadHistory.h"
#include"ConstraintSolver.h"
#include"NotePadForm.h"
#include"NotePadState.h"


NotePadRestorer::NotePadRestorer(NotePadForm* notePadForm) {
	this->notePadForm = notePadForm;
	this->notePadHistory = new NotePadHistory;
}


NotePadRestorer::~NotePadRestorer() {
	if (this->notePadHistory != 0) {
		delete this->notePadHistory;
	}
}
 

void NotePadRestorer::Undo() {
	ConstraintSolver constraintSolver(this->notePadForm);
	NotePadHistory* notePadHistory = this->notePadForm->GetNotePadRestorer()->GetNotePadHistory();
	constraintSolver.SetMemento(notePadHistory->GetAt(notePadHistory->GetCurrent()));
	
	if (constraintSolver.GetNotePadState()->GetIsWritingAction()==true) {
		constraintSolver.SolveUnDoingWriteConstraint();
	}
	else if (constraintSolver.GetNotePadState()->GetIsRemoveAction() == true) {
		if (constraintSolver.GetNotePadState()->GetIsSelectionErasedBeforeAction() == true) {
			constraintSolver.SolveUnDoingSelectionErasedBeforeActionConstraint();
			notePadHistory->MovePreviousHistory();
		}
		else {
			constraintSolver.SolveUnDoingRemoveConstraint();
		}
	}
	else if (constraintSolver.GetNotePadState()->GetIsPasteAction() == true) {
		Long rowIndexRelatedWithAfterAction = constraintSolver.GetNotePadState()->GetRowIndexRelatedWithAction();
		Long columnIndexRelatedWithAfterAction= constraintSolver.GetNotePadState()->GetColumnIndexRelatedWithAction();
		notePadHistory->MovePreviousHistory();
		constraintSolver.SetMemento(notePadHistory->GetAt(notePadHistory->GetCurrent()));
		constraintSolver.SolveUnDoingPasteConstraint(rowIndexRelatedWithAfterAction, columnIndexRelatedWithAfterAction);
	}
	else if (constraintSolver.GetNotePadState()->GetIsCutOutAction() == true) {
		constraintSolver.SolveUnDoingCutOutConstraint();
		notePadHistory->MovePreviousHistory();
	}
}


bool NotePadRestorer::UndoForReplaceAll() {
	bool stopUndo = false;
	ConstraintSolver constraintSolver(this->notePadForm);
	NotePadHistory* notePadHistory = this->notePadForm->GetNotePadRestorer()->GetNotePadHistory();
	constraintSolver.SetMemento(notePadHistory->GetAt(notePadHistory->GetCurrent()));

	if (constraintSolver.GetNotePadState()->GetIsSelectionErasedBeforeAction() == true && 
		constraintSolver.GetNotePadState()->GetIsRemoveAction() == false ) {

		constraintSolver.SolveUnDoingSelectionErasedBeforeActionConstraint();
		this->notePadHistory->MovePreviousHistory();
	}
	else {
		Long rowIndexRelatedWithAfterAction = constraintSolver.GetNotePadState()->GetRowIndexRelatedWithAction();
		Long columnIndexRelatedWithAfterAction = constraintSolver.GetNotePadState()->GetColumnIndexRelatedWithAction();
		notePadHistory->MovePreviousHistory();
		constraintSolver.SetMemento(notePadHistory->GetAt(notePadHistory->GetCurrent()));
		constraintSolver.SolveUnDoingPasteConstraint(rowIndexRelatedWithAfterAction, columnIndexRelatedWithAfterAction);
	}
	if (notePadHistory->GetCurrent()==0) {
		stopUndo = true;
	}
	else {
		constraintSolver.SetMemento(notePadHistory->GetAt(notePadHistory->GetCurrent()));
		stopUndo = constraintSolver.GetNotePadState()->GetIsBeginOrEndPointOfReplaceAllContents();
	}
	return stopUndo;
}


void NotePadRestorer::Redo() {
	ConstraintSolver constraintSolver(this->notePadForm);
	NotePadHistory* notePadHistory = this->notePadForm->GetNotePadRestorer()->GetNotePadHistory();
	constraintSolver.SetMemento(notePadHistory->GetAt(notePadHistory->GetCurrent()));
	
	if (constraintSolver.GetNotePadState()->GetIsWritingAction() == true) {
		constraintSolver.SolveReDoingWriteConstraint();
	}
	else if (constraintSolver.GetNotePadState()->GetIsRemoveAction() == true) {
		if (constraintSolver.GetNotePadState()->GetIsSelectionErasedBeforeAction() == true) {
			Long rowIndexRelatedWithBeforeAction = constraintSolver.GetNotePadState()->GetRowIndexRelatedWithAction();
			Long columnIndexRelatedWithBeforeAction = constraintSolver.GetNotePadState()->GetColumnIndexRelatedWithAction();
			notePadHistory->MoveNextHistory();
			constraintSolver.SetMemento(notePadHistory->GetAt(notePadHistory->GetCurrent()));
			constraintSolver.SolveReDoingSelectionErasedBeforeActionConstraint(rowIndexRelatedWithBeforeAction, columnIndexRelatedWithBeforeAction);
		}
		else {
			constraintSolver.SolveReDoingRemoveConstraint();
		}
	}
	else if (constraintSolver.GetNotePadState()->GetIsPasteAction() == true) {
		constraintSolver.SolveReDoingPasteConstraint();
		notePadHistory->MoveNextHistory();
	}
	else if (constraintSolver.GetNotePadState()->GetIsCutOutAction() == true) {
		Long rowIndexRelatedWithBeforeAction = constraintSolver.GetNotePadState()->GetRowIndexRelatedWithAction();
		Long columnIndexRelatedWithBeforeAction = constraintSolver.GetNotePadState()->GetColumnIndexRelatedWithAction();
		notePadHistory->MoveNextHistory();
		constraintSolver.SetMemento(notePadHistory->GetAt(notePadHistory->GetCurrent()));
		constraintSolver.SolveReDoingCutOutConstraint(rowIndexRelatedWithBeforeAction, columnIndexRelatedWithBeforeAction);
	}
}


bool NotePadRestorer::RedoForReplaceAll() {
	bool stopRedo = false;

	ConstraintSolver constraintSolver(this->notePadForm);
	NotePadHistory* notePadHistory = this->notePadForm->GetNotePadRestorer()->GetNotePadHistory();
	constraintSolver.SetMemento(notePadHistory->GetAt(notePadHistory->GetCurrent()));

	if (constraintSolver.GetNotePadState()->GetIsSelectionErasedBeforeAction() == true &&
		constraintSolver.GetNotePadState()->GetIsRemoveAction() == false) {

		Long rowIndexRelatedWithBeforeAction = constraintSolver.GetNotePadState()->GetRowIndexRelatedWithAction();
		Long columnIndexRelatedWithBeforeAction = constraintSolver.GetNotePadState()->GetColumnIndexRelatedWithAction();
		this->notePadHistory->MoveNextHistory();
		constraintSolver.SolveReDoingSelectionErasedBeforeActionConstraint(rowIndexRelatedWithBeforeAction, columnIndexRelatedWithBeforeAction);
		
	}
	else {
		constraintSolver.SolveReDoingPasteConstraint();
		notePadHistory->MoveNextHistory();
	}
	
	constraintSolver.SetMemento(notePadHistory->GetAt(notePadHistory->GetCurrent()));
    stopRedo = constraintSolver.GetNotePadState()->GetIsBeginOrEndPointOfReplaceAllContents();
	
	return stopRedo;
}


void NotePadRestorer::SetNotePadHistory(NotePadHistory* notePadHistory) {
	this->notePadHistory = notePadHistory;
}