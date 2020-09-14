//NewWindowCommand.cpp
#include"NewWindowCommand.h"
#include<Windows.h>
NewWindowCommand::NewWindowCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm) :Command(notePadForm) {
	this->notePadFormControlWnd = notePadFormControlWnd;
	this->notePadForm = notePadForm;
}

NewWindowCommand::~NewWindowCommand() {

}

void NewWindowCommand::Execute() {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi,sizeof(pi));
	char szUserName[100];
	unsigned long dwLength = 100;
	GetUserName(szUserName,&dwLength);
	CString path = "C:\\Users\\";
	path += szUserName;
	path += "\\Desktop\\메모장Setup\\2020_08_17_NotePadForm.exe";
	CreateProcess(path,NULL,
		            NULL,NULL,FALSE,0,NULL,NULL,&si,&pi);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

}//"C:\\Users\\LJh\\Desktop\\메모장.exe"