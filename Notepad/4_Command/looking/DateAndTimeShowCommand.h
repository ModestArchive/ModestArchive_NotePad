//DateAndTimeShowCommand.h

#ifndef _DATEANDTIMESHOWCOMMAND_H
#define _DATEANDTIMESHOWCOMMAND_H

#include"NotePadForm.h"
#include"Command.h"

class DateAndTimeShowCommand : public Command{
public:
	DateAndTimeShowCommand(NotePadForm* notePadForm);
	virtual ~DateAndTimeShowCommand();

	//¸Þ¼Òµå
	virtual void Execute();

private:
	NotePadForm* notePadForm;
};
#endif // !_DATEANDTIMESHOWCOMMAND_H

