//FinishTaskCommand.cpp

#include"FinishTaskCommand.h"
#include"NotePadFormControlWnd.h"
FinishTaskCommand::FinishTaskCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm) :Command(notePadForm){
	this->notePadFormControlWnd = notePadFormControlWnd;
	this->notePadForm = notePadForm;
}

FinishTaskCommand::~FinishTaskCommand() {

}

void FinishTaskCommand::Execute() {
	this->notePadFormControlWnd->OnClose();
}