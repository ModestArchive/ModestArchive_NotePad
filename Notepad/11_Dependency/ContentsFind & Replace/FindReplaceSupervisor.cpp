//FindReplaceSupervisor.cpp

#include"FindReplaceSupervisor.h"
#include"MatchIndexCollector.h"
#include"NotePadModifier.h"
#include"NotePadMetric.h"
#include"CoordinateCalculator.h"
#include"NotePadIndicator.h"
#include"Selector.h"
#include"MatchIndex.h"
#include"SelectModifier.h"

FindReplaceSupervisor::FindReplaceSupervisor(NotePadFormControlWnd* notePadFormControlWnd,NotePadForm* notePadForm,ContentsFinder* contentsFinder, ContentsReplacer* contentsReplacer, CFindReplaceDialog* pDlg) {
	this->notePadFormControlWnd = notePadFormControlWnd;
	this->notePadForm = notePadForm;
	this->contentsFinder = contentsFinder;
	this->contentsReplacer = contentsReplacer;
	this->pDlg = pDlg;
}


FindReplaceSupervisor::~FindReplaceSupervisor() {

}


void FindReplaceSupervisor::GetReadyToCreateFindPdlg() {
	if (contentsFinder == 0) {
		contentsFinder = new ContentsFinder(this->notePadFormControlWnd, this->notePadForm);
		this->notePadFormControlWnd->SetContentsFinder(contentsFinder);
	}
}


void FindReplaceSupervisor::GetReadyToCreateFindAndReplacePdlg() {
	if (contentsFinder == 0) {
		contentsFinder = new ContentsFinder(this->notePadFormControlWnd, this->notePadForm);
		this->notePadFormControlWnd->SetContentsFinder(contentsFinder);
	}
	if (contentsReplacer == 0) {
		contentsReplacer = new ContentsReplacer(this->notePadFormControlWnd, this->notePadForm);
		this->notePadFormControlWnd->SetContentsReplacer(contentsReplacer);
	}
}


void FindReplaceSupervisor::GetReadyToFindNextFromPdlg() {
	if (this->notePadForm->GetIsSelected() == true) {
		this->notePadForm->SetIsSelected(false);
		if (this->notePadForm->GetIsSelected() != 0) {
			delete this->notePadForm->GetSelector();
		}
		Selector* selector = new Selector(this->notePadForm);
		this->notePadForm->SetSelector(selector);
	}
	NotePadModifier notePadModifier(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);
	CoordinateCalculator coordinateCalculator(this->notePadForm);
	NotePadIndicator notePadIndicator(this->notePadForm);

	Long rowCount = notePadModifier.CountRowFromStartToCurrent();
	Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
	notePadModifier.Combine();
	CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCount);
	notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);

	if (this->contentsFinder->GetFindWhatString() == 0) {
		this->contentsFinder->SetFindWhatString(new string((LPSTR)(LPCTSTR)(this->pDlg->GetFindString())));
	}
	else {
		if (*this->contentsFinder->GetFindWhatString() != (LPSTR)(LPCTSTR)(this->pDlg->GetFindString())||
			 (contentsFinder->GetIsCompletelyMatchSearching()!=this->pDlg->MatchCase()|| contentsFinder->GetIsContentsMatchSearching()!=!(this->pDlg->MatchCase())||
			  contentsFinder->GetIsDownWardSearching()!=this->pDlg->SearchDown()||contentsFinder->GetIsUpWardSearching()!=!(this->pDlg->SearchDown()))) {

			delete this->contentsFinder->GetFindWhatString();
			this->contentsFinder->SetFindWhatString(0);
			this->contentsFinder->SetFindWhatString(new string((LPSTR)(LPCTSTR)(this->pDlg->GetFindString())));

			if (this->contentsFinder->GetMatchIndexCollector() != 0) {
				delete this->contentsFinder->GetMatchIndexCollector();
				MatchIndexCollector* matchIndexCollector = new MatchIndexCollector();
				contentsFinder->SetMatchIndexCollector(matchIndexCollector);
			}
			if (this->contentsFinder->GetStandardPoint() != 0) {
				delete this->contentsFinder->GetStandardPoint();
				this->contentsFinder->SetStandardPoint(0);
			}
			contentsFinder->SetIsDownWardSearching(false);
			contentsFinder->SetIsUpWardSearching(false);
			contentsFinder->SetIsCompletelyMatchSearching(false);
			contentsFinder->SetIsContentsMatchSearching(false);
		}
	}
}


