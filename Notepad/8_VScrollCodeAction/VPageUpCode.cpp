//VPageUpCode.cpp

#include"VPageUpCode.h"
#include"ScrollController.h"
#include"Font.h"
#include"NotePadForm.h"
#include"TextMetric.h"
#include"Glyph.h"

VPageUpCode::VPageUpCode(NotePadForm* notePadForm) :VScrollCodeAction(notePadForm) {

}

VPageUpCode::~VPageUpCode() {

}

void VPageUpCode::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	this->notePadForm->GetScrollController()->MoveVScrPageUp();
	this->notePadForm->SetScrollPos(SB_VERT, this->notePadForm->GetScrollController()->GetVPosition(), TRUE);
#if 0;
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	TextMetric textMetric(this->notePadForm);

	while (this->notePadForm->GetScrollController()->GetVPosition() + this->notePadForm->GetCy() <
		textMetric.GetY(this->notePadForm->notePad->GetCurrent()) + tm.tmHeight ) {
		this->notePadForm->GetScrollController()->MoveHScrFirst();
		this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
		this->notePadForm->notePad->Previous();
		this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
		this->notePadForm->row->First();
		textMetric.GetY(this->notePadForm->notePad->GetCurrent());
	}
#endif 0;
	
}