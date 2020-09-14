//SelectAllCommand.h
#include"SelectAllCommand.h"
#include"CtrlHomeKey.h"
#include"ShiftCtrlEndKey.h"
#include"SelectionJudge.h"

SelectAllCommand::SelectAllCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm) :Command(notePadForm){
	this->notePadFormControlWnd = notePadFormControlWnd;
	this->notePadForm = notePadForm;
}

SelectAllCommand::~SelectAllCommand() {

}

void SelectAllCommand::Execute() {
	CtrlHomeKey ctrlHomeKey(this->notePadForm);
	ctrlHomeKey.OnKeyDown(0,0,0);
	ShiftCtrlEndKey shiftCtrlEndKey(this->notePadForm);
	shiftCtrlEndKey.OnKeyDown(0, 0, 0);
	SelectionJudge selectionJudge(this->notePadForm, this->notePadForm->GetSelector());
	selectionJudge.SelectionDecide();
}