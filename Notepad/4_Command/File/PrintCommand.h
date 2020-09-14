//Printer.h

#ifndef _PRINTCOMMAND_H
#define _PRINTCOMMAND_H

#include"NotePadForm.h"
#include"NotePadFormControlWnd.h"
#include"Command.h"
class PrintCommand :public Command{
public:
	PrintCommand(NotePadFormControlWnd* notePadFormControlWnd,NotePadForm* notePadForm);
	virtual ~PrintCommand();

	virtual void Execute();
private:
	NotePadFormControlWnd* notePadFormControlWnd;
	NotePadForm* notePadForm;
};
#endif // !_PRINTCOMMAND_H

