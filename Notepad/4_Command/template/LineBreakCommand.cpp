//LineBreakCommand.cpp
#include"LineBreakCommand.h"
#include"ScrollController.h"
#include"AutoLineBreak.h"
#include"NotePadModifier.h"
#include"NotePad.h"
#include"Glyph.h"
#include"NotePadRestorer.h"
#include"Selector.h"
#include"NotePadFormControlWnd.h"
#include"FindReplaceSupervisor.h"


LineBreakCommand::LineBreakCommand(NotePadForm* notePadForm) :Command(notePadForm) {

	this->notePadForm = notePadForm;

}


LineBreakCommand::~LineBreakCommand() {

}


void LineBreakCommand::Execute() {
	CMenu* myMenu = this->notePadForm->GetParent()->GetMenu();
	NotePadModifier notePadModifier(this->notePadForm);
	
	if (myMenu->GetMenuState(30000,MF_BYCOMMAND)==MF_UNCHECKED) {//자동개행을 시작하는 상황
		AutoLineBreak* autoLineBreak = new AutoLineBreak(this->notePadForm);
		this->notePadForm->SetAutoLineBreak(autoLineBreak);
		myMenu->CheckMenuItem(30000, MF_CHECKED);
	}
	else if(myMenu->GetMenuState(30000, MF_BYCOMMAND) == MF_CHECKED){//자동개행을 해제하려는 상황
		
		if (this->notePadForm->GetAutoLineBreak() != 0) {
			AutoLineBreak* autoLineBreak = this->notePadForm->GetAutoLineBreak();
			delete this->notePadForm->GetAutoLineBreak();
			this->notePadForm->SetAutoLineBreak(0);
		}
		notePadModifier.Combine();
		myMenu->CheckMenuItem(30000, MF_UNCHECKED);
		this->notePadForm->SetIsAutoLineBreak(false);
	}

	if (this->notePadForm->GetIsComposition() == true) {
		this->notePadForm->SetIsComposition(false);
	}
	if (this->notePadForm->GetIsSelected()== true) {
		this->notePadForm->SetIsSelected(false);
		if (this->notePadForm->GetSelector()!= 0) {
			delete this->notePadForm->GetSelector();
		}
		Selector* selector = new Selector(this->notePadForm);
		this->notePadForm->SetSelector(selector);
		if (((NotePadFormControlWnd*)(this->notePadForm->GetParent()))->GetContentsFinder() != 0) {
			FindReplaceSupervisor findReplaceSupervisor(((NotePadFormControlWnd*)(this->notePadForm->GetParent())), this->notePadForm,
														((NotePadFormControlWnd*)(this->notePadForm->GetParent()))->GetContentsFinder(), 0, 0);
			findReplaceSupervisor.DeleteMatchIndexCollector();
		}
	}
	
	this->notePadForm->GetScrollController()->SetHPos(0);
	this->notePadForm->GetScrollController()->SetVPos(0);

	this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());

	if (this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetLength() > 0) {
		delete this->notePadForm->GetNotePadRestorer()->GetNotePadHistory();
		NotePadHistory* notePadHistory = new NotePadHistory();
		this->notePadForm->GetNotePadRestorer()->SetNotePadHistory(notePadHistory);
	}
}