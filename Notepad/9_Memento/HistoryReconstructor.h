//HistoryReconstructor.h

#ifndef _HISTORYRECONSTRUCTOR_H
#define _HISTORYRECONSTRUCTOR_H

class NotePadHistory;
class NotePadForm;

class HistoryReconstructor {

public:
	HistoryReconstructor(NotePadHistory* notePadHistory,NotePadForm* notePadForm);
	~HistoryReconstructor();
	void ReconstructHistory();

private:
	NotePadHistory* notePadHistory;
	NotePadForm* notePadForm;

};
#endif // !_HISTORYRECONSTRUCTOR_H

