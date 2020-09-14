//ScrollController.h
#ifndef _SCROLLCONTROLLER_H
#define _SCROLLCONTROLLER_H
#include"Observer.h"

class Scroll;
class NotePadForm;

class ScrollController :public Observer {
public:
	//������,�Ҹ���
	ScrollController(Scroll* scroll=0, NotePadForm* notePadForm=0  );
	~ScrollController();
	//�ż���
		//��ũ�� �����
	void SetHScroll();
	void SetVScroll();
	void SetIsHScrollOn(bool isHScrollOn);
	
		//��ũ�� �̵��ϱ�,�����ϱ�
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

		//��ũ�� �����
	void RemoveHScroll();
	void RemoveVScroll();
		//���������� ����
	virtual void Update(Subject* theChangedSubject);
	//�ζ����Լ�
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

