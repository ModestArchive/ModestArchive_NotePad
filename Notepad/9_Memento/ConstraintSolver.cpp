//ConstraintSolver.cpp
#include"SingleByteCharacter.h"
#include"ConstraintSolver.h"
#include"ConstraintSolverMemento.h"
#include"NotePadModifier.h"
#include"NotePadMetric.h"
#include"CoordinateCalculator.h"
#include"NotePadIndicator.h"
#include"NotePadRestorer.h"
#include"NotePadState.h"
#include"Glyph.h"
#include"NotePadMaker.h"


ConstraintSolver::ConstraintSolver(NotePadForm* notePadForm,NotePadState* notePadState) {
	this->notePadForm = notePadForm;
	this->notePadState = notePadState;
}


ConstraintSolver::~ConstraintSolver() {

}


void ConstraintSolver::SolveUnDoingWriteConstraint() {
	NotePadMetric notePadMetric(this->notePadForm);
	NotePadModifier notePadModifier(this->notePadForm);
	CoordinateCalculator coordinateCalculator(this->notePadForm);
	NotePadIndicator notePadIndicator(this->notePadForm);

	Long rowCountFromStartToCurrent = notePadModifier.CountRowFromStartToCurrent();
	Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
	notePadModifier.Combine();
	CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCountFromStartToCurrent);
	notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);
	
	ConstraintSolver constraintSolver(this->notePadForm);
	ConstraintSolverMemento* constraintSolverMemento = this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetAt(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent());
	constraintSolver.SetMemento(constraintSolverMemento);
	NotePadState* notePadState = constraintSolver.GetNotePadState();
	
	NotePadMaker notePadMaker(this->notePadForm);
	if (notePadState->GetGlyph() == 0) {//줄쓴거 지우기
		notePadIndicator.GoToCoordinate(notePadState->GetRowIndexRelatedWithAction()+1, 0);
		notePadMaker.EraseCurrentRowInNotePadForUndoRedo();
	}
	else {//단어쓴거 지우기
		if (dynamic_cast<SingleByteCharacter*>(notePadState->GetGlyph())) {
			if (((SingleByteCharacter*)(notePadState->GetGlyph()))->GetSingleByteContent() == '\t') {
				notePadIndicator.GoToCoordinate(notePadState->GetRowIndexRelatedWithAction(), notePadState->GetColumnIndexRelatedWithAction() + 8);
			}
			else {
				notePadIndicator.GoToCoordinate(notePadState->GetRowIndexRelatedWithAction(), notePadState->GetColumnIndexRelatedWithAction() + 1);
			}
		}
		else {
			notePadIndicator.GoToCoordinate(notePadState->GetRowIndexRelatedWithAction(), notePadState->GetColumnIndexRelatedWithAction() + 1);
		}
		notePadMaker.ErasePreviousCharacterInRowForUndoRedo();
	}
	//히스토리를 한단계 아래로 설정하는 개짓거리는 하지 말자!! 그건 ctrl+z눌렀을때 undo들어오기전에 해주는 것이다.
}

