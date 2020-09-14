//ControlMouseWheelDown.cpp

#include"ControlMouseWheelDown.h"

ControlMouseWheelDown::ControlMouseWheelDown(NotePadForm* notePadForm) : MouseWheelAction(notePadForm) {

}

ControlMouseWheelDown::~ControlMouseWheelDown() {

}


void ControlMouseWheelDown::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {

	LOGFONT downsizeLogfont = this->notePadForm->GetLogFont();
	downsizeLogfont.lfHeight += 10;
	if (downsizeLogfont.lfHeight > 10) {	
		downsizeLogfont.lfHeight -= 10;
	}
	this->notePadForm->SetLogFont(downsizeLogfont);

}