void FindReplaceSupervisor::GetReadyToFindPreviousFromPdlg() {
	Long previousSelectedStartRowIndex = -1;
	Long previousSelectedStartColumnIndex = -1;
	if (this->notePadForm->GetIsSelected() == true) {
		if (this->notePadFormControlWnd->GetContentsFinder()->GetMatchIndexCollector()->GetLength() > 0) {
			previousSelectedStartRowIndex = this->notePadForm->GetSelector()->GetOriginRowIndex();
			previousSelectedStartColumnIndex = this->notePadForm->GetSelector()->GetOriginColumnIndex();
		}
		this->notePadForm->SetIsSelected(false);
		if (this->notePadForm->GetIsSelected() != 0) {
			delete this->notePadForm->GetSelector();
		}
		Selector* selector = new Selector(this->notePadForm);
		this->notePadForm->SetSelector(selector);
	}

	NotePadModifier notePadModifier(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);
	CoordinateCalculator coordinateCalculator(this->notePadForm);
	NotePadIndicator notePadIndicator(this->notePadForm);

	if (previousSelectedStartRowIndex != -1 && previousSelectedStartColumnIndex != -1) {
		notePadIndicator.GoToCoordinate(previousSelectedStartRowIndex, previousSelectedStartColumnIndex);
	}

	Long rowCount = notePadModifier.CountRowFromStartToCurrent();
	Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
	notePadModifier.Combine();
	CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCount);
	notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);

	if (this->contentsFinder->GetFindWhatString() == 0) {
		this->contentsFinder->SetFindWhatString(new string((LPSTR)(LPCTSTR)(this->pDlg->GetFindString())));
	}
	else {
		if (*this->contentsFinder->GetFindWhatString() != (LPSTR)(LPCTSTR)(this->pDlg->GetFindString()) ||
			(contentsFinder->GetIsCompletelyMatchSearching() != this->pDlg->MatchCase() || contentsFinder->GetIsContentsMatchSearching() != !(this->pDlg->MatchCase()) ||
				contentsFinder->GetIsDownWardSearching() != this->pDlg->SearchDown() || contentsFinder->GetIsUpWardSearching() != !(this->pDlg->SearchDown()))) {

			delete this->contentsFinder->GetFindWhatString();
			this->contentsFinder->SetFindWhatString(0);
			this->contentsFinder->SetFindWhatString(new string((LPSTR)(LPCTSTR)(this->pDlg->GetFindString())));

			if (this->contentsFinder->GetMatchIndexCollector() != 0) {
				delete this->contentsFinder->GetMatchIndexCollector();
				MatchIndexCollector* matchIndexCollector = new MatchIndexCollector();
				contentsFinder->SetMatchIndexCollector(matchIndexCollector);
			}
			if (this->contentsFinder->GetStandardPoint() != 0) {
				delete this->contentsFinder->GetStandardPoint();
				this->contentsFinder->SetStandardPoint(0);
			}
			contentsFinder->SetIsDownWardSearching(false);
			contentsFinder->SetIsUpWardSearching(false);
			contentsFinder->SetIsCompletelyMatchSearching(false);
			contentsFinder->SetIsContentsMatchSearching(false);
		}
	}
}


