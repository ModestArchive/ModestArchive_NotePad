//CommandFactory.h

#ifndef _COMMANDFACTORY_H
#define _COMMANDFACTORY_H
#include"Command.h"
class NotePadForm;
class NotePadFormControlWnd;
class CommandFactory {
public:
	//������, �Ҹ���
	CommandFactory(NotePadForm* notePadForm,NotePadFormControlWnd* notePadFormControlWnd);
	~CommandFactory();
	//�޼ҵ�
	Command* MakeCommand(UINT nID);
	//�������Լ�
	//�ζ����Լ�
private:
	NotePadForm* notePadForm;
	NotePadFormControlWnd* notePadFormControlWnd;
};
#endif // !_COMMANDFACTORY_H
