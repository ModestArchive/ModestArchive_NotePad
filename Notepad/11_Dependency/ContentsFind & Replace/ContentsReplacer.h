//ContentsReplacer.h

#ifndef _CONTETNSREPLACER_H
#define _CONTETNSREPLACER_H

#include<string>
class NotePadFormControlWnd;
class MatchIndexCollector;
class NotePadForm;
typedef signed long int Long;
using namespace std;

class ContentsReplacer {

public:

	ContentsReplacer(NotePadFormControlWnd* notePadFormControlWnd,NotePadForm* notePadForm);
	~ContentsReplacer();
	//주요메소드
	void ReplaceCurrentContents();
	void ReplaceAllContents(bool isFirstReplace,bool isLastReplace);
	//세팅메소드
	void SetReplaceWhatString(string* replaceWhatString);
	//인라인함수
	NotePadFormControlWnd* GetNotePadFormControlWnd() const;
	NotePadForm* GetNotePadForm() const;
	string* GetReplaceWhatString() const;
	
private:
	NotePadFormControlWnd* notePadFormControlWnd;
	NotePadForm* notePadForm;
	string* replaceWhatString;
};

inline NotePadFormControlWnd* ContentsReplacer::GetNotePadFormControlWnd() const {
	return const_cast<NotePadFormControlWnd*>(this->notePadFormControlWnd);
}
inline NotePadForm* ContentsReplacer::GetNotePadForm() const {
	return const_cast<NotePadForm*>(this->notePadForm);
}
inline string* ContentsReplacer::GetReplaceWhatString() const {
	return const_cast<string*>(this->replaceWhatString);
}
#endif // !_CONTETNSREPLACER_H


