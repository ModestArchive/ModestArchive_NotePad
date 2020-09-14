//CtrlE.cpp
#include"CtrlE.h"
#include"NaverHyperLinkCommand.h"
CtrlE::CtrlE(NotePadForm* notePadForm) :KeyAction(notePadForm){

}

CtrlE::~CtrlE() {

}

void CtrlE::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	NaverHyperLinkCommand naverHyperLinkCommand(this->notePadForm->GetNotePadFormControlWnd(), this->notePadForm);
	naverHyperLinkCommand.Execute();
}