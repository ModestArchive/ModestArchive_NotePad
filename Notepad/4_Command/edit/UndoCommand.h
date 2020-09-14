//UndoCommand.h

#ifndef _UNDOCOMMAND_H
#define _UNDOCOMMAND_H

#include "Command.h"
class NotePadFormControlWnd;

class UndoCommand :public Command {

public:
	UndoCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm);
	virtual ~UndoCommand();
	virtual void Execute();

private:
	NotePadFormControlWnd* notePadFormControlWnd;
	NotePadForm* notePadForm;
};
#endif // !_NEWWINDOWCOMMAND_H
