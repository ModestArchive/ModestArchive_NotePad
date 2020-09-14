//ReplaceContentCommand.h

#ifndef _REPLACECONTENTCOMMAND_H
#define _REPLACECONTENTCOMMAND_H
#include"Command.h"

class ContentsFinder;
class NotePadFormControlWnd;
class ReplaceContentCommand :public Command {
public:
	ReplaceContentCommand(NotePadFormControlWnd* notePadFormControlWnd,NotePadForm* notePadForm);
	virtual ~ReplaceContentCommand();
	virtual void Execute();

private:
	NotePadFormControlWnd* notePadFormControlWnd;
	NotePadForm* notePadForm;
};
#endif // !_REPLACECONTENTCOMMAND_H
