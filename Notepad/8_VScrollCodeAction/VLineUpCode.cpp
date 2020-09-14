//VLineUpCode.cpp

#include"VLineUpCode.h"
#include"ScrollController.h"
#include"Font.h"
#include"TextMetric.h"
#include"Glyph.h"

VLineUpCode::VLineUpCode(NotePadForm* notePadForm) :VScrollCodeAction(notePadForm) {

}

VLineUpCode::~VLineUpCode() {

}

void VLineUpCode::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	this->notePadForm->GetScrollController()->MoveVScrPrevious();
	this->notePadForm->SetScrollPos(SB_VERT, this->notePadForm->GetScrollController()->GetVPosition(), TRUE);

	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	TextMetric textMetric(this->notePadForm);
#if 0;
	while (this->notePadForm->GetScrollController()->GetVPosition()+this->notePadForm->GetCy() <
		textMetric.GetY(this->notePadForm->notePad->GetCurrent()) + tm.tmHeight+5 ) {
		this->notePadForm->GetScrollController()->MoveHScrFirst();
		this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
		this->notePadForm->notePad->Previous();
		this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
		this->notePadForm->row->First();
	}
	while (this->notePadForm->GetScrollController()->GetVPosition() >=
		textMetric.GetY(this->notePadForm->notePad->GetCurrent()) + tm.tmHeight + 5) {
		this->notePadForm->GetScrollController()->MoveHScrFirst();
		this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
		this->notePadForm->notePad->Next();
		this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
		this->notePadForm->row->First();
	}
#endif 0;
}