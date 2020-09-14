//ShiftF3.cpp
#include"ShiftF3.h"
#include"FindPreviousCommand.h"
#include"NotePadForm.h"

ShiftF3::ShiftF3(NotePadForm* notePadForm):KeyAction(notePadForm) {
	
}

ShiftF3::~ShiftF3() {

}

void ShiftF3::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	FindPreviousCommand findPreviousCommand(this->notePadForm->GetNotePadFormControlWnd(), this->notePadForm);
	findPreviousCommand.Execute();
}