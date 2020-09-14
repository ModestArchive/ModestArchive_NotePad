//SaveCommand.cpp

#include "SaveCommand.h"
#include"File.h"
#include"NotePad.h"
#include<afxdlgs.h>
#include <string>
using namespace std;


SaveCommand::SaveCommand(NotePadFormControlWnd* notePadFormControlWnd,NotePadForm* notePadForm) :Command(notePadForm) {
	this->notePadFormControlWnd = notePadFormControlWnd;
	this->notePadForm = notePadForm;
}

SaveCommand::~SaveCommand() {


}

void SaveCommand::Execute() {
	//HWND hWnd;
	//hWnd = ((CWnd*)(this->notePadForm))->m_hWnd;

	File file(this->notePadForm);
	string captionBuffer = "";
	string originalBuffer = " 제목 없음 - 메모장 ";
	this->notePadFormControlWnd->GetWindowText((char*)captionBuffer.c_str(),100);

	if (strcmp((char*)captionBuffer.c_str(), (char*)originalBuffer.c_str())==0) {
		
		CFileDialog cFileDialog(false);
		OPENFILENAME& openFileName= cFileDialog.GetOFN();
		openFileName.Flags |= OFN_OVERWRITEPROMPT;
		openFileName.lpstrFilter = "Every File(*.*)\0*.*\0Text File(*.txt)\0*.txt;*.doc\0";
		openFileName.lpstrDefExt = ".txt";

		if (cFileDialog.DoModal() == IDOK) {

			string filePath =  openFileName.lpstrFile;
			string fileTitle = openFileName.lpstrFileTitle;

			this->notePadForm->SetFilePath(filePath);
			this->notePadForm->SetFileTitle(fileTitle);
			file.Save((char*)this->notePadForm->GetFilePath().c_str(), ((NotePad*)(this->notePadForm->notePad))->SaveModeGetContents());
			this->notePadForm->GetNotePadFormControlWnd()->SetWindowText((char*)this->notePadForm->GetFileTitle().c_str());
		}
	}
	else {
		file.Save((char*)this->notePadForm->GetFilePath().c_str(), ((NotePad*)(this->notePadForm->notePad))->SaveModeGetContents());
	}
	this->notePadForm->GetNotePadFormControlWnd()->SetNoNeedToScroll(true);
}
