//DownArrowKey.cpp
#include"DownArrowKey.h"
#include"Glyph.h"
#include"TextMetric.h"
#include"ScrollController.h"
#include"Font.h"


DownArrowKey::DownArrowKey() {


}

DownArrowKey::DownArrowKey(NotePadForm* notePadForm) :KeyAction(notePadForm){


}
DownArrowKey::~DownArrowKey() {

}

void DownArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	Long previousRowWidth=0;
	Long previousRowIndex = 0;
	Long currentRowWidth=0;
	Long testWidth = 0;
	 
	
	previousRowWidth = textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent());
	previousRowIndex = this->notePadForm->row->GetCurrent();

	
	this->notePadForm->notePad->Next();
	
	if (this->notePadForm->notePad->GetCurrent() >= this->notePadForm->notePad->GetLength()) {
		this->notePadForm->notePad->Previous();
	}
	else {
		this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());

		currentRowWidth = textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetLength());

		if (previousRowWidth >= currentRowWidth) {
			this->notePadForm->row->Last();
			this->notePadForm->GetScrollController()->SetHPos(0);
			while(textMetric.GetX(this->notePadForm->row,this->notePadForm->row->GetCurrent()) >
				  this->notePadForm->GetScrollController()->GetHPosition()+this->notePadForm->GetCx()-tm.tmAveCharWidth/2){
					  this->notePadForm->GetScrollController()->MoveHScrNext();

			}
		}
		else {
			this->notePadForm->row->First();

			testWidth = textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent());

			while (testWidth!=previousRowWidth && testWidth < previousRowWidth) {

				this->notePadForm->row->Next();
				testWidth = textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent());

			}


		}
		if (textMetric.GetY(this->notePadForm->notePad->GetCurrent())+tm.tmHeight+5 >= 
			this->notePadForm->GetScrollController()->GetVPosition()+this->notePadForm->GetCy()) {

			this->notePadForm->GetScrollController()->MoveVScrNext();
			this->notePadForm->SetScrollPos(SB_VERT, this->notePadForm->GetScrollController()->GetVPosition(), TRUE);
		}
	}
	this->notePadForm->SetNoNeedToAutoLineBreak(true);
}