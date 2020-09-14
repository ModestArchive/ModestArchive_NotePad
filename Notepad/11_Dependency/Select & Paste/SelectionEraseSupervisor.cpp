//SelectionEraseSupervisor.cpp
#include"SelectionEraseSupervisor.h"
#include"SelectionEraser.h"
#include"NotePadModifier.h"
#include"SelectModifier.h"
#include"SelectedAreaMetric.h"
#include"NotePadMaker.h"
#include"Selector.h"
#include"Glyph.h"
#include"ConstraintSolverMemento.h"
#include"ConstraintSolver.h"
#include"HistoryReconstructor.h"
#include"NotePadRestorer.h"
#include"NotePadMementoMaker.h"

SelectionEraseSupervisor::SelectionEraseSupervisor(NotePadForm* notePadForm) {
	this->notePadForm=notePadForm;
}


SelectionEraseSupervisor::~SelectionEraseSupervisor() {

}


void SelectionEraseSupervisor::EraseContents(string* contents, bool isRemoveAction) {
	NotePadModifier notePadModifier(this->notePadForm);
	SelectedAreaMetric selectedAreaMetric(this->notePadForm->GetSelector());
	SelectModifier selectModifier(this->notePadForm->GetSelector());
	SelectionEraser selectionEraser(this->notePadForm);

	NotePadMementoMaker notePadMementoMaker(this->notePadForm);
	ConstraintSolverMemento* constraintSolverMemento = 0;
	NotePadRestorer* notePadRestorer = this->notePadForm->GetNotePadRestorer();
	if (this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent() != this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetLength()) {
		HistoryReconstructor historyReconstructor(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory(), this->notePadForm);
		historyReconstructor.ReconstructHistory();
	}
	notePadRestorer->GetNotePadHistory()->MoveLastHistory();

	bool isRightDownwardSelectedArea = this->notePadForm->GetSelector()->IsRightDownWardSelectedArea();

	if (this->notePadForm->GetIsAutoLineBreak()==true) {

		selectModifier.SetAbsoluteSelectionInformation();
		
		Long rowCountInFirstToSelectedAreaStartPoint = selectModifier.CountRowInFirstToSelectedAreaStartPoint();
		Long rowCountInSelectedArea = selectModifier.CountRowInSelectedArea();
		bool isFirstLineInSelectedAreaDummyRow = false;
		if (isRightDownwardSelectedArea == true) {
			isFirstLineInSelectedAreaDummyRow = selectModifier.isFirstLineInSelectedAreaDummyRow(this->notePadForm->GetSelector()->GetOriginRowIndex());
		}
		else {
			isFirstLineInSelectedAreaDummyRow = selectModifier.isFirstLineInSelectedAreaDummyRow(this->notePadForm->GetSelector()->GetEndRowIndex());
		}
		if (isFirstLineInSelectedAreaDummyRow == true) {
			rowCountInSelectedArea++;
		}
		notePadModifier.Combine();
		
		if (isRightDownwardSelectedArea == true) {
			//바뀐 시작점 함수 불러와서 실인수 제대로 주고
			//길이가 다할때까지 한글자씩 지워주고, 일단 입력받은 길이에 해당되는 글자들을 지웠다면 줄까지도 확실하게 지워졌는지 확인한다.
			selectModifier.ChangeRightDownwardSelectedAreaStartPointAfterAction(rowCountInFirstToSelectedAreaStartPoint);
			selectModifier.ChangeRightDownwardSelectedAreaEndPointAfterAction(rowCountInSelectedArea);
			constraintSolverMemento = notePadMementoMaker.MakeNoStandardMemento(true,isRemoveAction,this->notePadForm->GetSelector()->GetEndRowIndex(), this->notePadForm->GetSelector()->GetEndColumnIndex(),contents);
		}                          
		else {
			selectModifier.ChangeLeftUpwardSelectedAreaStartPointAfterAction(rowCountInFirstToSelectedAreaStartPoint);
			selectModifier.ChangeLeftUpwardSelectedAreaEndPointAfterAction(rowCountInSelectedArea);
			constraintSolverMemento = notePadMementoMaker.MakeNoStandardMemento(true, isRemoveAction, this->notePadForm->GetSelector()->GetOriginRowIndex(), this->notePadForm->GetSelector()->GetOriginColumnIndex(), contents);
		}
		notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);
		selectionEraser.EraseSelectionContents();
		constraintSolverMemento = notePadMementoMaker.MakeNoStandardMemento(true, isRemoveAction, this->notePadForm->notePad->GetCurrent(), this->notePadForm->row->GetCurrent(), contents);
		notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);
	}
	else {
		if (isRightDownwardSelectedArea == true) {
			constraintSolverMemento = notePadMementoMaker.MakeNoStandardMemento(true, isRemoveAction, this->notePadForm->GetSelector()->GetEndRowIndex(), this->notePadForm->GetSelector()->GetEndColumnIndex(), contents);
		}
		else {
			constraintSolverMemento = notePadMementoMaker.MakeNoStandardMemento(true, isRemoveAction, this->notePadForm->GetSelector()->GetOriginRowIndex(), this->notePadForm->GetSelector()->GetOriginColumnIndex(), contents);
		}
		notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);
		selectionEraser.EraseSelectionContents();
		constraintSolverMemento = notePadMementoMaker.MakeNoStandardMemento(true, isRemoveAction, this->notePadForm->notePad->GetCurrent(), this->notePadForm->row->GetCurrent(), contents);
		notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);
	}
}


