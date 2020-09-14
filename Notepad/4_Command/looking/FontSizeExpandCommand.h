//FontSizeExpandCommand.h

#ifndef _FONTSIZEEXPANDCOMMAND_H
#define _FONTSIZEEXPANDCOMMAND_H
#include"Command.h"
class NotePadForm;

class FontSizeExpandCommand :public Command{
public:
	//持失切,社瑚切
	FontSizeExpandCommand(NotePadForm* notePadForm);
	virtual ~FontSizeExpandCommand();
	//五社球
	virtual void Execute();
private:
	NotePadForm* notePadForm;
};
#endif // !_FONTSIZEEXPANDCOMMAND_H

