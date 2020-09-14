//BeforehandAndPostProcesserForRedo.cpp

#include"BeforehandAndPostProcesserForRedo.h"
#include"ConstraintSolver.h"
#include"NotePadState.h"
#include"Selector.h"
#include"NotePadForm.h"
#include"SelectModifier.h"


BeforehandAndPostProcesserForRedo::BeforehandAndPostProcesserForRedo(NotePadForm* notePadForm, NotePadHistory* notePadHistory) {
	this->notePadForm = notePadForm;
	this->notePadHistory = notePadHistory;
}

BeforehandAndPostProcesserForRedo::~BeforehandAndPostProcesserForRedo() {
	
}

bool BeforehandAndPostProcesserForRedo::DoBeforehandProcessForRedo() {

	bool isGoingToBeSelected = false;

	ConstraintSolver constraintSolver(this->notePadForm);
	NotePadState* notePadState = 0;

	constraintSolver.SetMemento(this->notePadHistory->GetAt(this->notePadHistory->GetCurrent()));
	notePadState = constraintSolver.GetNotePadState();

	if (notePadState->GetIsSelectionErasedBeforeAction() == true && notePadState->GetIsRemoveAction() == false) {

		Long rowIndexRelatedWithBeforeAction = notePadState->GetRowIndexRelatedWithAction();
		Long columnIndexRelatedWithBeforeAction = notePadState->GetColumnIndexRelatedWithAction();

		this->notePadHistory->MoveNextHistory();
		constraintSolver.SetMemento(notePadHistory->GetAt(notePadHistory->GetCurrent()));
		constraintSolver.SolveReDoingSelectionErasedBeforeActionConstraint(rowIndexRelatedWithBeforeAction, columnIndexRelatedWithBeforeAction);
		this->notePadHistory->MoveNextHistory();

		isGoingToBeSelected = true;
	}
	return isGoingToBeSelected;
}


void BeforehandAndPostProcesserForRedo::DoPostProcessForRedo() {

	ConstraintSolver constraintSolver(this->notePadForm);
	NotePadState* notePadState = 0;

	constraintSolver.SetMemento(this->notePadHistory->GetAt(this->notePadHistory->GetCurrent() - 1));
	notePadState = constraintSolver.GetNotePadState();

	if (notePadState->GetIsPasteAction() == true) {
		constraintSolver.SetMemento(this->notePadHistory->GetAt(this->notePadHistory->GetCurrent()));
		NotePadState* relativeAfterNotePadState = constraintSolver.GetNotePadState();

		Selector* selector = this->notePadForm->GetSelector();
		selector->SetOriginRowIndex(notePadState->GetRowIndexRelatedWithAction());
		selector->SetOriginColumnIndex(notePadState->GetColumnIndexRelatedWithAction());
		selector->SetEndRowIndex(relativeAfterNotePadState->GetRowIndexRelatedWithAction());
		selector->SetEndColumnIndex(relativeAfterNotePadState->GetColumnIndexRelatedWithAction());

		SelectModifier selectModifier(selector);
		selectModifier.SetAbsoluteSelectionInformation();
		if (this->notePadForm->GetIsAutoLineBreak() == false) {
			this->notePadForm->GetSelector()->ReHighLightRightDownwardSumRegionMatchToClientArea();
		}
		this->notePadForm->SetIsSelected(true);
		this->notePadForm->SetIsReDoing(true);
	}

	constraintSolver.SetMemento(this->notePadHistory->GetAt(this->notePadHistory->GetCurrent()));
	notePadState = constraintSolver.GetNotePadState();

	if (notePadState->GetIsWritingAction() == true && notePadState->GetGlyph() != 0) {
		Selector* selector = this->notePadForm->GetSelector();

		selector->SetOriginRowIndex(notePadState->GetRowIndexRelatedWithAction());
		selector->SetOriginColumnIndex(notePadState->GetColumnIndexRelatedWithAction());
		selector->SetEndRowIndex(notePadState->GetRowIndexRelatedWithAction());
		selector->SetEndColumnIndex(notePadState->GetColumnIndexRelatedWithAction() + 1);

		SelectModifier selectModifier(selector);
		selectModifier.SetAbsoluteSelectionInformation();
		if (this->notePadForm->GetIsAutoLineBreak() == false) {
			this->notePadForm->GetSelector()->ReHighLightRightDownwardSumRegionMatchToClientArea();
		}
		this->notePadForm->SetIsSelected(true);
		this->notePadForm->SetIsReDoing(true);
	}
}