void FindReplaceSupervisor::GetReadyToFindNextFromMenuCommand() {
	if (this->notePadForm->GetIsSelected() == true) {
		this->notePadForm->SetIsSelected(false);
		if (this->notePadForm->GetIsSelected() != 0) {
			delete this->notePadForm->GetSelector();
		}
		Selector* selector = new Selector(this->notePadForm);
		this->notePadForm->SetSelector(selector);
	}

	NotePadModifier notePadModifier(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);
	CoordinateCalculator coordinateCalculator(this->notePadForm);
	NotePadIndicator notePadIndicator(this->notePadForm);

	Long rowCount = notePadModifier.CountRowFromStartToCurrent();
	Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
	notePadModifier.Combine();
	CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCount);
	notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);
	
	if (this->contentsFinder->GetIsUpWardSearching() == true) {

		if (this->contentsFinder->GetMatchIndexCollector() != 0) {
			delete this->contentsFinder->GetMatchIndexCollector();
			MatchIndexCollector* matchIndexCollector = new MatchIndexCollector();
			contentsFinder->SetMatchIndexCollector(matchIndexCollector);
		}
		if (this->contentsFinder->GetStandardPoint() != 0) {
			delete this->contentsFinder->GetStandardPoint();
			this->contentsFinder->SetStandardPoint(0);
		}
		// FromPdlg에서는 플레그값을 아싸리 초기화해주어도 되는 이유가 
		// FromPdlg가 꺼질때도 플레그값이 contentsFinder에 저장이되고 다시 검색할떄도 
		// contentsFinder의 현재 플래그값과 Pdlg값과 비교해서 전부초기화 하든가 초기화하지않고 현재 일치값들을 참고해서 표현해주는데
		// 지금은 Pdlg가 없는데 전에 이전찾기를 했다고 플래그 값을 초기화를 해주면 검색을 정해주는 플래그값도 초기화가 되는것이니
		// 검색을 지정해줄수가 없어서 검색자체를 하지못하게된다. 그러므로 matchIndexCollector만 초기화해주면 matchindexLength가 0이 되므로
		// 알아서 플래그값에 따라 정해진 검색함수의 알고리즘에의해(Length가 0이면 찾는다) 다시 찾아주게된다.  
	}
}


void FindReplaceSupervisor::GetReadyToFindPreviousFromMenuCommand() {
	Long previousSelectedStartRowIndex = -1;
	Long previousSelectedStartColumnIndex = -1;
	if (this->notePadForm->GetIsSelected() == true ) {
		if (this->notePadFormControlWnd->GetContentsFinder()->GetMatchIndexCollector()->GetLength() > 0) {
			previousSelectedStartRowIndex = this->notePadForm->GetSelector()->GetOriginRowIndex();
			previousSelectedStartColumnIndex = this->notePadForm->GetSelector()->GetOriginColumnIndex();
		}
		this->notePadForm->SetIsSelected(false);
		if (this->notePadForm->GetIsSelected() != 0) {
			delete this->notePadForm->GetSelector();
		}
		Selector* selector = new Selector(this->notePadForm);
		this->notePadForm->SetSelector(selector);
	}
	
	NotePadModifier notePadModifier(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);
	CoordinateCalculator coordinateCalculator(this->notePadForm);
	NotePadIndicator notePadIndicator(this->notePadForm);

	if (previousSelectedStartRowIndex!=-1 && previousSelectedStartColumnIndex!=-1) {
		notePadIndicator.GoToCoordinate(previousSelectedStartRowIndex,previousSelectedStartColumnIndex);
	}
	Long rowCount = notePadModifier.CountRowFromStartToCurrent();
	Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
	notePadModifier.Combine();
	CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCount);
	notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);

	if (this->contentsFinder->GetIsDownWardSearching()==true) {

		if (this->contentsFinder->GetMatchIndexCollector() != 0) {
			delete this->contentsFinder->GetMatchIndexCollector();
			MatchIndexCollector* matchIndexCollector = new MatchIndexCollector();
			contentsFinder->SetMatchIndexCollector(matchIndexCollector);
		}
		if (this->contentsFinder->GetStandardPoint() != 0) {
			delete this->contentsFinder->GetStandardPoint();
			this->contentsFinder->SetStandardPoint(0);
		}
	}
}


