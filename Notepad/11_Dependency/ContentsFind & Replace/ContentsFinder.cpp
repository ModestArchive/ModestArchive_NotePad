//ContentsFinder.cpp

#include"ContentsFinder.h"
#include"MatchIndexCollector.h"
#include"Glyph.h"
#include"NotePadForm.h"
#include"Row.h"
#include"SingleByteCharacter.h"
#include"MatchIndex.h"
#include"Selector.h"
#include"SelectModifier.h"
#include"NotePadFormControlWnd.h"
#include"NotePadIndicator.h"
#include"NotePadMetric.h"
#include"StringMaker.h"
#include"NotePad.h"


ContentsFinder::ContentsFinder(NotePadFormControlWnd* notePadFormControlWnd,NotePadForm* notePadForm) {
	this->notePadFormControlWnd = notePadFormControlWnd;
	this->notePadForm = notePadForm;
	this->matchIndexCollector = new MatchIndexCollector;
	this->findWhatString = 0;
	this->standardPoint = 0;
	this->isDownWardSearching = false;
	this->isUpWardSearching = false;
	this->isCompletelyMatchSearching = false;
	this->isContentsMatchSearching = false;
	
	this->pDlg = 0;
	this->isPdlgFindOnly = false;
}


ContentsFinder::~ContentsFinder() {
	if (this->matchIndexCollector!=0) {
		delete this->matchIndexCollector;
	}
	if (this->findWhatString!=0) {
		delete this->findWhatString;
	}
	if (this->standardPoint!=0) {
		delete this->standardPoint;
	}
}


void ContentsFinder::SetFindWhatString(string* findWhatString) {
	this->findWhatString = findWhatString;
}
void ContentsFinder::SetStandardPoint(CPoint* standardPoint) {
	this->standardPoint = standardPoint;
}
void ContentsFinder::SetMatchIndexCollector(MatchIndexCollector* matchIndexCollector) {
	this->matchIndexCollector = matchIndexCollector;
}
void ContentsFinder::SetIsDownWardSearching(bool isDownWardSearching) {
	this->isDownWardSearching = isDownWardSearching;
}
void ContentsFinder::SetIsUpWardSearching(bool isUpWardSearching) {
	this->isUpWardSearching = isUpWardSearching;
}
void ContentsFinder::SetIsCompletelyMatchSearching(bool isCompletelyMatchSearching) {
	this->isCompletelyMatchSearching = isCompletelyMatchSearching;
}
void ContentsFinder::SetIsContentsMatchSearching(bool isContentsMatchSearching) {
	this->isContentsMatchSearching = isContentsMatchSearching;
}
void ContentsFinder::SetPDlg(CFindReplaceDialog* pDlg) {
	this->pDlg = pDlg;
}
void ContentsFinder::SetIsPdlgFindOnly(bool isPdlgFindOnly) {
	this->isPdlgFindOnly = isPdlgFindOnly;
}


void ContentsFinder::FindSearchDownCompletelyMatchCase() { //일단 다 찾고 인덱스를 검색하다가 현재캐럿위치를 기준보다 크거나같고 제일가까운지점에 있는 단어를 표시한다. //한글은 똑같지만, 영어같은경우 대소문자 구분해서 검색한다음 일치하는 위치들을 찾는다.
	
	if (this->matchIndexCollector->GetLength() == 0) {//새롭게 대화상자를 열어서 탐색한 내역이 아무것도 없어서 일치하는내용을 새롭게 탐색할때
		int CompareContentsCompletelyMatch(void* one, void* other);
		Long calculateRealStringLength(string *findWhatString);
		
		this->standardPoint = new CPoint(this->notePadForm->row->GetCurrent(),this->notePadForm->notePad->GetCurrent());
		Long(*indexes) = 0;
		Long count = 0;
		string firstChar("");
		if (!(this->findWhatString->at(0)& 0x80)) {
			firstChar += this->GetFindWhatString()->at(0);
		}
		else {
			firstChar += this->GetFindWhatString()->at(0);
			firstChar += this->GetFindWhatString()->at(1);
		}
		Long realStringLength = calculateRealStringLength(this->findWhatString);
		Long i = this->notePadForm->notePad->GetCurrent();
		while (i < this->notePadForm->notePad->GetLength()) {
			Glyph* row = this->notePadForm->notePad->GetAt(i);
			((Row*)(row))->SearchMatchCharDuplicate(&firstChar, &indexes, &count, CompareContentsCompletelyMatch);
			Long j = 0;
			if (i == this->notePadForm->notePad->GetCurrent()) {
				while (indexes[j]<this->notePadForm->row->GetCurrent()) {
					j++;
				}
			}
			while (j < count) {
				if (indexes[j] + realStringLength <= row->GetLength()) {
					Long k = 0;
					string excerptContents("");
					while (k < realStringLength) {
						excerptContents += row->GetAt(indexes[j] + k)->GetContents();
						k++;
					}
					bool isMatched = false;
					if (excerptContents.compare(*this->findWhatString) == 0) {
						isMatched = true;
						this->matchIndexCollector->AddMatchIndex(new MatchIndex(i, indexes[j], i, indexes[j] +realStringLength));
					}
					k = 0;
					if (isMatched==true) {//찾았을때 검색위치재설정
						while (j + k<count && indexes[j] + realStringLength>indexes[j + k]) {
							k++;
						}
						if (j + k < count) {
							j += k;
						}
						else {
							j = count;
						}
					}
					else {//못찾았을때 검색위치재설정
						j++;
					}
				}
				else {
					j = count;
				}
			}
			if (indexes != 0) {
				delete indexes;
				indexes = 0;
			}
			count = 0;
			i++;
		}
		if (indexes!=0) {
			delete indexes;
			indexes = 0;
		}
		if (this->matchIndexCollector->GetLength()>0) {
			this->notePadForm->SetIsFindingContents(true);

			this->isCompletelyMatchSearching = true;
			this->isDownWardSearching = true;
			this->isContentsMatchSearching = false;
			this->isUpWardSearching = false;

			this->matchIndexCollector->MoveFirstMatchIndex();
			
			MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
			NotePadIndicator notePadIndicator(this->notePadForm);
			notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

			Selector* selector = this->notePadForm->GetSelector();
			selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
			selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
			selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
			selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

			SelectModifier selectModifier(selector);
			selectModifier.SetAbsoluteSelectionInformation();
			this->notePadForm->GetSelector()->HighLightMatchContents();
			this->notePadForm->SetIsSelected(true);
		}
		else {
			CString information;
			this->notePadForm->Notify();
			this->notePadForm->Invalidate();
			if (this->pDlg->FindNext()) {
				information.Format(_T("\"%s\"을(를) 찾을 수 없습니다."), (char*)(this->findWhatString->c_str()));
			}
			else if (this->pDlg->ReplaceCurrent()) {
				information.Format(_T("\"%s\"을(를) 찾을 수 없어 바꿔줄수없습니다."), (char*)(this->findWhatString->c_str()));
			}
			this->notePadFormControlWnd->MessageBox(information, _T("메모장"), MB_ICONINFORMATION);
			this->pDlg->SetFocus();
		}
	}
	else {//대화상자를 닫지않고 '찾기'컨트롤을 연속으로 눌러서 이미 탐색한 내용을 앞,뒤로 참고하며 다음 일치한곳을 표시해줄때 
		this->notePadForm->SetIsFindingContents(true);
		bool isReturnedToFirst = false;
		this->matchIndexCollector->MoveNextMatchIndex();
		if (this->matchIndexCollector->GetCurrent()>=this->matchIndexCollector->GetLength()) {
			this->matchIndexCollector->MoveFirstMatchIndex();
			isReturnedToFirst = true;
		}
		MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
		NotePadIndicator notePadIndicator(this->notePadForm);
		notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

		Selector* selector = this->notePadForm->GetSelector();
		selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
		selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
		selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
		selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

		SelectModifier selectModifier(selector);
		selectModifier.SetAbsoluteSelectionInformation();
		this->notePadForm->GetSelector()->HighLightMatchContents();
		this->notePadForm->SetIsSelected(true);
		if (isReturnedToFirst==true) {
			this->notePadFormControlWnd->MessageBox("더이상 일치하는 내용이 없습니다. 처음 찾았던 내용으로 이동합니다.", _T("메모장"), MB_ICONINFORMATION);
		}
	}
}


void ContentsFinder::FindSearchUpCompletelyMatchCase() { //일단 다 찾고 인덱스를 검색하다가 현재캐럿위치를 기준보다 작거나같고 제일가까운지점에 있는 단어를 표시한다.  //한글은 똑같지만, 영어같은경우 대소문자 구분해서 검색한다음 일치하는 위치들을 찾는다.
	
	if (this->matchIndexCollector->GetLength() == 0) {//새롭게 대화상자를 열어서 탐색한 내역이 아무것도 없어서 일치하는내용을 새롭게 탐색할때
		int CompareContentsCompletelyMatch(void* one, void* other);
		Long calculateRealStringLength(string * findWhatString);

		this->standardPoint = new CPoint(this->notePadForm->row->GetCurrent(), this->notePadForm->notePad->GetCurrent());
		Long(*indexes) = 0;
		Long count = 0;
		string firstChar("");
		if (!(this->findWhatString->at(0) & 0x80)) {
			firstChar += this->GetFindWhatString()->at(0);
		}
		else {
			firstChar += this->GetFindWhatString()->at(0);
			firstChar += this->GetFindWhatString()->at(1);
		}
		Long realStringLength = calculateRealStringLength(this->findWhatString);
		Long i = 0;
		while (i <= this->notePadForm->notePad->GetCurrent()) {
			Glyph* row = this->notePadForm->notePad->GetAt(i);
			((Row*)(row))->SearchMatchCharDuplicate(&firstChar, &indexes, &count, CompareContentsCompletelyMatch);
			Long j = 0;
			if (i == this->notePadForm->notePad->GetCurrent()) {
				Long k = 0;
				while (k<count && indexes[k]+realStringLength <= this->notePadForm->row->GetCurrent()) {
					k++;
				}
				count -= (count-k);
			}
			while (j < count) {
				if (indexes[j] + realStringLength <= row->GetLength()) {
					Long k = 0;
					string excerptContents("");
					while (k < realStringLength) {
						excerptContents += row->GetAt(indexes[j] + k)->GetContents();
						k++;
					}
					bool isMatched = false;
					if (excerptContents.compare(*this->findWhatString) == 0) {
						isMatched = true;
						this->matchIndexCollector->AddMatchIndex(new MatchIndex(i, indexes[j], i, indexes[j] + realStringLength));
					}
					k = 0;
					if (isMatched == true) {//찾았을때 검색위치재설정
						while (j + k<count && indexes[j] + realStringLength>indexes[j + k]) {
							k++;
						}
						if (j + k < count) {
							j += k;
						}
						else {
							j = count;
						}
					}
					else {//못찾았을때 검색위치재설정
						j++;
					}
				}
				else {
					j = count;
				}
			}
			if (indexes != 0) {
				delete indexes;
				indexes = 0;
			}
			count = 0;
			i++;
		}
		if (indexes != 0) {
			delete indexes;
			indexes = 0;
		}
		if (this->matchIndexCollector->GetLength() > 0) {
			this->notePadForm->SetIsFindingContents(true);

			this->isUpWardSearching = true;
			this->isCompletelyMatchSearching = true;
			this->isDownWardSearching = false;
			this->isContentsMatchSearching = false;
		
			this->matchIndexCollector->MovePreviousMatchIndex();
			
			MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
			NotePadIndicator notePadIndicator(this->notePadForm);
			notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

			Selector* selector = this->notePadForm->GetSelector();
			selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
			selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
			selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
			selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

			SelectModifier selectModifier(selector);
			selectModifier.SetAbsoluteSelectionInformation();
			this->notePadForm->GetSelector()->HighLightMatchContents();
			this->notePadForm->SetIsSelected(true);
		}
		else {
			CString information;
			this->notePadForm->Notify();
			this->notePadForm->Invalidate();
			information.Format(_T("\"%s\"을(를) 찾을 수 없습니다."), (char*)(this->findWhatString->c_str()));
			this->notePadFormControlWnd->MessageBox(information, _T("메모장"), MB_ICONINFORMATION);
			this->pDlg->SetFocus();
		}
	}
	else {//대화상자를 닫지않고 '찾기'컨트롤을 연속으로 눌러서 이미 탐색한 내용을 앞,뒤로 참고하며 다음 일치한곳을 표시해줄때 
		this->notePadForm->SetIsFindingContents(true);
		bool isReturnedToFirst = false;
		this->matchIndexCollector->MovePreviousMatchIndex();
		if (this->matchIndexCollector->GetCurrent() < 0) {
			this->matchIndexCollector->MoveLastMatchIndex();
			this->matchIndexCollector->MovePreviousMatchIndex();
			isReturnedToFirst = true;
		}
		MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
		NotePadIndicator notePadIndicator(this->notePadForm);
		notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

		Selector* selector = this->notePadForm->GetSelector();
		selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
		selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
		selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
		selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

		SelectModifier selectModifier(selector);
		selectModifier.SetAbsoluteSelectionInformation();
		this->notePadForm->GetSelector()->HighLightMatchContents();
		this->notePadForm->SetIsSelected(true);
		
		if (isReturnedToFirst == true) {
			this->notePadFormControlWnd->MessageBox("더이상 일치하는 내용이 없습니다. 처음 찾았던 내용으로 이동합니다.", _T("메모장"), MB_ICONINFORMATION);
		}
	}
}


