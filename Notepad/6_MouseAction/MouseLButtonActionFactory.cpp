//MouseLButtonActionFactory.cpp
#include"MouseLButtonActionFactory.h"
#include"ShiftMouseLButton.h"
#include"MouseLButtonOneClick.h"

MouseLButtonActionFactory::MouseLButtonActionFactory(NotePadForm* notePadForm) {
	this->notePadForm = notePadForm;
}


MouseLButtonActionFactory::~MouseLButtonActionFactory() {

}


MouseLButtonAction* MouseLButtonActionFactory::MakeMouseAction() {
	MouseLButtonAction* mouseLButtonAction = 0;

	if (GetKeyState(VK_SHIFT) & 0x8000) {
		mouseLButtonAction = new ShiftMouseLButton(this->notePadForm);
	}
	else {
		mouseLButtonAction = new MouseLButtonOneClick(this->notePadForm);
	}
	return mouseLButtonAction;
}