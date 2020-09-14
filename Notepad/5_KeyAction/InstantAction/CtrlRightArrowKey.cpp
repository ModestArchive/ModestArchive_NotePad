//CtrlRightArrowKey.cpp

#include"CtrlRightArrowKey.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"Font.h"
#include"TextMetric.h"
#include"NotePadMetric.h"
#include"NotePadModifier.h"
#include"CoordinateCalculator.h"
#include"NotePadIndicator.h"
CtrlRightArrowKey::CtrlRightArrowKey() {


}

CtrlRightArrowKey::CtrlRightArrowKey(NotePadForm* notePadForm):KeyAction(notePadForm) {


}

CtrlRightArrowKey::~CtrlRightArrowKey() {

}


void CtrlRightArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
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
	
	
	if (index == this->notePadForm->row->GetLength()) {

		if (this->notePadForm->notePad->GetCurrent() < this->notePadForm->notePad->GetLength()-1 ) {

			this->notePadForm->notePad->Next();
			this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
			this->notePadForm->row->First();
#if 0;
			this->notePadForm->GetScrollController()->MoveHScrFirst();
			this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);

			if (textMetric.GetY(this->notePadForm->notePad->GetCurrent()) + tm.tmHeight + 5 >
				this->notePadForm->GetScrollController()->GetVPosition()+this->notePadForm->GetCy()) {
				this->notePadForm->GetScrollController()->MoveVScrNext();
				this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
			}
#endif 0;
		}
	}

	else {
		
		while (this->notePadForm->row->GetCurrent() != this->notePadForm->row->GetLength() &&
			((char*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent() )->GetContents().c_str()))[0] != ' ') {


			this->notePadForm->row->Next();

		}
		if (this->notePadForm->row->GetCurrent() == index) {

			while (this->notePadForm->row->GetCurrent() != this->notePadForm->row->GetLength() &&
				((char*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent())->GetContents().c_str()))[0] == ' ') {

				this->notePadForm->row->Next();

			}
			while (this->notePadForm->row->GetCurrent() != this->notePadForm->row->GetLength() &&
				((char*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent())->GetContents().c_str()))[0] != ' ') {

				this->notePadForm->row->Next();

			}
			while (this->notePadForm->row->GetCurrent() != this->notePadForm->row->GetLength() &&
				((char*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent())->GetContents().c_str()))[0] == ' ') {

				this->notePadForm->row->Next();

			}
		}
		while (this->notePadForm->row->GetCurrent() != this->notePadForm->row->GetLength() &&
			((char*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent())->GetContents().c_str()))[0] == ' ') {

			this->notePadForm->row->Next();

		}
#if 0;
		if (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent()) >=
			this->notePadForm->GetScrollController()->GetHPosition() + this->notePadForm->GetCx()) {

			while (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent()) >=
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
