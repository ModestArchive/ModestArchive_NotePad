//CopySelectionCommand.h

#ifndef _COPYSELECTIONCOMMAND_H
#define _COPYSELECTIONCOMMAND_H

#include "Command.h"
class NotePadFormControlWnd;

class CopySelectionCommand :public Command {

public:
	CopySelectionCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm);
	virtual ~CopySelectionCommand();
	virtual void Execute();

private:
	NotePadFormControlWnd* notePadFormControlWnd;
	NotePadForm* notePadForm;
};
#endif // !_COPYSELECTIONCOMMAND_H
