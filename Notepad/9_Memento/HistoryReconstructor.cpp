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
	1.�� �����丮��ġ�� ���Ѵ�.
	2.���� �����丮������ ���Ѵ�.
	3.���� �����丮������ŭ �ݺ��Ѵ�.
		3.1.���� �����丮�� ������ �����丮��, �����������丮�� ���������丮�� ������ ���Ѵ�.
	4.�����丮�� ������ �̵���Ų��.
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
		if (cloneNotePadState.GetIsWritingAction() == true) {//�ܾ�,�� �����ؼ�!! �ϴ� �ܾ������ �ܾ ���̳� �ƴϳ�
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