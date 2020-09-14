//CtrlShiftS.cpp

#include"CtrlShiftS.h"
#include"NotePadForm.h"
#include"OtherNameSaveCommand.h"

CtrlShiftS::CtrlShiftS(NotePadForm* notePadForm) :KeyAction(notePadForm){

}

CtrlShiftS::~CtrlShiftS() {

}


void CtrlShiftS::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	OtherNameSaveCommand otherNameSaveCommand(this->notePadForm);
	otherNameSaveCommand.Execute();
}