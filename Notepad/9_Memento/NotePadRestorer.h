//NotePadRestorer.h
#ifndef _NOTEPADRESTORER_H
#define _NOTEPADRESTORER_H

class NotePadForm;
class NotePadHistory;
class NotePadRestorer {
public:
	NotePadRestorer(NotePadForm* notePadForm);
	~NotePadRestorer();
	void Undo();
	bool UndoForReplaceAll();
	void Redo();
	bool RedoForReplaceAll();
	void SetNotePadHistory(NotePadHistory* notePadHistory);
	//인라인함수
	NotePadHistory* GetNotePadHistory() const;
private:
	NotePadForm* notePadForm;
	NotePadHistory* notePadHistory;
	
};

inline NotePadHistory* NotePadRestorer::GetNotePadHistory() const {
	return this->notePadHistory;
}
#endif // !_NOTEPADRESTORER_H