void SelectionEraseSupervisor::EraseContentsForReplaceAll(string* contents, bool isFirstReplace) {
	NotePadModifier notePadModifier(this->notePadForm);
	SelectedAreaMetric selectedAreaMetric(this->notePadForm->GetSelector());
	SelectModifier selectModifier(this->notePadForm->GetSelector());
	SelectionEraser selectionEraser(this->notePadForm);

	NotePadMementoMaker notePadMementoMaker(this->notePadForm);
	ConstraintSolverMemento* constraintSolverMemento = 0;
	NotePadRestorer* notePadRestorer = this->notePadForm->GetNotePadRestorer();
	if (this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent() != this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetLength()) {
		HistoryReconstructor historyReconstructor(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory(), this->notePadForm);
		historyReconstructor.ReconstructHistory();
	}
	notePadRestorer->GetNotePadHistory()->MoveLastHistory();

	bool isRightDownwardSelectedArea = this->notePadForm->GetSelector()->IsRightDownWardSelectedArea();

	if (this->notePadForm->GetIsAutoLineBreak() == true) {

		selectModifier.SetAbsoluteSelectionInformation();
		Long rowCountInFirstToSelectedAreaStartPoint = selectModifier.CountRowInFirstToSelectedAreaStartPoint();
		Long rowCountInSelectedArea = selectModifier.CountRowInSelectedArea();

		bool isFirstLineInSelectedAreaDummyRow = false;
		if (isRightDownwardSelectedArea==true) {
			isFirstLineInSelectedAreaDummyRow=selectModifier.isFirstLineInSelectedAreaDummyRow(this->notePadForm->GetSelector()->GetOriginRowIndex());
		}
		else {
			isFirstLineInSelectedAreaDummyRow = selectModifier.isFirstLineInSelectedAreaDummyRow(this->notePadForm->GetSelector()->GetEndRowIndex());
		}
		if (isFirstLineInSelectedAreaDummyRow == true) {
			rowCountInSelectedArea++;
		}

		notePadModifier.Combine();

		if (isRightDownwardSelectedArea == true) {
			//바뀐 시작점 함수 불러와서 실인수 제대로 주고
			//길이가 다할때까지 한글자씩 지워주고, 일단 입력받은 길이에 해당되는 글자들을 지웠다면 줄까지도 확실하게 지워졌는지 확인한다.
			selectModifier.ChangeRightDownwardSelectedAreaStartPointAfterAction(rowCountInFirstToSelectedAreaStartPoint);
			selectModifier.ChangeRightDownwardSelectedAreaEndPointAfterAction(rowCountInSelectedArea);
			constraintSolverMemento = notePadMementoMaker.MakeReplaceAllMemento(true,false,isFirstReplace,this->notePadForm->GetSelector()->GetEndRowIndex(), this->notePadForm->GetSelector()->GetEndColumnIndex(), contents);
		}
		else {
			selectModifier.ChangeLeftUpwardSelectedAreaStartPointAfterAction(rowCountInFirstToSelectedAreaStartPoint);
			selectModifier.ChangeLeftUpwardSelectedAreaEndPointAfterAction(rowCountInSelectedArea);
			constraintSolverMemento = notePadMementoMaker.MakeReplaceAllMemento(true, false, isFirstReplace, this->notePadForm->GetSelector()->GetOriginRowIndex(), this->notePadForm->GetSelector()->GetOriginColumnIndex(), contents);
		}
		notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);

		selectionEraser.EraseSelectionContents();

		constraintSolverMemento = notePadMementoMaker.MakeReplaceAllMemento(true, false, false, this->notePadForm->notePad->GetCurrent(),this->notePadForm->row->GetCurrent(), contents);
		notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);
	}
	else {
		if (isRightDownwardSelectedArea == true) {
			constraintSolverMemento = notePadMementoMaker.MakeReplaceAllMemento(true, false, isFirstReplace, this->notePadForm->GetSelector()->GetEndRowIndex(), this->notePadForm->GetSelector()->GetEndColumnIndex(), contents);
		}
		else {
			constraintSolverMemento = notePadMementoMaker.MakeReplaceAllMemento(true, false, isFirstReplace, this->notePadForm->GetSelector()->GetOriginRowIndex(), this->notePadForm->GetSelector()->GetOriginColumnIndex(), contents);
		}
		notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);

		selectionEraser.EraseSelectionContents();

		constraintSolverMemento = notePadMementoMaker.MakeReplaceAllMemento(true,false, false,this->notePadForm->notePad->GetCurrent(), this->notePadForm->row->GetCurrent(), contents);
		notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);
	}
}


