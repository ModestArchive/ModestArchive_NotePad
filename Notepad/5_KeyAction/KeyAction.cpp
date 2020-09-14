//KeyAction.h

#include"KeyAction.h"

KeyAction::KeyAction() {
	this->notePadForm = 0;
}

KeyAction::KeyAction(NotePadForm *notePadForm) {
	this->notePadForm = notePadForm;
}

KeyAction::~KeyAction() {

}