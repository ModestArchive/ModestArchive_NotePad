//CtrlLeftArrowKey.cpp

#include"CtrlLeftArrowKey.h"
#include"ScrollController.h"
#include"TextMetric.h"
#include"Font.h"
#include"Glyph.h"
#include"NotePadMetric.h"
#include"NotePadModifier.h"
#include"CoordinateCalculator.h"
#include"NotePadIndicator.h"
CtrlLeftArrowKey::CtrlLeftArrowKey() {


}

CtrlLeftArrowKey::CtrlLeftArrowKey(NotePadForm* notePadForm) :KeyAction(notePadForm){
	
}

CtrlLeftArrowKey::~CtrlLeftArrowKey() {

}


void CtrlLeftArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

	NotePadModifier notePadModifier(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);
	CoordinateCalculator coordinateCalculator(this->notePadForm);
	NotePadIndicator notePadIndicator(this->notePadForm);

	Long rowCount = notePadModifier.CountRowFromStartToCurrent();
	Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
	notePadModifier.Combine();
	CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCount);
	notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);

	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	TextMetric textMetric(this->notePadForm);

	Long index = this->notePadForm->row->GetCurrent();

	if (index == 0) {
		if (notePadForm->notePad->GetCurrent() > 0) {

			this->notePadForm->notePad->Previous();
			this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
			this->notePadForm->row->Last();
#if 0;
			if (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetLength()) >=
				this->notePadForm->GetScrollController()->GetHPosition() + this->notePadForm->GetCx()) {

				while (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetLength()) >=
					this->notePadForm->GetScrollController()->GetHPosition() + this->notePadForm->GetCx()) {
					this->notePadForm->GetScrollController()->MoveHScrNext();
				}
				Long i = 0;
				while (i < 22) {
					this->notePadForm->GetScrollController()->MoveHScrNext();
					i++;
				}
			}
			this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);

			if (textMetric.GetY(this->notePadForm->notePad->GetCurrent()) + tm.tmHeight + 5 < this->notePadForm->GetScrollController()->GetVPosition()) {

				this->notePadForm->GetScrollController()->MoveVScrPrevious();
				this->notePadForm->SetScrollPos(SB_VERT, this->notePadForm->GetScrollController()->GetVPosition(), TRUE);
			}
#endif 0;
		}
	}
	else {

		while (this->notePadForm->row->GetCurrent() != 0 &&
			  ((char*)(this->notePadForm->row->GetAt((this->notePadForm->row->GetCurrent())-1)->GetContents().c_str()))[0] != ' ') {
				  this->notePadForm->row->Previous();
		}
		if (this->notePadForm->row->GetCurrent() == index) {
			while (this->notePadForm->row->GetCurrent() != 0 &&
				((char*)(this->notePadForm->row->GetAt((this->notePadForm->row->GetCurrent())-1)->GetContents().c_str()))[0] == ' ') {

				this->notePadForm->row->Previous();

			}

			while (this->notePadForm->row->GetCurrent() != 0 &&
				((char*)(this->notePadForm->row->GetAt((this->notePadForm->row->GetCurrent())-1)->GetContents().c_str()))[0] != ' ') {

				this->notePadForm->row->Previous();

			}
		}
#if 0;
		if (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent()) <
			this->notePadForm->GetScrollController()->GetHPosition()) {

			while (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent()) <
				this->notePadForm->GetScrollController()->GetHPosition()) {
				this->notePadForm->GetScrollController()->MoveHScrPrevious();
			}
			Long i = 0;
			while (i < 22) {
				this->notePadForm->GetScrollController()->MoveHScrPrevious();
				i++;
			}
		}
		this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
#endif 0;
	}
	if (this->notePadForm->GetIsAutoLineBreak()==true) {
		Long rowCount = notePadModifier.CountRowFromStartToCurrent();
		Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
		notePadModifier.Combine();
		notePadModifier.Split();
		CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCount);
		notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);
	}

}
