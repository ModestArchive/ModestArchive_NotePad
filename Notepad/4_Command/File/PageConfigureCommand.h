//PageConfigureCommand.h

#ifndef _PAGECONFIGURECOMMAND_H
#define _PAGECONFIGURECOMMAND_H

#include "Command.h"
class NotePadFormControlWnd;

class PageConfigureCommand :public Command {

public:
	PageConfigureCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm);
	virtual ~PageConfigureCommand();
	virtual void Execute();

private:
	NotePadFormControlWnd* notePadFormControlWnd;
	NotePadForm* notePadForm;
};
#endif // !_PAGECONFIGURECOMMAND_H
