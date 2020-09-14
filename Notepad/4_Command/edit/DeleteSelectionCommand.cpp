//DeleteSelectionCommand.cpp

#include"DeleteSelectionCommand.h"
#include"SelectionEraseSupervisor.h"
#include"StringMaker.h"
#include"Selector.h"

DeleteSelectionCommand::DeleteSelectionCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm) :Command(notePadForm) {
	this->notePadFormControlWnd = notePadFormControlWnd;
	this->notePadForm = notePadForm;
}

DeleteSelectionCommand::~DeleteSelectionCommand() {

}


void DeleteSelectionCommand::Execute() {
	SelectionEraseSupervisor selectionEraseSupervisor(this->notePadForm);
	StringMaker stringMaker(this->notePadForm);
	string* contents = new string(stringMaker.MakeStringInSelectedArea());
	selectionEraseSupervisor.EraseContents(contents, true);

	this->notePadForm->SetIsSelected(false);
	if (this->notePadForm->GetSelector() != 0) {
		delete this->notePadForm->GetSelector();
	}
	Selector* selector = new Selector(this->notePadForm);
	this->notePadForm->SetSelector(selector);
}