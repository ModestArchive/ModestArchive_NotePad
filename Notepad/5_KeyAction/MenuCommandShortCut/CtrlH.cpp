//CtrlH.cpp

#include"CtrlH.h"
#include"ReplaceContentCommand.h"

CtrlH::CtrlH(NotePadForm* notePadForm) :KeyAction(notePadForm) {

}


CtrlH::~CtrlH() {

}


void CtrlH::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	ReplaceContentCommand replaceContentCommand(this->notePadForm->GetNotePadFormControlWnd(), this->notePadForm);
	replaceContentCommand.Execute();
}