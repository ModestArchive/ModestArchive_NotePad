//MouseWheelActionFactory.cpp

#include"MouseWheelActionFactory.h"
#include"MouseWheelDown.h"
#include"MouseWheelUp.h"
#include"ControlMouseWheelDown.h"
#include"ControlMouseWheelUp.h"

MouseWheelActionFactory::MouseWheelActionFactory(NotePadForm* notePadForm) {
	this->notePadForm = notePadForm;
}

MouseWheelActionFactory::~MouseWheelActionFactory() {

}

MouseWheelAction* MouseWheelActionFactory::MakeMouseWheel(short zDelta, bool isControlPushing) {

	MouseWheelAction* mouseWheelAction = 0;

	if (isControlPushing==true) {
		if (zDelta <= 0) {
			mouseWheelAction = new ControlMouseWheelDown(this->notePadForm);

		}
		else {
			mouseWheelAction = new ControlMouseWheelUp(this->notePadForm);
		}
	}
	else {
		if (zDelta <= 0) {
			mouseWheelAction = new MouseWheelDown(this->notePadForm);

		}
		else {
			mouseWheelAction = new MouseWheelUp(this->notePadForm);
		}
	}
	
	return mouseWheelAction;
}