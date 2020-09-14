//Caret.cpp

#include"Caret.h"

Caret::Caret() {
	this->notCompositionCaretWidth=0;
	this->compositionCaretWidth=0;
	this->caretHeight = 0;
}


Caret::Caret(TEXTMETRIC fontMetric) {
	this->notCompositionCaretWidth = 0;
	this->compositionCaretWidth = fontMetric.tmMaxCharWidth;
	this->caretHeight = fontMetric.tmHeight;	
}


Caret::~Caret() {

}