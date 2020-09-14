//PostProcessForUndo.h

#include"PostProcesserForUndo.h"
#include"ConstraintSolver.h"
#include"NotePadState.h"
#include"Selector.h"
#include"NotePadForm.h"
#include"SelectModifier.h"


PostProcesserForUndo::PostProcesserForUndo(NotePadForm* notePadForm,NotePadHistory* notePadHistory) {
	this->notePadForm = notePadForm;
	this->notePadHistory = notePadHistory;
}


PostProcesserForUndo::~PostProcesserForUndo() {

}


void PostProcesserForUndo::DoPostProcessForUndo() {
	ConstraintSolver constraintSolver(this->notePadForm);
	NotePadState* notePadState = 0;
	constraintSolver.SetMemento(notePadHistory->GetAt(notePadHistory->GetCurrent()));
	notePadState = constraintSolver.GetNotePadState();

	if (notePadState->GetIsCutOutAction() == true || 
	    (notePadState->GetIsSelectionErasedBeforeAction() == true && notePadState->GetIsRemoveAction() == true)) {

		constraintSolver.SetMemento(notePadHistory->GetAt(notePadHistory->GetCurrent() + 1));
		NotePadState* relativeAfterNotePadState = constraintSolver.GetNotePadState();

		Selector* selector = this->notePadForm->GetSelector();
		selector->SetOriginRowIndex(relativeAfterNotePadState->GetRowIndexRelatedWithAction());
		selector->SetOriginColumnIndex(relativeAfterNotePadState->GetColumnIndexRelatedWithAction());
		selector->SetEndRowIndex(notePadState->GetRowIndexRelatedWithAction());
		selector->SetEndColumnIndex(notePadState->GetColumnIndexRelatedWithAction());

		SelectModifier selectModifier(selector);
		selectModifier.SetAbsoluteSelectionInformation();
		if (this->notePadForm->GetIsAutoLineBreak() == false) {
			this->notePadForm->GetSelector()->ReHighLightRightDownwardSumRegionMatchToClientArea();
		}
		this->notePadForm->SetIsSelected(true);
		this->notePadForm->SetIsUnDoing(true);
	}
	else if (this->notePadHistory->GetCurrent() > 0) {

		constraintSolver.SetMemento(notePadHistory->GetAt(notePadHistory->GetCurrent() - 1));
		notePadState = constraintSolver.GetNotePadState();

		if (notePadState->GetIsReplaceAllContentsAction()==false && 
			notePadState->GetIsSelectionErasedBeforeAction() == true && notePadState->GetIsRemoveAction() == false) {

			this->notePadHistory->MovePreviousHistory();
			constraintSolver.SolveUnDoingSelectionErasedBeforeActionConstraint();
			this->notePadHistory->MovePreviousHistory();

			Selector* selector = this->notePadForm->GetSelector();
			selector->SetOriginRowIndex(notePadState->GetRowIndexRelatedWithAction());
			selector->SetOriginColumnIndex(notePadState->GetColumnIndexRelatedWithAction());

			constraintSolver.SetMemento(notePadHistory->GetAt(notePadHistory->GetCurrent()));

			notePadState = constraintSolver.GetNotePadState();
			selector->SetEndRowIndex(notePadState->GetRowIndexRelatedWithAction());
			selector->SetEndColumnIndex(notePadState->GetColumnIndexRelatedWithAction());

			SelectModifier selectModifier(selector);
			selectModifier.SetAbsoluteSelectionInformation();
			if (this->notePadForm->GetIsAutoLineBreak() == false) {
				this->notePadForm->GetSelector()->ReHighLightRightDownwardSumRegionMatchToClientArea();
			}
			this->notePadForm->SetIsSelected(true);
			this->notePadForm->SetIsUnDoing(true);
		}
	}
}