//TextMetric.cpp

#include"TextMetric.h"
#include"Font.h"
#include"ScrollController.h"
#include"Glyph.h"
#include"DoubleByteCharacter.h"
#include"SingleByteCharacter.h"
#include"DummyRow.h"
#include"DoubleByteCharacter.h"


TextMetric::TextMetric(NotePadForm* notePadForm) {
	this->notePadForm = notePadForm;
	CDC* dc = this->notePadForm->GetDC();

	LOGFONT *logFont = &this->notePadForm->GetLogFont();
	CFont newFont;
	newFont.CreateFontIndirect(logFont);
    CFont* oldFont = dc->SelectObject(&newFont);

	CSize size;
	
	TCHAR buffer[2];
	buffer[0] = '\0';

	Long i = 1;
	while (i <128) {
		
		buffer[0] = (TCHAR)i;
		buffer[1] = '\0';
		size = dc->GetTextExtent(buffer, 1);
		this->widths[i] = size.cx;
		i++;
	}

	this->widths[0] = this->widths[32];

	TEXTMETRIC tm = { 0, };
	dc->GetTextMetrics(&tm);
	this->widths[128] = tm.tmMaxCharWidth;
	this->height = tm.tmHeight;

	dc->SelectObject(oldFont);
	newFont.DeleteObject();
	::ReleaseDC(this->notePadForm->m_hWnd, ((HDC)(*dc)));
}


TextMetric::~TextMetric() {
	
}


Long TextMetric::GetX(Glyph* row, Long index) {
	Long width = 0;
	Long i = 0;
	
	Glyph* glyph = 0;

	while (i < index) {

		glyph = row->GetAt(i);

		if (dynamic_cast<DoubleByteCharacter*>(glyph)) {
			width += this->widths[128];
		}
		else if (dynamic_cast<SingleByteCharacter*>(glyph)) {
			if (glyph->GetContents()[0] == 9) {
				width += this->widths[32] * 8;
			}
			else {
				width += this->widths[glyph->GetContents()[0]];
			}
		}
		i++;
	}
	return width;
}


Long TextMetric::GetDesignatedAreaX(Glyph* row, Long startIndex, Long LastIndex) {
	Long designatedAreaX = 0;
	Long i = 0;
	Glyph* glyph = 0;
	
	while (startIndex < LastIndex) {
		glyph = row->GetAt(startIndex);
		
		if (dynamic_cast<DoubleByteCharacter*>(glyph)) {
			designatedAreaX += this->widths[128];
		}
		else if (dynamic_cast<SingleByteCharacter*>(glyph)) {
			if (glyph->GetContents()[0] == 9) {
				designatedAreaX += this->widths[32] * 8;
			}
			else {
				designatedAreaX += this->widths[glyph->GetContents()[0]];
			}
		}
		startIndex++;
	}
	return designatedAreaX;
}

Long TextMetric::GetDummyX(Glyph* row, Long index) {
	Long x = 0;
	Long i = 0;
	Glyph* glyph = 0;
	if (((DummyRow*)(row))->GetIsTabErased() == true) {
		x += this->widths[32] * 8;
	}
	while (i < index) {
		glyph = row->GetAt(i);
		if (dynamic_cast<DoubleByteCharacter*>(glyph)) {
			x += this->widths[128];
		}
		else if (dynamic_cast<SingleByteCharacter*>(glyph)) {
			if (glyph->GetContents()[0] == 9) {
				x += this->widths[32] * 8;
			}
			else {
				x += this->widths[glyph->GetContents()[0]];
			}
		}
		i++;
	}
	
	return x;
}

Long TextMetric::GetY(Long index) {
	TEXTMETRIC tm = { 0, };
	Font font(this->notePadForm);
	tm = font.CalculateFontMetric();
	
	Long height = 0;
	Long i = 0;

	while (i < index ) {
		height += tm.tmHeight + 5;
		i++;
	}
	
	return height;
}


Long TextMetric::GetCurrentTextWidth(Glyph* row, Long index) {
	Long width = 0;
	Glyph* glyph = 0;
	glyph = row->GetAt(index);

	if (dynamic_cast<DoubleByteCharacter*>(glyph)) {
		width = this->widths[128];
	}
	else if (dynamic_cast<SingleByteCharacter*>(glyph)) {

		if (glyph->GetContents()[0] == 9) {
			width = this->widths[32] * 8;
		}

		else {
			width = this->widths[glyph->GetContents()[0]];
		}
	}

	return width;
}


