//FindReplaceSupervisor.h

#ifndef _FINDREPLACESUPERVISOR_H
#define _FINDREPLACESUPERVISOR_H

#include"ContentsFinder.h"
#include"ContentsReplacer.h"
#include"NotePadFormControlWnd.h"
#include"NotePadForm.h"
#include"MatchIndex.h"

class FindReplaceSupervisor {
public:
	FindReplaceSupervisor(NotePadFormControlWnd* notePadFormControlWnd,NotePadForm* notePadForm,ContentsFinder* contentsFinder, ContentsReplacer* contentsReplacer,CFindReplaceDialog* pDlg);
	~FindReplaceSupervisor();
	//주요 메소드
		//특정 행위전 세팅메소드	
	void GetReadyToCreateFindPdlg();
	void GetReadyToCreateFindAndReplacePdlg();
	void GetReadyToFindNextFromPdlg();
	void GetReadyToFindPreviousFromPdlg();
	void GetReadyToFindNextFromMenuCommand();
	void GetReadyToFindPreviousFromMenuCommand();
	MatchIndex GetReadyToReplaceCurrentFromPdlg();
	void GetReadyToReplaceAllFromPdlg();
	
		//대화상자이벤트 메소드
	void DoMatchCaseSearchDown();
	void DoMatchCaseSearchUp();
	void DoNoMatchCaseSearchDown();
	void DoNoMatchCaseSearchUp();
	void DoReplaceCurrentMatchCase(MatchIndex alreadyMatchedIndex);
	void DoReplaceCurrentNoMatchCase(MatchIndex alreadyMatchedIndex);
	void DoReplaceAllMatchCase();
	void DoReplaceAllNoMatchCase();
	   //메뉴커맨드 메소드
	void DoSearchDownForMenuCommand();
	void DoSearchUpForMenuCommand();
		//대화상자를 닫을때 스트링 저장 및 생성
	void SaveInformationAsPdlgTerminating();
		//찾은후에 바로 다시찾거나 바꾸지않고 다른행동을 했을때, 일치하는 위치값들을 제거해주는 메소드
	void DeleteMatchIndexCollector();
	void DeleteOnlyMatchIndexCollector();
private:
	NotePadFormControlWnd* notePadFormControlWnd;
	NotePadForm* notePadForm;
	ContentsFinder* contentsFinder;
	ContentsReplacer* contentsReplacer;
	CFindReplaceDialog* pDlg;
};
#endif // !_FINDREPLACESUPERVISOR_H

