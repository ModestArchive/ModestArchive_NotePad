//CtrlP.cpp
#include"CtrlP.h"
#include"PrintCommand.h"
CtrlP::CtrlP(NotePadForm* notePadForm): KeyAction(notePadForm){

}

CtrlP::~CtrlP() {

}


void CtrlP::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	PrintCommand printCommand(this->notePadForm->GetNotePadFormControlWnd(), this->notePadForm);
	printCommand.Execute();
}