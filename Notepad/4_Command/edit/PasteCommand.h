//PasteCommand.h

#ifndef _PASTECOMMAND_H
#define _PASTECOMMAND_H

#include "Command.h"
class NotePadFormControlWnd;

class PasteCommand :public Command {

public:
	PasteCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm);
	virtual ~PasteCommand();
	virtual void Execute();

private:
	NotePadFormControlWnd* notePadFormControlWnd;
	NotePadForm* notePadForm;
};
#endif // !_PASTECOMMAND_H

