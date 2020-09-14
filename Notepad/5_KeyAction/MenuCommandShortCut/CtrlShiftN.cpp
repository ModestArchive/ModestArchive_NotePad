//CtrlShiftN.cpp

#include"CtrlShiftN.h"
#include"NewWindowCommand.h"

CtrlSHiftN::CtrlSHiftN(NotePadForm* notePadForm) :KeyAction(notePadForm) {

}

CtrlSHiftN::~CtrlSHiftN() {

}

void CtrlSHiftN::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	NewWindowCommand newWindowCommand(this->notePadForm->GetNotePadFormControlWnd(), this->notePadForm);
	newWindowCommand.Execute();
}