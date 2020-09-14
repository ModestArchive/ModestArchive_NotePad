//Font.h

#ifndef _FONT_H
#define _FONT_H

#include"NotePadForm.h"

typedef signed long int Long;
class Font {
public:
	//������,�Ҹ���
	Font();
	Font(NotePadForm* notePadForm);
	~Font();
	//�żҵ�
	TEXTMETRIC CalculateFontMetric();
	LOGFONT MakeInitialLogFont();
	//�������Լ�
	//�ζ����Լ�
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