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
		// 할당된 메모리에 문자열을 복사하기 위해서 사용 가능한 주소를 얻는다. 
		char* p_data = (char*)::GlobalLock(h_data);
		if (NULL != p_data) {
			// 할당된 메모리 영역에 삽입할 문자열을 복사한다. 
			memcpy(p_data, (char*)contents.c_str(), contents_length);
			// 문자열을 복사하기 위해서 Lock 했던 메모리를 해제한다. 
			::GlobalUnlock(h_data);
			if (::OpenClipboard(this->notePadForm->m_hWnd)) {
				// 클립보드를 연다. 
				::EmptyClipboard();
				// 클립보드에 저장된 기존 문자열을 삭제한다. 
				::SetClipboardData(CF_TEXT, h_data);
				// 클립보드로 문자열을 복사한다. 
				::CloseClipboard(); // 클립보드를 닫는다.
			}
		}
	}
}