//FindNextCommand.h

#ifndef _FINDNEXTCOMMAND_H
#define _FINDNEXTCOMMAND_H

#include "Command.h"
class NotePadFormControlWnd;

class FindNextCommand :public Command {

public:
	FindNextCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm);
	virtual ~FindNextCommand();
	virtual void Execute();

private:
	NotePadFormControlWnd* notePadFormControlWnd;
	NotePadForm* notePadForm;
};
#endif // !_FINDNEXTCOMMAND_H


