//ContentsReplacer.cpp
#include"ContentsReplacer.h"
#include"SelectionEraseSupervisor.h"
#include"StringMaker.h"
#include"Selector.h"
#include"NotePadMementoMaker.h"
#include"NotePadRestorer.h"
#include"HistoryReconstructor.h"
#include"PasteSupervisor.h"
#include"FindReplaceSupervisor.h"
#include"Glyph.h"

ContentsReplacer::ContentsReplacer(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm) {
	this->notePadFormControlWnd = notePadFormControlWnd;
	this->notePadForm = notePadForm;
	this->replaceWhatString = 0;
}

ContentsReplacer::~ContentsReplacer() {
	if (this->replaceWhatString!=0) {
		delete this->replaceWhatString;
	}
}

void ContentsReplacer::SetReplaceWhatString(string* replaceWhatString) {
	this->replaceWhatString = replaceWhatString;
}


void ContentsReplacer::ReplaceCurrentContents() {
	FindReplaceSupervisor findReplaceSupervisor(this->notePadFormControlWnd, this->notePadForm,
												this->notePadFormControlWnd->GetContentsFinder(), 
												this->notePadFormControlWnd->GetContentsReplacer(),
												this->notePadFormControlWnd->GetContentsFinder()->GetPDlg());
	SelectionEraseSupervisor selectionEraseSupervisor(this->notePadForm);
	StringMaker stringMaker(this->notePadForm);
	string* contents = new string(stringMaker.MakeStringInSelectedArea());

	char(*buffer) = 0;
	buffer = (char*)(this->replaceWhatString->c_str());

	if (buffer[0]=='\0') {
		selectionEraseSupervisor.EraseContents(contents, true);
		this->notePadForm->SetIsSelected(false);
		if (this->notePadForm->GetSelector() != 0) {
			delete this->notePadForm->GetSelector();
		}
		Selector* selector = new Selector(this->notePadForm);
		this->notePadForm->SetSelector(selector);
	}
	else {
		selectionEraseSupervisor.EraseContents(contents, false);

		this->notePadForm->SetIsSelected(false);
		if (this->notePadForm->GetSelector() != 0) {
			delete this->notePadForm->GetSelector();
		}
		Selector* selector = new Selector(this->notePadForm);
		this->notePadForm->SetSelector(selector);

		NotePadMementoMaker notePadMementoMaker(this->notePadForm);
		ConstraintSolverMemento* constraintSolverMemento = 0;
		NotePadRestorer* notePadRestorer = this->notePadForm->GetNotePadRestorer();

		if (this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent() != this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetLength()) {
			HistoryReconstructor historyReconstructor(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory(), this->notePadForm);
			historyReconstructor.ReconstructHistory();
		}
		notePadRestorer->GetNotePadHistory()->MoveLastHistory();

		string* cloneContents = new string(*this->replaceWhatString);
		constraintSolverMemento = notePadMementoMaker.MakeMemento(true, false, -1, -1, cloneContents);
		notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);

		PasteSupervisor pasteSupervisor(this->notePadForm);
		pasteSupervisor.PasteContents(buffer);

		constraintSolverMemento = notePadMementoMaker.MakeMemento(true, false, -1, -1, cloneContents);
		notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);
	}
	findReplaceSupervisor.DeleteMatchIndexCollector();
}


void ContentsReplacer::ReplaceAllContents(bool isFirstReplace, bool isLastReplace) {
	FindReplaceSupervisor findReplaceSupervisor(this->notePadFormControlWnd, this->notePadForm,
												this->notePadFormControlWnd->GetContentsFinder(),
												this->notePadFormControlWnd->GetContentsReplacer(),
												this->notePadFormControlWnd->GetContentsFinder()->GetPDlg());
	SelectionEraseSupervisor selectionEraseSupervisor(this->notePadForm);
	StringMaker stringMaker(this->notePadForm);
	string* contents = new string(stringMaker.MakeStringInSelectedArea());

	char(*buffer) = 0;
	buffer = (char*)(this->replaceWhatString->c_str());

	if (buffer[0] == '\0') {
		selectionEraseSupervisor.EraseContentsForReplaceNoneAll(contents, isFirstReplace,isLastReplace);
		this->notePadForm->SetIsSelected(false);
		if (this->notePadForm->GetSelector() != 0) {
			delete this->notePadForm->GetSelector();
		}
		Selector* selector = new Selector(this->notePadForm);
		this->notePadForm->SetSelector(selector);
	}
	else {
		selectionEraseSupervisor.EraseContentsForReplaceAll(contents, isFirstReplace);

		this->notePadForm->SetIsSelected(false);
		if (this->notePadForm->GetSelector() != 0) {
			delete this->notePadForm->GetSelector();
		}
		Selector* selector = new Selector(this->notePadForm);
		this->notePadForm->SetSelector(selector);

		NotePadMementoMaker notePadMementoMaker(this->notePadForm);
		ConstraintSolverMemento* constraintSolverMemento = 0;
		NotePadRestorer* notePadRestorer = this->notePadForm->GetNotePadRestorer();

		if (this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent() != this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetLength()) {
			HistoryReconstructor historyReconstructor(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory(), this->notePadForm);
			historyReconstructor.ReconstructHistory();
		}
		notePadRestorer->GetNotePadHistory()->MoveLastHistory();

		string* cloneContents = new string(*this->replaceWhatString);
		constraintSolverMemento = notePadMementoMaker.MakeReplaceAllMemento(false, true,false, this->notePadForm->notePad->GetCurrent(), this->notePadForm->row->GetCurrent(), cloneContents);
		notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);

		PasteSupervisor pasteSupervisor(this->notePadForm);
		pasteSupervisor.PasteContents(buffer);

		constraintSolverMemento = notePadMementoMaker.MakeReplaceAllMemento(false, true, isLastReplace, this->notePadForm->notePad->GetCurrent(), this->notePadForm->row->GetCurrent(), cloneContents);
		notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);
	}
	findReplaceSupervisor.DeleteMatchIndexCollector();
}