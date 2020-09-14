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
	//�ֿ� �޼ҵ�
		//Ư�� ������ ���ø޼ҵ�	
	void GetReadyToCreateFindPdlg();
	void GetReadyToCreateFindAndReplacePdlg();
	void GetReadyToFindNextFromPdlg();
	void GetReadyToFindPreviousFromPdlg();
	void GetReadyToFindNextFromMenuCommand();
	void GetReadyToFindPreviousFromMenuCommand();
	MatchIndex GetReadyToReplaceCurrentFromPdlg();
	void GetReadyToReplaceAllFromPdlg();
	
		//��ȭ�����̺�Ʈ �޼ҵ�
	void DoMatchCaseSearchDown();
	void DoMatchCaseSearchUp();
	void DoNoMatchCaseSearchDown();
	void DoNoMatchCaseSearchUp();
	void DoReplaceCurrentMatchCase(MatchIndex alreadyMatchedIndex);
	void DoReplaceCurrentNoMatchCase(MatchIndex alreadyMatchedIndex);
	void DoReplaceAllMatchCase();
	void DoReplaceAllNoMatchCase();
	   //�޴�Ŀ�ǵ� �޼ҵ�
	void DoSearchDownForMenuCommand();
	void DoSearchUpForMenuCommand();
		//��ȭ���ڸ� ������ ��Ʈ�� ���� �� ����
	void SaveInformationAsPdlgTerminating();
		//ã���Ŀ� �ٷ� �ٽ�ã�ų� �ٲ����ʰ� �ٸ��ൿ�� ������, ��ġ�ϴ� ��ġ������ �������ִ� �޼ҵ�
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

