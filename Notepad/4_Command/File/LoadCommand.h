//LoadCommand.h

#ifndef _LOADCOMMAND_H
#define _LOADCOMMAND_H

#include"Command.h"

class LoadCommand :public Command {
public:
	LoadCommand(NotePadForm* notePadForm = 0);
	virtual ~LoadCommand();
	virtual void Execute();
	

private:
	NotePadForm* notePadForm;

};
#endif // !_LOADCOMMAND_H
