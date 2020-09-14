//VThumbTrackCode.cpp

#include"VThumbTrackCode.h"
#include"ScrollController.h"
#include"Font.h"
#include"TextMetric.h"
#include"Glyph.h"


VThumbTrackCode::VThumbTrackCode(NotePadForm* notePadForm) :VScrollCodeAction(notePadForm) {

}

VThumbTrackCode::~VThumbTrackCode() {

}

void VThumbTrackCode::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {

	this->notePadForm->GetScrollController()->MoveVScrThumb();
	this->notePadForm->SetScrollPos(SB_VERT, this->notePadForm->GetScrollController()->GetVPosition(), TRUE);
#if 0;
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	TextMetric textMetric(this->notePadForm);

	while (this->notePadForm->GetScrollController()->GetVPosition() >
		textMetric.GetY(this->notePadForm->notePad->GetCurrent()) ) {
		this->notePadForm->GetScrollController()->MoveHScrFirst();
		this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
		this->notePadForm->notePad->Next();
		this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
		this->notePadForm->row->First();
		//textMetric.GetY(this->notePadForm->notePad->GetCurrent()+1);
	}


	while (this->notePadForm->GetScrollController()->GetVPosition() + this->notePadForm->GetCy() <
		textMetric.GetY(this->notePadForm->notePad->GetCurrent())+tm.tmHeight) {
		this->notePadForm->GetScrollController()->MoveHScrFirst();
		this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
		this->notePadForm->notePad->Previous();
		this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
		this->notePadForm->row->First();
		//textMetric.GetY(this->notePadForm->notePad->GetCurrent());
	}
#endif 0;
}