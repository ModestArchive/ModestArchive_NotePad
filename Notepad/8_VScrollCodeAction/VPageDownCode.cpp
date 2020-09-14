//VPageDownCode.cpp


#include"VPageDownCode.h"
#include"ScrollController.h"
#include"Font.h"
#include"NotePadForm.h"
#include"TextMetric.h"
#include"Glyph.h"

VPageDownCode::VPageDownCode(NotePadForm* notePadForm) :VScrollCodeAction(notePadForm) {

}

VPageDownCode::~VPageDownCode() {

}

void VPageDownCode::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	this->notePadForm->GetScrollController()->MoveVScrPageDown();
	this->notePadForm->SetScrollPos(SB_VERT, this->notePadForm->GetScrollController()->GetVPosition(), TRUE);
#if 0;
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	TextMetric textMetric(this->notePadForm);
	while (this->notePadForm->GetScrollController()->GetVPosition() >=
		textMetric.GetY(this->notePadForm->notePad->GetCurrent()) + tm.tmHeight + 5) {
		this->notePadForm->GetScrollController()->MoveHScrFirst();
		this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
		this->notePadForm->notePad->Next();
		this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
		this->notePadForm->row->First();
		textMetric.GetY(this->notePadForm->notePad->GetCurrent()+1);
	}
#endif 0;
	
}