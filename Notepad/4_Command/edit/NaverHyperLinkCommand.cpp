//NaverHyperLinkCommand.cpp
#include"NaverHyperLinkCommand.h"
#include"NotePadFormControlWnd.h"
NaverHyperLinkCommand::NaverHyperLinkCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm) :Command(notePadForm) {
	this->notePadFormControlWnd = notePadFormControlWnd;
	this->notePadForm = notePadForm;
}

NaverHyperLinkCommand::~NaverHyperLinkCommand() {

}


void NaverHyperLinkCommand::Execute() {
	ShellExecute(this->notePadFormControlWnd->GetSafeHwnd(), "open", "http://www.naver.com", NULL, NULL, SW_SHOW);

}