void ConstraintSolver::SolveUnDoingRemoveConstraint() {
	NotePadMetric notePadMetric(this->notePadForm);
	NotePadModifier notePadModifier(this->notePadForm);
	CoordinateCalculator coordinateCalculator(this->notePadForm);
	NotePadIndicator notePadIndicator(this->notePadForm);
	
	Long rowCountFromStartToCurrent = notePadModifier.CountRowFromStartToCurrent();
	Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
	notePadModifier.Combine();
	CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCountFromStartToCurrent);
	notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);

	ConstraintSolver constraintSolver(this->notePadForm);
	ConstraintSolverMemento* constraintSolverMemento = this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetAt(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent());
	constraintSolver.SetMemento(constraintSolverMemento);
	NotePadState* notePadState = constraintSolver.GetNotePadState();
	notePadIndicator.GoToCoordinate(notePadState->GetRowIndexRelatedWithAction(), notePadState->GetColumnIndexRelatedWithAction());
	
	NotePadMaker notePadMaker(this->notePadForm);
	if (notePadState->GetIsBackspaceRemoving()==true) {
		if (notePadState->GetGlyph()==0) {//백스페이스지운줄->줄추가
			notePadMaker.PlusRowInNotePadForUndoRedo();
		}
		else {//백스페이스지운단어->단어추가
			if (dynamic_cast<SingleByteCharacter*>(notePadState->GetGlyph())) {
				if (((SingleByteCharacter*)(notePadState->GetGlyph()))->GetSingleByteContent()=='\t') {
					notePadMaker.WriteTabInRowForUndoRedo(notePadState->GetGlyph());
				}
				else {
					notePadMaker.WriteContentsInRowForUndoRedo(notePadState->GetGlyph());
				}
			}
			else {
				notePadMaker.WriteContentsInRowForUndoRedo(notePadState->GetGlyph());
			}
		}
	}
	else {
		if (notePadState->GetGlyph() == 0) {//delete지운줄->줄추가
			notePadMaker.PlusRowInNotePadNoCurrentMoveForUndoRedo();
		}
		else {//delete지운단어->단어추가
			if (dynamic_cast<SingleByteCharacter*>(notePadState->GetGlyph())) {
				if (((SingleByteCharacter*)(notePadState->GetGlyph()))->GetSingleByteContent() == '\t') {
					notePadMaker.WriteTabInRowNoCurrentMoveForUndoRedo(notePadState->GetGlyph());
				}
				else {
					notePadMaker.WriteContentsInRowNoCurrentMoveForUndoRedo(notePadState->GetGlyph());
				}
			}
			else {
				notePadMaker.WriteContentsInRowNoCurrentMoveForUndoRedo(notePadState->GetGlyph()->Clone());
			}
		}
	}
}


void ConstraintSolver::SolveUnDoingPasteConstraint(Long rowIndexRelatedWithAfterAction, Long columnIndexRelatedWithAfterAction) {
	NotePadMetric notePadMetric(this->notePadForm);
	NotePadModifier notePadModifier(this->notePadForm);
	CoordinateCalculator coordinateCalculator(this->notePadForm);
	NotePadIndicator notePadIndicator(this->notePadForm);

	Long rowCountFromStartToCurrent = notePadModifier.CountRowFromStartToCurrent();
	Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
	notePadModifier.Combine();
	CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCountFromStartToCurrent);
	notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);

	ConstraintSolver constraintSolver(this->notePadForm);
	ConstraintSolverMemento* constraintSolverMemento = this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetAt(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent());
	constraintSolver.SetMemento(constraintSolverMemento);
	NotePadState* notePadState = constraintSolver.GetNotePadState();
	notePadIndicator.GoToCoordinate(notePadState->GetRowIndexRelatedWithAction(), notePadState->GetColumnIndexRelatedWithAction());

	NotePadMaker notePadMaker(this->notePadForm);
	notePadMaker.EraseDesignatedAreaForUndoPaste(rowIndexRelatedWithAfterAction, columnIndexRelatedWithAfterAction);
}


void ConstraintSolver::SolveUnDoingCutOutConstraint() {
	NotePadMetric notePadMetric(this->notePadForm);
	NotePadModifier notePadModifier(this->notePadForm);
	CoordinateCalculator coordinateCalculator(this->notePadForm);
	NotePadIndicator notePadIndicator(this->notePadForm);

	Long rowCountFromStartToCurrent = notePadModifier.CountRowFromStartToCurrent();
	Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
	notePadModifier.Combine();
	CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCountFromStartToCurrent);
	notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);

	ConstraintSolver constraintSolver(this->notePadForm);
	ConstraintSolverMemento* constraintSolverMemento = this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetAt(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent());
	constraintSolver.SetMemento(constraintSolverMemento);
	NotePadState* notePadState = constraintSolver.GetNotePadState();
	notePadIndicator.GoToCoordinate(notePadState->GetRowIndexRelatedWithAction(), notePadState->GetColumnIndexRelatedWithAction());

	NotePadMaker notePadMaker(this->notePadForm);
	notePadMaker.WriteContentsFromStringForUndoRedo(notePadState->GetContents());
}


