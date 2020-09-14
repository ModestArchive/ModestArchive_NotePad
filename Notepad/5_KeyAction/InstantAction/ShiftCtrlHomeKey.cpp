//ShiftCtrlHomeKey.cpp

#include"ShiftCtrlHomeKey.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"KeyAction.h"
#include"Selector.h"
#include"TextMetric.h"
#include"CtrlHomeKey.h"
#include"NotePadMetric.h"
#include"CoordinateCalculator.h"
#include"NotePadIndicator.h"
#include"SelectModifier.h"
#include"NotePadModifier.h"


ShiftCtrlHomeKey::ShiftCtrlHomeKey() {

}

ShiftCtrlHomeKey::ShiftCtrlHomeKey(NotePadForm* notePadForm) :KeyAction(notePadForm) {


}

ShiftCtrlHomeKey::~ShiftCtrlHomeKey() {


}

void ShiftCtrlHomeKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Selector* selector = this->notePadForm->GetSelector();
	KeyAction* ctrlHomeKey = new CtrlHomeKey(this->notePadForm);


	if (this->notePadForm->GetIsSelected() == false) {
		selector->SetOriginRowIndex(this->notePadForm->notePad->GetCurrent());
		selector->SetOriginColumnIndex(this->notePadForm->row->GetCurrent());
		selector->SetStartRowIndex(this->notePadForm->notePad->GetCurrent());
		selector->SetStartColumnIndex(this->notePadForm->row->GetCurrent());
		selector->SetEndRowIndex(this->notePadForm->notePad->GetCurrent());
		selector->SetEndColumnIndex(this->notePadForm->row->GetCurrent());
	}
	else {
		selector->SetStartRowIndex(selector->GetEndRowIndex());
		selector->SetStartColumnIndex(selector->GetEndColumnIndex());
	}

	ctrlHomeKey->OnKeyDown(nChar, nRepCnt, nFlags);
	if (ctrlHomeKey != 0) {
		delete ctrlHomeKey;
	}

	selector->SetEndRowIndex(this->notePadForm->notePad->GetCurrent());
	selector->SetEndColumnIndex(this->notePadForm->row->GetCurrent());

#if 0;
	if (this->notePadForm->GetIsAutoLineBreak() == true) {
		NotePadModifier notePadModifier(this->notePadForm);
		NotePadMetric notePadMetric(this->notePadForm);
		CoordinateCalculator coordinateCalculator(this->notePadForm);
		NotePadIndicator notePadIndicator(this->notePadForm);
		SelectModifier selectModifier(this->notePadForm->GetSelector());

		selectModifier.SetAbsoluteSelectionInformation();
		Long rowCount = 0;
		Long totalLengthToCurrent = 0;

		Long rowCountInFirstToSelectedAreaStartPoint = selectModifier.CountRowInFirstToSelectedAreaStartPoint();
		Long rowCountInSelectedArea = selectModifier.CountRowInSelectedArea();

		rowCount = notePadModifier.CountRowFromStartToCurrent();
		totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
		notePadModifier.Combine();
		notePadModifier.Split();
		CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCount);
		notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);


		bool isRightDownWardSelectedArea = this->notePadForm->GetSelector()->IsRightDownWardSelectedArea();
		if (isRightDownWardSelectedArea == true) {
			selectModifier.ChangeRightDownwardSelectedAreaStartPointAfterAction(rowCountInFirstToSelectedAreaStartPoint);
			bool isFirstLineInSelectedAreaDummyRow = selectModifier.isFirstLineInSelectedAreaDummyRow();
			if (isFirstLineInSelectedAreaDummyRow == true) {
				rowCountInSelectedArea--;
			}
			selectModifier.ChangeRightDownwardSelectedAreaEndPointAfterAction(rowCountInSelectedArea);
		}
		else {
			selectModifier.ChangeLeftUpwardSelectedAreaStartPointAfterAction(rowCountInFirstToSelectedAreaStartPoint);
			bool isFirstLineInSelectedAreaDummyRow = selectModifier.isFirstLineInSelectedAreaDummyRow();
			if (isFirstLineInSelectedAreaDummyRow == true) {
				rowCountInSelectedArea--;
			}
			selectModifier.ChangeLeftUpwardSelectedAreaEndPointAfterAction(rowCountInSelectedArea);
		}
		
	}
#endif 0;
}