void SelectionEraseSupervisor::EraseContentsForReplaceNoneAll(string* contents, bool isFirstReplace, bool isLastReplace) {
	NotePadModifier notePadModifier(this->notePadForm);
	SelectedAreaMetric selectedAreaMetric(this->notePadForm->GetSelector());
	SelectModifier selectModifier(this->notePadForm->GetSelector());
	SelectionEraser selectionEraser(this->notePadForm);

	NotePadMementoMaker notePadMementoMaker(this->notePadForm);
	ConstraintSolverMemento* constraintSolverMemento = 0;
	NotePadRestorer* notePadRestorer = this->notePadForm->GetNotePadRestorer();
	if (this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent() != this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetLength()) {
		HistoryReconstructor historyReconstructor(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory(), this->notePadForm);
		historyReconstructor.ReconstructHistory();
	}
	notePadRestorer->GetNotePadHistory()->MoveLastHistory();

	bool isRightDownwardSelectedArea = this->notePadForm->GetSelector()->IsRightDownWardSelectedArea();

	if (this->notePadForm->GetIsAutoLineBreak() == true) {
		
		selectModifier.SetAbsoluteSelectionInformation();
		
		Long rowCountInFirstToSelectedAreaStartPoint = selectModifier.CountRowInFirstToSelectedAreaStartPoint();
		Long rowCountInSelectedArea = selectModifier.CountRowInSelectedArea();
		bool isFirstLineInSelectedAreaDummyRow = false;
		if (isRightDownwardSelectedArea == true) {
			isFirstLineInSelectedAreaDummyRow = selectModifier.isFirstLineInSelectedAreaDummyRow(this->notePadForm->GetSelector()->GetOriginRowIndex());
		}
		else {
			isFirstLineInSelectedAreaDummyRow = selectModifier.isFirstLineInSelectedAreaDummyRow(this->notePadForm->GetSelector()->GetEndRowIndex());
		}
		if (isFirstLineInSelectedAreaDummyRow == true) {
			rowCountInSelectedArea++;
		}
		notePadModifier.Combine();

		if (isRightDownwardSelectedArea == true) {
			//바뀐 시작점 함수 불러와서 실인수 제대로 주고
			//길이가 다할때까지 한글자씩 지워주고, 일단 입력받은 길이에 해당되는 글자들을 지웠다면 줄까지도 확실하게 지워졌는지 확인한다.
			selectModifier.ChangeRightDownwardSelectedAreaStartPointAfterAction(rowCountInFirstToSelectedAreaStartPoint);
			selectModifier.ChangeRightDownwardSelectedAreaEndPointAfterAction(rowCountInSelectedArea);
			constraintSolverMemento = notePadMementoMaker.MakeReplaceAllMemento(true,false, isFirstReplace, this->notePadForm->GetSelector()->GetEndRowIndex(), this->notePadForm->GetSelector()->GetEndColumnIndex(), contents);
		}
		else {
			selectModifier.ChangeLeftUpwardSelectedAreaStartPointAfterAction(rowCountInFirstToSelectedAreaStartPoint);
			selectModifier.ChangeLeftUpwardSelectedAreaEndPointAfterAction(rowCountInSelectedArea);
			constraintSolverMemento = notePadMementoMaker.MakeReplaceAllMemento(true, false, isFirstReplace, this->notePadForm->GetSelector()->GetOriginRowIndex(), this->notePadForm->GetSelector()->GetOriginColumnIndex(), contents);
		}
		notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);

		selectionEraser.EraseSelectionContents();

		constraintSolverMemento = notePadMementoMaker.MakeReplaceAllMemento(true, false, isLastReplace, this->notePadForm->notePad->GetCurrent(), this->notePadForm->row->GetCurrent(), contents);
		notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);
	}
	else {
		if (isRightDownwardSelectedArea == true) {
			constraintSolverMemento = notePadMementoMaker.MakeReplaceAllMemento(true, false, isFirstReplace, this->notePadForm->GetSelector()->GetEndRowIndex(), this->notePadForm->GetSelector()->GetEndColumnIndex(), contents);
		}
		else {
			constraintSolverMemento = notePadMementoMaker.MakeReplaceAllMemento(true, false, isFirstReplace, this->notePadForm->GetSelector()->GetOriginRowIndex(), this->notePadForm->GetSelector()->GetOriginColumnIndex(), contents);
		}
		notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);

		selectionEraser.EraseSelectionContents();

		constraintSolverMemento = notePadMementoMaker.MakeReplaceAllMemento(true, false, isLastReplace, this->notePadForm->notePad->GetCurrent(), this->notePadForm->row->GetCurrent(), contents);
		notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);
	}
}



