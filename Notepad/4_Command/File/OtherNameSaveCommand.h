//OtherNameSaveCommand.h

#ifndef _OTHERNAMESAVECOMMAND_H
#define _OTHERNAMESAVECOMMAND_H

#include"Command.h"
#include"NotePadForm.h"

class OtherNameSaveCommand :public Command {

public:
	OtherNameSaveCommand(NotePadForm* notePadForm=0);
	virtual ~OtherNameSaveCommand();
	virtual void Execute();

private:
	NotePadForm* notePadForm;
};
#endif // !_OTHERNAMESAVECOMMAND_H
