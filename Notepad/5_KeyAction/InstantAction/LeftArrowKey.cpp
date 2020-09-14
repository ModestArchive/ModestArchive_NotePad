//LeftArrowKey.cpp

#include"LeftArrowKey.h"
#include"SingleByteCharacter.h"
#include"TextMetric.h"
#include"Font.h"
#include"ScrollController.h"
#include"Glyph.h"
#include"NotePadModifier.h"
#include"NotePadMetric.h"
#include"CoordinateCalculator.h"
#include"NotePadIndicator.h"

LeftArrowKey::LeftArrowKey() {


}


LeftArrowKey::LeftArrowKey(NotePadForm* notePadForm): KeyAction(notePadForm) {


}
LeftArrowKey::~LeftArrowKey() {


}

void LeftArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
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

	this->notePadForm->row->Previous();

	if (this->notePadForm->row->GetCurrent() < 0) {
		if (notePadForm->notePad->GetCurrent() > 0) {
			this->notePadForm->row->Next();
			this->notePadForm->notePad->Previous();
			this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
			this->notePadForm->row->Last();
#if 0;
			//스크롤 이동
			if (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetLength()) >= this->notePadForm->GetCx()) {
				this->notePadForm->GetScrollController()->SetHPos(textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetLength()) - this->notePadForm->GetCx() + tm.tmAveCharWidth);
				this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
			}
			if (textMetric.GetY(this->notePadForm->notePad->GetCurrent()) + tm.tmHeight + 5 < this->notePadForm->GetScrollController()->GetVPosition()) {

				this->notePadForm->GetScrollController()->MoveVScrPrevious();
				this->notePadForm->SetScrollPos(SB_VERT, this->notePadForm->GetScrollController()->GetVPosition(), TRUE);
			}
#endif 0;
		}
		else {
			this->notePadForm->row->Next();
		}
	}
	else {
		if (dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent()))) {

			if (((SingleByteCharacter*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent())))->GetSingleByteContent() == '\t') {
					Long i = 0;
					while(i<7){
					this->notePadForm->row->Previous();
					i++;
					}
			}
		}
#if 0;
		if (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent()) <=
			this->notePadForm->GetScrollController()->GetHPosition()) {
			Long i = 0;
			while (i < 15) {
				this->notePadForm->GetScrollController()->MoveHScrPrevious();
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
