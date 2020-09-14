//DeleteSelectionCommand.h

#ifndef _DELETESELECTIONCOMMAND_H
#define _DELETESELECTIONCOMMAND_H

#include "Command.h"
class NotePadFormControlWnd;

class DeleteSelectionCommand :public Command {

public:
	DeleteSelectionCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm);
	virtual ~DeleteSelectionCommand();
	virtual void Execute();

private:
	NotePadFormControlWnd* notePadFormControlWnd;
	NotePadForm* notePadForm;
};
#endif // !_DELETESELECTIONCOMMAND_H
