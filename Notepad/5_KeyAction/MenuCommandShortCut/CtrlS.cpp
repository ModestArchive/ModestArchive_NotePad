//CtrlS.cpp
#include"CtrlS.h"
#include"SaveCommand.h"
CtrlS::CtrlS(NotePadForm* notePadForm) : KeyAction(notePadForm) {

}

CtrlS::~CtrlS() {

}

void CtrlS::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	SaveCommand saveCommand(this->notePadForm->GetNotePadFormControlWnd(), this->notePadForm);
	saveCommand.Execute();
}