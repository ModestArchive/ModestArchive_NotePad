//CtrlF.cpp

#include"CtrlF.h"
#include"FindContentCommand.h"

CtrlF::CtrlF(NotePadForm* notePadForm) :KeyAction(notePadForm) {

}

CtrlF::~CtrlF() {

}

void CtrlF::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	FindContentCommand findContents(this->notePadForm->GetNotePadFormControlWnd(),this->notePadForm);
	findContents.Execute();
}