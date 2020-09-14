//RedoCommand.h

#ifndef _REDOCOMMAND_H
#define _REDOCOMMAND_H

#include "Command.h"
class NotePadFormControlWnd;

class RedoCommand :public Command {

public:
	RedoCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm);
	virtual ~RedoCommand();
	virtual void Execute();

private:
	NotePadFormControlWnd* notePadFormControlWnd;
	NotePadForm* notePadForm;
};
#endif // !_REDOCOMMAND_H
