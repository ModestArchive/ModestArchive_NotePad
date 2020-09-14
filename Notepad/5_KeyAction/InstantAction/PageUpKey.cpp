//PageUpKey.cpp

#include"PageUpKey.h"
#include"ScrollController.h"
#include"Font.h"
#include"TextMetric.h"
#include"Glyph.h"

PageUpKey::PageUpKey() {


}


PageUpKey::PageUpKey(NotePadForm* notePadForm) : KeyAction(notePadForm) {


}

PageUpKey::~PageUpKey() {


}

void PageUpKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	this->notePadForm->GetScrollController()->MoveVScrPageUp();
	this->notePadForm->SetScrollPos(SB_VERT, this->notePadForm->GetScrollController()->GetVPosition(), TRUE);

	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	TextMetric textMetric(this->notePadForm);

	while (this->notePadForm->GetScrollController()->GetVPosition() + this->notePadForm->GetCy() <
		textMetric.GetY(this->notePadForm->notePad->GetCurrent()) + tm.tmHeight) {
		this->notePadForm->GetScrollController()->MoveHScrFirst();
		this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
		this->notePadForm->notePad->Previous();
		this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
		this->notePadForm->row->First();
		textMetric.GetY(this->notePadForm->notePad->GetCurrent());
	}
}