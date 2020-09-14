//OtherNameSaveCommand.h

#include"OtherNameSaveCommand.h"
#include"File.h"
#include"NotePad.h"
#include"NotePadFormControlWnd.h"
#include<afxdlgs.h>
#include <string>

OtherNameSaveCommand::OtherNameSaveCommand(NotePadForm* notePadForm) :Command(notePadForm) {
	this->notePadForm = notePadForm;

}

OtherNameSaveCommand::~OtherNameSaveCommand() {

}

void OtherNameSaveCommand::Execute() {

	string captionBuffer = "";
	HWND hWnd;
	File file(this->notePadForm);
	hWnd = ((CWnd*)(this->notePadForm))->m_hWnd;
	GetWindowText(hWnd, (char*)captionBuffer.c_str(), 100);
	
	CFileDialog cFileDialog(false);

	OPENFILENAME& openFileName = cFileDialog.GetOFN();
	openFileName.Flags |= OFN_OVERWRITEPROMPT;
	openFileName.lpstrFilter = "Every File(*.*)\0*.*\0텍스트 문서(*.txt)\0*.txt;*.doc\0";


	if (cFileDialog.DoModal() == IDOK) {
		string fileName = "";
		fileName = openFileName.lpstrFile;	
		string filePath = openFileName.lpstrFile;
		string fileTitle = openFileName.lpstrFileTitle;

		this->notePadForm->SetFilePath(filePath);
		this->notePadForm->SetFileTitle(fileTitle);
		file.Save((char*)fileName.c_str(), ((NotePad*)(this->notePadForm->notePad))->SaveModeGetContents());
		this->notePadForm->GetNotePadFormControlWnd()->SetWindowText((char*)this->notePadForm->GetFileTitle().c_str());
	}
	this->notePadForm->GetNotePadFormControlWnd()->SetNoNeedToScroll(true);
}