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
		// FromPdlg������ �÷��װ��� �ƽθ� �ʱ�ȭ���־ �Ǵ� ������ 
		// FromPdlg�� �������� �÷��װ��� contentsFinder�� �����̵ǰ� �ٽ� �˻��ҋ��� 
		// contentsFinder�� ���� �÷��װ��� Pdlg���� ���ؼ� �����ʱ�ȭ �ϵ簡 �ʱ�ȭ�����ʰ� ���� ��ġ������ �����ؼ� ǥ�����ִµ�
		// ������ Pdlg�� ���µ� ���� ����ã�⸦ �ߴٰ� �÷��� ���� �ʱ�ȭ�� ���ָ� �˻��� �����ִ� �÷��װ��� �ʱ�ȭ�� �Ǵ°��̴�
		// �˻��� �������ټ��� ��� �˻���ü�� �������ϰԵȴ�. �׷��Ƿ� matchIndexCollector�� �ʱ�ȭ���ָ� matchindexLength�� 0�� �ǹǷ�
		// �˾Ƽ� �÷��װ��� ���� ������ �˻��Լ��� �˰�������(Length�� 0�̸� ã�´�) �ٽ� ã���ְԵȴ�.  
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
		this->notePadForm->Invalidate();//���� ��ģ���¿��� �κ�������Ʈ���ϴ� �ڵ������� �����Ȱ� �ڿ� ���̴ٰ� �˸�â���� ������.
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

	contentsFinder->SetIsPdlgFindOnly(false);//ã��/�ٲٱ� ��ȭ���ڸ� �����ִ� �� ���������� false�� �ٲٱ� ��ȭ���ڸ� �ǹ��ϱ⺸�� �ƹ��͵� ���ٶ�� �ǹ̷� ����.
											 //�������� ������ �ٲٱ� ��ȭ���ڷ� �ۿ� �ؼ��Ҽ�����.
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