void ConstraintSolver::SolveUnDoingSelectionErasedBeforeActionConstraint() {
	NotePadMetric notePadMetric(this->notePadForm);
	NotePadModifier notePadModifier(this->notePadForm);
	CoordinateCalculator coordinateCalculator(this->notePadForm);
	NotePadIndicator notePadIndicator(this->notePadForm);

	Long rowCountFromStartToCurrent = notePadModifier.CountRowFromStartToCurrent();
	Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
	notePadModifier.Combine();
	CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCountFromStartToCurrent);
	notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);

	ConstraintSolver constraintSolver(this->notePadForm);
	ConstraintSolverMemento* constraintSolverMemento = this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetAt(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent());
	constraintSolver.SetMemento(constraintSolverMemento);
	NotePadState* notePadState = constraintSolver.GetNotePadState();
	notePadIndicator.GoToCoordinate(notePadState->GetRowIndexRelatedWithAction(), notePadState->GetColumnIndexRelatedWithAction());

	NotePadMaker notePadMaker(this->notePadForm);
	notePadMaker.WriteContentsFromStringForUndoRedo(notePadState->GetContents());
}


void ConstraintSolver::SolveReDoingWriteConstraint() {
	NotePadMetric notePadMetric(this->notePadForm);
	NotePadModifier notePadModifier(this->notePadForm);
	CoordinateCalculator coordinateCalculator(this->notePadForm);
	NotePadIndicator notePadIndicator(this->notePadForm);

	Long rowCountFromStartToCurrent = notePadModifier.CountRowFromStartToCurrent();
	Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
	notePadModifier.Combine();
	CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCountFromStartToCurrent);
	notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);

	ConstraintSolver constraintSolver(this->notePadForm);
	ConstraintSolverMemento* constraintSolverMemento = this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetAt(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent());
	constraintSolver.SetMemento(constraintSolverMemento);
	NotePadState* notePadState = constraintSolver.GetNotePadState();
	notePadIndicator.GoToCoordinate(notePadState->GetRowIndexRelatedWithAction(), notePadState->GetColumnIndexRelatedWithAction());
	
	NotePadMaker notePadMaker(this->notePadForm);
	if (notePadState->GetGlyph() == 0) {//줄 다시쓰기
		notePadMaker.PlusRowInNotePadForUndoRedo();
	}
	else {//단어 다시쓰기
		if (dynamic_cast<SingleByteCharacter*>(notePadState->GetGlyph())) {
			if (((SingleByteCharacter*)(notePadState->GetGlyph()))->GetSingleByteContent() == '\t') {
				notePadMaker.WriteTabInRowForUndoRedo(notePadState->GetGlyph());
			}
			else {
				notePadMaker.WriteContentsInRowForUndoRedo(notePadState->GetGlyph());
			}
		}
		else {
			notePadMaker.WriteContentsInRowForUndoRedo(notePadState->GetGlyph()->Clone());
		}
	}
}


void ConstraintSolver::SolveReDoingRemoveConstraint() {
	NotePadMetric notePadMetric(this->notePadForm);
	NotePadModifier notePadModifier(this->notePadForm);
	CoordinateCalculator coordinateCalculator(this->notePadForm);
	NotePadIndicator notePadIndicator(this->notePadForm);

	Long rowCountFromStartToCurrent = notePadModifier.CountRowFromStartToCurrent();
	Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
	notePadModifier.Combine();
	CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCountFromStartToCurrent);
	notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);
	
	ConstraintSolver constraintSolver(this->notePadForm);
	ConstraintSolverMemento* constraintSolverMemento = this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetAt(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent());
	constraintSolver.SetMemento(constraintSolverMemento);
	NotePadState* notePadState = constraintSolver.GetNotePadState();
	NotePadMaker notePadMaker(this->notePadForm);
	if (notePadState->GetIsBackspaceRemoving() == true) {
		
		if (notePadState->GetGlyph() == 0) {//백스페이스로 줄 다시 지워주기
			notePadIndicator.GoToCoordinate(notePadState->GetRowIndexRelatedWithAction()+1, 0);
			notePadMaker.EraseCurrentRowInNotePadForUndoRedo();
		}
		else {//백스페이스로 단어 다시 지워주기
			notePadIndicator.GoToCoordinate(notePadState->GetRowIndexRelatedWithAction(), notePadState->GetColumnIndexRelatedWithAction()+1);
			notePadMaker.ErasePreviousCharacterInRowForUndoRedo();
		}
	}
	else {
		notePadIndicator.GoToCoordinate(notePadState->GetRowIndexRelatedWithAction(), notePadState->GetColumnIndexRelatedWithAction());
		if (notePadState->GetGlyph() == 0) {//delete로 줄 다시 지워주기
			notePadMaker.EraseNextRowInNotePadForUndoRedo();
		}
		else {//delete로 단어 다시 지워주기
			notePadMaker.EraseCurrentCharactorInRowForUndoRedo();
		}
	}
}


