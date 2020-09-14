//ControlMouseWheelUp.cpp

#include"ControlMouseWheelUp.h"

ControlMouseWheelUp::ControlMouseWheelUp(NotePadForm* notePadForm) : MouseWheelAction(notePadForm) {

}

ControlMouseWheelUp::~ControlMouseWheelUp() {

}

void ControlMouseWheelUp::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	LOGFONT expandLogfont = this->notePadForm->GetLogFont();
	expandLogfont.lfHeight -= 10;
	if (expandLogfont.lfHeight < -200) {
		expandLogfont.lfHeight += 10;
	}
	this->notePadForm->SetLogFont(expandLogfont);
}