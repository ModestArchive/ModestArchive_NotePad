//FontSizeExpandCommand.h

#ifndef _FONTSIZEEXPANDCOMMAND_H
#define _FONTSIZEEXPANDCOMMAND_H
#include"Command.h"
class NotePadForm;

class FontSizeExpandCommand :public Command{
public:
	//������,�Ҹ���
	FontSizeExpandCommand(NotePadForm* notePadForm);
	virtual ~FontSizeExpandCommand();
	//�޼ҵ�
	virtual void Execute();
private:
	NotePadForm* notePadForm;
};
#endif // !_FONTSIZEEXPANDCOMMAND_H

