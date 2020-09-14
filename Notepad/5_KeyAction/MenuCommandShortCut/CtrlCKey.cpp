//CtrlCKey.cpp

#include"CtrlCKey.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"TextMetric.h"
#include"Selector.h"
#include"GlyphFactory.h"
#include"DummyRow.h"
#include"SingleByteCharacter.h"
#include"StringMaker.h"

CtrlCKey::CtrlCKey() {


}

CtrlCKey::CtrlCKey(NotePadForm* notePadForm) : KeyAction(notePadForm) {

}


CtrlCKey::~CtrlCKey() {

}


void CtrlCKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (this->notePadForm->GetIsSelected()==true) {

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