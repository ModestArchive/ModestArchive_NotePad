//RightArrowKey.cpp

#include"RightArrowKey.h"
#include"SingleByteCharacter.h"
#include"Font.h"
#include"ScrollController.h"
#include"TextMetric.h"
#include"Glyph.h"
#include"NotePadModifier.h"
#include"NotePadMetric.h"
#include"CoordinateCalculator.h"
#include"NotePadIndicator.h"

RightArrowKey::RightArrowKey() {

}
RightArrowKey::RightArrowKey(NotePadForm* notePadForm):KeyAction(notePadForm) {

}

RightArrowKey::~RightArrowKey() {

}

void RightArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	TextMetric textMetric(this->notePadForm);

	NotePadModifier notePadModifier(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);
	CoordinateCalculator coordinateCalculator(this->notePadForm);
	NotePadIndicator notePadIndicator(this->notePadForm);

	Long rowCount = notePadModifier.CountRowFromStartToCurrent();
	Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
	notePadModifier.Combine();
	CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCount);
	notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);

	this->notePadForm->row->Next();

	if (this->notePadForm->row->GetCurrent() > this->notePadForm->row->GetLength()) {

		if (this->notePadForm->notePad->GetCurrent() < this->notePadForm->notePad->GetLength()-1) {
			notePadForm->row->Previous();
			notePadForm->notePad->Next();
			notePadForm->row = notePadForm->notePad->GetAt(notePadForm->notePad->GetCurrent());
			notePadForm->row->First();
#if 0;
			this->notePadForm->GetScrollController()->MoveHScrFirst();
			this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);

			if (textMetric.GetY(this->notePadForm->notePad->GetCurrent()) + tm.tmHeight + 5 >
				this->notePadForm->GetScrollController()->GetVPosition() + this->notePadForm->GetCy()) {
				this->notePadForm->GetScrollController()->MoveVScrNext();
				this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
			}
#endif 0;
		}
		else {
			notePadForm->row->Previous();
		}
	}
	else {
		if (dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt((this->notePadForm->row->GetCurrent())-1))) {
			if (((SingleByteCharacter*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent()-1)))->GetSingleByteContent() == '\t') {
				Long i = 0;
				while (i < 7) {
					this->notePadForm->row->Next();
					i++;
				}
			}
		}
#if 0;
		if (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent()) >=
			this->notePadForm->GetScrollController()->GetHPosition()+this->notePadForm->GetCx()) {
			Long i = 0;
			while (i < 15) {
				this->notePadForm->GetScrollController()->MoveHScrNext();
				i++;
			}
			this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
		}
#endif 0;
	}
	if (this->notePadForm->GetIsAutoLineBreak() == true) {
		Long rowCount = notePadModifier.CountRowFromStartToCurrent();
		Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
		notePadModifier.Combine();
		notePadModifier.Split();
		CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCount);
		notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);
	}
}
