//HLeftCode.cpp

#include"HLeftCode.h"
#include"ScrollController.h"
#include"Glyph.h"
#include"TextMetric.h"
HLeftCode::HLeftCode(NotePadForm* notePadForm):HScrollCodeAction(notePadForm) {

}

HLeftCode::~HLeftCode() {

}

void HLeftCode::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {

	this->notePadForm->GetScrollController()->MoveHScrFirst();
	this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
	TextMetric textMetric(this->notePadForm);
#if 0;
	while (this->notePadForm->GetScrollController()->GetHPosition() + this->notePadForm->GetCx() <
		textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent())) {

		this->notePadForm->row->Previous();
		
	}
#endif 0;
}