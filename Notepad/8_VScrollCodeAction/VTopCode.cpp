//VTopCode.cpp

#include"VTopCode.h"
#include"ScrollController.h"
#include"TextMetric.h"
#include"Glyph.h"
#include"Font.h"

VTopCode::VTopCode(NotePadForm* notePadForm) :VScrollCodeAction(notePadForm) {

}

VTopCode::~VTopCode() {

}

void VTopCode::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar){
	this->notePadForm->GetScrollController()->MoveVScrFirst();
	this->notePadForm->SetScrollPos(SB_VERT, this->notePadForm->GetScrollController()->GetVPosition(), TRUE);
#if 0;
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	

	while (this->notePadForm->GetScrollController()->GetVPosition()+this->notePadForm->GetCy() <
		textMetric.GetY(this->notePadForm->notePad->GetCurrent())+tm.tmHeight) {
		this->notePadForm->GetScrollController()->MoveHScrFirst();
		this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
		this->notePadForm->notePad->Previous();
		this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
		this->notePadForm->row->First();
		textMetric.GetY(this->notePadForm->notePad->GetCurrent());
	}
#endif 0;
}