MatchIndex FindReplaceSupervisor::GetReadyToReplaceCurrentFromPdlg() {
	
	NotePadModifier notePadModifier(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);
	CoordinateCalculator coordinateCalculator(this->notePadForm);
	NotePadIndicator notePadIndicator(this->notePadForm);
	MatchIndex alreadyMatchedIndex(-1, -1, -1, -1);
	

	if (this->contentsFinder->GetMatchIndexCollector()->GetLength()>0 && this->notePadForm->GetIsSelected()==true) {
	
		SelectModifier selectModifier(this->notePadForm->GetSelector());
		Long rowCountInFirstToSelectedAreaStartPoint = selectModifier.CountRowInFirstToSelectedAreaStartPoint();
		Long rowCountInSelectedArea = selectModifier.CountRowInSelectedArea();
		bool isFirstLineInSelectedAreaDummyRow = selectModifier.isFirstLineInSelectedAreaDummyRow(this->notePadForm->GetSelector()->GetOriginRowIndex());
		if (isFirstLineInSelectedAreaDummyRow == true) {
			rowCountInSelectedArea++;
		}
		Long rowCount = notePadModifier.CountRowFromStartToCurrent();
		Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
		notePadModifier.Combine();
		CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCount);
		notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);

		selectModifier.ChangeRightDownwardSelectedAreaStartPointAfterAction(rowCountInFirstToSelectedAreaStartPoint);
		selectModifier.ChangeRightDownwardSelectedAreaEndPointAfterAction(rowCountInSelectedArea);
		Selector* selector = this->notePadForm->GetSelector();
		MatchIndex matchIndex(selector->GetOriginRowIndex(),selector->GetOriginColumnIndex(),selector->GetEndRowIndex(),selector->GetEndColumnIndex());
		alreadyMatchedIndex = matchIndex;
		notePadIndicator.GoToCoordinate(selector->GetOriginRowIndex(), selector->GetOriginColumnIndex());
	}
	else {
		Long rowCount = notePadModifier.CountRowFromStartToCurrent();
		Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
		notePadModifier.Combine();
		CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCount);
		notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);
	}
	if (this->contentsFinder->GetFindWhatString() == 0) {
		this->contentsFinder->SetFindWhatString(new string((LPSTR)(LPCTSTR)(this->pDlg->GetFindString())));
	}
	else {

			delete this->contentsFinder->GetFindWhatString();
			this->contentsFinder->SetFindWhatString(0);
			this->contentsFinder->SetFindWhatString(new string((LPSTR)(LPCTSTR)(this->pDlg->GetFindString())));
			if (this->contentsFinder->GetMatchIndexCollector() != 0) {
				delete this->contentsFinder->GetMatchIndexCollector();
				MatchIndexCollector* matchIndexCollector = new MatchIndexCollector();
				contentsFinder->SetMatchIndexCollector(matchIndexCollector);
			}
			if (this->contentsFinder->GetStandardPoint() != 0) {
				delete this->contentsFinder->GetStandardPoint();
				this->contentsFinder->SetStandardPoint(0);
			}
			contentsFinder->SetIsDownWardSearching(false);
			contentsFinder->SetIsUpWardSearching(false);
			contentsFinder->SetIsCompletelyMatchSearching(false);
			contentsFinder->SetIsContentsMatchSearching(false);

			if (this->notePadForm->GetIsSelected() == true) {
				this->notePadForm->SetIsSelected(false);
				if (this->notePadForm->GetIsSelected() != 0) {
					delete this->notePadForm->GetSelector();
				}
				Selector* selector = new Selector(this->notePadForm);
				this->notePadForm->SetSelector(selector);
			}
		
	}
	if (this->contentsReplacer->GetReplaceWhatString() == 0) {
		this->contentsReplacer->SetReplaceWhatString(new string((LPSTR)(LPCTSTR)(this->pDlg->GetReplaceString())));
	}
	else {
		if (*this->contentsReplacer->GetReplaceWhatString() != (LPSTR)(LPCTSTR)(this->pDlg->GetReplaceString())) {
			delete this->contentsReplacer->GetReplaceWhatString();
			this->contentsReplacer->SetReplaceWhatString(0);
			this->contentsReplacer->SetReplaceWhatString(new string((LPSTR)(LPCTSTR)(this->pDlg->GetReplaceString())));
		}
	}
	return alreadyMatchedIndex;
}


