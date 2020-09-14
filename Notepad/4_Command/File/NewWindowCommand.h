//NewWindowCommand.h

#ifndef _NEWWINDOWCOMMAND_H
#define _NEWWINDOWCOMMAND_H

#include "Command.h"
class NotePadFormControlWnd;

class NewWindowCommand :public Command {

public:
	NewWindowCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm);
	virtual ~NewWindowCommand();
	virtual void Execute();

private:
	NotePadFormControlWnd* notePadFormControlWnd;
	NotePadForm* notePadForm;
};
#endif // !_NEWWINDOWCOMMAND_H
