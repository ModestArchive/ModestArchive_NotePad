//ScrollController.h
#ifndef _SCROLLCONTROLLER_H
#define _SCROLLCONTROLLER_H
#include"Observer.h"

class Scroll;
class NotePadForm;

class ScrollController :public Observer {
public:
	//생성자,소멸자
	ScrollController(Scroll* scroll=0, NotePadForm* notePadForm=0  );
	~ScrollController();
	//매서드
		//스크롤 만들기
	void SetHScroll();
	void SetVScroll();
	void SetIsHScrollOn(bool isHScrollOn);
	
		//스크롤 이동하기,셋팅하기
	void SetHPos(Long hPosition);
	void SetVPos(Long vPosition);
	void MoveHScrFirst();
	void MoveHScrLast();
	void MoveHScrNext();
	void MoveHScrPrevious();
	void MoveHScrPageLeft();
	void MoveHScrPageRight();
	void MoveHScrThumb();
	void MoveVScrFirst();
	void MoveVScrLast();
	void MoveVScrNext();
	void MoveVScrPrevious();
	void MoveVScrPageUp();
	void MoveVScrPageDown();
	void MoveVScrThumb();

		//스크롤 지우기
	void RemoveHScroll();
	void RemoveVScroll();
		//옵저버패턴 업뎃
	virtual void Update(Subject* theChangedSubject);
	//인라인함수
	Scroll* GetScroll() const;
	Long GetHPosition() const;
	Long GetVPosition() const;
	Long GetHMaximum() const;
	Long GetVMaximum() const;
	bool GetIsHScrollOn() const;
	bool GetIsVScrollOn() const;
	
private:
	NotePadForm* notePadForm;
	Scroll* scroll;
	Long hPosition;
	Long vPosition;
	Long hMaximum;
	Long vMaximum;
	bool isHScrollOn;
	bool isVScrollOn;
};

inline Scroll* ScrollController::GetScroll() const {
	return const_cast<Scroll*>(this->scroll);
}

inline Long ScrollController::GetHPosition() const {
	return this->hPosition;
}

inline Long ScrollController::GetVPosition() const {
	return this->vPosition;
}

inline Long ScrollController::GetHMaximum() const {
	return this->hMaximum;
}


inline Long ScrollController::GetVMaximum() const {
	return this->vMaximum;
}

inline bool ScrollController::GetIsHScrollOn() const {
	return this->isHScrollOn;
}

inline bool ScrollController::GetIsVScrollOn() const {
	return this->isVScrollOn;
}
#endif // !_SCROLLCONTROLLER_H

