//Printer.cpp

#include"Printer.h"

Printer::Printer(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm) {
	this->notePadFormControlWnd = notePadFormControlWnd;
	this->notePadForm = notePadForm;
	PAGESETUPDLG psd;
	psd.rtMargin.top = 800;
	psd.rtMargin.left = 650;
	psd.rtMargin.right = 650;
	psd.rtMargin.bottom = 800;
	this->pageSetUpdlg = new PAGESETUPDLG(psd);
}

Printer::~Printer() {
	if (this->pageSetUpdlg!=0) {//notePadFormControlWnd OnCreate할때 만들어주고 ,OnClose에서 지워주기.
		delete this->pageSetUpdlg;
	}
}


void Printer::PrintContents() {

}

void Printer::SetUpPageconfiguration() {

}