void FindReplaceSupervisor::GetReadyToReplaceAllFromPdlg() {
	if (this->notePadForm->GetIsSelected() == true) {
		this->notePadForm->SetIsSelected(false);
		if (this->notePadForm->GetIsSelected() != 0) {
			delete this->notePadForm->GetSelector();
		}
		Selector* selector = new Selector(this->notePadForm);
		this->notePadForm->SetSelector(selector);
	}
	NotePadModifier notePadModifier(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);
	CoordinateCalculator coordinateCalculator(this->notePadForm);
	NotePadIndicator notePadIndicator(this->notePadForm);

	notePadModifier.Combine();

	if (this->contentsFinder->GetFindWhatString()!=0) {
		delete this->contentsFinder->GetFindWhatString();
		this->contentsFinder->SetFindWhatString(0);
	}
	this->contentsFinder->SetFindWhatString(new string((LPSTR)(LPCTSTR)(this->pDlg->GetFindString())));

	if (contentsFinder->GetMatchIndexCollector() != 0) {
		delete contentsFinder->GetMatchIndexCollector();
		MatchIndexCollector* matchIndexCollector = new MatchIndexCollector();
		contentsFinder->SetMatchIndexCollector(matchIndexCollector);
	}
	if (contentsFinder->GetStandardPoint() != 0) {
		delete contentsFinder->GetStandardPoint();
		contentsFinder->SetStandardPoint(0);
	}
	contentsFinder->SetIsDownWardSearching(false);
	contentsFinder->SetIsUpWardSearching(false);
	contentsFinder->SetIsCompletelyMatchSearching(false);
	contentsFinder->SetIsContentsMatchSearching(false);

	if (this->contentsReplacer->GetReplaceWhatString()!=0) {
		delete this->contentsReplacer->GetReplaceWhatString();
		this->contentsReplacer->SetReplaceWhatString(0);
	}
	this->contentsReplacer->SetReplaceWhatString(new string((LPSTR)(LPCTSTR)(this->pDlg->GetReplaceString())));
}


void FindReplaceSupervisor::DoMatchCaseSearchDown() {
	string tab("\t");
	string line("\r\n");
	if (this->contentsFinder->GetFindWhatString()->find(tab) != -1 ||this->contentsFinder->GetFindWhatString()->find(line) != -1 ) {
		this->contentsFinder->FindSearchDownCompletelyMatchCaseForTabAndRow();
	}
	else {
		this->contentsFinder->FindSearchDownCompletelyMatchCase();
	}
}


void FindReplaceSupervisor::DoMatchCaseSearchUp() {
	string tab("\t");
	string line("\r\n");
	if (this->contentsFinder->GetFindWhatString()->find(tab) != -1 || this->contentsFinder->GetFindWhatString()->find(line) != -1) {
		this->contentsFinder->FindSearchUpCompletelyMatchCaseForTabAndRow();
	}
	else {
		this->contentsFinder->FindSearchUpCompletelyMatchCase();
	}
}


void FindReplaceSupervisor::DoNoMatchCaseSearchDown() {
	string tab("\t");
	string line("\r\n");
	if (this->contentsFinder->GetFindWhatString()->find(tab) != -1 || this->contentsFinder->GetFindWhatString()->find(line) != -1) {
		this->contentsFinder->FindSearchDownContentsMatchCaseForTabAndRow();
	}
	else {
		this->contentsFinder->FindSearchDownContentsMatchCase();
	}
}

void FindReplaceSupervisor::DoNoMatchCaseSearchUp() {
	string tab("\t");
	string line("\r\n");
	if (this->contentsFinder->GetFindWhatString()->find(tab) != -1 || this->contentsFinder->GetFindWhatString()->find(line) != -1) {
		this->contentsFinder->FindSearchUpContentsMatchCaseForTabAndRow();
	}
	else {
		this->contentsFinder->FindSearchUpContentsMatchCase();
	}
}