void SelectionEraseSupervisor::EraseContentsForCtrlX(string* cloneContents) {
	NotePadModifier notePadModifier(this->notePadForm);
	SelectedAreaMetric selectedAreaMetric(this->notePadForm->GetSelector());
	SelectModifier selectModifier(this->notePadForm->GetSelector());
	SelectionEraser selectionEraser(this->notePadForm);

	NotePadMementoMaker notePadMementoMaker(this->notePadForm);
	ConstraintSolverMemento* constraintSolverMemento = 0;
	NotePadRestorer* notePadRestorer = this->notePadForm->GetNotePadRestorer();
	if (this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent() != this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetLength()) {
		HistoryReconstructor historyReconstructor(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory(), this->notePadForm);
		historyReconstructor.ReconstructHistory();
	}
	notePadRestorer->GetNotePadHistory()->MoveLastHistory();
	
	bool isRightDownwardSelectedArea = this->notePadForm->GetSelector()->IsRightDownWardSelectedArea();

	if (this->notePadForm->GetIsAutoLineBreak() == true) {
	
		selectModifier.SetAbsoluteSelectionInformation();
		Long rowCountInSelectedArea = selectModifier.CountRowInSelectedArea();
		bool isFirstLineInSelectedAreaDummyRow = false;
		if (isRightDownwardSelectedArea == true) {
			isFirstLineInSelectedAreaDummyRow = selectModifier.isFirstLineInSelectedAreaDummyRow(this->notePadForm->GetSelector()->GetOriginRowIndex());
		}
		else {
			isFirstLineInSelectedAreaDummyRow = selectModifier.isFirstLineInSelectedAreaDummyRow(this->notePadForm->GetSelector()->GetEndRowIndex());
		}
		if (isFirstLineInSelectedAreaDummyRow==true) {
			rowCountInSelectedArea++;
		}
		Long rowCountInFirstToSelectedAreaStartPoint = selectModifier.CountRowInFirstToSelectedAreaStartPoint();
		notePadModifier.Combine();
	
		if (isRightDownwardSelectedArea == true) {
			//바뀐 시작점 함수 불러와서 실인수 제대로 주고
			//길이가 다할때까지 한글자씩 지워주고, 일단 입력받은 길이에 해당되는 글자들을 지웠다면 줄까지도 확실하게 지워졌는지 확인한다.
			selectModifier.ChangeRightDownwardSelectedAreaStartPointAfterAction(rowCountInFirstToSelectedAreaStartPoint);
			selectModifier.ChangeRightDownwardSelectedAreaEndPointAfterAction(rowCountInSelectedArea);
			constraintSolverMemento = notePadMementoMaker.MakeMemento(false,true,this->notePadForm->GetSelector()->GetEndRowIndex(), this->notePadForm->GetSelector()->GetEndColumnIndex(),cloneContents);
		}
		else {
			selectModifier.ChangeLeftUpwardSelectedAreaStartPointAfterAction(rowCountInFirstToSelectedAreaStartPoint);
			selectModifier.ChangeLeftUpwardSelectedAreaEndPointAfterAction(rowCountInSelectedArea);
			constraintSolverMemento = notePadMementoMaker.MakeMemento(false, true, this->notePadForm->GetSelector()->GetOriginRowIndex(), this->notePadForm->GetSelector()->GetOriginColumnIndex(), cloneContents);
		}
		notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);
		selectionEraser.EraseSelectionContents();

		constraintSolverMemento = notePadMementoMaker.MakeMemento(false, true, this->notePadForm->notePad->GetCurrent(), this->notePadForm->row->GetCurrent(), cloneContents);
		notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);
	}
	else {
		if (isRightDownwardSelectedArea == true) {
			constraintSolverMemento = notePadMementoMaker.MakeMemento(false, true, this->notePadForm->GetSelector()->GetEndRowIndex(), this->notePadForm->GetSelector()->GetEndColumnIndex(), cloneContents);
		}
		else {
			constraintSolverMemento = notePadMementoMaker.MakeMemento(false, true, this->notePadForm->GetSelector()->GetOriginRowIndex(), this->notePadForm->GetSelector()->GetOriginColumnIndex(), cloneContents);
		}
		notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);
		selectionEraser.EraseSelectionContents();
		constraintSolverMemento = notePadMementoMaker.MakeMemento(false, true, this->notePadForm->notePad->GetCurrent(), this->notePadForm->row->GetCurrent(), cloneContents);
		notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);
	}
}


