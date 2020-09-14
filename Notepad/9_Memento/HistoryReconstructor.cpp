//HistoryReconstructor.cpp
#include"HistoryReconstructor.h"
#include"NotePadHistory.h"
#include"ConstraintSolver.h"
#include"ConstraintSolverMemento.h"
#include"NotePadState.h"
#include"SingleByteCharacter.h"
#include"HistoryModifier.h"


HistoryReconstructor::HistoryReconstructor(NotePadHistory* notePadHistory,NotePadForm* notePadForm) {
	this->notePadHistory = notePadHistory;
	this->notePadForm = notePadForm;
}

HistoryReconstructor::~HistoryReconstructor() {

}

	/*
	1.현 히스토리위치를 구한다.
	2.더할 히스토리개수를 구한다.
	3.더할 히스토리개수만큼 반복한다.
		3.1.더한 히스토리는 삭제한 히스토리로, 삭제한히스토리는 더한히스토리로 역으로 더한다.
	4.히스토리를 끝으로 이동시킨다.
	*/
void HistoryReconstructor::ReconstructHistory() {

	HistoryModifier historyModifier(this->notePadHistory,this->notePadForm);
	ConstraintSolver constraintSolverForReading;
	Long historyIndex = this->notePadHistory->GetCurrent();
	Long addCount = this->notePadHistory->GetLength() - historyIndex;
	Long i = 0;
	Long reverseBeginCount = 0;
	bool writeOrPasteStateIsReversingTiming = false;
	Long currentReversedCount = 0;
	NotePadState* beforeActionNotePadState = 0;
	while (i<addCount) {
		constraintSolverForReading.SetMemento(this->notePadHistory->GetAt(historyIndex));
		NotePadState cloneNotePadState(*constraintSolverForReading.GetNotePadState());
		if (cloneNotePadState.GetIsWritingAction() == true) {//단어,줄 구분해서!! 일단 단어끼리부터 단어도 텝이냐 아니냐
			if (writeOrPasteStateIsReversingTiming == false) {
				historyModifier.ModifyWriteStateToRemoveState(&cloneNotePadState);
			}
			else {
				beforeActionNotePadState=historyModifier.ModifyWriteStateToSelectionErasedBeforeActionState(&cloneNotePadState);
				writeOrPasteStateIsReversingTiming = false;
			}
		}
		else if (cloneNotePadState.GetIsRemoveAction() == true) {
			if (cloneNotePadState.GetIsSelectionErasedBeforeAction()==true) {
				historyModifier.ModifyRemoveSelectionEraseToPasteState(&cloneNotePadState);
			}
			else {
				historyModifier.ModifyRemoveStateToWriteState(&cloneNotePadState);
			}
		}
		else if (cloneNotePadState.GetIsPasteAction()==true) {
			if (writeOrPasteStateIsReversingTiming==false) {
				historyModifier.ModifyPasteStateToCutOutState(&cloneNotePadState);
			}
			else {
				historyModifier.ModifyPasteStateToSelectionErasedBeforeActionState(&cloneNotePadState);
				currentReversedCount++;
				if (currentReversedCount==2) {
					currentReversedCount = 0;
					writeOrPasteStateIsReversingTiming = false;
				}
			}
		}
		else if (cloneNotePadState.GetIsCutOutAction()==true) {
			historyModifier.ModifyCutOutStateToPasteState(&cloneNotePadState);
		}
		else if (cloneNotePadState.GetIsSelectionErasedBeforeAction()==true) {
			historyModifier.ModifySelectionErasedBeforeActionToPasteState(&cloneNotePadState);
			reverseBeginCount++;
			if (reverseBeginCount==2) {
				reverseBeginCount = 0;
				writeOrPasteStateIsReversingTiming = true;
			}
		}
		NotePadState* renewalNotePadState = new NotePadState(cloneNotePadState);
		if (cloneNotePadState.GetGlyph()!=0) {
			delete cloneNotePadState.GetGlyph();
			cloneNotePadState.SetGlyph(0);
		}
		if (cloneNotePadState.GetContents()!=0) {
			delete cloneNotePadState.GetContents();
			cloneNotePadState.SetContents(0);
		}
		ConstraintSolver constraintSolverForSetting(0, renewalNotePadState);
		ConstraintSolverMemento* constraintSolverMemento = constraintSolverForSetting.CreateConstraintSolverMemento();
		if (beforeActionNotePadState!=0) {
			ConstraintSolver constraintSolverForAfterActionSetting(0,beforeActionNotePadState);
			ConstraintSolverMemento* constraintSolverMementoBeforeAction = constraintSolverForAfterActionSetting.CreateConstraintSolverMemento();
			this->notePadHistory->PutHistory(this->notePadHistory->GetLength() - i, constraintSolverMemento);
			this->notePadHistory->PutHistory(this->notePadHistory->GetLength() - (i+1), constraintSolverMementoBeforeAction);
			historyIndex++;
			i++;
		}
		else {
			this->notePadHistory->PutHistory(this->notePadHistory->GetLength() - i, constraintSolverMemento);
			this->notePadHistory->MovePreviousHistory();
			historyIndex++;
			i++;
		}
	}
	this->notePadHistory->MoveLastHistory();
}