void ConstraintSolver::SolveReDoingPasteConstraint() {
	NotePadMetric notePadMetric(this->notePadForm);
	NotePadModifier notePadModifier(this->notePadForm);
	CoordinateCalculator coordinateCalculator(this->notePadForm);
	NotePadIndicator notePadIndicator(this->notePadForm);

	Long rowCountFromStartToCurrent = notePadModifier.CountRowFromStartToCurrent();
	Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
	notePadModifier.Combine();
	CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCountFromStartToCurrent);
	notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);

	ConstraintSolver constraintSolver(this->notePadForm);
	ConstraintSolverMemento* constraintSolverMemento = this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetAt(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent());
	constraintSolver.SetMemento(constraintSolverMemento);
	NotePadState* notePadState = constraintSolver.GetNotePadState();
	notePadIndicator.GoToCoordinate(notePadState->GetRowIndexRelatedWithAction(), notePadState->GetColumnIndexRelatedWithAction());

	NotePadMaker notePadMaker(this->notePadForm);
	notePadMaker.WriteContentsFromStringForUndoRedo(notePadState->GetContents());
}

  
void ConstraintSolver::SolveReDoingCutOutConstraint(Long rowIndexRelatedWithBeforeAction, Long columnIndexRelatedWithBeforeAction) {
	NotePadMetric notePadMetric(this->notePadForm);
	NotePadModifier notePadModifier(this->notePadForm);
	CoordinateCalculator coordinateCalculator(this->notePadForm);
	NotePadIndicator notePadIndicator(this->notePadForm);

	Long rowCountFromStartToCurrent = notePadModifier.CountRowFromStartToCurrent();
	Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
	notePadModifier.Combine();
	CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCountFromStartToCurrent);
	notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);

	ConstraintSolver constraintSolver(this->notePadForm);
	ConstraintSolverMemento* constraintSolverMemento = this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetAt(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent());
	constraintSolver.SetMemento(constraintSolverMemento);
	NotePadState* notePadState = constraintSolver.GetNotePadState();
	notePadIndicator.GoToCoordinate(notePadState->GetRowIndexRelatedWithAction(), notePadState->GetColumnIndexRelatedWithAction());

	NotePadMaker notePadMaker(this->notePadForm);
	notePadMaker.EraseDesignatedAreaForRedoCutOut(rowIndexRelatedWithBeforeAction, columnIndexRelatedWithBeforeAction);
}

void ConstraintSolver::SolveReDoingSelectionErasedBeforeActionConstraint(Long rowIndexRelatedWithBeforeAction, Long columnIndexRelatedWithBeforeAction) {
	NotePadMetric notePadMetric(this->notePadForm);
	NotePadModifier notePadModifier(this->notePadForm);
	CoordinateCalculator coordinateCalculator(this->notePadForm);
	NotePadIndicator notePadIndicator(this->notePadForm);

	Long rowCountFromStartToCurrent = notePadModifier.CountRowFromStartToCurrent();
	Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
	notePadModifier.Combine();
	CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCountFromStartToCurrent);
	notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);

	ConstraintSolver constraintSolver(this->notePadForm);
	ConstraintSolverMemento* constraintSolverMemento = this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetAt(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent());
	constraintSolver.SetMemento(constraintSolverMemento);
	NotePadState* notePadState = constraintSolver.GetNotePadState();
	notePadIndicator.GoToCoordinate(notePadState->GetRowIndexRelatedWithAction(), notePadState->GetColumnIndexRelatedWithAction());

	NotePadMaker notePadMaker(this->notePadForm);
	notePadMaker.EraseDesignatedAreaForRedoCutOut(rowIndexRelatedWithBeforeAction, columnIndexRelatedWithBeforeAction);
}


ConstraintSolverMemento* ConstraintSolver::CreateConstraintSolverMemento() {
	return new ConstraintSolverMemento(this->notePadState);
}


void ConstraintSolver::SetMemento(ConstraintSolverMemento* constraintSolverMemento) {
	this->notePadState = constraintSolverMemento->GetState();
}