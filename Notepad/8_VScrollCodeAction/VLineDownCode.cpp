//VLineDownCode.cpp

#include"VLineDownCode.h"
#include"ScrollController.h"
#include"TextMetric.h"
#include"Glyph.h"
#include"Font.h"


VLineDownCode::VLineDownCode(NotePadForm* notePadForm) :VScrollCodeAction(notePadForm) {

}

VLineDownCode::~VLineDownCode() {

}

void VLineDownCode::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	this->notePadForm->GetScrollController()->MoveVScrNext();
	this->notePadForm->SetScrollPos(SB_VERT, this->notePadForm->GetScrollController()->GetVPosition(), TRUE);
#if 0;
	TextMetric textMetric(this->notePadForm);
	while (this->notePadForm->GetScrollController()->GetVPosition() >=
		textMetric.GetY(this->notePadForm->notePad->GetCurrent())+tm.tmHeight+5) {
		this->notePadForm->GetScrollController()->MoveHScrFirst();
		this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
		this->notePadForm->notePad->Next();
		this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
		this->notePadForm->row->First();
	}
	while (this->notePadForm->GetScrollController()->GetVPosition() + this->notePadForm->GetCy() <
		textMetric.GetY(this->notePadForm->notePad->GetCurrent()) + tm.tmHeight + 5) {
		this->notePadForm->GetScrollController()->MoveHScrFirst();
		this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
		this->notePadForm->notePad->Previous();
		this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
		this->notePadForm->row->First();
	}
#endif 0;
}