//CommandFactory.cpp

#include"CommandFactory.h"
#include"LoadCommand.h"
#include"SaveCommand.h"
#include"OtherNameSaveCommand.h"
#include"LineBreakCommand.h"
#include"FontConfigureCommand.h"
#include"StatusBarCommand.h"
#include"FindContentCommand.h"
#include"ReplaceContentCommand.h"
#include"NotePadFormControlWnd.h"
#include"FontSizeInitializeCommand.h"
#include"FontSizeExpandCommand.h"
#include"FontSizeDownsizeCommand.h"
#include"DateAndTimeShowCommand.h"
#include"PrintCommand.h"
#include"HelpCommand.h"
#include"FinishTaskCommand.h"
#include"NewFileMakeCommand.h"
#include"NewWindowCommand.h"
#include"NaverHyperLinkCommand.h"
#include"UndoCommand.h"
#include"RedoCommand.h"
#include"CutSelectionCommand.h"
#include"CopySelectionCommand.h"
#include"DeleteSelectionCommand.h"
#include"PasteCommand.h"
#include"FindNextCommand.h"
#include"FindPreviousCommand.h"
#include"PageConfigureCommand.h"
#include"PageConfigureCommand.h"
#include"SelectAllCommand.h"
#include <afxwin.h>

CommandFactory::CommandFactory(NotePadForm* notePadForm, NotePadFormControlWnd* notePadFormControlWnd) {
	this->notePadForm = notePadForm;
	this->notePadFormControlWnd = notePadFormControlWnd;
}

CommandFactory::~CommandFactory() {

}

Command* CommandFactory::MakeCommand(UINT nID) {

	Command* command = 0;
	//CMenu* cMainMenu = this->notePadForm->GetMenu();
	//CMenu* subMenu = cMainMenu->GetSubMenu(0);

	if (nID == 10000 ) {
		command = new LoadCommand(this->notePadForm);
		this->notePadForm->GetNotePadFormControlWnd()->SetNoNeedToScroll(true);
	}
	else if (nID== 10001) {
		command = new SaveCommand(this->notePadFormControlWnd,this->notePadForm);
		this->notePadForm->GetNotePadFormControlWnd()->SetNoNeedToScroll(true);
	}
	else if (nID== 10002) {
		command = new OtherNameSaveCommand(this->notePadForm);
		this->notePadForm->GetNotePadFormControlWnd()->SetNoNeedToScroll(true);
	}
	else if (nID == 10003) {
		command = new PrintCommand(this->notePadFormControlWnd,this->notePadForm);
	}
	else if (nID==9000) {
		command = new NewFileMakeCommand(this->notePadFormControlWnd,this->notePadForm );
	}
	else if (nID==9001) {
		command = new NewWindowCommand(this->notePadFormControlWnd, this->notePadForm);
	}
	else if (nID==9003) {
		command = new PageConfigureCommand(this->notePadFormControlWnd, this->notePadForm);
		this->notePadForm->GetNotePadFormControlWnd()->SetNoNeedToScroll(true);
	}
	else if (nID==9004) {
		command = new FinishTaskCommand(this->notePadFormControlWnd, this->notePadForm);
	}
	else if (nID==9005) {
		command = new UndoCommand(this->notePadFormControlWnd, this->notePadForm);
	}
	else if (nID==9006) {
		command = new RedoCommand(this->notePadFormControlWnd, this->notePadForm);
	}
	else if (nID==9007) {
		command = new CutSelectionCommand(this->notePadFormControlWnd,this->notePadForm);
	}
	else if (nID==9008) {
		command = new CopySelectionCommand(this->notePadFormControlWnd, this->notePadForm);
	}
	else if (nID==9009) {
		command = new DeleteSelectionCommand(this->notePadFormControlWnd, this->notePadForm);
	}
	else if (nID==9010) {
		command = new PasteCommand(this->notePadFormControlWnd, this->notePadForm);
	}
	else if (nID==9011) {
		command = new NaverHyperLinkCommand(this->notePadFormControlWnd,this->notePadForm);
	}
	else if (nID==9012) {
		command = new FindNextCommand(this->notePadFormControlWnd,this->notePadForm);
	}
	else if (nID==9013) {
		command = new FindPreviousCommand(this->notePadFormControlWnd,this->notePadForm);
	}
	else if (nID==9014) {
		command = new SelectAllCommand(this->notePadFormControlWnd, this->notePadForm);
	}
	else if (nID==20000) {
		command = new FindContentCommand(this->notePadFormControlWnd,this->notePadForm);
	}
	else if (nID == 20001) {
		command = new ReplaceContentCommand(this->notePadFormControlWnd,this->notePadForm);
	}
	else if (nID==20002) {
		command = new DateAndTimeShowCommand(this->notePadForm);
	}
	else if (nID == 30000) {
		command = new LineBreakCommand(this->notePadForm);
	}
	else if (nID==30001) {
		command = new FontConfigureCommand(this->notePadForm);
		this->notePadForm->GetNotePadFormControlWnd()->SetNoNeedToScroll(true);
	}
	else if (nID==30002) {
		command=  new StatusBarCommand(this->notePadFormControlWnd,this->notePadForm);
	}
	else if (nID==30003) {
		command = new FontSizeExpandCommand(this->notePadForm);
	}
	else if (nID == 30004) {
		command = new FontSizeDownsizeCommand(this->notePadForm);
	}
	else if (nID == 30005) {
		command = new FontSizeInitializeCommand(this->notePadForm);
	}
	else if (nID == 30006) {
		command = new HelpCommand(this->notePadForm);
		this->notePadForm->GetNotePadFormControlWnd()->SetNoNeedToScroll(true);
	}

	return command;
}