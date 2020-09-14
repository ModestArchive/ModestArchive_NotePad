//FindNextCommand.cpp

#include<afxdlgs.h>
#include"FindNextCommand.h"
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

FindNextCommand::FindNextCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm) :Command(notePadForm) {
	this->notePadFormControlWnd = notePadFormControlWnd;
	this->notePadForm = notePadForm;
}

FindNextCommand::~FindNextCommand() {

}

void FindNextCommand::Execute() {
	if (this->notePadFormControlWnd->GetContentsFinder() == 0) {//처음으로 찾기기능을 사용했을때

		this->notePadFormControlWnd->SetContentsFinder(new ContentsFinder(this->notePadFormControlWnd, this->notePadForm));
		ContentsFinder* contentsFinder = this->notePadFormControlWnd->GetContentsFinder();

		CFindReplaceDialog* cFindReplaceDialog = new CFindReplaceDialog();
		if (this->notePadForm->GetIsSelected()==true) {
			StringMaker stringMaker(this->notePadForm);
			string selectedContents = "";
			selectedContents = stringMaker.MakeStringInSelectedArea();

			cFindReplaceDialog->Create(true, selectedContents.c_str(), _T(""), FR_DOWN | FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
		}
		else {
			cFindReplaceDialog->Create(true, _T(""), _T(""), FR_DOWN | FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
		}
		
		contentsFinder->SetPDlg(cFindReplaceDialog);
		contentsFinder->SetIsPdlgFindOnly(true);
		contentsFinder->GetPDlg()->SetFocus();
	}
	else {//전에 한번이라도 찾기기능을 사용했을때
		ContentsFinder* contentsFinder = this->notePadFormControlWnd->GetContentsFinder();
		if (*contentsFinder->GetFindWhatString()=="\0") {

			CFindReplaceDialog* cFindReplaceDialog = new CFindReplaceDialog();
			if (this->notePadForm->GetIsSelected() == true) {
				StringMaker stringMaker(this->notePadForm);
				string selectedContents = "";
				selectedContents = stringMaker.MakeStringInSelectedArea();
				if (contentsFinder->GetIsCompletelyMatchSearching()) {
					cFindReplaceDialog->Create(true, selectedContents.c_str(), _T(""), FR_DOWN | FR_MATCHCASE | FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
				}
				else {
					cFindReplaceDialog->Create(true, selectedContents.c_str(), _T(""), FR_DOWN | FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
				}
			}
			else {
				if (contentsFinder->GetIsCompletelyMatchSearching()) {
					cFindReplaceDialog->Create(true, contentsFinder->GetFindWhatString()->c_str(), _T(""), FR_DOWN | FR_MATCHCASE | FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
				}
				else {
					cFindReplaceDialog->Create(true, contentsFinder->GetFindWhatString()->c_str(), _T(""), FR_DOWN | FR_NOWHOLEWORD, ((CWnd*)(this->notePadFormControlWnd)));
				}
			}
			contentsFinder->SetPDlg(cFindReplaceDialog);
			contentsFinder->SetIsPdlgFindOnly(true);
			contentsFinder->GetPDlg()->SetFocus();
		}
		else {
			ContentsFinder* contentsFinder = this->notePadFormControlWnd->GetContentsFinder();
			FindReplaceSupervisor findReplaceSupervisor(this->notePadFormControlWnd, this->notePadForm, this->notePadFormControlWnd->GetContentsFinder(), 0, 0);
			findReplaceSupervisor.GetReadyToFindNextFromMenuCommand();
			
			findReplaceSupervisor.DoSearchDownForMenuCommand();
		}
	}
}