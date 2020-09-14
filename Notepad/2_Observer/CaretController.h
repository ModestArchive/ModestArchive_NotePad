//CaretController.h

#ifndef _CARETCONTROLLER_H
#define _CARETCONTROLLER_H

#include"Caret.h"
#include"Font.h"
#include"Observer.h"
#include"NotePadForm.h"
#include"Composite.h"

typedef signed long int Long;
class CaretController : public Observer {
public:
	//생성자,소멸자
	CaretController();
	CaretController(NotePadForm* notePadForm);
	CaretController(NotePadForm* notePadForm , Caret *caret);
	~CaretController();
	
	//메소드
	virtual void Update(Subject* theChangedSubject);
	void CalculateCaretCordinate();
	void SetCaret();
	void KillCaret();
	
	//인라인
	NotePadForm* GetNotePadForm() const;
	Caret* GetCaret() const;
	CSize GetCaretCordinate() const;
	
private:
	NotePadForm *notePadForm;
	Caret *caret;
	CSize caretCordinate;
	
};

inline NotePadForm* CaretController::GetNotePadForm() const {
	return const_cast<NotePadForm*>(this->notePadForm);
}
inline  Caret* CaretController::GetCaret() const {
	return const_cast<Caret*>(this->caret);
}
inline CSize CaretController:: GetCaretCordinate() const {
	return this->caretCordinate;
}

#endif // _CARETCONTROLLER_H
