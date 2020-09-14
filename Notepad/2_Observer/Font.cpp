//Font.cpp

#include "Font.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif
Font::Font() {
	this->notePadForm = 0;
	this->fontMetric = { 0, };    
	
}

Font::Font(NotePadForm* notePadForm) {
	this->notePadForm = notePadForm;
	this->fontMetric = {0,};
	
}

Font::~Font() {

}

LOGFONT Font::MakeInitialLogFont() {
	LOGFONT logFont = { 0, };
	logFont.lfHeight = -65;
	logFont.lfWidth = 0;
	strcpy_s(logFont.lfFaceName, _T((char*)("µ¸¿ò")));
	
	return logFont;
}

TEXTMETRIC Font::CalculateFontMetric() {
	CDC* dc = this->notePadForm->GetDC();
	LOGFONT logFont = { 0, };
	logFont = this->notePadForm->GetLogFont();
	CFont newFont;

	newFont.CreateFontIndirect(&logFont);
	CFont* oldFont = dc->SelectObject(&newFont);
	
	TEXTMETRIC tm = { 0, };
	dc->GetTextMetrics(&tm);

	dc->SelectObject(oldFont);
	newFont.DeleteObject();
	::ReleaseDC(this->notePadForm->m_hWnd, ((HDC)(*dc)));
	return tm;
}



