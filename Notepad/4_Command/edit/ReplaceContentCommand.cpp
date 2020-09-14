//ReplaceContentCommand.cpp
#include"NotePadFormControlWnd.h"
#include"ReplaceContentCommand.h"
#include"ContentsFinder.h"
#include"MatchIndexCollector.h"
#include"FindReplaceSupervisor.h"
#include"StringMaker.h"

ReplaceContentCommand::ReplaceContentCommand(NotePadFormControlWnd* notePadFormControlWnd,NotePadForm* notePadForm) :Command(notePadForm){
	this->notePadFormControlWnd = notePadFormControlWnd;
	this->notePadForm = notePadForm;
}


ReplaceContentCommand::~ReplaceContentCommand() {

}


void ReplaceContentCommand::Execute() {
	FindReplaceSupervisor findReplaceSupervisor(this->notePadFormControlWnd,this->notePadForm ,
												this->notePadFormControlWnd->GetContentsFinder(),
												this->notePadFormControlWnd->GetContentsReplacer(),0 );
	
	findReplaceSupervisor.GetReadyToCreateFindAndReplacePdlg();

	ContentsFinder* contentsFinder = this->notePadFormControlWnd->GetContentsFinder();
	ContentsReplacer* contentsReplacer = this->notePadFormControlWnd->GetContentsReplacer();

	CFindReplaceDialog* cFindReplaceDialog = new CFindReplaceDialog();
	if (this->notePadForm->GetIsSelected()==true) {
		StringMaker stringMaker(this->notePadForm);
		string selectedContents = "";
		selectedContents = stringMaker.MakeStringInSelectedArea();
		if (contentsReplacer->GetReplaceWhatString()!=0) {
			if (contentsFinder->GetIsCompletelyMatchSearching()) {
				cFindReplaceDialog->Create(FALSE, selectedContents.c_str(), contentsReplacer->GetReplaceWhatString()->c_str(), FR_MATCHCASE | FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
			}
			else {
				cFindReplaceDialog->Create(FALSE, selectedContents.c_str(), contentsReplacer->GetReplaceWhatString()->c_str(), FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
			}
		}
		else {
			if (contentsFinder->GetIsCompletelyMatchSearching()) {
				cFindReplaceDialog->Create(FALSE, selectedContents.c_str(), _T(""), FR_MATCHCASE | FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
			}
			else {
				cFindReplaceDialog->Create(FALSE, selectedContents.c_str(), _T(""), FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
			}
		}
	}
	else {
		if (contentsFinder->GetFindWhatString() != 0) {
			if (contentsReplacer->GetReplaceWhatString() != 0) {
				if (contentsFinder->GetIsCompletelyMatchSearching()) {
					cFindReplaceDialog->Create(FALSE, contentsFinder->GetFindWhatString()->c_str(), contentsReplacer->GetReplaceWhatString()->c_str(), FR_MATCHCASE | FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
				}
				else {
					cFindReplaceDialog->Create(FALSE, contentsFinder->GetFindWhatString()->c_str(), contentsReplacer->GetReplaceWhatString()->c_str(), FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
				}
			}
			else {
				if (contentsFinder->GetIsCompletelyMatchSearching()) {
					cFindReplaceDialog->Create(FALSE, contentsFinder->GetFindWhatString()->c_str(), _T(""), FR_MATCHCASE | FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
				}
				else {
					cFindReplaceDialog->Create(FALSE, contentsFinder->GetFindWhatString()->c_str(), _T(""), FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
				}

			}
		}
		else {
			if (contentsReplacer->GetReplaceWhatString() != 0) {
				cFindReplaceDialog->Create(FALSE, _T(""), contentsReplacer->GetReplaceWhatString()->c_str(), FR_DOWN | FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
			}
			else {
			cFindReplaceDialog->Create(FALSE, _T(""), _T(""), FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
			}
		}
	}
	contentsFinder->SetPDlg(cFindReplaceDialog);
	contentsFinder->SetIsPdlgFindOnly(false);
	contentsFinder->GetPDlg()->SetFocus();
}