void  FindReplaceSupervisor::DoReplaceCurrentMatchCase(MatchIndex alreadyMatchedIndex) {
	string tab("\t");
	string line("\r\n");
	if (this->contentsFinder->GetFindWhatString()->find(tab) != -1 || this->contentsFinder->GetFindWhatString()->find(line) != -1) {
		if (alreadyMatchedIndex.GetStartRowIndex() != -1) {
			this->contentsFinder->FindSearchDownCompletelyMatchCaseForTabAndRow();
			if (this->contentsFinder->GetMatchIndexCollector()->GetLength() > 0) {
				if (alreadyMatchedIndex == *this->contentsFinder->GetMatchIndexCollector()->GetAt(contentsFinder->GetMatchIndexCollector()->GetCurrent())) {
					this->contentsReplacer->ReplaceCurrentContents();
					this->notePadForm->Invalidate();
					this->contentsFinder->FindSearchDownCompletelyMatchCaseForTabAndRow();
				}
			}
		}
		else {
			this->contentsFinder->FindSearchDownCompletelyMatchCaseForTabAndRow();
		}
	}
	else {
		if (alreadyMatchedIndex.GetStartRowIndex() != -1) {
			this->contentsFinder->FindSearchDownCompletelyMatchCase();
			if (this->contentsFinder->GetMatchIndexCollector()->GetLength() > 0) {
				if (alreadyMatchedIndex == *this->contentsFinder->GetMatchIndexCollector()->GetAt(contentsFinder->GetMatchIndexCollector()->GetCurrent())) {
					this->contentsReplacer->ReplaceCurrentContents();
					this->notePadForm->Invalidate();
					this->contentsFinder->FindSearchDownCompletelyMatchCase();
				}
			}
		}
		else {
			this->contentsFinder->FindSearchDownCompletelyMatchCase();
		}
	}
}


void  FindReplaceSupervisor::DoReplaceCurrentNoMatchCase(MatchIndex alreadyMatchedIndex) {
	string tab("\t");
	string line("\r\n");
	if (this->contentsFinder->GetFindWhatString()->find(tab) != -1 || this->contentsFinder->GetFindWhatString()->find(line) != -1) {
		if (alreadyMatchedIndex.GetStartRowIndex() != -1) {
			this->contentsFinder->FindSearchDownContentsMatchCaseForTabAndRow();
			if (this->contentsFinder->GetMatchIndexCollector()->GetLength() > 0) {
				if (alreadyMatchedIndex == *this->contentsFinder->GetMatchIndexCollector()->GetAt(contentsFinder->GetMatchIndexCollector()->GetCurrent())) {
					this->contentsReplacer->ReplaceCurrentContents();
					this->notePadForm->Invalidate();
					this->contentsFinder->FindSearchDownContentsMatchCaseForTabAndRow();
				}
			}
		}
		else {
			this->contentsFinder->FindSearchDownContentsMatchCaseForTabAndRow();
		}
	}
	else {
		if (alreadyMatchedIndex.GetStartRowIndex() != -1) {
			this->contentsFinder->FindSearchDownContentsMatchCase();
			if (this->contentsFinder->GetMatchIndexCollector()->GetLength() > 0) {
				if (alreadyMatchedIndex == *this->contentsFinder->GetMatchIndexCollector()->GetAt(contentsFinder->GetMatchIndexCollector()->GetCurrent())) {
					this->contentsReplacer->ReplaceCurrentContents();
					this->notePadForm->Invalidate();
					this->contentsFinder->FindSearchDownContentsMatchCase();
				}
			}
		}
		else {
			this->contentsFinder->FindSearchDownContentsMatchCase();
		}
	}
}


void FindReplaceSupervisor::DoReplaceAllMatchCase() {
	NotePadIndicator notePadIndicator(this->notePadForm);
	Long countOfReplace = 0;
	bool isFirstReplaceAttempt = true;

	string tab("\t");
	string line("\r\n");
	bool isFindWhatStringIncludeTabAndRow = false;
	if (this->contentsFinder->GetFindWhatString()->find(tab) != -1 || this->contentsFinder->GetFindWhatString()->find(line) != -1) {
		isFindWhatStringIncludeTabAndRow = true;
	}

	if (isFindWhatStringIncludeTabAndRow==true) {
		this->contentsFinder->FindSearchDownCompletelyMatchCaseForReplaceAllForTabAndRow(isFirstReplaceAttempt, countOfReplace);
	}
	else {
		this->contentsFinder->FindSearchDownCompletelyMatchCaseForReplaceAll(isFirstReplaceAttempt, countOfReplace);
	}
	
	while (this->contentsFinder->GetMatchIndexCollector()->GetLength() > 0) {
		MatchIndexCollector* matchIndexCollector = this->contentsFinder->GetMatchIndexCollector();

		MatchIndex* matchIndex = matchIndexCollector->GetAt(matchIndexCollector->GetCurrent());
		notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

		Selector* selector = this->notePadForm->GetSelector();
		selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
		selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
		selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
		selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());
		
		bool isLastReplaceAttempt = false;
		if (matchIndexCollector->GetLength() == 1) {
			isLastReplaceAttempt = true;
		}
		this->contentsReplacer->ReplaceAllContents(isFirstReplaceAttempt,isLastReplaceAttempt);
		countOfReplace++;
		this->notePadForm->Invalidate();//현재 합친상태에서 인벨리데이트를하니 자동개행이 해제된게 뒤에 보이다가 알림창끄면 없어짐.
		isFirstReplaceAttempt = false;
		if (isFindWhatStringIncludeTabAndRow == true) {
			this->contentsFinder->FindSearchDownCompletelyMatchCaseForReplaceAllForTabAndRow(isFirstReplaceAttempt, countOfReplace);
		}
		else {
			this->contentsFinder->FindSearchDownCompletelyMatchCaseForReplaceAll(isFirstReplaceAttempt, countOfReplace);
		}
	}
	notePadIndicator.GoToCoordinate(0, 0);
}


