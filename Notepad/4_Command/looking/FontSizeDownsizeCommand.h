//FontSizeDownsizeCommand.h

#ifndef _FONTSIZEDOWNSIZECOMMAND_H
#define _FONTSIZEDOWNSIZECOMMAND_H
#include"Command.h"
class NotePadForm;
class FontSizeDownsizeCommand :public Command{
public:
	//������,�Ҹ���
	FontSizeDownsizeCommand(NotePadForm* notePadForm);
	virtual ~FontSizeDownsizeCommand();
	//�޼ҵ�
	virtual void Execute();
private:
	NotePadForm* notePadForm;
};
#endif // !_FONTSIZEEXPANDCOMMAND_H


