//ContentsFinder.h

#ifndef _CONTETNSFINDER_H
#define _CONTETNSFINDER_H

#include"NotePadForm.h"
#include<string>
#include<afxdlgs.h>
class MatchIndexCollector;
typedef signed long int Long;
using namespace std;

class ContentsFinder {

public:

	ContentsFinder(NotePadFormControlWnd* notePadFormControlWnd,NotePadForm* notePadForm);
	~ContentsFinder();

	//찾기를 위한 메소드(tab이 없고 , line을 벗어나지않는 내용을 찾지않을때)
	void FindSearchDownCompletelyMatchCase();
	void FindSearchUpCompletelyMatchCase();
	void FindSearchDownContentsMatchCase();
	void FindSearchUpContentsMatchCase();
	//찾기를 위한 메소드(tab이 있거나, line을 벗어나는 내용을 찾을때)
	void FindSearchDownCompletelyMatchCaseForTabAndRow();
	void FindSearchUpCompletelyMatchCaseForTabAndRow();
	void FindSearchDownContentsMatchCaseForTabAndRow();
	void FindSearchUpContentsMatchCaseForTabAndRow();

	//메뉴찾기 커맨드를 위한 메소드(tab이 없고 , line을 벗어나지않는 내용을 찾지않을때)
	void FindSearchDownCompletelyMatchCaseForMenuCommand();
	void FindSearchUpCompletelyMatchCaseForMenuCommand();
	void FindSearchDownContentsMatchCaseForMenuCommand();
	void FindSearchUpContentsMatchCaseForMenuCommand();
	//메뉴찾기 커맨드를 위한 메소드(tab이 있거나, line을 벗어나는 내용을 찾을때)
	void FindSearchDownCompletelyMatchCaseForMenuCommandForTabAndRow();
	void FindSearchUpCompletelyMatchCaseForMenuCommandForTabAndRow();
	void FindSearchDownContentsMatchCaseForMenuCommandForTabAndRow();
	void FindSearchUpContentsMatchCaseForMenuCommandForTabAndRow();
	
	//모두 바꾸기를 위한 메소드(tab이 없고 , line을 벗어나지않는 내용을 찾지않을때)
	void FindSearchDownCompletelyMatchCaseForReplaceAll(bool isFirstSearch,Long countOfReplaced);
	void FindSearchDownContentsMatchCaseForReplaceAll(bool isFirstSearch, Long countOfReplaced);
	//모두 바꾸기를 위한 메소드(tab이 있거나, line을 벗어나는 내용을 찾을때)
	void FindSearchDownCompletelyMatchCaseForReplaceAllForTabAndRow(bool isFirstSearch, Long countOfReplaced);
	void FindSearchDownContentsMatchCaseForReplaceAllForTabAndRow(bool isFirstSearch, Long countOfReplaced);

	//세팅메소드
	void SetFindWhatString(string* findWhatString);
	void SetStandardPoint(CPoint* standardPoint);
	void SetMatchIndexCollector(MatchIndexCollector* matchIndexCollector);
	void SetIsDownWardSearching(bool isDownWardSearching);
	void SetIsUpWardSearching(bool isUpWardSearching);
	void SetIsCompletelyMatchSearching(bool isCompletelyMatchSearching);
	void SetIsContentsMatchSearching(bool isContentsMatchSearching);
	void SetPDlg(CFindReplaceDialog* pDlg);
	void SetIsPdlgFindOnly(bool isPdlgFindOnly);
	
	//인라인함수
	NotePadFormControlWnd* GetNotePadFormControlWnd() const;
	NotePadForm* GetNotePadForm() const;
	MatchIndexCollector* GetMatchIndexCollector() const;
	string* GetFindWhatString() const;
	CPoint* GetStandardPoint() const;
	bool GetIsDownWardSearching() const;
	bool GetIsUpWardSearching() const;
	bool GetIsCompletelyMatchSearching() const;
	bool GetIsContentsMatchSearching() const;
	CFindReplaceDialog* GetPDlg() const;
	bool GetIsPdlgFindOnly() const;
	
private:
	NotePadFormControlWnd* notePadFormControlWnd;
	NotePadForm* notePadForm;
	MatchIndexCollector* matchIndexCollector;
	string* findWhatString;
	CPoint* standardPoint;
	bool isDownWardSearching;
	bool isUpWardSearching;
	bool isCompletelyMatchSearching;
	bool isContentsMatchSearching;
	CFindReplaceDialog* pDlg;
	bool isPdlgFindOnly;
};

inline NotePadFormControlWnd* ContentsFinder::GetNotePadFormControlWnd() const {
	return const_cast<NotePadFormControlWnd*>(this->notePadFormControlWnd);
}

inline NotePadForm* ContentsFinder::GetNotePadForm() const {
	return const_cast<NotePadForm*>(this->notePadForm);
}
inline MatchIndexCollector* ContentsFinder::GetMatchIndexCollector() const {
	return const_cast<MatchIndexCollector*>(this->matchIndexCollector);
}
inline string* ContentsFinder::GetFindWhatString() const {
	return const_cast<string*>(this->findWhatString);
}
inline CPoint* ContentsFinder::GetStandardPoint() const {
	return const_cast<CPoint*>(this->standardPoint);
}
inline bool ContentsFinder::GetIsDownWardSearching() const {
	return this->isDownWardSearching;
}
inline bool ContentsFinder::GetIsUpWardSearching() const {
	return this->isUpWardSearching;
}
inline bool ContentsFinder::GetIsCompletelyMatchSearching() const {
	return this->isCompletelyMatchSearching;
}
inline bool ContentsFinder::GetIsContentsMatchSearching() const {
	return this->isContentsMatchSearching;
}
inline CFindReplaceDialog* ContentsFinder::GetPDlg() const {
	return const_cast<CFindReplaceDialog*>(this->pDlg);
}
inline bool ContentsFinder::GetIsPdlgFindOnly() const {
	return this->isPdlgFindOnly;
}

#endif // !_CONTETNSFINDER_H

