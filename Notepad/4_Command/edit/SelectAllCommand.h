//SelectAllCommand.h

#ifndef _SELECTALLCOMMAND_H
#define _SELECTALLCOMMAND_H

#include "Command.h"
class NotePadFormControlWnd;

class SelectAllCommand :public Command {

public:
	SelectAllCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm);
	virtual ~SelectAllCommand();
	virtual void Execute();

private:
	NotePadFormControlWnd* notePadFormControlWnd;
	NotePadForm* notePadForm;
};
#endif // !_SELECTALLCOMMAND_H

