//VBottomCode.cpp

#include"VBottomCode.h"
#include"ScrollController.h"
#include"Font.h"
#include"TextMetric.h"
#include"Glyph.h"


VBottomCode::VBottomCode(NotePadForm* notePadForm) :VScrollCodeAction(notePadForm){

}

VBottomCode::~VBottomCode() {

}

void VBottomCode::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {

	this->notePadForm->GetScrollController()->MoveVScrLast();
	this->notePadForm->SetScrollPos(SB_VERT, this->notePadForm->GetScrollController()->GetVPosition(), TRUE);
#if 0;
	TextMetric textMetric(this->notePadForm);
	while (this->notePadForm->GetScrollController()->GetVPosition() >
		textMetric.GetY(this->notePadForm->notePad->GetCurrent())) {
		this->notePadForm->GetScrollController()->MoveHScrFirst();
		this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
		this->notePadForm->notePad->Next();
		this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
		this->notePadForm->row->First();
		textMetric.GetY(this->notePadForm->notePad->GetCurrent()+1);
	}
#endif 0;
}