void ContentsFinder::FindSearchDownContentsMatchCase() { //일단 다 찾고 인덱스를 검색하다가 현재캐럿위치를 기준보다 크거나같고, 제일가까운지점에 있는 단어를 표시한다.
								     //한글은 똑같지만, 영어같은경우 대소문자 구분하지않고 내용을 검색한다음 일치하는 위치들을 찾는다. 
	if (this->matchIndexCollector->GetLength() == 0) {//새롭게 대화상자를 열어서 탐색한 내역이 아무것도 없어서 일치하는내용을 새롭게 탐색할때
		int CompareContentsMatch(void* one, void* other);
		int CompareWholeContentsMatch(string one, string other);
		Long calculateRealStringLength(string * findWhatString);
		this->standardPoint = new CPoint(this->notePadForm->row->GetCurrent(), this->notePadForm->notePad->GetCurrent());

		Long(*indexes) = 0;
		Long count = 0;
		string firstChar("");
		if (!(this->findWhatString->at(0) & 0x80)) {
			firstChar += this->GetFindWhatString()->at(0);
		}
		else {
			firstChar += this->GetFindWhatString()->at(0);
			firstChar += this->GetFindWhatString()->at(1);
		}
		Long realStringLength = calculateRealStringLength(this->findWhatString);
		Long i = this->notePadForm->notePad->GetCurrent();
		while (i < this->notePadForm->notePad->GetLength()) {
			Glyph* row = this->notePadForm->notePad->GetAt(i);
			((Row*)(row))->SearchMatchCharDuplicate(&firstChar, &indexes, &count, CompareContentsMatch);
			Long j = 0;
			if (i == this->notePadForm->notePad->GetCurrent()) {
				while (indexes[j] < this->notePadForm->row->GetCurrent()) {
					j++;
				}
			}
			while (j < count) {
				if (indexes[j] + realStringLength <= row->GetLength()) {
					Long k = 0;
					string excerptContents("");
					while (k < realStringLength) {
						excerptContents += row->GetAt(indexes[j] + k)->GetContents();
						k++;
					}
					bool isMatched = false;
					if (CompareWholeContentsMatch(*this->findWhatString, excerptContents) == 0) {
						isMatched = true;
						this->matchIndexCollector->AddMatchIndex(new MatchIndex(i, indexes[j], i, indexes[j] + realStringLength));
					}
					k = 0;
					if (isMatched == true) {//찾았을때 검색위치재설정
						while (j + k<count && indexes[j] + realStringLength>indexes[j + k]) {
							k++;
						}
						if (j + k < count) {
							j += k;
						}
						else {
							j = count;
						}
					}
					else {//못찾았을때 검색위치재설정
						j++;
					}
				}
				else {
					j = count;
				}
			}
			if (indexes != 0) {
				delete indexes;
				indexes = 0;
			}
			count = 0;
			i++;
		}
		if (indexes != 0) {
			delete indexes;
			indexes = 0;
		}
		if (this->matchIndexCollector->GetLength() > 0) {
			this->notePadForm->SetIsFindingContents(true);

			this->isDownWardSearching = true;
			this->isContentsMatchSearching = true;
			this->isUpWardSearching = false;
			this->isCompletelyMatchSearching = false;

			this->matchIndexCollector->MoveFirstMatchIndex();
			MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
			NotePadIndicator notePadIndicator(this->notePadForm);
			notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

			Selector* selector = this->notePadForm->GetSelector();
			selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
			selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
			selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
			selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

			SelectModifier selectModifier(selector);
			selectModifier.SetAbsoluteSelectionInformation();
			this->notePadForm->GetSelector()->HighLightMatchContents();
			this->notePadForm->SetIsSelected(true);
		}
		else {
			CString information;
			this->notePadForm->Notify();
			this->notePadForm->Invalidate();
			if (this->pDlg->FindNext()) {
				information.Format(_T("\"%s\"을(를) 찾을 수 없습니다."), (char*)(this->findWhatString->c_str()));
			}
			else if (this->pDlg->ReplaceCurrent()) {
				information.Format(_T("\"%s\"을(를) 찾을 수 없어서 바꿔줄 수 없습니다."), (char*)(this->findWhatString->c_str()));
			}
			this->notePadFormControlWnd->MessageBox(information, _T("메모장"), MB_ICONINFORMATION);
			
			this->pDlg->SetFocus();
		}
	}
	else {//대화상자를 닫지않고 '찾기'컨트롤을 연속으로 눌러서 이미 탐색한 내용을 앞,뒤로 참고하며 다음 일치한곳을 표시해줄때 
		this->notePadForm->SetIsFindingContents(true);

		bool isReturnedToFirst = false;
		this->matchIndexCollector->MoveNextMatchIndex();
		if (this->matchIndexCollector->GetCurrent() >= this->matchIndexCollector->GetLength()) {
			this->matchIndexCollector->MoveFirstMatchIndex();
			isReturnedToFirst = true;
		}
		MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
		NotePadIndicator notePadIndicator(this->notePadForm);
		notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

		Selector* selector = this->notePadForm->GetSelector();
		selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
		selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
		selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
		selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

		SelectModifier selectModifier(selector);
		selectModifier.SetAbsoluteSelectionInformation();
		this->notePadForm->GetSelector()->HighLightMatchContents();
		this->notePadForm->SetIsSelected(true);
		 
		if (isReturnedToFirst == true) {
			this->notePadFormControlWnd->MessageBox("더이상 일치하는 내용이 없습니다. 처음 찾았던 내용으로 이동합니다.", _T("메모장"), MB_ICONINFORMATION);
		}
	}
}


void ContentsFinder::FindSearchUpContentsMatchCase() { //일단 다 찾고 인덱스를 검색하다가 현재캐럿위치를 기준보다 작거나같고 제일가까운지점에 있는 단어를 표시한다.
							 	  //한글은 똑같지만, 영어같은경우 대소문자 구분하지않고 내용을 검색한다음 일치하는 위치들을 찾는다. 
	if (this->matchIndexCollector->GetLength() == 0) {//새롭게 대화상자를 열어서 탐색한 내역이 아무것도 없어서 일치하는내용을 새롭게 탐색할때
		int CompareContentsMatch(void* one, void* other);
		int CompareWholeContentsMatch(string one, string other);
		Long calculateRealStringLength(string * findWhatString);

		this->standardPoint = new CPoint(this->notePadForm->row->GetCurrent(), this->notePadForm->notePad->GetCurrent());
		Long(*indexes) = 0;
		Long count = 0;
		string firstChar("");
		if (!(this->findWhatString->at(0) & 0x80)) {
			firstChar += this->GetFindWhatString()->at(0);
		}
		else {
			firstChar += this->GetFindWhatString()->at(0);
			firstChar += this->GetFindWhatString()->at(1);
		}
		Long realStringLength = calculateRealStringLength(this->findWhatString);
		Long i = 0;
		while (i <= this->notePadForm->notePad->GetCurrent()) {
			Glyph* row = this->notePadForm->notePad->GetAt(i);
			((Row*)(row))->SearchMatchCharDuplicate(&firstChar, &indexes, &count, CompareContentsMatch);
			Long j = 0;
			if (i == this->notePadForm->notePad->GetCurrent()) {
				Long k = 0;
				while (k < count && indexes[k] + realStringLength <= this->notePadForm->row->GetCurrent()) {
					k++;
				}
				count -= (count - k);
			}
			while (j < count) {
				if (indexes[j] + realStringLength <= row->GetLength()) {
					Long k = 0;
					string excerptContents("");
					while (k < realStringLength) {
						excerptContents += row->GetAt(indexes[j] + k)->GetContents();
						k++;
					}
					bool isMatched = false;
					if (CompareWholeContentsMatch(*this->findWhatString, excerptContents) == 0) {
						isMatched = true;
						this->matchIndexCollector->AddMatchIndex(new MatchIndex(i, indexes[j], i, indexes[j] + realStringLength));
					}
					k = 0;
					if (isMatched == true) {//찾았을때 검색위치재설정
						while (j + k<count && indexes[j] + realStringLength>indexes[j + k]) {
							k++;
						}
						if (j + k < count) {
							j += k;
						}
						else {
							j = count;
						}
					}
					else {//못찾았을때 검색위치재설정
						j++;
					}
				}
				else {
					j = count;
				}
			}
			if (indexes != 0) {
				delete indexes;
				indexes = 0;
			}
			count = 0;
			i++;
		}
		if (indexes != 0) {
			delete indexes;
			indexes = 0;
		}
		if (this->matchIndexCollector->GetLength() > 0) {
			this->notePadForm->SetIsFindingContents(true);

			this->isUpWardSearching = true;
			this->isContentsMatchSearching = true;
			this->isDownWardSearching = false;
			this->isCompletelyMatchSearching = false;

			this->matchIndexCollector->MovePreviousMatchIndex();
			MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
			NotePadIndicator notePadIndicator(this->notePadForm);
			notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

			Selector* selector = this->notePadForm->GetSelector();
			selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
			selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
			selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
			selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

			SelectModifier selectModifier(selector);
			selectModifier.SetAbsoluteSelectionInformation();
			this->notePadForm->GetSelector()->HighLightMatchContents();
			this->notePadForm->SetIsSelected(true);
		}
		else {
			CString information;
			this->notePadForm->Notify();
			this->notePadForm->Invalidate();
			information.Format(_T("\"%s\"을(를) 찾을 수 없습니다."), (char*)(this->findWhatString->c_str()));
			this->notePadFormControlWnd->MessageBox(information, _T("메모장"), MB_ICONINFORMATION);
			this->pDlg->SetFocus();
		}
	}
	else {//이미 탐색한 내용을 앞,뒤로 참고하며 다음 일치한곳을 표시해줄때 
		this->notePadForm->SetIsFindingContents(true);

		bool isReturnedToFirst = false;
		this->matchIndexCollector->MovePreviousMatchIndex();
		if (this->matchIndexCollector->GetCurrent() < 0) {
			this->matchIndexCollector->MoveLastMatchIndex();
			this->matchIndexCollector->MovePreviousMatchIndex();
			isReturnedToFirst = true;
		}
		MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
		NotePadIndicator notePadIndicator(this->notePadForm);
		notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

		Selector* selector = this->notePadForm->GetSelector();
		selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
		selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
		selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
		selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

		SelectModifier selectModifier(selector);
		selectModifier.SetAbsoluteSelectionInformation();
		this->notePadForm->GetSelector()->HighLightMatchContents();
		this->notePadForm->SetIsSelected(true);
		
		if (isReturnedToFirst == true) {
			this->notePadFormControlWnd->MessageBox("더이상 일치하는 내용이 없습니다. 처음 찾았던 내용으로 이동합니다.", _T("메모장"), MB_ICONINFORMATION);
		}
	}
}


void ContentsFinder::FindSearchDownCompletelyMatchCaseForTabAndRow() {
	if (this->matchIndexCollector->GetLength() == 0){
		string notePadCotents = ((NotePad*)(this->notePadForm->notePad))->GetContentsForString();
		string tab("\t");
		string row("\r\n");
		Long notePadFormRowIndex= this->notePadForm->notePad->GetCurrent();
		Long countedRowIndex = 0;
		Long realStartIndex = 0;

		while (notePadCotents.find(row, realStartIndex)!=-1 && countedRowIndex!=notePadFormRowIndex) {
			realStartIndex = notePadCotents.find(row, realStartIndex) + 1;
			countedRowIndex++;
		}
		if (realStartIndex>0) {
			realStartIndex--;
		}
		NotePadMetric notePadMetric(this->notePadForm);
		Long tabCount = notePadMetric.GetHowManyTabInToCurrentColumnInCurrentRow();
		if (realStartIndex==0) {
			realStartIndex =this->notePadForm->row->GetCurrent() - (tabCount * 7);
		}
		else {
			realStartIndex = realStartIndex + 2 + this->notePadForm->row->GetCurrent() - (tabCount * 7);
		}

		while (notePadCotents.find(*this->findWhatString, realStartIndex) != -1) {
			Long startFindedIndex = notePadCotents.find(*this->findWhatString, realStartIndex);
			Long rowIndex = 0;
			Long startRowIndex = 0;
			Long startColumnIndex = 0;
			
			while (notePadCotents.find(row, rowIndex) != -1 && startFindedIndex > notePadCotents.find(row, rowIndex)) {
				rowIndex = notePadCotents.find(row, rowIndex) + 1;
				startRowIndex++;
			}
			if (startRowIndex>0) {
				rowIndex--;
			}

			Long tabCount = 0;
			Long tabIndex = rowIndex;
			while (notePadCotents.find(tab, tabIndex) != -1 && startFindedIndex > notePadCotents.find(tab, tabIndex)) {
				tabIndex = notePadCotents.find(tab, tabIndex) + 1;
				tabCount++;
			}
			if (rowIndex>0) {
				startColumnIndex = startFindedIndex - rowIndex - 2 + (tabCount * 7);
			}
			else {
				startColumnIndex= startFindedIndex+ (tabCount * 7);
			}
			
			Long endFindedIndex = startFindedIndex + this->findWhatString->length();
			rowIndex = 0;
			Long endRowIndex = 0;
			Long endColumnIndex = 0;
			
			while (notePadCotents.find(row,rowIndex) != -1 && endFindedIndex > notePadCotents.find(row, rowIndex)) {
				rowIndex = notePadCotents.find(row, rowIndex) + 1;
				endRowIndex++;
			}
			if (endRowIndex>0) {
				rowIndex--;
			}

			tabCount = 0;
			tabIndex = rowIndex;
			while (notePadCotents.find(tab, tabIndex) != -1 && endFindedIndex > notePadCotents.find(tab, tabIndex)) {
				tabIndex = notePadCotents.find(tab, tabIndex) + 1;
				tabCount++;
			}
			if (rowIndex>0) {
				endColumnIndex = endFindedIndex - rowIndex - 2 + (tabCount * 7);
			}
			else {
				endColumnIndex = endFindedIndex + (tabCount * 7);
			}
			this->matchIndexCollector->AddMatchIndex(new MatchIndex(startRowIndex, startColumnIndex, endRowIndex, endColumnIndex));
			realStartIndex=endFindedIndex ;
		}
		if (this->matchIndexCollector->GetLength() > 0) {
			this->notePadForm->SetIsFindingContents(true);

			this->isCompletelyMatchSearching = true;
			this->isDownWardSearching = true;
			this->isContentsMatchSearching = false;
			this->isUpWardSearching = false;

			this->matchIndexCollector->MoveFirstMatchIndex();

			MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
			NotePadIndicator notePadIndicator(this->notePadForm);
			notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

			Selector* selector = this->notePadForm->GetSelector();
			selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
			selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
			selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
			selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

			SelectModifier selectModifier(selector);
			selectModifier.SetAbsoluteSelectionInformation();
			this->notePadForm->GetSelector()->HighLightMatchContents();
			this->notePadForm->SetIsSelected(true);
		}
		else {
			CString information;
			this->notePadForm->Notify();
			this->notePadForm->Invalidate();
			if (this->pDlg->FindNext()) {
				information.Format(_T("\"%s\"을(를) 찾을 수 없습니다."), (char*)(this->findWhatString->c_str()));
			}
			else if (this->pDlg->ReplaceCurrent()) {
				information.Format(_T("\"%s\"을(를) 찾을 수 없어 바꿔줄수없습니다."), (char*)(this->findWhatString->c_str()));
			}
			this->notePadFormControlWnd->MessageBox(information, _T("메모장"), MB_ICONINFORMATION);
			this->pDlg->SetFocus();
		}
	}
	else {//대화상자를 닫지않고 '찾기'컨트롤을 연속으로 눌러서 이미 탐색한 내용을 앞,뒤로 참고하며 다음 일치한곳을 표시해줄때 
		this->notePadForm->SetIsFindingContents(true);
		bool isReturnedToFirst = false;
		this->matchIndexCollector->MoveNextMatchIndex();
		if (this->matchIndexCollector->GetCurrent() >= this->matchIndexCollector->GetLength()) {
			this->matchIndexCollector->MoveFirstMatchIndex();
			isReturnedToFirst = true;
		}
		MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
		NotePadIndicator notePadIndicator(this->notePadForm);
		notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

		Selector* selector = this->notePadForm->GetSelector();
		selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
		selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
		selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
		selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

		SelectModifier selectModifier(selector);
		selectModifier.SetAbsoluteSelectionInformation();
		this->notePadForm->GetSelector()->HighLightMatchContents();
		this->notePadForm->SetIsSelected(true);
		if (isReturnedToFirst == true) {
			this->notePadFormControlWnd->MessageBox("더이상 일치하는 내용이 없습니다. 처음 찾았던 내용으로 이동합니다.", _T("메모장"), MB_ICONINFORMATION);
		}
	}
}

