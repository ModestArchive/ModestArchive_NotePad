//CopySelectionCommand.cpp

#include"CopySelectionCommand.h"
#include"StringMaker.h"

CopySelectionCommand::CopySelectionCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm) :Command(notePadForm){
	this->notePadFormControlWnd = notePadFormControlWnd;
	this->notePadForm = notePadForm;
}


CopySelectionCommand::~CopySelectionCommand() {

}

void CopySelectionCommand::Execute() {
	if (this->notePadForm->GetIsSelected() == true) {

		StringMaker stringMaker(this->notePadForm);
		string contents = stringMaker.MakeStringInSelectedArea();

		int contents_length = strlen((char*)contents.c_str()) + 1;
		HANDLE h_data = ::GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, contents_length);
		// �Ҵ�� �޸𸮿� ���ڿ��� �����ϱ� ���ؼ� ��� ������ �ּҸ� ��´�. 
		char* p_data = (char*)::GlobalLock(h_data);
		if (NULL != p_data) {
			// �Ҵ�� �޸� ������ ������ ���ڿ��� �����Ѵ�. 
			memcpy(p_data, (char*)contents.c_str(), contents_length);
			// ���ڿ��� �����ϱ� ���ؼ� Lock �ߴ� �޸𸮸� �����Ѵ�. 
			::GlobalUnlock(h_data);
			if (::OpenClipboard(this->notePadForm->m_hWnd)) {
				// Ŭ�����带 ����. 
				::EmptyClipboard();
				// Ŭ�����忡 ����� ���� ���ڿ��� �����Ѵ�. 
				::SetClipboardData(CF_TEXT, h_data);
				// Ŭ������� ���ڿ��� �����Ѵ�. 
				::CloseClipboard(); // Ŭ�����带 �ݴ´�.
			}
		}
	}
}