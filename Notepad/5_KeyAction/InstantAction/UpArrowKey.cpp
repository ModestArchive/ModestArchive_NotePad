//UpArrowKey.cpp
#include"UpArrowKey.h"
#include"Glyph.h"
#include"TextMetric.h"
#include"ScrollController.h"
#include"Font.h"


UpArrowKey::UpArrowKey() {


}

UpArrowKey::UpArrowKey(NotePadForm* notePadForm): KeyAction(notePadForm) {


}
UpArrowKey::~UpArrowKey() {

}

void UpArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	TextMetric textMetric(this->notePadForm);

	Long previousRowWidth=0;
	Long previousRowIndex = 0;
	Long currentRowWidth=0;
	Long testWidth = 0;
	 
	
	previousRowWidth = textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent());
	previousRowIndex = this->notePadForm->row->GetCurrent();


	this->notePadForm->notePad->Previous();

	if (this->notePadForm->notePad->GetCurrent() < 0) {
		this->notePadForm->notePad->Next();
	}

	else {
		this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());

		currentRowWidth= textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetLength());

		if (previousRowWidth >= currentRowWidth) {
			this->notePadForm->row->Last();
		}
		else {
			this->notePadForm->row->First();
			testWidth = textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent());
			while ( testWidth != previousRowWidth && testWidth < previousRowWidth ) {
				this->notePadForm->row->Next();
				testWidth = textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent());
			}
			
		}
		
		if (textMetric.GetY(this->notePadForm->notePad->GetCurrent()) + tm.tmHeight + 5 <= this->notePadForm->GetScrollController()->GetVPosition()) {

			this->notePadForm->GetScrollController()->MoveVScrPrevious();
			this->notePadForm->SetScrollPos(SB_VERT, this->notePadForm->GetScrollController()->GetVPosition(), TRUE);
		}
		while (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent()) < 
			   this->notePadForm->GetScrollController()->GetHPosition()) {
			this->notePadForm->GetScrollController()->MoveHScrPrevious();
			this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
		}
		
	}
	this->notePadForm->SetNoNeedToAutoLineBreak(true);
}