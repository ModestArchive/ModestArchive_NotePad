//CtrlO.h
#include"CtrlO.h"
#include"LoadCommand.h"

CtrlO::CtrlO(NotePadForm* notePadForm) :KeyAction(notePadForm) {
	
}

CtrlO::~CtrlO() {

}

void CtrlO::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	LoadCommand loadCommand(this->notePadForm);
	loadCommand.Execute();
}