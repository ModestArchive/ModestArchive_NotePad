//FindPreviousCommand.h

#ifndef _FINDPREVIOUSCOMMAND_H
#define _FINDPREVIOUSCOMMAND_H

#include "Command.h"
class NotePadFormControlWnd;

class FindPreviousCommand :public Command {

public:
	FindPreviousCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm);
	virtual ~FindPreviousCommand();
	virtual void Execute();

private:
	NotePadFormControlWnd* notePadFormControlWnd;
	NotePadForm* notePadForm;
};
#endif // !_FINDPREVIOUSCOMMAND_H

