//CtrlYKey.cpp

#include"CtrlYKey.h"
#include"NotePadRestorer.h"
#include"NotePadHistory.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"TextMetric.h"
#include"ConstraintSolver.h"
#include"NotePadState.h"
#include"Selector.h"
#include"SelectModifier.h"
#include"BeforehandAndPostProcesserForRedo.h"

CtrlYKey::CtrlYKey() {

}

CtrlYKey::CtrlYKey(NotePadForm* notePadForm) : KeyAction(notePadForm) {

}

CtrlYKey::~CtrlYKey() {

}

void CtrlYKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	NotePadRestorer* notePadRestorer = this->notePadForm->GetNotePadRestorer();
	BeforehandAndPostProcesserForRedo beforehandAndPostProcesserForRedo(this->notePadForm, notePadRestorer->GetNotePadHistory());

	bool isGoingToBeSelected = false;

	if (notePadRestorer->GetNotePadHistory()->GetLength() > 0 && 
		notePadRestorer->GetNotePadHistory()->GetCurrent() < notePadRestorer->GetNotePadHistory()->GetLength()) {
		
		ConstraintSolver constraintSolver(this->notePadForm);
		NotePadState* notePadState = 0;
		constraintSolver.SetMemento(notePadRestorer->GetNotePadHistory()->GetAt(notePadRestorer->GetNotePadHistory()->GetCurrent()));
		notePadState = constraintSolver.GetNotePadState();

		if (notePadState->GetIsReplaceAllContentsAction() == true) {
			bool stopRedo = false;
			while (stopRedo == false) {
				stopRedo = notePadRestorer->RedoForReplaceAll();
				if (stopRedo== false) {
					notePadRestorer->GetNotePadHistory()->MoveNextHistory();
				}
			}
		}
		else {
			isGoingToBeSelected = beforehandAndPostProcesserForRedo.DoBeforehandProcessForRedo();
			notePadRestorer->Redo();
			if (isGoingToBeSelected == true) {
				beforehandAndPostProcesserForRedo.DoPostProcessForRedo();
			}
		}
		notePadRestorer->GetNotePadHistory()->MoveNextHistory();
	}
}