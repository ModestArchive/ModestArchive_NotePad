//CtrlA.cpp
#include"CtrlA.h"
#include"SelectAllCommand.h"
CtrlA::CtrlA(NotePadForm* notePadForm) :KeyAction(notePadForm) {
	
}

CtrlA::~CtrlA() {

}

void CtrlA::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	SelectAllCommand selectAllCommand(this->notePadForm->GetNotePadFormControlWnd(), this->notePadForm);
	selectAllCommand.Execute();
}