//CMyDialog.cpp

#include"CMyDialog.h"
#include<afxdlgs.h>
#include<afxdialogex.h>
#include"NotePad.h"
#include"File.h"
#include"GlyphFactory.h"
#include"NotePadMaker.h"
#include<string.h>
#include<iostream>
#include"resource.h"
#include"NotePadFormControlWnd.h"
using namespace std;

BEGIN_MESSAGE_MAP(CMyDialog,CDialog)
	ON_BN_CLICKED(IDC_SAVE, OnSaveButtonClicked)
	ON_BN_CLICKED(IDC_NOSAVE, OnNoSaveButtonClicked)
	ON_BN_CLICKED(IDC_CANCEL, OnCancelButtonClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

CMyDialog::CMyDialog(NotePadForm* notePadForm , CWnd* parent ) :CDialog(CMyDialog::IDD, parent) {
	this->notePadForm = notePadForm;
}

BOOL CMyDialog::OnInitDialog() {
	 CDialog::OnInitDialog();

	CFont font;
	font.CreateFont(80,50,0,0,1,0,0,0,0, OUT_DEFAULT_PRECIS, 
		0,DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
		"consolas"); 
	this->GetDlgItem(IDC_STATIC)->SetFont(&font);

	string captionBuffer = "";
	string originalBuffer = " 제목 없음 - 메모장 ";
	this->notePadForm->GetParent()->GetWindowText((char*)captionBuffer.c_str(), 100);////////////////
	
	if(strcmp((char*)captionBuffer.c_str(), (char*)originalBuffer.c_str())==0){
		string information = " 변경 내용을 제목 없음에 저장하시겠습니까? ";
		this->GetDlgItem(IDC_STATIC)->SetWindowText((char*)information.c_str());
	}
	else {
		string information = "";
		information += " 변경 내용을 ";
		information += this->notePadForm->GetFilePath();
		information += " 에 저장하시겠습니까? ";
		this->GetDlgItem(IDC_STATIC)->SetWindowText((char*)information.c_str());
	}

	return FALSE;
}


void CMyDialog::OnSaveButtonClicked() {
	
	File file(this->notePadForm);
	string captionBuffer = "";
	string originalBuffer = " 제목 없음 - 메모장 ";
	this->notePadForm->GetParent()->GetWindowText((char*)captionBuffer.c_str(), 100);


	if (strcmp((char*)captionBuffer.c_str(), (char*)originalBuffer.c_str())==0) {

		CFileDialog cFileSaveDialog(false);
		OPENFILENAME& openFileName = cFileSaveDialog.GetOFN();
		openFileName.Flags |= OFN_OVERWRITEPROMPT;
		openFileName.lpstrFilter = "Every File(*.*)\0*.*\0Text File(*.txt)\0*.txt;*.doc\0";
		openFileName.lpstrDefExt = "txt";

		if (cFileSaveDialog.DoModal() == IDOK) {

			string filePath = openFileName.lpstrFile;
			string fileTitle = openFileName.lpstrFileTitle;

			this->notePadForm->SetFilePath(filePath);
			this->notePadForm->SetFileTitle(fileTitle);

			file.Save((char*)this->notePadForm->GetFilePath().c_str(), ((NotePad*)(this->notePadForm->notePad))->SaveModeGetContents());
			this->notePadForm->GetParent()->SetWindowText((char*)this->notePadForm->GetFileTitle().c_str());//////////////
			this->EndDialog(0);
		}
		else{
			this->EndDialog(1);
		}
	}
	else {
		file.Save((char*)this->notePadForm->GetFilePath().c_str(), ((NotePad*)(this->notePadForm->notePad))->SaveModeGetContents());
		this->EndDialog(0);
	}
	this->notePadForm->GetNotePadFormControlWnd()->SetNoNeedToScroll(true);
	
}

void CMyDialog::OnNoSaveButtonClicked() {

	this->EndDialog(0);
	this->notePadForm->GetNotePadFormControlWnd()->SetNoNeedToScroll(true);
}

void CMyDialog::OnCancelButtonClicked() {
	this->EndDialog(1);
	this->notePadForm->GetNotePadFormControlWnd()->SetNoNeedToScroll(true);
}

void CMyDialog::OnClose() {
	this->EndDialog(1);
	this->notePadForm->GetNotePadFormControlWnd()->SetNoNeedToScroll(true);
}