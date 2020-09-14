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

	//ã�⸦ ���� �޼ҵ�(tab�� ���� , line�� ������ʴ� ������ ã��������)
	void FindSearchDownCompletelyMatchCase();
	void FindSearchUpCompletelyMatchCase();
	void FindSearchDownContentsMatchCase();
	void FindSearchUpContentsMatchCase();
	//ã�⸦ ���� �޼ҵ�(tab�� �ְų�, line�� ����� ������ ã����)
	void FindSearchDownCompletelyMatchCaseForTabAndRow();
	void FindSearchUpCompletelyMatchCaseForTabAndRow();
	void FindSearchDownContentsMatchCaseForTabAndRow();
	void FindSearchUpContentsMatchCaseForTabAndRow();

	//�޴�ã�� Ŀ�ǵ带 ���� �޼ҵ�(tab�� ���� , line�� ������ʴ� ������ ã��������)
	void FindSearchDownCompletelyMatchCaseForMenuCommand();
	void FindSearchUpCompletelyMatchCaseForMenuCommand();
	void FindSearchDownContentsMatchCaseForMenuCommand();
	void FindSearchUpContentsMatchCaseForMenuCommand();
	//�޴�ã�� Ŀ�ǵ带 ���� �޼ҵ�(tab�� �ְų�, line�� ����� ������ ã����)
	void FindSearchDownCompletelyMatchCaseForMenuCommandForTabAndRow();
	void FindSearchUpCompletelyMatchCaseForMenuCommandForTabAndRow();
	void FindSearchDownContentsMatchCaseForMenuCommandForTabAndRow();
	void FindSearchUpContentsMatchCaseForMenuCommandForTabAndRow();
	
	//��� �ٲٱ⸦ ���� �޼ҵ�(tab�� ���� , line�� ������ʴ� ������ ã��������)
	void FindSearchDownCompletelyMatchCaseForReplaceAll(bool isFirstSearch,Long countOfReplaced);
	void FindSearchDownContentsMatchCaseForReplaceAll(bool isFirstSearch, Long countOfReplaced);
	//��� �ٲٱ⸦ ���� �޼ҵ�(tab�� �ְų�, line�� ����� ������ ã����)
	void FindSearchDownCompletelyMatchCaseForReplaceAllForTabAndRow(bool isFirstSearch, Long countOfReplaced);
	void FindSearchDownContentsMatchCaseForReplaceAllForTabAndRow(bool isFirstSearch, Long countOfReplaced);

	//���ø޼ҵ�
	void SetFindWhatString(string* findWhatString);
	void SetStandardPoint(CPoint* standardPoint);
	void SetMatchIndexCollector(MatchIndexCollector* matchIndexCollector);
	void SetIsDownWardSearching(bool isDownWardSearching);
	void SetIsUpWardSearching(bool isUpWardSearching);
	void SetIsCompletelyMatchSearching(bool isCompletelyMatchSearching);
	void SetIsContentsMatchSearching(bool isContentsMatchSearching);
	void SetPDlg(CFindReplaceDialog* pDlg);
	void SetIsPdlgFindOnly(bool isPdlgFindOnly);
	
	//�ζ����Լ�
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

