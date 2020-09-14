//LineBreakCommand.h

#ifndef _LINEBREAKCOMMAND_H
#define _LINEBREAKCOMMAND_H

#include"Command.h"

class LineBreakCommand :public Command {
public:
	LineBreakCommand(NotePadForm* notePadForm = 0);
	virtual ~LineBreakCommand();
	virtual void Execute();
	
private:
	NotePadForm* notePadForm;

};
#endif // !_LINEBREAKCOMMAND_H