void ContentsFinder::FindSearchUpCompletelyMatchCaseForTabAndRow() {
	if (this->matchIndexCollector->GetLength() == 0) {
		string notePadCotents = ((NotePad*)(this->notePadForm->notePad))->GetContentsForString();
		string tab("\t");
		string row("\r\n");
		Long notePadFormRowIndex = this->notePadForm->notePad->GetCurrent();
		Long countedRowIndex = 0;
		Long breakIndex = 0;

		while (notePadCotents.find(row, breakIndex) != -1 && countedRowIndex != notePadFormRowIndex) {
			breakIndex = notePadCotents.find(row, breakIndex) + 1;
			countedRowIndex++;
		}
		if (breakIndex> 0) {
			breakIndex--;
		}
		NotePadMetric notePadMetric(this->notePadForm);
		Long tabCount = notePadMetric.GetHowManyTabInToCurrentColumnInCurrentRow();
		if (breakIndex== 0) {
			breakIndex = this->notePadForm->row->GetCurrent() - (tabCount * 7);
		}
		else {
			breakIndex= breakIndex+ 2 + this->notePadForm->row->GetCurrent() - (tabCount * 7);
		}
		bool isStopTiming = false;
		Long i = 0;
		while (i < breakIndex && notePadCotents.find(*this->findWhatString, i) != -1) {
			Long startFindedIndex = notePadCotents.find(*this->findWhatString, i);
			Long rowIndex = 0;
			Long startRowIndex = 0;
			Long startColumnIndex = 0;

			while (notePadCotents.find(row, rowIndex) != -1 && startFindedIndex > notePadCotents.find(row, rowIndex)) {
				rowIndex = notePadCotents.find(row, rowIndex) + 1;
				startRowIndex++;
			}
			if (startRowIndex > 0) {
				rowIndex--;
			}

			Long tabCount = 0;
			Long tabIndex = rowIndex;
			while (notePadCotents.find(tab, tabIndex) != -1 && startFindedIndex > notePadCotents.find(tab, tabIndex)) {
				tabIndex = notePadCotents.find(tab, tabIndex) + 1;
				tabCount++;
			}
			if (rowIndex > 0) {
				startColumnIndex = startFindedIndex - rowIndex - 2 + (tabCount * 7);
			}
			else {
				startColumnIndex = startFindedIndex + (tabCount * 7);
			}

			Long endFindedIndex = startFindedIndex + this->findWhatString->length();
			rowIndex = 0;
			Long endRowIndex = 0;
			Long endColumnIndex = 0;

			while (notePadCotents.find(row, rowIndex) != -1 && endFindedIndex > notePadCotents.find(row, rowIndex)) {
				rowIndex = notePadCotents.find(row, rowIndex) + 1;
				endRowIndex++;
			}
			if (endRowIndex > 0) {
				rowIndex--;
			}

			tabCount = 0;
			tabIndex = rowIndex;
			while (notePadCotents.find(tab, tabIndex) != -1 && endFindedIndex > notePadCotents.find(tab, tabIndex)) {
				tabIndex = notePadCotents.find(tab, tabIndex) + 1;
				tabCount++;
			}
			if (rowIndex > 0) {
				endColumnIndex = endFindedIndex - rowIndex - 2 + (tabCount * 7);
			}
			else {
				endColumnIndex = endFindedIndex + (tabCount * 7);
			}
			i = endFindedIndex;
			if (i<=breakIndex) {
				this->matchIndexCollector->AddMatchIndex(new MatchIndex(startRowIndex, startColumnIndex, endRowIndex, endColumnIndex));
			}
			else {
				isStopTiming = true;
			}
		}
		if (this->matchIndexCollector->GetLength() > 0) {
			this->notePadForm->SetIsFindingContents(true);

			this->isUpWardSearching = true;
			this->isCompletelyMatchSearching = true;
			this->isDownWardSearching = false;
			this->isContentsMatchSearching = false;

			this->matchIndexCollector->MovePreviousMatchIndex();

			MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
			NotePadIndicator notePadIndicator(this->notePadForm);
			notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

			Selector* selector = this->notePadForm->GetSelector();
			selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
			selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
			selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
			selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

			SelectModifier selectModifier(selector);
			selectModifier.SetAbsoluteSelectionInformation();
			this->notePadForm->GetSelector()->HighLightMatchContents();
			this->notePadForm->SetIsSelected(true);
		}
		else {
			CString information;
			this->notePadForm->Notify();
			this->notePadForm->Invalidate();
			information.Format(_T("\"%s\"을(를) 찾을 수 없습니다."), (char*)(this->findWhatString->c_str()));
			this->notePadFormControlWnd->MessageBox(information, _T("메모장"), MB_ICONINFORMATION);
			this->pDlg->SetFocus();
		}
	}
	else {//대화상자를 닫지않고 '찾기'컨트롤을 연속으로 눌러서 이미 탐색한 내용을 앞,뒤로 참고하며 다음 일치한곳을 표시해줄때 
		this->notePadForm->SetIsFindingContents(true);
		bool isReturnedToFirst = false;
		this->matchIndexCollector->MovePreviousMatchIndex();
		if (this->matchIndexCollector->GetCurrent() < 0) {
			this->matchIndexCollector->MoveLastMatchIndex();
			this->matchIndexCollector->MovePreviousMatchIndex();
			isReturnedToFirst = true;
		}
		MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
		NotePadIndicator notePadIndicator(this->notePadForm);
		notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

		Selector* selector = this->notePadForm->GetSelector();
		selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
		selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
		selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
		selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

		SelectModifier selectModifier(selector);
		selectModifier.SetAbsoluteSelectionInformation();
		this->notePadForm->GetSelector()->HighLightMatchContents();
		this->notePadForm->SetIsSelected(true);

		if (isReturnedToFirst == true) {
			this->notePadFormControlWnd->MessageBox("더이상 일치하는 내용이 없습니다. 처음 찾았던 내용으로 이동합니다.", _T("메모장"), MB_ICONINFORMATION);
		}
	}
}

void ContentsFinder::FindSearchDownContentsMatchCaseForTabAndRow() {
	if (this->matchIndexCollector->GetLength() == 0) {
		StringMaker stringMaker(this->notePadForm);
		string transferedFindWhatString = stringMaker.MakeNoCapitalStringForFindNoMatchCase(*this->findWhatString);
		string transferedNotePadContents = stringMaker.MakeNoCapitalStringForFindNoMatchCase(((NotePad*)(this->notePadForm->notePad))->GetContentsForString());
		
		string tab("\t");
		string row("\r\n");

		Long notePadFormRowIndex = this->notePadForm->notePad->GetCurrent();
		Long countedRowIndex = 0;
		Long realStartIndex = 0;

		while (transferedNotePadContents.find(row, realStartIndex) != -1 && countedRowIndex != notePadFormRowIndex) {
			realStartIndex = transferedNotePadContents.find(row, realStartIndex) + 1;
			countedRowIndex++;
		}
		if (realStartIndex > 0) {
			realStartIndex--;
		}
		NotePadMetric notePadMetric(this->notePadForm);
		Long tabCount = notePadMetric.GetHowManyTabInToCurrentColumnInCurrentRow();
		if (realStartIndex == 0) {
			realStartIndex = this->notePadForm->row->GetCurrent() - (tabCount * 7);
		}
		else {
			realStartIndex = realStartIndex + 2 + this->notePadForm->row->GetCurrent() - (tabCount * 7);
		}

		while (transferedNotePadContents.find(transferedFindWhatString, realStartIndex) != -1) {
			Long startFindedIndex = transferedNotePadContents.find(transferedFindWhatString, realStartIndex);
			Long rowIndex = 0;
			Long startRowIndex = 0;
			Long startColumnIndex = 0;

			while (transferedNotePadContents.find(row, rowIndex) != -1 && startFindedIndex > transferedNotePadContents.find(row, rowIndex)) {
				rowIndex = transferedNotePadContents.find(row, rowIndex) + 1;
				startRowIndex++;
			}
			if (startRowIndex > 0) {
				rowIndex--;
			}

			Long tabCount = 0;
			Long tabIndex = rowIndex;
			while (transferedNotePadContents.find(tab, tabIndex) != -1 && startFindedIndex > transferedNotePadContents.find(tab, tabIndex)) {
				tabIndex = transferedNotePadContents.find(tab, tabIndex) + 1;
				tabCount++;
			}
			if (rowIndex > 0) {
				startColumnIndex = startFindedIndex - rowIndex - 2 + (tabCount * 7);
			}
			else {
				startColumnIndex = startFindedIndex + (tabCount * 7);
			}

			Long endFindedIndex = startFindedIndex + this->findWhatString->length();
			rowIndex = 0;
			Long endRowIndex = 0;
			Long endColumnIndex = 0;

			while (transferedNotePadContents.find(row, rowIndex) != -1 && endFindedIndex > transferedNotePadContents.find(row, rowIndex)) {
				rowIndex = transferedNotePadContents.find(row, rowIndex) + 1;
				endRowIndex++;
			}
			if (endRowIndex > 0) {
				rowIndex--;
			}

			tabCount = 0;
			tabIndex = rowIndex;
			while (transferedNotePadContents.find(tab, tabIndex) != -1 && endFindedIndex > transferedNotePadContents.find(tab, tabIndex)) {
				tabIndex = transferedNotePadContents.find(tab, tabIndex) + 1;
				tabCount++;
			}
			if (rowIndex > 0) {
				endColumnIndex = endFindedIndex - rowIndex - 2 + (tabCount * 7);
			}
			else {
				endColumnIndex = endFindedIndex + (tabCount * 7);
			}
			this->matchIndexCollector->AddMatchIndex(new MatchIndex(startRowIndex, startColumnIndex, endRowIndex, endColumnIndex));
			realStartIndex = endFindedIndex;
		}
		if (this->matchIndexCollector->GetLength() > 0) {
			this->notePadForm->SetIsFindingContents(true);

			this->isDownWardSearching = true;
			this->isContentsMatchSearching = true;
			this->isUpWardSearching = false;
			this->isCompletelyMatchSearching = false;

			this->matchIndexCollector->MoveFirstMatchIndex();
			MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
			NotePadIndicator notePadIndicator(this->notePadForm);
			notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

			Selector* selector = this->notePadForm->GetSelector();
			selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
			selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
			selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
			selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

			SelectModifier selectModifier(selector);
			selectModifier.SetAbsoluteSelectionInformation();
			this->notePadForm->GetSelector()->HighLightMatchContents();
			this->notePadForm->SetIsSelected(true);
		}
		else {
			CString information;
			this->notePadForm->Notify();
			this->notePadForm->Invalidate();
			if (this->pDlg->FindNext()) {
				information.Format(_T("\"%s\"을(를) 찾을 수 없습니다."), (char*)(this->findWhatString->c_str()));
			}
			else if (this->pDlg->ReplaceCurrent()) {
				information.Format(_T("\"%s\"을(를) 찾을 수 없어서 바꿔줄 수 없습니다."), (char*)(this->findWhatString->c_str()));
			}
			this->notePadFormControlWnd->MessageBox(information, _T("메모장"), MB_ICONINFORMATION);

			this->pDlg->SetFocus();
		}
	}
	else {//대화상자를 닫지않고 '찾기'컨트롤을 연속으로 눌러서 이미 탐색한 내용을 앞,뒤로 참고하며 다음 일치한곳을 표시해줄때 
		this->notePadForm->SetIsFindingContents(true);

		bool isReturnedToFirst = false;
		this->matchIndexCollector->MoveNextMatchIndex();
		if (this->matchIndexCollector->GetCurrent() >= this->matchIndexCollector->GetLength()) {
			this->matchIndexCollector->MoveFirstMatchIndex();
			isReturnedToFirst = true;
		}
		MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
		NotePadIndicator notePadIndicator(this->notePadForm);
		notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

		Selector* selector = this->notePadForm->GetSelector();
		selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
		selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
		selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
		selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

		SelectModifier selectModifier(selector);
		selectModifier.SetAbsoluteSelectionInformation();
		this->notePadForm->GetSelector()->HighLightMatchContents();
		this->notePadForm->SetIsSelected(true);

		if (isReturnedToFirst == true) {
			this->notePadFormControlWnd->MessageBox("더이상 일치하는 내용이 없습니다. 처음 찾았던 내용으로 이동합니다.", _T("메모장"), MB_ICONINFORMATION);
		}

	}
}

