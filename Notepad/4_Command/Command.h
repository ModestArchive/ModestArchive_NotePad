//Command.h

#ifndef _COMMAND_H
#define _COMMAND_H

#include "NotePadForm.h"
class NotePadForm;
class Command {
public:

	virtual ~Command();
	virtual void Execute() = 0;

protected:
	Command(NotePadForm* notePadForm);
protected:
	NotePadForm* notePadForm;
};
#endif // !_COMMAND_H

