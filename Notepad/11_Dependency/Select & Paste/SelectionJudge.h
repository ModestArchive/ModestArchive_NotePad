//SelectionJudge.h

#ifndef _SELECTIONJUDGE_H
#define _SELECTIONJUDGE_H

class NotePadForm;
class Selector;

class SelectionJudge {

public:
	SelectionJudge(NotePadForm* notePadForm, Selector* selector);
	~SelectionJudge();
	void SelectionDecide();

private:
	NotePadForm* notePadForm;
	Selector* selector;
};
#endif // !_SELECTIONJUDGE_H

