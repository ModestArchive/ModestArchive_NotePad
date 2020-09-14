//UndoCommand.cpp

#include"UndoCommand.h"
#include"NotePadRestorer.h"
#include"NotePadHistory.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"TextMetric.h"
#include"ConstraintSolver.h"
#include"NotePadState.h"
#include"SelectModifier.h"
#include"Selector.h"
#include"PostProcesserForUndo.h"

UndoCommand::UndoCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm) : Command(notePadForm){
	this->notePadFormControlWnd = notePadFormControlWnd;
	this->notePadForm = notePadForm;
}


UndoCommand::~UndoCommand() {

}


void UndoCommand::Execute() {
	NotePadRestorer* notePadRestorer = this->notePadForm->GetNotePadRestorer();

	PostProcesserForUndo postProcesserForUndo(this->notePadForm, notePadRestorer->GetNotePadHistory());
	if (notePadRestorer->GetNotePadHistory()->GetLength() > 0 && notePadRestorer->GetNotePadHistory()->GetCurrent() > 0) {

		notePadRestorer->GetNotePadHistory()->MovePreviousHistory();

		ConstraintSolver constraintSolver(this->notePadForm);
		NotePadState* notePadState = 0;
		constraintSolver.SetMemento(notePadRestorer->GetNotePadHistory()->GetAt(notePadRestorer->GetNotePadHistory()->GetCurrent()));
		notePadState = constraintSolver.GetNotePadState();

		if (notePadState->GetIsReplaceAllContentsAction() == true) {
			bool stopUndo = false;
			while (stopUndo == false) {
				stopUndo = notePadRestorer->UndoForReplaceAll();
				if (stopUndo == false) {
					notePadRestorer->GetNotePadHistory()->MovePreviousHistory();
				}
			}
		}
		else {
			notePadRestorer->Undo();
			postProcesserForUndo.DoPostProcessForUndo();
		}

	}
}