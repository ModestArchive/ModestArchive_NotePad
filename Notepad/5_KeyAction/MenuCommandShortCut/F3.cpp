//F3.cpp

#include"F3.h"
#include"FindNextCommand.h"
#include"NotePadForm.h"

F3::F3(NotePadForm* notePadForm) :KeyAction(notePadForm) {

}

F3::~F3() {
	
}

void F3::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	FindNextCommand findNextCommand(this->notePadForm->GetNotePadFormControlWnd(),this->notePadForm);
	findNextCommand.Execute();
}