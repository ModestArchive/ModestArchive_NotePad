//Caret.h

#ifndef  _CARET_H
#define  _CARET_H
#include"Font.h"

typedef signed long int Long;
class Caret  {
public:
	//생성자,소멸자
	Caret();
	Caret(TEXTMETRIC fontMetric);
	~Caret();
	//메소드
	//연산자함수
	//인라인함수
	Long GetCompositionCaretWidth() const;
	Long GetNotCompositionCaretWidth() const;
	Long GetCaretHeight() const;
	
private:
	Long compositionCaretWidth;
	Long notCompositionCaretWidth;
	Long caretHeight;

};

inline Long Caret::GetCompositionCaretWidth() const {
	return this->compositionCaretWidth;
}

inline Long Caret::GetNotCompositionCaretWidth() const {
	return this->notCompositionCaretWidth;
}

inline Long Caret::GetCaretHeight() const {
	return this->caretHeight;
}


#endif //  _CARET_H

