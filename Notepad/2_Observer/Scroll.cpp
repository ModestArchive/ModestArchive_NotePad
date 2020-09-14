//Scroll.cpp

#include"Scroll.h"
#include "NotePadForm.h"
Scroll::Scroll(NotePadForm* notePadForm) {
	this->notePadForm = notePadForm;
	this->scrollWidth = this->notePadForm->GetCx();
	this->scrollHeight = this->notePadForm->GetCy();
	
}

Scroll::~Scroll() {

}


void Scroll::SetScrollWidth(Long scrollWidth) {
	this->scrollWidth = scrollWidth;
}

void Scroll::SetScrollHeight(Long scrollHeight) {
	this->scrollHeight = scrollHeight;
}