void ContentsFinder::FindSearchUpContentsMatchCaseForTabAndRow() {
	if (this->matchIndexCollector->GetLength() == 0) {
		StringMaker stringMaker(this->notePadForm);
		string transferedFindWhatString = stringMaker.MakeNoCapitalStringForFindNoMatchCase(*this->findWhatString);
		string transferedNotePadContents = stringMaker.MakeNoCapitalStringForFindNoMatchCase(((NotePad*)(this->notePadForm->notePad))->GetContentsForString());

		string tab("\t");
		string row("\r\n");

		Long notePadFormRowIndex = this->notePadForm->notePad->GetCurrent();
		Long countedRowIndex = 0;
		Long breakIndex = 0;

		while (transferedNotePadContents.find(row, breakIndex) != -1 && countedRowIndex != notePadFormRowIndex) {
			breakIndex = transferedNotePadContents.find(row, breakIndex) + 1;
			countedRowIndex++;
		}
		if (breakIndex > 0) {
			breakIndex--;
		}
		NotePadMetric notePadMetric(this->notePadForm);
		Long tabCount = notePadMetric.GetHowManyTabInToCurrentColumnInCurrentRow();
		if (breakIndex == 0) {
			breakIndex = this->notePadForm->row->GetCurrent() - (tabCount * 7);
		}
		else {
			breakIndex = breakIndex + 2 + this->notePadForm->row->GetCurrent() - (tabCount * 7);
		}
		bool isStopTiming = false;
		Long i = 0;
		while (isStopTiming==false &&transferedNotePadContents.find(transferedFindWhatString, i) != -1) {
			Long startFindedIndex = transferedNotePadContents.find(transferedFindWhatString, i);
			Long rowIndex = 0;
			Long startRowIndex = 0;
			Long startColumnIndex = 0;

			while (transferedNotePadContents.find(row, rowIndex) != -1 && startFindedIndex > transferedNotePadContents.find(row, rowIndex)) {
				rowIndex = transferedNotePadContents.find(row, rowIndex) + 1;
				startRowIndex++;
			}
			if (startRowIndex > 0) {
				rowIndex--;
			}

			Long tabCount = 0;
			Long tabIndex = rowIndex;
			while (transferedNotePadContents.find(tab, tabIndex) != -1 && startFindedIndex > transferedNotePadContents.find(tab, tabIndex)) {
				tabIndex = transferedNotePadContents.find(tab, tabIndex) + 1;
				tabCount++;
			}
			if (rowIndex > 0) {
				startColumnIndex = startFindedIndex - rowIndex - 2 + (tabCount * 7);
			}
			else {
				startColumnIndex = startFindedIndex + (tabCount * 7);
			}

			Long endFindedIndex = startFindedIndex + this->findWhatString->length();
			rowIndex = 0;
			Long endRowIndex = 0;
			Long endColumnIndex = 0;

			while (transferedNotePadContents.find(row, rowIndex) != -1 && endFindedIndex > transferedNotePadContents.find(row, rowIndex)) {
				rowIndex = transferedNotePadContents.find(row, rowIndex) + 1;
				endRowIndex++;
			}
			if (endRowIndex > 0) {
				rowIndex--;
			}

			tabCount = 0;
			tabIndex = rowIndex;
			while (transferedNotePadContents.find(tab, tabIndex) != -1 && endFindedIndex > transferedNotePadContents.find(tab, tabIndex)) {
				tabIndex = transferedNotePadContents.find(tab, tabIndex) + 1;
				tabCount++;
			}
			if (rowIndex > 0) {
				endColumnIndex = endFindedIndex - rowIndex - 2 + (tabCount * 7);
			}
			else {
				endColumnIndex = endFindedIndex + (tabCount * 7);
			}
			i = endFindedIndex;
			if (i<=breakIndex) {
				this->matchIndexCollector->AddMatchIndex(new MatchIndex(startRowIndex, startColumnIndex, endRowIndex, endColumnIndex));
			}
			else {
				isStopTiming = true;
			}
		}
		if (this->matchIndexCollector->GetLength() > 0) {
			this->notePadForm->SetIsFindingContents(true);

			this->isUpWardSearching = true;
			this->isCompletelyMatchSearching = false;
			this->isDownWardSearching = false;
			this->isContentsMatchSearching = true;

			this->matchIndexCollector->MovePreviousMatchIndex();

			MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
			NotePadIndicator notePadIndicator(this->notePadForm);
			notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

			Selector* selector = this->notePadForm->GetSelector();
			selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
			selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
			selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
			selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

			SelectModifier selectModifier(selector);
			selectModifier.SetAbsoluteSelectionInformation();
			this->notePadForm->GetSelector()->HighLightMatchContents();
			this->notePadForm->SetIsSelected(true);
		}
		else {
			CString information;
			this->notePadForm->Notify();
			this->notePadForm->Invalidate();
			information.Format(_T("\"%s\"을(를) 찾을 수 없습니다."), (char*)(this->findWhatString->c_str()));
			this->notePadFormControlWnd->MessageBox(information, _T("메모장"), MB_ICONINFORMATION);
			this->pDlg->SetFocus();
		}
	}
	else {//대화상자를 닫지않고 '찾기'컨트롤을 연속으로 눌러서 이미 탐색한 내용을 앞,뒤로 참고하며 다음 일치한곳을 표시해줄때 
		this->notePadForm->SetIsFindingContents(true);
		bool isReturnedToFirst = false;
		this->matchIndexCollector->MovePreviousMatchIndex();
		if (this->matchIndexCollector->GetCurrent() < 0) {
			this->matchIndexCollector->MoveLastMatchIndex();
			this->matchIndexCollector->MovePreviousMatchIndex();
			isReturnedToFirst = true;
		}
		MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
		NotePadIndicator notePadIndicator(this->notePadForm);
		notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

		Selector* selector = this->notePadForm->GetSelector();
		selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
		selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
		selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
		selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

		SelectModifier selectModifier(selector);
		selectModifier.SetAbsoluteSelectionInformation();
		this->notePadForm->GetSelector()->HighLightMatchContents();
		this->notePadForm->SetIsSelected(true);

		if (isReturnedToFirst == true) {
			this->notePadFormControlWnd->MessageBox("더이상 일치하는 내용이 없습니다. 처음 찾았던 내용으로 이동합니다.", _T("메모장"), MB_ICONINFORMATION);
		}
	}
}


void ContentsFinder::FindSearchDownCompletelyMatchCaseForMenuCommand() {
	if (this->matchIndexCollector->GetLength() == 0) {//새롭게 대화상자를 열어서 탐색한 내역이 아무것도 없어서 일치하는내용을 새롭게 탐색할때
		int CompareContentsCompletelyMatch(void* one, void* other);
		Long calculateRealStringLength(string * findWhatString);

		this->standardPoint = new CPoint(this->notePadForm->row->GetCurrent(), this->notePadForm->notePad->GetCurrent());
		Long(*indexes) = 0;
		Long count = 0;
		string firstChar("");
		if (!(this->findWhatString->at(0) & 0x80)) {
			firstChar += this->GetFindWhatString()->at(0);
		}
		else {
			firstChar += this->GetFindWhatString()->at(0);
			firstChar += this->GetFindWhatString()->at(1);
		}
		Long realStringLength = calculateRealStringLength(this->findWhatString);
		Long i = this->notePadForm->notePad->GetCurrent();
		while (i < this->notePadForm->notePad->GetLength()) {
			Glyph* row = this->notePadForm->notePad->GetAt(i);
			((Row*)(row))->SearchMatchCharDuplicate(&firstChar, &indexes, &count, CompareContentsCompletelyMatch);
			Long j = 0;
			if (i == this->notePadForm->notePad->GetCurrent()) {
				while (indexes[j] < this->notePadForm->row->GetCurrent()) {
					j++;
				}
			}
			while (j < count) {
				if (indexes[j] + realStringLength <= row->GetLength()) {
					Long k = 0;
					string excerptContents("");
					while (k < realStringLength) {
						excerptContents += row->GetAt(indexes[j] + k)->GetContents();
						k++;
					}
					bool isMatched = false;
					if (excerptContents.compare(*this->findWhatString) == 0) {
						isMatched = true;
						this->matchIndexCollector->AddMatchIndex(new MatchIndex(i, indexes[j], i, indexes[j] + realStringLength));
					}
					k = 0;
					if (isMatched == true) {//찾았을때 검색위치재설정
						while (j + k<count && indexes[j] + realStringLength>indexes[j + k]) {
							k++;
						}
						if (j + k < count) {
							j += k;
						}
						else {
							j = count;
						}
					}
					else {//못찾았을때 검색위치재설정
						j++;
					}
				}
				else {
					j = count;
				}
			}
			if (indexes != 0) {
				delete indexes;
				indexes = 0;
			}
			count = 0;
			i++;
		}
		if (indexes != 0) {
			delete indexes;
			indexes = 0;
		}
		if (this->matchIndexCollector->GetLength() > 0) {
			this->notePadForm->SetIsFindingContents(true);

			this->isCompletelyMatchSearching = true;
			this->isDownWardSearching = true;
			this->isContentsMatchSearching = false;
			this->isUpWardSearching = false;

			this->matchIndexCollector->MoveFirstMatchIndex();

			MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
			NotePadIndicator notePadIndicator(this->notePadForm);
			notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

			Selector* selector = this->notePadForm->GetSelector();
			selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
			selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
			selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
			selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

			SelectModifier selectModifier(selector);
			selectModifier.SetAbsoluteSelectionInformation();
			this->notePadForm->GetSelector()->HighLightMatchContents();
			this->notePadForm->SetIsSelected(true);
		}
		else {
			CString information;
			this->notePadForm->Notify();
			this->notePadForm->Invalidate();
			information.Format(_T("\"%s\"을(를) 찾을 수 없습니다."), (char*)(this->findWhatString->c_str()));
			this->notePadFormControlWnd->MessageBox(information, _T("메모장"), MB_ICONINFORMATION);
		}
	}
	else {//대화상자를 닫지않고 '찾기'컨트롤을 연속으로 눌러서 이미 탐색한 내용을 앞,뒤로 참고하며 다음 일치한곳을 표시해줄때 
		this->notePadForm->SetIsFindingContents(true);

		bool isReturnedToFirst = false;
		this->matchIndexCollector->MoveNextMatchIndex();
		if (this->matchIndexCollector->GetCurrent() >= this->matchIndexCollector->GetLength()) {
			this->matchIndexCollector->MoveFirstMatchIndex();
			isReturnedToFirst = true;
		}
		MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
		NotePadIndicator notePadIndicator(this->notePadForm);
		notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

		Selector* selector = this->notePadForm->GetSelector();
		selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
		selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
		selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
		selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

		SelectModifier selectModifier(selector);
		selectModifier.SetAbsoluteSelectionInformation();
		this->notePadForm->GetSelector()->HighLightMatchContents();
		this->notePadForm->SetIsSelected(true);
		if (isReturnedToFirst == true) {
			this->notePadFormControlWnd->MessageBox("더이상 일치하는 내용이 없습니다. 처음 찾았던 내용으로 이동합니다.", _T("메모장"), MB_ICONINFORMATION);
		}
	}
}


