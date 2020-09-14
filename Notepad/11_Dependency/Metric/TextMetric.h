//TextMetric.h

#ifndef _TEXTMETRIC_H
#define _TEXTMETRIC_H

#include"NotePadForm.h"

class TextMetric {
public:
	//생성자,소멸자
	TextMetric(NotePadForm* notePadForm = 0);
	~TextMetric();
	//메소드
	//Long CalculateCharWidth(Glyph* row);
	Long GetX(Glyph* row, Long index);
	Long GetDesignatedAreaX(Glyph* row,Long startIndex,Long LastIndex);
	Long GetDummyX(Glyph* row, Long index);
	Long GetY(Long index);
	Long GetCurrentTextWidth(Glyph* row, Long index);
	
	
	//연산자함수
	//인라인함수
	Long  GetTextWidth(Long index) const;
	Long  GetTextHeight() const;
private:
	NotePadForm* notePadForm;
	Long widths[129];
	Long height;
};

inline Long TextMetric::GetTextWidth(Long index) const {//생각을 확장시키자!!!
	return this->widths[index];
}

inline Long TextMetric::GetTextHeight() const {
	return this->height;
}
#endif // !_TEXTMETRIC_H
