//HelpCommand.cpp
#include"HelpCommand.h"

HelpCommand::HelpCommand(NotePadForm* notePadForm):Command(notePadForm) {

}


HelpCommand::~HelpCommand() {

}


void HelpCommand::Execute() {
	char szUserName[100];
	unsigned long dwLength = 100;
	GetUserName(szUserName, &dwLength);
	CString path = "C:\\Users\\";
	path += szUserName;
	path += "\\Desktop\\메모장Setup\\도움말1.chm";
	//CString path ="C:\\Users\\LJh\\source\\repos\\2020_08_17_NotePadForm\\Release\\도움말1.chm";
	::ShellExecute(NULL, "open", path, 0, 0, SW_SHOW);
}
//"C:\\Program Files(x86)\\NotePadFormSetup\\도움말1.chm"
//C:\\Users\\LJh\\source\\repos\\2020_08_17_NotePadForm\\Release\\도움말1.chm
