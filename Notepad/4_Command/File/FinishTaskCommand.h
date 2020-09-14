//FinishTaskCommand.h

#ifndef _FINISHTASKCOMMAND_H
#define _FINISHTASKCOMMAND_H

#include "Command.h"
class NotePadFormControlWnd;

class FinishTaskCommand :public Command {

public:
	FinishTaskCommand(NotePadFormControlWnd* notePadFormControlWnd,NotePadForm* notePadForm);
	virtual ~FinishTaskCommand();
	virtual void Execute();

private:
	NotePadFormControlWnd* notePadFormControlWnd;
	NotePadForm* notePadForm;
};
#endif // !_FINISHTASKCOMMAND_H
