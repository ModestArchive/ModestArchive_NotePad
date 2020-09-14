//Font.h

#ifndef _FONT_H
#define _FONT_H

#include"NotePadForm.h"

typedef signed long int Long;
class Font {
public:
	//생성자,소멸자
	Font();
	Font(NotePadForm* notePadForm);
	~Font();
	//매소드
	TEXTMETRIC CalculateFontMetric();
	LOGFONT MakeInitialLogFont();
	//연산자함수
	//인라인함수
	NotePadForm* GetNotePadForm() const;
	TEXTMETRIC GetFontMetric() const;

private:
	NotePadForm *notePadForm;
	TEXTMETRIC fontMetric;

};

inline NotePadForm* Font::GetNotePadForm() const {
	return const_cast<NotePadForm*>(this->notePadForm);
}

inline TEXTMETRIC Font::GetFontMetric() const {
	return this->fontMetric;
}


#endif//_FONT_H