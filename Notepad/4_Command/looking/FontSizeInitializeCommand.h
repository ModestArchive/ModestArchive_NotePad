//FontSizeInitializeCommand.h

#ifndef _FONTSIZEINITIALIZECOMMAND_H
#define _FONTSIZEINITIALIZECOMMAND_H
#include"Command.h"
class NotePadForm;
class FontSizeInitializeCommand :public Command{
public:
	//������,�Ҹ���
	FontSizeInitializeCommand(NotePadForm* notePadForm);
	virtual ~FontSizeInitializeCommand();
	//�޼ҵ�
	virtual void Execute(); 
private:
	NotePadForm* notePadForm;
};
#endif // !_FONTSIZEINITIALIZECOMMAND_H
