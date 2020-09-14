#ifndef _NOTEPADINDICATOR_H
#define _NOTEPADINDICATOR_H


typedef signed long int Long;
class NotePadForm;
class NotePadIndicator {
public:
	NotePadIndicator(NotePadForm* notePadForm);
	~NotePadIndicator();
	void GoToCoordinate(Long rowIndex,Long columnIndex);

private:
	NotePadForm* notePadForm;
};
#endif // !_NOTEPADINDICATOR_H