void ContentsFinder::FindSearchUpCompletelyMatchCaseForMenuCommand() {
	if (this->matchIndexCollector->GetLength() == 0) {//새롭게 대화상자를 열어서 탐색한 내역이 아무것도 없어서 일치하는내용을 새롭게 탐색할때
		int CompareContentsCompletelyMatch(void* one, void* other);
		Long calculateRealStringLength(string * findWhatString);

		this->standardPoint = new CPoint(this->notePadForm->row->GetCurrent(), this->notePadForm->notePad->GetCurrent());
		Long(*indexes) = 0;
		Long count = 0;
		string firstChar("");
		if (!(this->findWhatString->at(0) & 0x80)) {
			firstChar += this->GetFindWhatString()->at(0);
		}
		else {
			firstChar += this->GetFindWhatString()->at(0);
			firstChar += this->GetFindWhatString()->at(1);
		}
		Long realStringLength = calculateRealStringLength(this->findWhatString);
		Long i = 0;
		while (i <= this->notePadForm->notePad->GetCurrent()) {
			Glyph* row = this->notePadForm->notePad->GetAt(i);
			((Row*)(row))->SearchMatchCharDuplicate(&firstChar, &indexes, &count, CompareContentsCompletelyMatch);
			Long j = 0;
			if (i == this->notePadForm->notePad->GetCurrent()) {
				Long k = 0;
				while (k < count && indexes[k] + realStringLength <= this->notePadForm->row->GetCurrent()) {
					k++;
				}
				count -= (count - k);
			}
			while (j < count) {
				if (indexes[j] + realStringLength <= row->GetLength()) {
					Long k = 0;
					string excerptContents("");
					while (k < realStringLength) {
						excerptContents += row->GetAt(indexes[j] + k)->GetContents();
						k++;
					}
					bool isMatched = false;
					if (excerptContents.compare(*this->findWhatString) == 0) {
						isMatched = true;
						this->matchIndexCollector->AddMatchIndex(new MatchIndex(i, indexes[j], i, indexes[j] + realStringLength));
					}
					k = 0;
					if (isMatched == true) {//찾았을때 검색위치재설정
						while (j + k<count && indexes[j] + realStringLength>indexes[j + k]) {
							k++;
						}
						if (j + k < count) {
							j += k;
						}
						else {
							j = count;
						}
					}
					else {//못찾았을때 검색위치재설정
						j++;
					}
				}
				else {
					j = count;
				}
			}
			if (indexes != 0) {
				delete indexes;
				indexes = 0;
			}
			count = 0;
			i++;
		}
		if (indexes != 0) {
			delete indexes;
			indexes = 0;
		}
		if (this->matchIndexCollector->GetLength() > 0) {
			this->notePadForm->SetIsFindingContents(true);

			this->isUpWardSearching = true;
			this->isCompletelyMatchSearching = true;
			this->isDownWardSearching = false;
			this->isContentsMatchSearching = false;

			this->matchIndexCollector->MovePreviousMatchIndex();

			MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
			NotePadIndicator notePadIndicator(this->notePadForm);
			notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

			Selector* selector = this->notePadForm->GetSelector();
			selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
			selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
			selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
			selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

			SelectModifier selectModifier(selector);
			selectModifier.SetAbsoluteSelectionInformation();
			this->notePadForm->GetSelector()->HighLightMatchContents();
			this->notePadForm->SetIsSelected(true);
		}
		else {
			CString information;
			this->notePadForm->Notify();
			this->notePadForm->Invalidate();
			information.Format(_T("\"%s\"을(를) 찾을 수 없습니다."), (char*)(this->findWhatString->c_str()));
			this->notePadFormControlWnd->MessageBox(information, _T("메모장"), MB_ICONINFORMATION);
		}
	}
	else {//대화상자를 닫지않고 '찾기'컨트롤을 연속으로 눌러서 이미 탐색한 내용을 앞,뒤로 참고하며 다음 일치한곳을 표시해줄때 
		this->notePadForm->SetIsFindingContents(true);
		bool isReturnedToFirst = false;
		this->matchIndexCollector->MovePreviousMatchIndex();
		if (this->matchIndexCollector->GetCurrent() < 0) {
			this->matchIndexCollector->MoveLastMatchIndex();
			this->matchIndexCollector->MovePreviousMatchIndex();
			isReturnedToFirst = true;
		}
		MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
		NotePadIndicator notePadIndicator(this->notePadForm);
		notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

		Selector* selector = this->notePadForm->GetSelector();
		selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
		selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
		selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
		selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

		SelectModifier selectModifier(selector);
		selectModifier.SetAbsoluteSelectionInformation();
		this->notePadForm->GetSelector()->HighLightMatchContents();
		this->notePadForm->SetIsSelected(true);

		if (isReturnedToFirst == true) {
			this->notePadFormControlWnd->MessageBox("더이상 일치하는 내용이 없습니다. 처음 찾았던 내용으로 이동합니다.", _T("메모장"), MB_ICONINFORMATION);
		}
	}
}


void ContentsFinder::FindSearchDownContentsMatchCaseForMenuCommand(){
	if (this->matchIndexCollector->GetLength() == 0) {//새롭게 대화상자를 열어서 탐색한 내역이 아무것도 없어서 일치하는내용을 새롭게 탐색할때
		int CompareContentsMatch(void* one, void* other);
		int CompareWholeContentsMatch(string one, string other);
		Long calculateRealStringLength(string * findWhatString);
		this->standardPoint = new CPoint(this->notePadForm->row->GetCurrent(), this->notePadForm->notePad->GetCurrent());

		Long(*indexes) = 0;
		Long count = 0;
		string firstChar("");
		if (!(this->findWhatString->at(0) & 0x80)) {
			firstChar += this->GetFindWhatString()->at(0);
		}
		else {
			firstChar += this->GetFindWhatString()->at(0);
			firstChar += this->GetFindWhatString()->at(1);
		}
		Long realStringLength = calculateRealStringLength(this->findWhatString);
		Long i = this->notePadForm->notePad->GetCurrent();
		while (i < this->notePadForm->notePad->GetLength()) {
			Glyph* row = this->notePadForm->notePad->GetAt(i);
			((Row*)(row))->SearchMatchCharDuplicate(&firstChar, &indexes, &count, CompareContentsMatch);
			Long j = 0;
			if (i == this->notePadForm->notePad->GetCurrent()) {
				while (indexes[j] < this->notePadForm->row->GetCurrent()) {
					j++;
				}
			}
			while (j < count) {
				if (indexes[j] + realStringLength <= row->GetLength()) {
					Long k = 0;
					string excerptContents("");
					while (k < realStringLength) {
						excerptContents += row->GetAt(indexes[j] + k)->GetContents();
						k++;
					}
					bool isMatched = false;
					if (CompareWholeContentsMatch(*this->findWhatString, excerptContents) == 0) {
						isMatched = true;
						this->matchIndexCollector->AddMatchIndex(new MatchIndex(i, indexes[j], i, indexes[j] + realStringLength));
					}
					k = 0;
					if (isMatched == true) {//찾았을때 검색위치재설정
						while (j + k<count && indexes[j] + realStringLength>indexes[j + k]) {
							k++;
						}
						if (j + k < count) {
							j += k;
						}
						else {
							j = count;
						}
					}
					else {//못찾았을때 검색위치재설정
						j++;
					}
				}
				else {
					j = count;
				}
			}
			if (indexes != 0) {
				delete indexes;
				indexes = 0;
			}
			count = 0;
			i++;
		}
		if (indexes != 0) {
			delete indexes;
			indexes = 0;
		}
		if (this->matchIndexCollector->GetLength() > 0) {
			this->notePadForm->SetIsFindingContents(true);
			this->isDownWardSearching = true;
			this->isContentsMatchSearching = true;
			this->isUpWardSearching = false;
			this->isCompletelyMatchSearching = false;

			this->matchIndexCollector->MoveFirstMatchIndex();
			MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
			NotePadIndicator notePadIndicator(this->notePadForm);
			notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

			Selector* selector = this->notePadForm->GetSelector();
			selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
			selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
			selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
			selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

			SelectModifier selectModifier(selector);
			selectModifier.SetAbsoluteSelectionInformation();
			this->notePadForm->GetSelector()->HighLightMatchContents();
			this->notePadForm->SetIsSelected(true);
		}
		else {
			CString information;
			this->notePadForm->Notify();
			this->notePadForm->Invalidate();
			information.Format(_T("\"%s\"을(를) 찾을 수 없습니다."), (char*)(this->findWhatString->c_str()));
			this->notePadFormControlWnd->MessageBox(information, _T("메모장"), MB_ICONINFORMATION);
		}
	}
	else {//대화상자를 닫지않고 '찾기'컨트롤을 연속으로 눌러서 이미 탐색한 내용을 앞,뒤로 참고하며 다음 일치한곳을 표시해줄때 
		this->notePadForm->SetIsFindingContents(true);

		bool isReturnedToFirst = false;
		this->matchIndexCollector->MoveNextMatchIndex();
		if (this->matchIndexCollector->GetCurrent() >= this->matchIndexCollector->GetLength()) {
			this->matchIndexCollector->MoveFirstMatchIndex();
			isReturnedToFirst = true;
		}
		MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
		NotePadIndicator notePadIndicator(this->notePadForm);
		notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

		Selector* selector = this->notePadForm->GetSelector();
		selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
		selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
		selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
		selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

		SelectModifier selectModifier(selector);
		selectModifier.SetAbsoluteSelectionInformation();
		this->notePadForm->GetSelector()->HighLightMatchContents();
		this->notePadForm->SetIsSelected(true);

		if (isReturnedToFirst == true) {
			this->notePadFormControlWnd->MessageBox("더이상 일치하는 내용이 없습니다. 처음 찾았던 내용으로 이동합니다.", _T("메모장"), MB_ICONINFORMATION);
		}
	}

}


void ContentsFinder::FindSearchUpContentsMatchCaseForMenuCommand() {
	if (this->matchIndexCollector->GetLength() == 0) {//새롭게 대화상자를 열어서 탐색한 내역이 아무것도 없어서 일치하는내용을 새롭게 탐색할때
		int CompareContentsMatch(void* one, void* other);
		int CompareWholeContentsMatch(string one, string other);
		Long calculateRealStringLength(string * findWhatString);

		this->standardPoint = new CPoint(this->notePadForm->row->GetCurrent(), this->notePadForm->notePad->GetCurrent());
		Long(*indexes) = 0;
		Long count = 0;
		string firstChar("");
		if (!(this->findWhatString->at(0) & 0x80)) {
			firstChar += this->GetFindWhatString()->at(0);
		}
		else {
			firstChar += this->GetFindWhatString()->at(0);
			firstChar += this->GetFindWhatString()->at(1);
		}
		Long realStringLength = calculateRealStringLength(this->findWhatString);
		Long i = 0;
		while (i <= this->notePadForm->notePad->GetCurrent()) {
			Glyph* row = this->notePadForm->notePad->GetAt(i);
			((Row*)(row))->SearchMatchCharDuplicate(&firstChar, &indexes, &count, CompareContentsMatch);
			Long j = 0;
			if (i == this->notePadForm->notePad->GetCurrent()) {
				Long k = 0;
				while (k < count && indexes[k] + realStringLength <= this->notePadForm->row->GetCurrent()) {
					k++;
				}
				count -= (count - k);
			}
			while (j < count) {
				if (indexes[j] + realStringLength <= row->GetLength()) {
					Long k = 0;
					string excerptContents("");
					while (k < realStringLength) {
						excerptContents += row->GetAt(indexes[j] + k)->GetContents();
						k++;
					}
					bool isMatched = false;
					if (CompareWholeContentsMatch(*this->findWhatString, excerptContents) == 0) {
						isMatched = true;
						this->matchIndexCollector->AddMatchIndex(new MatchIndex(i, indexes[j], i, indexes[j] + realStringLength));
					}
					k = 0;
					if (isMatched == true) {//찾았을때 검색위치재설정
						while (j + k<count && indexes[j] + realStringLength>indexes[j + k]) {
							k++;
						}
						if (j + k < count) {
							j += k;
						}
						else {
							j = count;
						}
					}
					else {//못찾았을때 검색위치재설정
						j++;
					}
				}
				else {
					j = count;
				}
			}
			if (indexes != 0) {
				delete indexes;
				indexes = 0;
			}
			count = 0;
			i++;
		}
		if (indexes != 0) {
			delete indexes;
			indexes = 0;
		}
		if (this->matchIndexCollector->GetLength() > 0) {
			this->notePadForm->SetIsFindingContents(true);

			this->isUpWardSearching = true;
			this->isContentsMatchSearching = true;
			this->isDownWardSearching = false;
			this->isCompletelyMatchSearching = false;

			this->matchIndexCollector->MovePreviousMatchIndex();
			MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
			NotePadIndicator notePadIndicator(this->notePadForm);
			notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

			Selector* selector = this->notePadForm->GetSelector();
			selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
			selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
			selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
			selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

			SelectModifier selectModifier(selector);
			selectModifier.SetAbsoluteSelectionInformation();
			this->notePadForm->GetSelector()->HighLightMatchContents();
			this->notePadForm->SetIsSelected(true);
		}
		else {
			CString information;
			this->notePadForm->Notify();
			this->notePadForm->Invalidate();
			information.Format(_T("\"%s\"을(를) 찾을 수 없습니다."), (char*)(this->findWhatString->c_str()));
			this->notePadFormControlWnd->MessageBox(information, _T("메모장"), MB_ICONINFORMATION);
		}
	}
	else {//이미 탐색한 내용을 앞,뒤로 참고하며 다음 일치한곳을 표시해줄때 
		this->notePadForm->SetIsFindingContents(true);

		bool isReturnedToFirst = false;
		this->matchIndexCollector->MovePreviousMatchIndex();
		if (this->matchIndexCollector->GetCurrent() < 0) {
			this->matchIndexCollector->MoveLastMatchIndex();
			this->matchIndexCollector->MovePreviousMatchIndex();
			isReturnedToFirst = true;
		}
		MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
		NotePadIndicator notePadIndicator(this->notePadForm);
		notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

		Selector* selector = this->notePadForm->GetSelector();
		selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
		selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
		selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
		selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

		SelectModifier selectModifier(selector);
		selectModifier.SetAbsoluteSelectionInformation();
		this->notePadForm->GetSelector()->HighLightMatchContents();
		this->notePadForm->SetIsSelected(true);

		if (isReturnedToFirst == true) {
			this->notePadFormControlWnd->MessageBox("더이상 일치하는 내용이 없습니다. 처음 찾았던 내용으로 이동합니다.", _T("메모장"), MB_ICONINFORMATION);
		}
	}
}


