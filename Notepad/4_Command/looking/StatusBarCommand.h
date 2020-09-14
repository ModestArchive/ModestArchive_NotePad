//StatusBarCommand.h

#ifndef _STATUSBARCOMMAND_H
#define _STATUSBARCOMMAND_H

#include"Command.h"

class NotePadFormControlWnd;
class NotePadForm;
class StatusBarCommand :public Command {

public:
	StatusBarCommand(NotePadFormControlWnd* notePadFormControlWnd,NotePadForm* notePadForm);
	virtual ~StatusBarCommand();
	virtual void Execute();
	
private:
	NotePadFormControlWnd* notePadFormControlWnd;
	NotePadForm* notePadForm;
};
#endif // !_STATUSBARCOMMAND__H
