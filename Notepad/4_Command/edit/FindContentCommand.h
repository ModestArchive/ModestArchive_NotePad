//FindContentCommand.h

#ifndef _FINDCONTENTCOMMAND_H
#define _FINDCONTENTCOMMAND_H

#include "Command.h"
class NotePadFormControlWnd;
class ContentsFinder;

class FindContentCommand :public Command {

public:
	FindContentCommand(NotePadFormControlWnd* notePadFormControlWnd,NotePadForm* notePadForm);
	virtual ~FindContentCommand();
	virtual void Execute();

private:
	NotePadFormControlWnd* notePadFormControlWnd;
	NotePadForm* notePadForm;
};
#endif // !_FINDCONTENTCOMMAND_H
