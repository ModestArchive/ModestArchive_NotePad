//NotePadMementoMaker.cpp
#include"Glyph.h"
#include"NotePadState.h"
#include"NotePadMementoMaker.h"
#include"NotePadForm.h"
#include"NotePadMetric.h"
#include"NotePadModifier.h"
#include"NotePadState.h"
#include"ConstraintSolver.h"
#include"ConstraintSolverMemento.h"
#include"CoordinateCalculator.h"
#include"NotePadIndicator.h"
#include"ScrollController.h"

NotePadMementoMaker::NotePadMementoMaker(NotePadForm* notePadForm) {
	this->notePadForm = notePadForm;
}

NotePadMementoMaker::~NotePadMementoMaker() {

}


ConstraintSolverMemento* NotePadMementoMaker::MakeMemento(bool isWritingAction,
															bool isRemoveAction,
															bool isBackspaceRemoving,
															Glyph* cloneGlyph){

	ConstraintSolverMemento* constraintSolverMemento = 0;
	if (this->notePadForm->GetIsAutoLineBreak()==true) {

		NotePadMetric notePadMetric(this->notePadForm);
		NotePadModifier notePadModifier(this->notePadForm);
		CoordinateCalculator coordinateCalculator(this->notePadForm);
		NotePadIndicator notePadIndicator(this->notePadForm);

		Long rowCountFromStartToCurrent = notePadModifier.CountRowFromStartToCurrent();
		Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
		notePadModifier.Combine();
		CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCountFromStartToCurrent);
		notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);

		NotePadState* notePadState = new NotePadState(isWritingAction,
														isRemoveAction,
														isBackspaceRemoving,
														false,
														false,
														false,
														false,
														false,
														cloneGlyph,
														0,
														cPoint.y,
														cPoint.x);

		ConstraintSolver constraintSolver(this->notePadForm,notePadState);
		constraintSolverMemento = constraintSolver.CreateConstraintSolverMemento();
	}
	else {
		NotePadState* notePadState = new NotePadState(isWritingAction,
														isRemoveAction, 
														isBackspaceRemoving,
														false,
														false,
														false, 
														false,
														false,
														cloneGlyph,
														0,
														this->notePadForm->notePad->GetCurrent(),
														this->notePadForm->row->GetCurrent());

		ConstraintSolver constraintSolver(this->notePadForm, notePadState);
		constraintSolverMemento = constraintSolver.CreateConstraintSolverMemento();
	}
	return constraintSolverMemento;
}




ConstraintSolverMemento* NotePadMementoMaker::MakeMemento(bool isPasteAction,
															bool isCutOutAction,
															Long designatedRowIndexRelatedWithAction,
															Long designatedColumnIndexRelatedWithAction,
															string* cloneContents) {

	ConstraintSolverMemento* constraintSolverMemento = 0;
	if (isPasteAction==true) {
		if (this->notePadForm->GetIsAutoLineBreak() == true) {

			NotePadMetric notePadMetric(this->notePadForm);
			NotePadModifier notePadModifier(this->notePadForm);
			CoordinateCalculator coordinateCalculator(this->notePadForm);
			NotePadIndicator notePadIndicator(this->notePadForm);

			Long rowCountFromStartToCurrent = notePadModifier.CountRowFromStartToCurrent();
			Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
			notePadModifier.Combine();
			CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCountFromStartToCurrent);
			notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);

			NotePadState* notePadState = new NotePadState(false,
															false,
															false,
															isPasteAction,
															isCutOutAction,
															false, 
															false,
															false,
															0,
															cloneContents,
															cPoint.y,
															cPoint.x);

			ConstraintSolver constraintSolver(this->notePadForm, notePadState);
			constraintSolverMemento = constraintSolver.CreateConstraintSolverMemento();
		}
		else {
			NotePadState* notePadState = new NotePadState(false,
														false,
														false,
														isPasteAction,
														isCutOutAction,
														false,
														false,
														false,
														0,
														cloneContents,
														this->notePadForm->notePad->GetCurrent(),
														this->notePadForm->row->GetCurrent());

			ConstraintSolver constraintSolver(this->notePadForm, notePadState);
			constraintSolverMemento = constraintSolver.CreateConstraintSolverMemento();
		}
	}
	else if(isCutOutAction==true) {//선택영역지울땐 무조건 상황이 combine시킨다음 선택영역이 수정된 상황이기때문에 쉽게해줄수있다. 
		NotePadState* notePadState = new NotePadState(false,
													false,
													false,
													isPasteAction,
													isCutOutAction,
													false,
													false,
													false,
													0,
													cloneContents,
													designatedRowIndexRelatedWithAction,
													designatedColumnIndexRelatedWithAction);

		ConstraintSolver constraintSolver(this->notePadForm, notePadState);
		constraintSolverMemento = constraintSolver.CreateConstraintSolverMemento();
	}
	
	return constraintSolverMemento;
}


ConstraintSolverMemento* NotePadMementoMaker::MakeNoStandardMemento(bool isSelectionErasedBeforeAction,
															bool isRemoveAction,
															Long designatedRowIndexRelatedWithAction,
															Long designatedColumnIndexRelatedWithAction,
															string* cloneContents) {
	ConstraintSolverMemento* constraintSolverMemento = 0;
	NotePadState* notePadState = new NotePadState(false,
													isRemoveAction,
													false,
													false,
													false,
													isSelectionErasedBeforeAction,
													false,
													false,
													0,
													cloneContents,
													designatedRowIndexRelatedWithAction,
													designatedColumnIndexRelatedWithAction);

	ConstraintSolver constraintSolver(this->notePadForm, notePadState);
	constraintSolverMemento = constraintSolver.CreateConstraintSolverMemento();

	return constraintSolverMemento;
}


ConstraintSolverMemento* NotePadMementoMaker::MakeReplaceAllMemento(bool isSelectionErasedBeforeAction,
																	bool isPasteAction,
																	bool isFirstOrLastReplace,
																	Long designatedRowIndexRelatedWithAction,
																	Long designatedColumnIndexRelatedWithAction,
																	string* cloneContents) {


	ConstraintSolverMemento* constraintSolverMemento = 0;
	NotePadState* notePadState = new NotePadState(false,
													false,
													false,
													isPasteAction,
													false,
													isSelectionErasedBeforeAction,
													true,
													isFirstOrLastReplace,
													0,
													cloneContents,
													designatedRowIndexRelatedWithAction,
													designatedColumnIndexRelatedWithAction);

	ConstraintSolver constraintSolver(this->notePadForm, notePadState);
	constraintSolverMemento = constraintSolver.CreateConstraintSolverMemento();
	
	return constraintSolverMemento;
}