void ContentsFinder::FindSearchDownCompletelyMatchCaseForMenuCommandForTabAndRow() {
	if (this->matchIndexCollector->GetLength() == 0) {
		string notePadCotents = ((NotePad*)(this->notePadForm->notePad))->GetContentsForString();
		string tab("\t");
		string row("\r\n");
		Long notePadFormRowIndex = this->notePadForm->notePad->GetCurrent();
		Long countedRowIndex = 0;
		Long realStartIndex = 0;

		while (notePadCotents.find(row, realStartIndex) != -1 && countedRowIndex != notePadFormRowIndex) {
			realStartIndex = notePadCotents.find(row, realStartIndex) + 1;
			countedRowIndex++;
		}
		if (realStartIndex > 0) {
			realStartIndex--;
		}
		NotePadMetric notePadMetric(this->notePadForm);
		Long tabCount = notePadMetric.GetHowManyTabInToCurrentColumnInCurrentRow();
		if (realStartIndex == 0) {
			realStartIndex = this->notePadForm->row->GetCurrent() - (tabCount * 7);
		}
		else {
			realStartIndex = realStartIndex + 2 + this->notePadForm->row->GetCurrent() - (tabCount * 7);
		}

		while (notePadCotents.find(*this->findWhatString, realStartIndex) != -1) {
			Long startFindedIndex = notePadCotents.find(*this->findWhatString, realStartIndex);
			Long rowIndex = 0;
			Long startRowIndex = 0;
			Long startColumnIndex = 0;

			while (notePadCotents.find(row, rowIndex) != -1 && startFindedIndex > notePadCotents.find(row, rowIndex)) {
				rowIndex = notePadCotents.find(row, rowIndex) + 1;
				startRowIndex++;
			}
			if (startRowIndex > 0) {
				rowIndex--;
			}

			Long tabCount = 0;
			Long tabIndex = rowIndex;
			while (notePadCotents.find(tab, tabIndex) != -1 && startFindedIndex > notePadCotents.find(tab, tabIndex)) {
				tabIndex = notePadCotents.find(tab, tabIndex) + 1;
				tabCount++;
			}
			if (rowIndex > 0) {
				startColumnIndex = startFindedIndex - rowIndex - 2 + (tabCount * 7);
			}
			else {
				startColumnIndex = startFindedIndex + (tabCount * 7);
			}

			Long endFindedIndex = startFindedIndex + this->findWhatString->length();
			rowIndex = 0;
			Long endRowIndex = 0;
			Long endColumnIndex = 0;

			while (notePadCotents.find(row, rowIndex) != -1 && endFindedIndex > notePadCotents.find(row, rowIndex)) {
				rowIndex = notePadCotents.find(row, rowIndex) + 1;
				endRowIndex++;
			}
			if (endRowIndex > 0) {
				rowIndex--;
			}

			tabCount = 0;
			tabIndex = rowIndex;
			while (notePadCotents.find(tab, tabIndex) != -1 && endFindedIndex > notePadCotents.find(tab, tabIndex)) {
				tabIndex = notePadCotents.find(tab, tabIndex) + 1;
				tabCount++;
			}
			if (rowIndex > 0) {
				endColumnIndex = endFindedIndex - rowIndex - 2 + (tabCount * 7);
			}
			else {
				endColumnIndex = endFindedIndex + (tabCount * 7);
			}
			this->matchIndexCollector->AddMatchIndex(new MatchIndex(startRowIndex, startColumnIndex, endRowIndex, endColumnIndex));
			realStartIndex = endFindedIndex;
		}
		if (this->matchIndexCollector->GetLength() > 0) {
			this->notePadForm->SetIsFindingContents(true);

			this->isCompletelyMatchSearching = true;
			this->isDownWardSearching = true;
			this->isContentsMatchSearching = false;
			this->isUpWardSearching = false;

			this->matchIndexCollector->MoveFirstMatchIndex();

			MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
			NotePadIndicator notePadIndicator(this->notePadForm);
			notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

			Selector* selector = this->notePadForm->GetSelector();
			selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
			selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
			selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
			selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

			SelectModifier selectModifier(selector);
			selectModifier.SetAbsoluteSelectionInformation();
			this->notePadForm->GetSelector()->HighLightMatchContents();
			this->notePadForm->SetIsSelected(true);
		}
		else {
			CString information;
			this->notePadForm->Notify();
			this->notePadForm->Invalidate();
			information.Format(_T("\"%s\"을(를) 찾을 수 없습니다."), (char*)(this->findWhatString->c_str()));
			this->notePadFormControlWnd->MessageBox(information, _T("메모장"), MB_ICONINFORMATION);
		}
	}
	else {//대화상자를 닫지않고 '찾기'컨트롤을 연속으로 눌러서 이미 탐색한 내용을 앞,뒤로 참고하며 다음 일치한곳을 표시해줄때 
		this->notePadForm->SetIsFindingContents(true);
		bool isReturnedToFirst = false;
		this->matchIndexCollector->MoveNextMatchIndex();
		if (this->matchIndexCollector->GetCurrent() >= this->matchIndexCollector->GetLength()) {
			this->matchIndexCollector->MoveFirstMatchIndex();
			isReturnedToFirst = true;
		}
		MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
		NotePadIndicator notePadIndicator(this->notePadForm);
		notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

		Selector* selector = this->notePadForm->GetSelector();
		selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
		selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
		selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
		selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

		SelectModifier selectModifier(selector);
		selectModifier.SetAbsoluteSelectionInformation();
		this->notePadForm->GetSelector()->HighLightMatchContents();
		this->notePadForm->SetIsSelected(true);
		if (isReturnedToFirst == true) {
			this->notePadFormControlWnd->MessageBox("더이상 일치하는 내용이 없습니다. 처음 찾았던 내용으로 이동합니다.", _T("메모장"), MB_ICONINFORMATION);
		}
	}
}


void ContentsFinder::FindSearchUpCompletelyMatchCaseForMenuCommandForTabAndRow() {
	if (this->matchIndexCollector->GetLength() == 0) {
		string notePadCotents = ((NotePad*)(this->notePadForm->notePad))->GetContentsForString();
		string tab("\t");
		string row("\r\n");
		Long notePadFormRowIndex = this->notePadForm->notePad->GetCurrent();
		Long countedRowIndex = 0;
		Long breakIndex = 0;

		while (notePadCotents.find(row, breakIndex) != -1 && countedRowIndex != notePadFormRowIndex) {
			breakIndex = notePadCotents.find(row, breakIndex) + 1;
			countedRowIndex++;
		}
		if (breakIndex > 0) {
			breakIndex--;
		}
		NotePadMetric notePadMetric(this->notePadForm);
		Long tabCount = notePadMetric.GetHowManyTabInToCurrentColumnInCurrentRow();
		if (breakIndex == 0) {
			breakIndex = this->notePadForm->row->GetCurrent() - (tabCount * 7);
		}
		else {
			breakIndex = breakIndex + 2 + this->notePadForm->row->GetCurrent() - (tabCount * 7);
		}
		bool isStopTiming = false;
		Long i = 0;
		while (i < breakIndex && notePadCotents.find(*this->findWhatString, i) != -1) {
			Long startFindedIndex = notePadCotents.find(*this->findWhatString, i);
			Long rowIndex = 0;
			Long startRowIndex = 0;
			Long startColumnIndex = 0;

			while (notePadCotents.find(row, rowIndex) != -1 && startFindedIndex > notePadCotents.find(row, rowIndex)) {
				rowIndex = notePadCotents.find(row, rowIndex) + 1;
				startRowIndex++;
			}
			if (startRowIndex > 0) {
				rowIndex--;
			}

			Long tabCount = 0;
			Long tabIndex = rowIndex;
			while (notePadCotents.find(tab, tabIndex) != -1 && startFindedIndex > notePadCotents.find(tab, tabIndex)) {
				tabIndex = notePadCotents.find(tab, tabIndex) + 1;
				tabCount++;
			}
			if (rowIndex > 0) {
				startColumnIndex = startFindedIndex - rowIndex - 2 + (tabCount * 7);
			}
			else {
				startColumnIndex = startFindedIndex + (tabCount * 7);
			}

			Long endFindedIndex = startFindedIndex + this->findWhatString->length();
			rowIndex = 0;
			Long endRowIndex = 0;
			Long endColumnIndex = 0;

			while (notePadCotents.find(row, rowIndex) != -1 && endFindedIndex > notePadCotents.find(row, rowIndex)) {
				rowIndex = notePadCotents.find(row, rowIndex) + 1;
				endRowIndex++;
			}
			if (endRowIndex > 0) {
				rowIndex--;
			}

			tabCount = 0;
			tabIndex = rowIndex;
			while (notePadCotents.find(tab, tabIndex) != -1 && endFindedIndex > notePadCotents.find(tab, tabIndex)) {
				tabIndex = notePadCotents.find(tab, tabIndex) + 1;
				tabCount++;
			}
			if (rowIndex > 0) {
				endColumnIndex = endFindedIndex - rowIndex - 2 + (tabCount * 7);
			}
			else {
				endColumnIndex = endFindedIndex + (tabCount * 7);
			}
			i = endFindedIndex;
			if (i <= breakIndex) {
				this->matchIndexCollector->AddMatchIndex(new MatchIndex(startRowIndex, startColumnIndex, endRowIndex, endColumnIndex));
			}
			else {
				isStopTiming = true;
			}
		}
		if (this->matchIndexCollector->GetLength() > 0) {
			this->notePadForm->SetIsFindingContents(true);

			this->isUpWardSearching = true;
			this->isCompletelyMatchSearching = true;
			this->isDownWardSearching = false;
			this->isContentsMatchSearching = false;

			this->matchIndexCollector->MovePreviousMatchIndex();

			MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
			NotePadIndicator notePadIndicator(this->notePadForm);
			notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

			Selector* selector = this->notePadForm->GetSelector();
			selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
			selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
			selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
			selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

			SelectModifier selectModifier(selector);
			selectModifier.SetAbsoluteSelectionInformation();
			this->notePadForm->GetSelector()->HighLightMatchContents();
			this->notePadForm->SetIsSelected(true);
		}
		else {
			CString information;
			this->notePadForm->Notify();
			this->notePadForm->Invalidate();
			information.Format(_T("\"%s\"을(를) 찾을 수 없습니다."), (char*)(this->findWhatString->c_str()));
			this->notePadFormControlWnd->MessageBox(information, _T("메모장"), MB_ICONINFORMATION);
		}
	}
	else {//대화상자를 닫지않고 '찾기'컨트롤을 연속으로 눌러서 이미 탐색한 내용을 앞,뒤로 참고하며 다음 일치한곳을 표시해줄때 
		this->notePadForm->SetIsFindingContents(true);
		bool isReturnedToFirst = false;
		this->matchIndexCollector->MovePreviousMatchIndex();
		if (this->matchIndexCollector->GetCurrent() < 0) {
			this->matchIndexCollector->MoveLastMatchIndex();
			this->matchIndexCollector->MovePreviousMatchIndex();
			isReturnedToFirst = true;
		}
		MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
		NotePadIndicator notePadIndicator(this->notePadForm);
		notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

		Selector* selector = this->notePadForm->GetSelector();
		selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
		selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
		selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
		selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

		SelectModifier selectModifier(selector);
		selectModifier.SetAbsoluteSelectionInformation();
		this->notePadForm->GetSelector()->HighLightMatchContents();
		this->notePadForm->SetIsSelected(true);

		if (isReturnedToFirst == true) {
			this->notePadFormControlWnd->MessageBox("더이상 일치하는 내용이 없습니다. 처음 찾았던 내용으로 이동합니다.", _T("메모장"), MB_ICONINFORMATION);
		}
	}
}


void ContentsFinder::FindSearchDownContentsMatchCaseForMenuCommandForTabAndRow() {
	if (this->matchIndexCollector->GetLength() == 0) {
		StringMaker stringMaker(this->notePadForm);
		string transferedFindWhatString = stringMaker.MakeNoCapitalStringForFindNoMatchCase(*this->findWhatString);
		string transferedNotePadContents = stringMaker.MakeNoCapitalStringForFindNoMatchCase(((NotePad*)(this->notePadForm->notePad))->GetContentsForString());

		string tab("\t");
		string row("\r\n");

		Long notePadFormRowIndex = this->notePadForm->notePad->GetCurrent();
		Long countedRowIndex = 0;
		Long realStartIndex = 0;

		while (transferedNotePadContents.find(row, realStartIndex) != -1 && countedRowIndex != notePadFormRowIndex) {
			realStartIndex = transferedNotePadContents.find(row, realStartIndex) + 1;
			countedRowIndex++;
		}
		if (realStartIndex > 0) {
			realStartIndex--;
		}
		NotePadMetric notePadMetric(this->notePadForm);
		Long tabCount = notePadMetric.GetHowManyTabInToCurrentColumnInCurrentRow();
		if (realStartIndex == 0) {
			realStartIndex = this->notePadForm->row->GetCurrent() - (tabCount * 7);
		}
		else {
			realStartIndex = realStartIndex + 2 + this->notePadForm->row->GetCurrent() - (tabCount * 7);
		}

		while (transferedNotePadContents.find(transferedFindWhatString, realStartIndex) != -1) {
			Long startFindedIndex = transferedNotePadContents.find(transferedFindWhatString, realStartIndex);
			Long rowIndex = 0;
			Long startRowIndex = 0;
			Long startColumnIndex = 0;

			while (transferedNotePadContents.find(row, rowIndex) != -1 && startFindedIndex > transferedNotePadContents.find(row, rowIndex)) {
				rowIndex = transferedNotePadContents.find(row, rowIndex) + 1;
				startRowIndex++;
			}
			if (startRowIndex > 0) {
				rowIndex--;
			}

			Long tabCount = 0;
			Long tabIndex = rowIndex;
			while (transferedNotePadContents.find(tab, tabIndex) != -1 && startFindedIndex > transferedNotePadContents.find(tab, tabIndex)) {
				tabIndex = transferedNotePadContents.find(tab, tabIndex) + 1;
				tabCount++;
			}
			if (rowIndex > 0) {
				startColumnIndex = startFindedIndex - rowIndex - 2 + (tabCount * 7);
			}
			else {
				startColumnIndex = startFindedIndex + (tabCount * 7);
			}

			Long endFindedIndex = startFindedIndex + this->findWhatString->length();
			rowIndex = 0;
			Long endRowIndex = 0;
			Long endColumnIndex = 0;

			while (transferedNotePadContents.find(row, rowIndex) != -1 && endFindedIndex > transferedNotePadContents.find(row, rowIndex)) {
				rowIndex = transferedNotePadContents.find(row, rowIndex) + 1;
				endRowIndex++;
			}
			if (endRowIndex > 0) {
				rowIndex--;
			}

			tabCount = 0;
			tabIndex = rowIndex;
			while (transferedNotePadContents.find(tab, tabIndex) != -1 && endFindedIndex > transferedNotePadContents.find(tab, tabIndex)) {
				tabIndex = transferedNotePadContents.find(tab, tabIndex) + 1;
				tabCount++;
			}
			if (rowIndex > 0) {
				endColumnIndex = endFindedIndex - rowIndex - 2 + (tabCount * 7);
			}
			else {
				endColumnIndex = endFindedIndex + (tabCount * 7);
			}
			this->matchIndexCollector->AddMatchIndex(new MatchIndex(startRowIndex, startColumnIndex, endRowIndex, endColumnIndex));
			realStartIndex = endFindedIndex;
		}
		if (this->matchIndexCollector->GetLength() > 0) {
			this->notePadForm->SetIsFindingContents(true);

			this->isDownWardSearching = true;
			this->isContentsMatchSearching = true;
			this->isUpWardSearching = false;
			this->isCompletelyMatchSearching = false;

			this->matchIndexCollector->MoveFirstMatchIndex();
			MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
			NotePadIndicator notePadIndicator(this->notePadForm);
			notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

			Selector* selector = this->notePadForm->GetSelector();
			selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
			selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
			selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
			selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

			SelectModifier selectModifier(selector);
			selectModifier.SetAbsoluteSelectionInformation();
			this->notePadForm->GetSelector()->HighLightMatchContents();
			this->notePadForm->SetIsSelected(true);
		}
		else {
			CString information;
			this->notePadForm->Notify();
			this->notePadForm->Invalidate();
			information.Format(_T("\"%s\"을(를) 찾을 수 없습니다."), (char*)(this->findWhatString->c_str()));
			this->notePadFormControlWnd->MessageBox(information, _T("메모장"), MB_ICONINFORMATION);
		}
	}
	else {//대화상자를 닫지않고 '찾기'컨트롤을 연속으로 눌러서 이미 탐색한 내용을 앞,뒤로 참고하며 다음 일치한곳을 표시해줄때 
		this->notePadForm->SetIsFindingContents(true);

		bool isReturnedToFirst = false;
		this->matchIndexCollector->MoveNextMatchIndex();
		if (this->matchIndexCollector->GetCurrent() >= this->matchIndexCollector->GetLength()) {
			this->matchIndexCollector->MoveFirstMatchIndex();
			isReturnedToFirst = true;
		}
		MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
		NotePadIndicator notePadIndicator(this->notePadForm);
		notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

		Selector* selector = this->notePadForm->GetSelector();
		selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
		selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
		selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
		selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

		SelectModifier selectModifier(selector);
		selectModifier.SetAbsoluteSelectionInformation();
		this->notePadForm->GetSelector()->HighLightMatchContents();
		this->notePadForm->SetIsSelected(true);

		if (isReturnedToFirst == true) {
			this->notePadFormControlWnd->MessageBox("더이상 일치하는 내용이 없습니다. 처음 찾았던 내용으로 이동합니다.", _T("메모장"), MB_ICONINFORMATION);
		}
	}
}


