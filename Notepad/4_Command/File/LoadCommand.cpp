//LoadCommand.cpp
#include"LoadCommand.h"
#include<string.h>
#include<iostream>
#include<afxdlgs.h>
#include<afxdialogex.h>
#include"CMyDialog.h"
#include"File.h"
#include"GlyphFactory.h"
#include"NotePadMaker.h"
#include"ScrollController.h"
#include"NotePadFormControlWnd.h"
#include"NotePad.h"
using namespace std;

LoadCommand::LoadCommand(NotePadForm* notePadForm) :Command(notePadForm) {
	
	this->notePadForm = notePadForm;
}

LoadCommand::~LoadCommand() {

}

void LoadCommand::Execute() {
	
	File file(this->notePadForm);
	HWND hWnd;
	hWnd = ((CWnd*)(this->notePadForm->GetParent()))->m_hWnd;
	string captionBuffer = "";
	GetWindowText(hWnd,(char*)captionBuffer.c_str(), 100);
	string originalBuffer = " 제목 없음 - 메모장 ";
	string nullString = "";
	Long ret = 0;

	if (strcmp((char*)captionBuffer.c_str(), (char*)originalBuffer.c_str()) == 0) {
		if (strcmp((char*)this->notePadForm->notePad->GetContents().c_str(), (char*)nullString.c_str()) != 0) {
			CMyDialog cMyDialog(this->notePadForm);
			
			ret=cMyDialog.DoModal();
		}
		else {
			ret = 0;
		}
	}
	else {
		string contents = ((NotePad*)(this->notePadForm->notePad))->SaveModeGetContents();
		string fileContents = file.Load((char*)(this->notePadForm->GetFilePath().c_str()));

		if (strcmp((char*)contents.c_str(),(char*)fileContents.c_str())!= 0) {
			CMyDialog cMyDialog(this->notePadForm);
			
			ret=cMyDialog.DoModal();
		}
		else {
			ret = 0;
		}
	}
	if (ret == 0) {
		CFileDialog cFileLoadDialog(TRUE);
		OPENFILENAME& openFileName = cFileLoadDialog.GetOFN();
		openFileName.Flags |= OFN_OVERWRITEPROMPT;
		openFileName.lpstrFilter = "Every File(*.*)\0*.*\0Text File(*.txt)\0*.txt;*.doc\0";
		openFileName.lpstrDefExt = "txt";
		
	
		if (cFileLoadDialog.DoModal() == IDOK) {
			
			string loadFilePath = openFileName.lpstrFile;
			string loadFileName = openFileName.lpstrFileTitle;

			this->notePadForm->SetFilePath(loadFilePath);
			this->notePadForm->SetFileTitle(loadFileName);

			string contents = "";
            contents=file.Load((char*)this->notePadForm->GetFilePath().c_str());

			if (this->notePadForm->notePad != 0) {
				delete this->notePadForm->notePad;
			}
			NotePadMaker notePadMaker(this->notePadForm);
			notePadMaker.MakeNotePad(contents);
			this->notePadForm->GetNotePadFormControlWnd()->SetWindowText((char*)this->notePadForm->GetFileTitle().c_str());/////////////

			//this->notePadForm->GetScrollController()->MoveHScrFirst();
			//this->notePadForm->GetScrollController()->MoveVScrFirst();
			this->notePadForm->GetNotePadFormControlWnd()->SetNoNeedToScroll(false);
		}
		else {
			this->notePadForm->GetNotePadFormControlWnd()->SetNoNeedToScroll(true);
		}
	}
}