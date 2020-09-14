//CtrlN.cpp
#include"CtrlN.h"
#include"NewFileMakeCommand.h"

CtrlN::CtrlN(NotePadForm* notePadForm):KeyAction(notePadForm) {

}

CtrlN::~CtrlN() {

}

void CtrlN::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	NewFileMakeCommand newFileMakeCommand(this->notePadForm->GetNotePadFormControlWnd(), this->notePadForm);
	newFileMakeCommand.Execute();
}