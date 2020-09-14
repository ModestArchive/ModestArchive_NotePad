//FindContentCommand.cpp

#include<afxdlgs.h>
#include"Glyph.h"
#include"FindContentCommand.h"
#include"MatchIndexCollector.h"
#include"ContentsFinder.h"
#include"NotePadModifier.h"
#include"NotePadMetric.h"
#include"CoordinateCalculator.h"
#include"NotePadIndicator.h"
#include"MatchIndex.h"
#include"NotePadFormControlWnd.h"
#include"FindReplaceSupervisor.h"
#include"StringMaker.h"


FindContentCommand::FindContentCommand(NotePadFormControlWnd* notePadFormControlWnd,NotePadForm* notePadForm) :Command(notePadForm) {
	this->notePadFormControlWnd = notePadFormControlWnd;
	this->notePadForm = notePadForm;
}


FindContentCommand::~FindContentCommand() {

}


void FindContentCommand::Execute() {

	FindReplaceSupervisor findReplaceSupervisor(this->notePadFormControlWnd,this->notePadForm,this->notePadFormControlWnd->GetContentsFinder(),0,0);
	findReplaceSupervisor.GetReadyToCreateFindPdlg();

	ContentsFinder* contentsFinder = this->notePadFormControlWnd->GetContentsFinder();
	CFindReplaceDialog* cFindReplaceDialog = new CFindReplaceDialog();

	if (this->notePadForm->GetIsSelected()==true) {
		StringMaker stringMaker(this->notePadForm);
		string selectedContents = "";
		selectedContents = stringMaker.MakeStringInSelectedArea();
		if (contentsFinder->GetFindWhatString() != 0) {
			if (contentsFinder->GetIsDownWardSearching() && contentsFinder->GetIsCompletelyMatchSearching()) {
				cFindReplaceDialog->Create(true, selectedContents.c_str(), _T(""), FR_DOWN | FR_MATCHCASE | FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
			}
			else if (contentsFinder->GetIsDownWardSearching() && contentsFinder->GetIsContentsMatchSearching()) {
				cFindReplaceDialog->Create(true, selectedContents.c_str(), _T(""), FR_DOWN | FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
			}
			else if (contentsFinder->GetIsUpWardSearching() && contentsFinder->GetIsCompletelyMatchSearching()) {
				cFindReplaceDialog->Create(true, selectedContents.c_str(), _T(""), FR_MATCHCASE | FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
			}
			else if (contentsFinder->GetIsUpWardSearching() && contentsFinder->GetIsContentsMatchSearching()) {
				cFindReplaceDialog->Create(true, selectedContents.c_str(), _T(""), FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
			}
		}
		else {//처음열어본거
			cFindReplaceDialog->Create(true, selectedContents.c_str(), _T(""), FR_DOWN | FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
		}
	}
	else {
		if (contentsFinder->GetFindWhatString() != 0) {
			if (contentsFinder->GetIsDownWardSearching() && contentsFinder->GetIsCompletelyMatchSearching()) {
				cFindReplaceDialog->Create(true, contentsFinder->GetFindWhatString()->c_str(), _T(""), FR_DOWN | FR_MATCHCASE | FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
			}
			else if (contentsFinder->GetIsDownWardSearching() && contentsFinder->GetIsContentsMatchSearching()) {
				cFindReplaceDialog->Create(true, contentsFinder->GetFindWhatString()->c_str(), _T(""), FR_DOWN | FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
			}
			else if (contentsFinder->GetIsUpWardSearching() && contentsFinder->GetIsCompletelyMatchSearching()) {
				cFindReplaceDialog->Create(true, contentsFinder->GetFindWhatString()->c_str(), _T(""), FR_MATCHCASE | FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
			}
			else if (contentsFinder->GetIsUpWardSearching() && contentsFinder->GetIsContentsMatchSearching()) {
				cFindReplaceDialog->Create(true, contentsFinder->GetFindWhatString()->c_str(), _T(""), FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
			}
		}
		else {//처음열어본거
			cFindReplaceDialog->Create(true, _T(""), _T(""), FR_DOWN | FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
		}
	}
	
	contentsFinder->SetPDlg(cFindReplaceDialog);
	contentsFinder->SetIsPdlgFindOnly(true);
	contentsFinder->GetPDlg()->SetFocus();
}