//SaveCommand.h

#ifndef _SAVECOMMAND_H
#define _SAVECOMMAND_H

#include"Command.h"
#include"NotePadForm.h"
#include"NotePadFormControlWnd.h"
class SaveCommand : public Command {
public:
	SaveCommand(NotePadFormControlWnd* notePadFormControlWnd,NotePadForm* notePadForm);
	virtual ~SaveCommand();
	virtual void Execute();

private:
	NotePadForm* notePadForm;
	NotePadFormControlWnd* notePadFormControlWnd;
};
#endif // !_SAVECOMMAND_H
