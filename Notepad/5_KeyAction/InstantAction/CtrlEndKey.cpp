//CtrlEndKey.cpp

#include"CtrlEndKey.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"TextMetric.h"
#include"Font.h"
#include"NotePadMetric.h"
#include"NotePadModifier.h"
#include"CoordinateCalculator.h"
#include"NotePadIndicator.h"


CtrlEndKey::CtrlEndKey() {


}

CtrlEndKey::CtrlEndKey(NotePadForm* notePadForm) : KeyAction(notePadForm){

}

CtrlEndKey::~CtrlEndKey() {

}

void CtrlEndKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

	NotePadModifier notePadModifier(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);
	CoordinateCalculator coordinateCalculator(this->notePadForm);
	NotePadIndicator notePadIndicator(this->notePadForm);

	Long rowCount = notePadModifier.CountRowFromStartToCurrent();
	Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
	notePadModifier.Combine();
	CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCount);
	notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);

	this->notePadForm->notePad->Last();
	this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
	this->notePadForm->row->Last();
#if 0;
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	TextMetric textMetric(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);

	if (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetLength()) > this->notePadForm->GetCx() - tm.tmAveCharWidth / 2) {
		if (this->notePadForm->row == this->notePadForm->notePad->GetAt(notePadMetric.GetLongestXRowIndex())) {
			this->notePadForm->GetScrollController()->SetHPos(this->notePadForm->GetScrollLimit(SB_HORZ));
		}
		else {
			this->notePadForm->GetScrollController()->SetHPos(0);
			while (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent()) > this->notePadForm->GetScrollController()->GetHPosition() + this->notePadForm->GetCx() - tm.tmAveCharWidth / 2) {
				this->notePadForm->GetScrollController()->MoveHScrNext();
			}
			Long i = 0;
			while (i < 10) {
				this->notePadForm->GetScrollController()->MoveHScrNext();
				i++;
			}
		}
	}
	else {
		this->notePadForm->GetScrollController()->SetHPos(0);
	}
	if (textMetric.GetY(this->notePadForm->notePad->GetCurrent()) + tm.tmHeight + 5 > this->notePadForm->GetCy() + this->notePadForm->GetScrollController()->GetVPosition()) {
		this->notePadForm->GetScrollController()->MoveVScrLast();
		this->notePadForm->SetScrollPos(SB_VERT, this->notePadForm->GetScrollController()->GetVPosition(), TRUE);
	}
#endif 0;
	if (this->notePadForm->GetIsAutoLineBreak() == true) {
		Long rowCount = notePadModifier.CountRowFromStartToCurrent();
		Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
		notePadModifier.Combine();
		notePadModifier.Split();
		CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCount);
		notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);
	}
}