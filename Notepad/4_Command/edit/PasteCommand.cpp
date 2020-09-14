//PasteCommand.cpp

#include"PasteCommand.h"
#include"SelectionEraseSupervisor.h"
#include"PasteSupervisor.h"
#include"NotePadMaker.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"TextMetric.h"
#include"Selector.h"
#include"GlyphFactory.h"
#include"DummyRow.h"
#include"NotePadMementoMaker.h"
#include"HistoryReconstructor.h"
#include"NotePadRestorer.h"
#include"StringMaker.h"

PasteCommand::PasteCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm):Command(notePadForm) {
	this->notePadFormControlWnd = notePadFormControlWnd;
	this->notePadForm = notePadForm;
}

PasteCommand::~PasteCommand() {

}


void PasteCommand::Execute() {
	if (this->notePadForm->GetIsComposition() == true) {
		this->notePadForm->SetIsComposition(false);
	}
	if (this->notePadForm->GetIsSelected() == true) {
		SelectionEraseSupervisor selectionEraseSupervisor(this->notePadForm);
		StringMaker stringMaker(this->notePadForm);
		string* contents = new string(stringMaker.MakeStringInSelectedArea());
		selectionEraseSupervisor.EraseContents(contents, false);


		this->notePadForm->SetIsSelected(false);
		if (this->notePadForm->GetSelector() != 0) {
			delete this->notePadForm->GetSelector();
		}
		Selector* selector = new Selector(this->notePadForm);
		this->notePadForm->SetSelector(selector);
	}

	unsigned int priority_list = CF_TEXT;
	char* p_string = NULL;
	// Ŭ�����忡�� ���ڿ��� �����Ҽ� �ִ°��� �ƴϱ� ������ 
	// ���� ���ڿ��� ����Ǿ� �ִ��� Ȯ���Ѵ�. 
	if (::GetPriorityClipboardFormat(&priority_list, 1) == CF_TEXT) {
		// Ŭ�����忡 �ִ� ��Ʈ�� ������ ��� ���ؼ� Ŭ�����带 ����. 
		if (::OpenClipboard(this->notePadForm->m_hWnd)) {
			// Ŭ�����忡�� ���ڿ��� ����� �޸��� �ڵ� ���� ��´�. 
			HANDLE h_clipboard_data = ::GetClipboardData(CF_TEXT);
			if (h_clipboard_data != NULL) {
				// �޸� �ڵ� ���� �̿��Ͽ� ���� ��밡���� �ּҸ� ��´�. 
				char* p_clipboard_data = (char*)::GlobalLock(h_clipboard_data);
				// Ŭ�����忡 ����� ���ڿ��� ���̸� ���Ѵ�. ('\0'���� ũ��) 
				int string_len = strlen(p_clipboard_data) + 1;
				// Ŭ�����忡 ����� ���ڿ��� �����ϱ� ���� �޸𸮸� �Ҵ��Ѵ�. 
				p_string = new char[string_len];
				// �Ҵ�� �޸𸮿� Ŭ������ ���ڿ��� �����Ѵ�.
				memcpy(p_string, p_clipboard_data, string_len);
				// ���ڿ��� �����ϱ� ���ؼ� Lock�ߴ� �޸𸮸� �����Ѵ�.
				::GlobalUnlock(h_clipboard_data);
			}
			// Ŭ�����带 �ݴ´�. 
			::CloseClipboard();

			string contents(p_string);

			char(*buffer) = 0;
			buffer = (char*)(contents.c_str());

			NotePadMementoMaker notePadMementoMaker(this->notePadForm);
			ConstraintSolverMemento* constraintSolverMemento = 0;
			NotePadRestorer* notePadRestorer = this->notePadForm->GetNotePadRestorer();

			if (this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent() != this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetLength()) {
				HistoryReconstructor historyReconstructor(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory(), this->notePadForm);
				historyReconstructor.ReconstructHistory();
			}
			notePadRestorer->GetNotePadHistory()->MoveLastHistory();
			string* cloneContents = new string(contents);
			constraintSolverMemento = notePadMementoMaker.MakeMemento(true, false, -1, -1, cloneContents);
			notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);

			PasteSupervisor pasteSupervisor(this->notePadForm);
			pasteSupervisor.PasteContents(buffer);

			constraintSolverMemento = notePadMementoMaker.MakeMemento(true, false, -1, -1, cloneContents);
			notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);
		}
	}
}