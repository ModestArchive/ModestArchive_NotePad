//F5.cpp
#include"F5.h"
#include"DateAndTimeShowCommand.h"
#include"NotePadForm.h"

F5::F5(NotePadForm* notePadForm) : KeyAction(notePadForm){

}

F5::~F5() {

}

void F5::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	DateAndTimeShowCommand dateAndTimeShowCommand(this->notePadForm);
	dateAndTimeShowCommand.Execute();
}