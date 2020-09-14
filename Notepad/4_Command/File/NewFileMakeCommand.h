//NewFileMakeCommand.h

#ifndef _NEWFILEMAKECOMMAND_H
#define _NEWFILEMAKECOMMAND_H

#include "Command.h"
class NotePadFormControlWnd;

class NewFileMakeCommand :public Command {

public:
	NewFileMakeCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm);
	virtual ~NewFileMakeCommand();
	virtual void Execute();

private:
	NotePadFormControlWnd* notePadFormControlWnd;
	NotePadForm* notePadForm;
};
#endif // !_NEWFILEMAKECOMMAND_H
