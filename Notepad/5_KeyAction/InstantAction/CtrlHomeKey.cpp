//CtrlHomeKey.cpp

#include"CtrlHomeKey.h"
#include"ScrollController.h"
#include"Glyph.h"
#include"NotePadMetric.h"
#include"NotePadModifier.h"
#include"CoordinateCalculator.h"
#include"NotePadIndicator.h"

CtrlHomeKey::CtrlHomeKey() {


}

CtrlHomeKey::CtrlHomeKey(NotePadForm* notePadForm) :KeyAction(notePadForm){


}
CtrlHomeKey::~CtrlHomeKey() {


}


void CtrlHomeKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

	NotePadModifier notePadModifier(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);
	CoordinateCalculator coordinateCalculator(this->notePadForm);
	NotePadIndicator notePadIndicator(this->notePadForm);

	Long rowCount = notePadModifier.CountRowFromStartToCurrent();
	Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
	notePadModifier.Combine();
	CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCount);
	notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);

	this->notePadForm->notePad->First();
	this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
	this->notePadForm->row->First();

#if 0;
	this->notePadForm->GetScrollController()->MoveHScrFirst();
	this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
	this->notePadForm->GetScrollController()->MoveVScrFirst();
	this->notePadForm->SetScrollPos(SB_VERT, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
#endif 0;

#if 0;
	if (this->notePadForm->GetIsAutoLineBreak() == true) {
		Long rowCount = notePadModifier.CountRowFromStartToCurrent();
		Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
		notePadModifier.Combine();
		notePadModifier.Split();
		CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCount);
		notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);
	}
#endif 0;
}