//FontSizeDownsizeCommand.h

#ifndef _FONTSIZEDOWNSIZECOMMAND_H
#define _FONTSIZEDOWNSIZECOMMAND_H
#include"Command.h"
class NotePadForm;
class FontSizeDownsizeCommand :public Command{
public:
	//持失切,社瑚切
	FontSizeDownsizeCommand(NotePadForm* notePadForm);
	virtual ~FontSizeDownsizeCommand();
	//五社球
	virtual void Execute();
private:
	NotePadForm* notePadForm;
};
#endif // !_FONTSIZEEXPANDCOMMAND_H


