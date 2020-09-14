//FontSizeInitializeCommand.h

#ifndef _FONTSIZEINITIALIZECOMMAND_H
#define _FONTSIZEINITIALIZECOMMAND_H
#include"Command.h"
class NotePadForm;
class FontSizeInitializeCommand :public Command{
public:
	//持失切,社瑚切
	FontSizeInitializeCommand(NotePadForm* notePadForm);
	virtual ~FontSizeInitializeCommand();
	//五社球
	virtual void Execute(); 
private:
	NotePadForm* notePadForm;
};
#endif // !_FONTSIZEINITIALIZECOMMAND_H
