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
	if (notePadState->GetGlyph() == 0) {//�پ��� �����
		notePadIndicator.GoToCoordinate(notePadState->GetRowIndexRelatedWithAction()+1, 0);
		notePadMaker.EraseCurrentRowInNotePadForUndoRedo();
	}
	else {//�ܾ�� �����
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
	//�����丮�� �Ѵܰ� �Ʒ��� �����ϴ� �����Ÿ��� ���� ����!! �װ� ctrl+z�������� undo���������� ���ִ� ���̴�.
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
		if (notePadState->GetGlyph()==0) {//�齺���̽�������->���߰�
			notePadMaker.PlusRowInNotePadForUndoRedo();
		}
		else {//�齺���̽�����ܾ�->�ܾ��߰�
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
		if (notePadState->GetGlyph() == 0) {//delete������->���߰�
			notePadMaker.PlusRowInNotePadNoCurrentMoveForUndoRedo();
		}
		else {//delete����ܾ�->�ܾ��߰�
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
	if (notePadState->GetGlyph() == 0) {//�� �ٽþ���
		notePadMaker.PlusRowInNotePadForUndoRedo();
	}
	else {//�ܾ� �ٽþ���
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
		
		if (notePadState->GetGlyph() == 0) {//�齺���̽��� �� �ٽ� �����ֱ�
			notePadIndicator.GoToCoordinate(notePadState->GetRowIndexRelatedWithAction()+1, 0);
			notePadMaker.EraseCurrentRowInNotePadForUndoRedo();
		}
		else {//�齺���̽��� �ܾ� �ٽ� �����ֱ�
			notePadIndicator.GoToCoordinate(notePadState->GetRowIndexRelatedWithAction(), notePadState->GetColumnIndexRelatedWithAction()+1);
			notePadMaker.ErasePreviousCharacterInRowForUndoRedo();
		}
	}
	else {
		notePadIndicator.GoToCoordinate(notePadState->GetRowIndexRelatedWithAction(), notePadState->GetColumnIndexRelatedWithAction());
		if (notePadState->GetGlyph() == 0) {//delete�� �� �ٽ� �����ֱ�
			notePadMaker.EraseNextRowInNotePadForUndoRedo();
		}
		else {//delete�� �ܾ� �ٽ� �����ֱ�
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