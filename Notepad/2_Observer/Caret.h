//Caret.h

#ifndef  _CARET_H
#define  _CARET_H
#include"Font.h"

typedef signed long int Long;
class Caret  {
public:
	//������,�Ҹ���
	Caret();
	Caret(TEXTMETRIC fontMetric);
	~Caret();
	//�޼ҵ�
	//�������Լ�
	//�ζ����Լ�
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