void FindReplaceSupervisor::DoReplaceAllNoMatchCase() {
	NotePadIndicator notePadIndicator(this->notePadForm);
	Long countOfReplace = 0;
	bool isFirstReplaceAttempt = true;

	string tab("\t");
	string line("\r\n");
	bool isFindWhatStringIncludeTabAndRow = false;
	if (this->contentsFinder->GetFindWhatString()->find(tab) != -1 || this->contentsFinder->GetFindWhatString()->find(line) != -1) {
		isFindWhatStringIncludeTabAndRow = true;
	}

	if (isFindWhatStringIncludeTabAndRow==true) {
		this->contentsFinder->FindSearchDownContentsMatchCaseForReplaceAllForTabAndRow(isFirstReplaceAttempt, countOfReplace);
	}
	else {
		this->contentsFinder->FindSearchDownContentsMatchCaseForReplaceAll(isFirstReplaceAttempt, countOfReplace);
	}

	while (this->contentsFinder->GetMatchIndexCollector()->GetLength() > 0) {
		countOfReplace++;
		MatchIndexCollector* matchIndexCollector = this->contentsFinder->GetMatchIndexCollector();

		MatchIndex* matchIndex = matchIndexCollector->GetAt(matchIndexCollector->GetCurrent());
		notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

		Selector* selector = this->notePadForm->GetSelector();
		selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
		selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
		selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
		selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

		bool isLastReplaceAttempt = false;
		if (matchIndexCollector->GetLength()==1) {
			isLastReplaceAttempt = true;
		}
		this->contentsReplacer->ReplaceAllContents(isFirstReplaceAttempt, isLastReplaceAttempt);
		this->notePadForm->Invalidate();
		isFirstReplaceAttempt = false;

		if (isFindWhatStringIncludeTabAndRow == true) {
			this->contentsFinder->FindSearchDownContentsMatchCaseForReplaceAllForTabAndRow(isFirstReplaceAttempt, countOfReplace);
		}
		else {
			this->contentsFinder->FindSearchDownContentsMatchCaseForReplaceAll(isFirstReplaceAttempt, countOfReplace);
		}
	}
	notePadIndicator.GoToCoordinate(0,0);
}


void FindReplaceSupervisor::DoSearchDownForMenuCommand() {
	string tab("\t");
	string line("\r\n");

	if (this->contentsFinder->GetFindWhatString()->find(tab) != -1 || this->contentsFinder->GetFindWhatString()->find(line) != -1) {
		if (contentsFinder->GetIsCompletelyMatchSearching() == true) {
			this->contentsFinder->FindSearchDownCompletelyMatchCaseForMenuCommandForTabAndRow();
		}
		else if (contentsFinder->GetIsContentsMatchSearching() == true) {
			this->contentsFinder->FindSearchDownContentsMatchCaseForMenuCommandForTabAndRow();
		}
	}
	else {
		if (contentsFinder->GetIsCompletelyMatchSearching() == true) {
			this->contentsFinder->FindSearchDownCompletelyMatchCaseForMenuCommand();
		}
		else if (contentsFinder->GetIsContentsMatchSearching() == true) {
			this->contentsFinder->FindSearchDownContentsMatchCaseForMenuCommand();
		}
	}
}


