//FontConfigureCommand.h

#ifndef _FONTCONFIGURECOMMAND_H
#define _FONTCONFIGURECOMMAND_H

#include"Command.h"

class FontConfigureCommand :public Command {
public:
	FontConfigureCommand(NotePadForm* notePadForm = 0);
	virtual ~FontConfigureCommand();
	virtual void Execute();


private:
	NotePadForm* notePadForm;

};
#endif // !_FONTCONFIGURECOMMAND_H