void ContentsFinder::FindSearchUpContentsMatchCaseForMenuCommandForTabAndRow() {
	if (this->matchIndexCollector->GetLength() == 0) {
		StringMaker stringMaker(this->notePadForm);
		string transferedFindWhatString = stringMaker.MakeNoCapitalStringForFindNoMatchCase(*this->findWhatString);
		string transferedNotePadContents = stringMaker.MakeNoCapitalStringForFindNoMatchCase(((NotePad*)(this->notePadForm->notePad))->GetContentsForString());

		string tab("\t");
		string row("\r\n");

		Long notePadFormRowIndex = this->notePadForm->notePad->GetCurrent();
		Long countedRowIndex = 0;
		Long breakIndex = 0;

		while (transferedNotePadContents.find(row, breakIndex) != -1 && countedRowIndex != notePadFormRowIndex) {
			breakIndex = transferedNotePadContents.find(row, breakIndex) + 1;
			countedRowIndex++;
		}
		if (breakIndex > 0) {
			breakIndex--;
		}
		NotePadMetric notePadMetric(this->notePadForm);
		Long tabCount = notePadMetric.GetHowManyTabInToCurrentColumnInCurrentRow();
		if (breakIndex == 0) {
			breakIndex = this->notePadForm->row->GetCurrent() - (tabCount * 7);
		}
		else {
			breakIndex = breakIndex + 2 + this->notePadForm->row->GetCurrent() - (tabCount * 7);
		}
		bool isStopTiming = false;
		Long i = 0;
		while (isStopTiming == false && transferedNotePadContents.find(transferedFindWhatString, i) != -1) {
			Long startFindedIndex = transferedNotePadContents.find(transferedFindWhatString, i);
			Long rowIndex = 0;
			Long startRowIndex = 0;
			Long startColumnIndex = 0;

			while (transferedNotePadContents.find(row, rowIndex) != -1 && startFindedIndex > transferedNotePadContents.find(row, rowIndex)) {
				rowIndex = transferedNotePadContents.find(row, rowIndex) + 1;
				startRowIndex++;
			}
			if (startRowIndex > 0) {
				rowIndex--;
			}

			Long tabCount = 0;
			Long tabIndex = rowIndex;
			while (transferedNotePadContents.find(tab, tabIndex) != -1 && startFindedIndex > transferedNotePadContents.find(tab, tabIndex)) {
				tabIndex = transferedNotePadContents.find(tab, tabIndex) + 1;
				tabCount++;
			}
			if (rowIndex > 0) {
				startColumnIndex = startFindedIndex - rowIndex - 2 + (tabCount * 7);
			}
			else {
				startColumnIndex = startFindedIndex + (tabCount * 7);
			}

			Long endFindedIndex = startFindedIndex + this->findWhatString->length();
			rowIndex = 0;
			Long endRowIndex = 0;
			Long endColumnIndex = 0;

			while (transferedNotePadContents.find(row, rowIndex) != -1 && endFindedIndex > transferedNotePadContents.find(row, rowIndex)) {
				rowIndex = transferedNotePadContents.find(row, rowIndex) + 1;
				endRowIndex++;
			}
			if (endRowIndex > 0) {
				rowIndex--;
			}

			tabCount = 0;
			tabIndex = rowIndex;
			while (transferedNotePadContents.find(tab, tabIndex) != -1 && endFindedIndex > transferedNotePadContents.find(tab, tabIndex)) {
				tabIndex = transferedNotePadContents.find(tab, tabIndex) + 1;
				tabCount++;
			}
			if (rowIndex > 0) {
				endColumnIndex = endFindedIndex - rowIndex - 2 + (tabCount * 7);
			}
			else {
				endColumnIndex = endFindedIndex + (tabCount * 7);
			}
			i = endFindedIndex;
			if (i <= breakIndex) {
				this->matchIndexCollector->AddMatchIndex(new MatchIndex(startRowIndex, startColumnIndex, endRowIndex, endColumnIndex));
			}
			else {
				isStopTiming = true;
			}
		}
		if (this->matchIndexCollector->GetLength() > 0) {
			this->notePadForm->SetIsFindingContents(true);

			this->isUpWardSearching = true;
			this->isCompletelyMatchSearching = false;
			this->isDownWardSearching = false;
			this->isContentsMatchSearching = true;

			this->matchIndexCollector->MovePreviousMatchIndex();

			MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
			NotePadIndicator notePadIndicator(this->notePadForm);
			notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

			Selector* selector = this->notePadForm->GetSelector();
			selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
			selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
			selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
			selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

			SelectModifier selectModifier(selector);
			selectModifier.SetAbsoluteSelectionInformation();
			this->notePadForm->GetSelector()->HighLightMatchContents();
			this->notePadForm->SetIsSelected(true);
		}
		else {
			CString information;
			this->notePadForm->Notify();
			this->notePadForm->Invalidate();
			information.Format(_T("\"%s\"을(를) 찾을 수 없습니다."), (char*)(this->findWhatString->c_str()));
			this->notePadFormControlWnd->MessageBox(information, _T("메모장"), MB_ICONINFORMATION);
		}
	}
	else {//대화상자를 닫지않고 '찾기'컨트롤을 연속으로 눌러서 이미 탐색한 내용을 앞,뒤로 참고하며 다음 일치한곳을 표시해줄때 
		this->notePadForm->SetIsFindingContents(true);
		bool isReturnedToFirst = false;
		this->matchIndexCollector->MovePreviousMatchIndex();
		if (this->matchIndexCollector->GetCurrent() < 0) {
			this->matchIndexCollector->MoveLastMatchIndex();
			this->matchIndexCollector->MovePreviousMatchIndex();
			isReturnedToFirst = true;
		}
		MatchIndex* matchIndex = this->matchIndexCollector->GetAt(this->matchIndexCollector->GetCurrent());
		NotePadIndicator notePadIndicator(this->notePadForm);
		notePadIndicator.GoToCoordinate(matchIndex->GetEndRowIndex(), matchIndex->GetEndColumnIndex());

		Selector* selector = this->notePadForm->GetSelector();
		selector->SetOriginRowIndex(matchIndex->GetStartRowIndex());
		selector->SetOriginColumnIndex(matchIndex->GetStartColumnIndex());
		selector->SetEndRowIndex(matchIndex->GetEndRowIndex());
		selector->SetEndColumnIndex(matchIndex->GetEndColumnIndex());

		SelectModifier selectModifier(selector);
		selectModifier.SetAbsoluteSelectionInformation();
		this->notePadForm->GetSelector()->HighLightMatchContents();
		this->notePadForm->SetIsSelected(true);

		if (isReturnedToFirst == true) {
			this->notePadFormControlWnd->MessageBox("더이상 일치하는 내용이 없습니다. 처음 찾았던 내용으로 이동합니다.", _T("메모장"), MB_ICONINFORMATION);
		}
	}
}


void ContentsFinder::FindSearchDownCompletelyMatchCaseForReplaceAll(bool isFirstSearch, Long countOfReplaced) {
	int CompareContentsCompletelyMatch(void* one, void* other);

	Long calculateRealStringLength(string * findWhatString);

	this->standardPoint = new CPoint(this->notePadForm->row->GetCurrent(), this->notePadForm->notePad->GetCurrent());
	Long(*indexes) = 0;
	Long count = 0;
	string firstChar("");
	if (!(this->findWhatString->at(0) & 0x80)) {
		firstChar += this->GetFindWhatString()->at(0);
	}
	else {
		firstChar += this->GetFindWhatString()->at(0);
		firstChar += this->GetFindWhatString()->at(1);
	}
	Long realStringLength = calculateRealStringLength(this->findWhatString);
	Long i = this->notePadForm->notePad->GetCurrent();
	while (i < this->notePadForm->notePad->GetLength()) {
		Glyph* row = this->notePadForm->notePad->GetAt(i);
		((Row*)(row))->SearchMatchCharDuplicate(&firstChar, &indexes, &count, CompareContentsCompletelyMatch);
		Long j = 0;
		if (i == this->notePadForm->notePad->GetCurrent()) {
			while (indexes[j] < this->notePadForm->row->GetCurrent()) {
				j++;
			}
		}
		while (j < count) {
			if (indexes[j] + realStringLength <= row->GetLength()) {
				Long k = 0;
				string excerptContents("");
				while (k < realStringLength) {
					excerptContents += row->GetAt(indexes[j] + k)->GetContents();
					k++;
				}
				bool isMatched = false;
				if (excerptContents.compare(*this->findWhatString) == 0) {
					isMatched = true;
					this->matchIndexCollector->AddMatchIndex(new MatchIndex(i, indexes[j], i, indexes[j] + realStringLength));
				}
				k = 0;
				if (isMatched == true) {//찾았을때 검색위치재설정
					while (j + k<count && indexes[j] + realStringLength>indexes[j + k]) {
						k++;
					}
					if (j + k < count) {
						j += k;
					}
					else {
						j = count;
					}
				}
				else {//못찾았을때 검색위치재설정
					j++;
				}
			}
			else {
				j = count;
			}
		}
		if (indexes != 0) {
			delete indexes;
			indexes = 0;
		}
		count = 0;
		i++;
	}
	if (indexes != 0) {
		delete indexes;
		indexes = 0;
	}
	if (this->matchIndexCollector->GetLength() <= 0) {
		CString information;
		this->notePadForm->Notify();
		this->notePadForm->Invalidate();
		if (isFirstSearch==true) {
			information.Format(_T("\"%s\"을(를) 찾을 수 없어 모두 바꿔줄 수 없습니다."), (char*)(this->findWhatString->c_str()));
		}
		else {
			information.Format(_T("\"%s\"을(를) 총 %d개 바꿔주었습니다!"), (char*)(this->findWhatString->c_str()),countOfReplaced);
		}
		this->notePadFormControlWnd->MessageBox(information, _T("메모장"), MB_ICONINFORMATION);
		this->pDlg->SetFocus();
	}
	else {
		this->matchIndexCollector->MoveFirstMatchIndex();
	}
}


void ContentsFinder::FindSearchDownContentsMatchCaseForReplaceAll(bool isFirstSearch, Long countOfReplaced) {
	int CompareContentsMatch(void* one, void* other);//Array메소드로 넘겨줄 실인수 함수포인터

	int CompareWholeContentsMatch(string one, string other);
	Long calculateRealStringLength(string * findWhatString);
	this->standardPoint = new CPoint(this->notePadForm->row->GetCurrent(), this->notePadForm->notePad->GetCurrent());

	Long(*indexes) = 0;
	Long count = 0;
	string firstChar("");
	if (!(this->findWhatString->at(0) & 0x80)) {
		firstChar += this->GetFindWhatString()->at(0);
	}
	else {
		firstChar += this->GetFindWhatString()->at(0);
		firstChar += this->GetFindWhatString()->at(1);
	}
	Long realStringLength = calculateRealStringLength(this->findWhatString);
	Long i = this->notePadForm->notePad->GetCurrent();
	while (i < this->notePadForm->notePad->GetLength()) {
		Glyph* row = this->notePadForm->notePad->GetAt(i);
		((Row*)(row))->SearchMatchCharDuplicate(&firstChar, &indexes, &count, CompareContentsMatch);
		Long j = 0;
		if (i == this->notePadForm->notePad->GetCurrent()) {
			while (indexes[j] < this->notePadForm->row->GetCurrent()) {
				j++;
			}
		}
		while (j < count) {
			if (indexes[j] + realStringLength <= row->GetLength()) {
				Long k = 0;
				string excerptContents("");
				while (k < realStringLength) {
					excerptContents += row->GetAt(indexes[j] + k)->GetContents();
					k++;
				}
				bool isMatched = false;
				if (CompareWholeContentsMatch(*this->findWhatString, excerptContents) == 0) {
					isMatched = true;
					this->matchIndexCollector->AddMatchIndex(new MatchIndex(i, indexes[j], i, indexes[j] + realStringLength));
				}
				k = 0;
				if (isMatched == true) {//찾았을때 검색위치재설정
					while (j + k<count && indexes[j] + realStringLength>indexes[j + k]) {
						k++;
					}
					if (j + k < count) {
						j += k;
					}
					else {
						j = count;
					}
				}
				else {//못찾았을때 검색위치재설정
					j++;
				}
			}
			else {
				j = count;
			}
		}
		if (indexes != 0) {
			delete indexes;
			indexes = 0;
		}
		count = 0;
		i++;
	}
	if (indexes != 0) {
		delete indexes;
		indexes = 0;
	}
	if (this->matchIndexCollector->GetLength() <= 0){
		CString information;
		this->notePadForm->Notify();
		this->notePadForm->Invalidate();
		if (isFirstSearch == true) {
			information.Format(_T("\"%s\"을(를) 찾을 수 없어 모두 바꿔줄 수 없습니다."), (char*)(this->findWhatString->c_str()));
		}
		else {
			information.Format(_T("\"%s\"을(를) 총 %d개 바꿔주었습니다!"), (char*)(this->findWhatString->c_str()), countOfReplaced);
		}
		this->notePadFormControlWnd->MessageBox(information, _T("메모장"), MB_ICONINFORMATION);
		this->pDlg->SetFocus();
	}
	else {
		this->matchIndexCollector->MoveFirstMatchIndex();
	}
}