void FindReplaceSupervisor::DoSearchUpForMenuCommand() {
	string tab("\t");
	string line("\r\n");

	if (this->contentsFinder->GetFindWhatString()->find(tab) != -1 || this->contentsFinder->GetFindWhatString()->find(line) != -1) {
		if (contentsFinder->GetIsCompletelyMatchSearching() == true) {
			this->contentsFinder->FindSearchUpCompletelyMatchCaseForMenuCommandForTabAndRow();
		}
		else if (contentsFinder->GetIsContentsMatchSearching() == true) {
			this->contentsFinder->FindSearchUpContentsMatchCaseForMenuCommandForTabAndRow();
		}
	}
	else {
		if (contentsFinder->GetIsCompletelyMatchSearching() == true) {
			this->contentsFinder->FindSearchUpCompletelyMatchCaseForMenuCommand();
		}
		else if (contentsFinder->GetIsContentsMatchSearching() == true) {
			this->contentsFinder->FindSearchUpContentsMatchCaseForMenuCommand();
		}
	}
}


void FindReplaceSupervisor::SaveInformationAsPdlgTerminating() {
	
	if (this->contentsFinder->GetFindWhatString() != 0) {
		delete this->contentsFinder->GetFindWhatString();
		this->contentsFinder->SetFindWhatString(0);
	}
	this->contentsFinder->SetFindWhatString(new string((LPSTR)(LPCTSTR)(this->pDlg->GetFindString())));

	if (contentsFinder->GetIsPdlgFindOnly() == false) {
		if (this->contentsReplacer->GetReplaceWhatString() != 0) {
			delete this->contentsReplacer->GetReplaceWhatString();
			this->contentsReplacer->SetReplaceWhatString(0);
		}
		this->contentsReplacer->SetReplaceWhatString(new string((LPSTR)(LPCTSTR)(this->pDlg->GetReplaceString())));
	}
	this->contentsFinder->SetIsCompletelyMatchSearching(this->pDlg->MatchCase());
	this->contentsFinder->SetIsContentsMatchSearching(!(this->pDlg->MatchCase()));
	this->contentsFinder->SetIsDownWardSearching(this->pDlg->SearchDown());
	this->contentsFinder->SetIsUpWardSearching(!(this->pDlg->SearchDown()));

	contentsFinder->SetIsPdlgFindOnly(false);//찾기/바꾸기 대화상자를 없애주는 이 시점에서는 false가 바꾸기 대화상자를 의미하기보단 아무것도 없다라는 의미로 보자.
											 //있을때는 무조건 바꾸기 대화상자로 밖에 해석할수없다.
	this->contentsFinder->SetPDlg(0);
}


void FindReplaceSupervisor::DeleteMatchIndexCollector() {

	if (contentsFinder->GetMatchIndexCollector()->GetLength()>0) {
		delete contentsFinder->GetMatchIndexCollector();
		MatchIndexCollector* matchIndexCollector = new MatchIndexCollector();
		contentsFinder->SetMatchIndexCollector(matchIndexCollector);
	}
	if (contentsFinder->GetStandardPoint() != 0) {
		delete contentsFinder->GetStandardPoint();
		contentsFinder->SetStandardPoint(0);
	}
	if (this->notePadForm->GetIsSelected()==true) {
		delete this->notePadForm->GetSelector();
		this->notePadForm->SetSelector(0);
		this->notePadForm->SetSelector(new Selector(this->notePadForm));
		this->notePadForm->SetIsSelected(false);
	}
}

void FindReplaceSupervisor::DeleteOnlyMatchIndexCollector() {
	if (contentsFinder->GetMatchIndexCollector()->GetLength() > 0) {
		delete contentsFinder->GetMatchIndexCollector();
		MatchIndexCollector* matchIndexCollector = new MatchIndexCollector();
		contentsFinder->SetMatchIndexCollector(matchIndexCollector);
	}
	if (contentsFinder->GetStandardPoint() != 0) {
		delete contentsFinder->GetStandardPoint();
		contentsFinder->SetStandardPoint(0);
	}
}