//MouseWheelUp.cpp

#include"MouseWheelUp.h"
#include"Font.h"
#include"TextMetric.h"
#include"ScrollController.h"
#include"Glyph.h"


MouseWheelUp::MouseWheelUp(NotePadForm* notePadForm) : MouseWheelAction(notePadForm) {

}

MouseWheelUp::~MouseWheelUp() {

}

void MouseWheelUp::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {

	this->notePadForm->GetScrollController()->MoveVScrPrevious();
	this->notePadForm->SetScrollPos(SB_VERT, this->notePadForm->GetScrollController()->GetVPosition(), TRUE);

	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	TextMetric textMetric(this->notePadForm);
#if 0;
	if (this->notePadForm->GetScrollController()->GetVPosition() + this->notePadForm->GetCy() <
		textMetric.GetY(this->notePadForm->notePad->GetCurrent()) + tm.tmHeight) {
		this->notePadForm->GetScrollController()->MoveHScrFirst();
		this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
		this->notePadForm->notePad->Previous();
		this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
		this->notePadForm->row->First();
	}
#endif 0;
}
