//CutSelectionCommand.h

#ifndef _CUTSELECTIONCOMMAND_H
#define _CUTSELECTIONCOMMAND_H

#include "Command.h"
class NotePadFormControlWnd;

class CutSelectionCommand :public Command {

public:
	CutSelectionCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm);
	virtual ~CutSelectionCommand();
	virtual void Execute();

private:
	NotePadFormControlWnd* notePadFormControlWnd;
	NotePadForm* notePadForm;
};
#endif // !_CUTSELECTIONCOMMAND_H

