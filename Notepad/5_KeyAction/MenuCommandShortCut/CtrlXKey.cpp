//CtrlXKey.cpp

#include"CtrlXKey.h"
#include"SelectionEraseSupervisor.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"TextMetric.h"
#include"Selector.h"
#include"GlyphFactory.h"
#include"DummyRow.h"
#include"SingleByteCharacter.h"
#include"Font.h"
#include"NotePadForm.h"
#include"NotePadRestorer.h"
#include"NotePadMementoMaker.h"
#include"HistoryReconstructor.h"
#include"StringMaker.h"

CtrlXKey::CtrlXKey() {
	
}

CtrlXKey::CtrlXKey(NotePadForm* notePadForm) : KeyAction(notePadForm) {

}


CtrlXKey::~CtrlXKey() {

}


void CtrlXKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (this->notePadForm->GetIsSelected() == true) {
		StringMaker stringMaker(this->notePadForm);
		string contents(stringMaker.MakeStringInSelectedArea());

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
		string* cloneContents = new string(contents);
		SelectionEraseSupervisor selectionEraseSupervisor(this->notePadForm);
		selectionEraseSupervisor.EraseContentsForCtrlX(cloneContents);

		TextMetric textMetric(this->notePadForm);
		Font font(this->notePadForm);
		TEXTMETRIC tm = { 0, };
		tm = font.CalculateFontMetric();
		
		this->notePadForm->SetIsSelected(false);
		if (this->notePadForm->GetSelector() != 0) {
			delete this->notePadForm->GetSelector();
		}
		this->notePadForm->SetSelector(new Selector(this->notePadForm));

		this->notePadForm->Notify();

		if (textMetric.GetX(this->notePadForm->row,this->notePadForm->row->GetCurrent())+tm.tmAveCharWidth/4<=this->notePadForm->GetScrollController()->GetHPosition()) {
			while (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent())+ tm.tmAveCharWidth / 4 <=  this->notePadForm->GetScrollController()->GetHPosition()) {
				this->notePadForm->GetScrollController()->MoveHScrPrevious();
			}
			Long iteratorControlVariable = 0;
			while (iteratorControlVariable < 8) {
				this->notePadForm->GetScrollController()->MoveHScrPrevious();
				iteratorControlVariable++;
			}
		}
		if (textMetric.GetY(this->notePadForm->notePad->GetCurrent())+tm.tmHeight+5 <= this->notePadForm->GetScrollController()->GetVPosition()) {
			while (textMetric.GetY(this->notePadForm->notePad->GetCurrent()) + tm.tmHeight + 5 <= this->notePadForm->GetScrollController()->GetVPosition()) {
				this->notePadForm->GetScrollController()->MoveVScrPrevious();
			}
			Long i= 0;
			while (i< 3) {
				this->notePadForm->GetScrollController()->MoveVScrPrevious();
				i++;
			}
		}
	
	}
}