void ContentsFinder::FindSearchDownCompletelyMatchCaseForReplaceAllForTabAndRow(bool isFirstSearch, Long countOfReplaced) {
	if (this->matchIndexCollector->GetLength() == 0) {
		string notePadCotents = ((NotePad*)(this->notePadForm->notePad))->GetContentsForString();
		string tab("\t");
		string row("\r\n");
		Long notePadFormRowIndex = this->notePadForm->notePad->GetCurrent();
		Long countedRowIndex = 0;
		Long realStartIndex = 0;

		while (notePadCotents.find(row, realStartIndex) != -1 && countedRowIndex != notePadFormRowIndex) {
			realStartIndex = notePadCotents.find(row, realStartIndex) + 1;
			countedRowIndex++;
		}
		if (realStartIndex > 0) {
			realStartIndex--;
		}
		NotePadMetric notePadMetric(this->notePadForm);
		Long tabCount = notePadMetric.GetHowManyTabInToCurrentColumnInCurrentRow();
		if (realStartIndex == 0) {
			realStartIndex = this->notePadForm->row->GetCurrent() - (tabCount * 7);
		}
		else {
			realStartIndex = realStartIndex + 2 + this->notePadForm->row->GetCurrent() - (tabCount * 7);
		}

		while (notePadCotents.find(*this->findWhatString, realStartIndex) != -1) {
			Long startFindedIndex = notePadCotents.find(*this->findWhatString, realStartIndex);
			Long rowIndex = 0;
			Long startRowIndex = 0;
			Long startColumnIndex = 0;

			while (notePadCotents.find(row, rowIndex) != -1 && startFindedIndex > notePadCotents.find(row, rowIndex)) {
				rowIndex = notePadCotents.find(row, rowIndex) + 1;
				startRowIndex++;
			}
			if (startRowIndex > 0) {
				rowIndex--;
			}

			Long tabCount = 0;
			Long tabIndex = rowIndex;
			while (notePadCotents.find(tab, tabIndex) != -1 && startFindedIndex > notePadCotents.find(tab, tabIndex)) {
				tabIndex = notePadCotents.find(tab, tabIndex) + 1;
				tabCount++;
			}
			if (rowIndex > 0) {
				startColumnIndex = startFindedIndex - rowIndex - 2 + (tabCount * 7);
			}
			else {
				startColumnIndex = startFindedIndex + (tabCount * 7);
			}

			Long endFindedIndex = startFindedIndex + this->findWhatString->length();
			rowIndex = 0;
			Long endRowIndex = 0;
			Long endColumnIndex = 0;

			while (notePadCotents.find(row, rowIndex) != -1 && endFindedIndex > notePadCotents.find(row, rowIndex)) {
				rowIndex = notePadCotents.find(row, rowIndex) + 1;
				endRowIndex++;
			}
			if (endRowIndex > 0) {
				rowIndex--;
			}

			tabCount = 0;
			tabIndex = rowIndex;
			while (notePadCotents.find(tab, tabIndex) != -1 && endFindedIndex > notePadCotents.find(tab, tabIndex)) {
				tabIndex = notePadCotents.find(tab, tabIndex) + 1;
				tabCount++;
			}
			if (rowIndex > 0) {
				endColumnIndex = endFindedIndex - rowIndex - 2 + (tabCount * 7);
			}
			else {
				endColumnIndex = endFindedIndex + (tabCount * 7);
			}
			this->matchIndexCollector->AddMatchIndex(new MatchIndex(startRowIndex, startColumnIndex, endRowIndex, endColumnIndex));
			realStartIndex = endFindedIndex;
		}
		if (this->matchIndexCollector->GetLength() <= 0) {
			CString information;
			this->notePadForm->Notify();
			this->notePadForm->Invalidate();
			if (isFirstSearch == true) {
				information.Format(_T("\"%s\"을(를) 찾을 수 없어 모두 바꿔줄 수 없습니다."), (char*)(this->findWhatString->c_str()));
			}
			else {
				information.Format(_T("\"%s\"을(를) 총 %d개 바꿔주었습니다!"), (char*)(this->findWhatString->c_str()), countOfReplaced);
			}
			this->notePadFormControlWnd->MessageBox(information, _T("메모장"), MB_ICONINFORMATION);
			this->pDlg->SetFocus();
		}
		else {
			this->matchIndexCollector->MoveFirstMatchIndex();
		}
	}
}

void ContentsFinder::FindSearchDownContentsMatchCaseForReplaceAllForTabAndRow(bool isFirstSearch, Long countOfReplaced) {
	if (this->matchIndexCollector->GetLength() == 0) {
		StringMaker stringMaker(this->notePadForm);
		string transferedFindWhatString = stringMaker.MakeNoCapitalStringForFindNoMatchCase(*this->findWhatString);
		string transferedNotePadContents = stringMaker.MakeNoCapitalStringForFindNoMatchCase(((NotePad*)(this->notePadForm->notePad))->GetContentsForString());

		string tab("\t");
		string row("\r\n");

		Long notePadFormRowIndex = this->notePadForm->notePad->GetCurrent();
		Long countedRowIndex = 0;
		Long realStartIndex = 0;

		while (transferedNotePadContents.find(row, realStartIndex) != -1 && countedRowIndex != notePadFormRowIndex) {
			realStartIndex = transferedNotePadContents.find(row, realStartIndex) + 1;
			countedRowIndex++;
		}
		if (realStartIndex > 0) {
			realStartIndex--;
		}
		NotePadMetric notePadMetric(this->notePadForm);
		Long tabCount = notePadMetric.GetHowManyTabInToCurrentColumnInCurrentRow();
		if (realStartIndex == 0) {
			realStartIndex = this->notePadForm->row->GetCurrent() - (tabCount * 7);
		}
		else {
			realStartIndex = realStartIndex + 2 + this->notePadForm->row->GetCurrent() - (tabCount * 7);
		}

		while (transferedNotePadContents.find(transferedFindWhatString, realStartIndex) != -1) {
			Long startFindedIndex = transferedNotePadContents.find(transferedFindWhatString, realStartIndex);
			Long rowIndex = 0;
			Long startRowIndex = 0;
			Long startColumnIndex = 0;

			while (transferedNotePadContents.find(row, rowIndex) != -1 && startFindedIndex > transferedNotePadContents.find(row, rowIndex)) {
				rowIndex = transferedNotePadContents.find(row, rowIndex) + 1;
				startRowIndex++;
			}
			if (startRowIndex > 0) {
				rowIndex--;
			}

			Long tabCount = 0;
			Long tabIndex = rowIndex;
			while (transferedNotePadContents.find(tab, tabIndex) != -1 && startFindedIndex > transferedNotePadContents.find(tab, tabIndex)) {
				tabIndex = transferedNotePadContents.find(tab, tabIndex) + 1;
				tabCount++;
			}
			if (rowIndex > 0) {
				startColumnIndex = startFindedIndex - rowIndex - 2 + (tabCount * 7);
			}
			else {
				startColumnIndex = startFindedIndex + (tabCount * 7);
			}

			Long endFindedIndex = startFindedIndex + this->findWhatString->length();
			rowIndex = 0;
			Long endRowIndex = 0;
			Long endColumnIndex = 0;

			while (transferedNotePadContents.find(row, rowIndex) != -1 && endFindedIndex > transferedNotePadContents.find(row, rowIndex)) {
				rowIndex = transferedNotePadContents.find(row, rowIndex) + 1;
				endRowIndex++;
			}
			if (endRowIndex > 0) {
				rowIndex--;
			}

			tabCount = 0;
			tabIndex = rowIndex;
			while (transferedNotePadContents.find(tab, tabIndex) != -1 && endFindedIndex > transferedNotePadContents.find(tab, tabIndex)) {
				tabIndex = transferedNotePadContents.find(tab, tabIndex) + 1;
				tabCount++;
			}
			if (rowIndex > 0) {
				endColumnIndex = endFindedIndex - rowIndex - 2 + (tabCount * 7);
			}
			else {
				endColumnIndex = endFindedIndex + (tabCount * 7);
			}
			this->matchIndexCollector->AddMatchIndex(new MatchIndex(startRowIndex, startColumnIndex, endRowIndex, endColumnIndex));
			realStartIndex = endFindedIndex;
		}
		if (this->matchIndexCollector->GetLength() <= 0) {
			CString information;
			this->notePadForm->Notify();
			this->notePadForm->Invalidate();
			if (isFirstSearch == true) {
				information.Format(_T("\"%s\"을(를) 찾을 수 없어 모두 바꿔줄 수 없습니다."), (char*)(this->findWhatString->c_str()));
			}
			else {
				information.Format(_T("\"%s\"을(를) 총 %d개 바꿔주었습니다!"), (char*)(this->findWhatString->c_str()), countOfReplaced);
			}
			this->notePadFormControlWnd->MessageBox(information, _T("메모장"), MB_ICONINFORMATION);
			this->pDlg->SetFocus();
		}
		else {
			this->matchIndexCollector->MoveFirstMatchIndex();
		}
	}
}

int CompareContentsCompletelyMatch(void* one, void* other) {
	
	int ret = -1;
	
	if ((*(static_cast<Glyph**>(one)))->GetContents()==*(static_cast<string*>(other))) {
		ret = 0;
	}
	

	return ret;
}


int CompareContentsMatch(void* one, void* other) {
	int ret = -1;
	int CompareContentsCompletelyMatch(void* one, void* other);

	ret = CompareContentsCompletelyMatch(one, other);
	
	if (ret==-1) {
		if (!((*(static_cast<Glyph**>(one)))->GetContents()[0]& 0x80) && !((*(static_cast<Glyph**>(one)))->GetContents()[0]&0x80)) {

			bool oneIsCapitalChar = false;
			bool otherIsCapitalChar = false;
			if ((*(static_cast<Glyph**>(one)))->GetContents()[0] > 64 && (*(static_cast<Glyph**>(one)))->GetContents()[0] < 91) {
				oneIsCapitalChar = true;
			}
			if ((*(static_cast<string*>(other)))[0] > 64 && (*(static_cast<string*>(other)))[0] < 91) {
				otherIsCapitalChar = true;
			}
			if (oneIsCapitalChar == true && otherIsCapitalChar == false) {
				if ((*(static_cast<Glyph**>(one)))->GetContents()[0] + 32 == (*(static_cast<string*>(other)))[0]) {
					ret = 0;
				}
			}
			else if (oneIsCapitalChar == false && otherIsCapitalChar == true) {
				if ((*(static_cast<Glyph**>(one)))->GetContents()[0] == (*(static_cast<string*>(other)))[0] + 32) {
					ret = 0;
				}
			}
		}
	}
	return ret;
}


int CompareWholeContentsMatch(string one, string other) {
	int ret = -1;
	int CompareStringContent(string one, string other);
	Long i = 0;
	Long matchCount = 0;

	if (one.length()==other.length()) {
		while (i < one.length()) {
			char oneBuffer[2];
			oneBuffer[0] = one[i];
			oneBuffer[1] = '\0';
			char otherBuffer[2];
			otherBuffer[0] = other[i];
			otherBuffer[1] = '\0';
			string oneChar(oneBuffer);
			string otherChar(otherBuffer);
			ret = CompareStringContent(oneChar,otherChar);
			if (ret==0) {
				matchCount++;
			}
			else {
				if (!(one[i] & 0x80) && !(other[i] & 0x80)) {

					bool oneIsCapitalChar = false;
					bool otherIsCapitalChar = false;
					if (one[i] > 64 && one[i] < 91) {
						oneIsCapitalChar = true;
					}
					if (other[i] > 64 && other[i] < 91) {
						otherIsCapitalChar = true;
					}
					if (oneIsCapitalChar!=otherIsCapitalChar) {
						if (oneIsCapitalChar == true && otherIsCapitalChar == false) {
							if (one[i] + 32 == other[i]) {
								matchCount++;
							}
						}
						else if (oneIsCapitalChar == false && otherIsCapitalChar == true) {
							if (one[i] == other[i] + 32) {
								matchCount++;
							}
						}
					}
				}
			}
			i++;
		}
	}
	if (matchCount==i) {
		ret = 0;
	}
	else {
		ret = -1;
	}
	return ret;
}


int CompareStringContent(string one, string other) {
	int ret = -1;

	if (one == other) {
		ret = 0;
	}
	return ret;
}


Long calculateRealStringLength(string* findWhatString) {
	Long realStringLength = 0;
	Long i = 0;
	Long originalLength = findWhatString->length();
	while (i<originalLength) {
		if (!(findWhatString->at(i) & 0x80)) {
			i++;
		}
		else {
			i += 2;
		}
		realStringLength++;
	}
	return realStringLength;
}
