//StatusBarCommand.cpp
#include"StatusBarCommand.h"
#include"NotePadFormControlWnd.h"
#include"NotePadForm.h"
#include"StatusBarMaker.h"
#include<afxext.h>

StatusBarCommand::StatusBarCommand(NotePadFormControlWnd* notePadFormControlWnd,NotePadForm* notePadForm) :Command(notePadForm) {
	this->notePadFormControlWnd = notePadFormControlWnd;
	this->notePadForm = notePadForm;
}


StatusBarCommand::~StatusBarCommand() {
	
}


void StatusBarCommand::Execute() {
	StatusBarMaker statusBarMaker(this->notePadFormControlWnd);
	if (this->notePadForm->GetParent()->GetMenu()->GetMenuState(30002,MF_BYCOMMAND)==MF_UNCHECKED) {
		statusBarMaker.SetStatusBar();
		this->notePadForm->GetParent()->GetMenu()->CheckMenuItem(30002, MF_CHECKED);
	}
	else {
		statusBarMaker.RemoveStatusBar();
		this->notePadForm->GetParent()->GetMenu()->CheckMenuItem(30002, MF_UNCHECKED);
	}
}