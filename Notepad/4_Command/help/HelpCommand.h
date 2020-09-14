//HelpCommand.h

#ifndef _HELPCOMMAND_H
#define _HELPCOMMAND_H

#include"Command.h"

class HelpCommand :public Command {
public:
	HelpCommand(NotePadForm* notePadForm = 0);
	virtual ~HelpCommand();
	virtual void Execute();

private:
	NotePadForm* notePadForm;

};
#endif // !_LINEBREAKCOMMAND_H
