//MouseWheelDown.cpp

#include"MouseWheelDown.h"
#include"Font.h"
#include"TextMetric.h"
#include"ScrollController.h"
#include"Glyph.h"

MouseWheelDown::MouseWheelDown(NotePadForm* notePadForm): MouseWheelAction(notePadForm){

}

MouseWheelDown::~MouseWheelDown() {

}

void MouseWheelDown::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {

	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	this->notePadForm->GetScrollController()->MoveVScrNext();
	this->notePadForm->SetScrollPos(SB_VERT, this->notePadForm->GetScrollController()->GetVPosition(), TRUE);
#if 0;
	TextMetric textMetric(this->notePadForm);
	if (this->notePadForm->GetScrollController()->GetVPosition() >=
		textMetric.GetY(this->notePadForm->notePad->GetCurrent()) + tm.tmHeight + 5) {
		this->notePadForm->GetScrollController()->MoveHScrFirst();
		this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
		this->notePadForm->notePad->Next();
		this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
		this->notePadForm->row->First();
	}
#endif 0;
}
