//CommandFactory.h

#ifndef _COMMANDFACTORY_H
#define _COMMANDFACTORY_H
#include"Command.h"
class NotePadForm;
class NotePadFormControlWnd;
class CommandFactory {
public:
	//생성자, 소멸자
	CommandFactory(NotePadForm* notePadForm,NotePadFormControlWnd* notePadFormControlWnd);
	~CommandFactory();
	//메소드
	Command* MakeCommand(UINT nID);
	//연산자함수
	//인라인함수
private:
	NotePadForm* notePadForm;
	NotePadFormControlWnd* notePadFormControlWnd;
};
#endif // !_COMMANDFACTORY_H
