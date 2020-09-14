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
	// 클립보드에는 문자열만 저장할수 있는것이 아니기 때문에 
	// 현재 문자열이 저장되어 있는지 확인한다. 
	if (::GetPriorityClipboardFormat(&priority_list, 1) == CF_TEXT) {
		// 클립보드에 있는 비트맵 정보를 얻기 위해서 클립보드를 연다. 
		if (::OpenClipboard(this->notePadForm->m_hWnd)) {
			// 클립보드에서 문자열이 저장된 메모리의 핸들 값을 얻는다. 
			HANDLE h_clipboard_data = ::GetClipboardData(CF_TEXT);
			if (h_clipboard_data != NULL) {
				// 메모리 핸들 값을 이용하여 실제 사용가능한 주소를 얻는다. 
				char* p_clipboard_data = (char*)::GlobalLock(h_clipboard_data);
				// 클립보드에 저장된 문자열의 길이를 구한다. ('\0'포함 크기) 
				int string_len = strlen(p_clipboard_data) + 1;
				// 클립보드에 저장된 문자열을 저장하기 위해 메모리를 할당한다. 
				p_string = new char[string_len];
				// 할당된 메모리에 클리보드 문자열을 복사한다.
				memcpy(p_string, p_clipboard_data, string_len);
				// 문자열을 복사하기 위해서 Lock했던 메모리를 해제한다.
				::GlobalUnlock(h_clipboard_data);
			}
			// 클립보드를 닫는다. 
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