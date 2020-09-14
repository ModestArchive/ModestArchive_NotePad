//NaverHyperLinkCommand.h

#ifndef _NAVERHYPERLINKCOMMAND_H
#define _NAVERHYPERLINKCOMMAND_H

#include "Command.h"
class NotePadFormControlWnd;

class NaverHyperLinkCommand :public Command {

public:
	NaverHyperLinkCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm);
	virtual ~NaverHyperLinkCommand();
	virtual void Execute();

private:
	NotePadFormControlWnd* notePadFormControlWnd;
	NotePadForm* notePadForm;
};
#endif // !_NAVERHYPERLINKCOMMAND_H
