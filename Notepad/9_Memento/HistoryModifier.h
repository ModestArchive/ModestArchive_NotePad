//HistoryModifier.h

#ifndef _HISTORYMODIFIER_H
#define _HISTORYMODIFIER_H

class NotePadHistory;
class NotePadState;
class NotePadForm;
class HistoryModifier {

public:
	HistoryModifier(NotePadHistory* notePadHistory,NotePadForm* notePadForm);
	~HistoryModifier();
	void ModifyWriteStateToRemoveState(NotePadState* notePadState);
	void ModifyRemoveStateToWriteState(NotePadState* notePadState);
	void ModifyPasteStateToCutOutState(NotePadState* notePadState);
	void ModifyCutOutStateToPasteState(NotePadState* notePadState);
	void ModifyRemoveSelectionEraseToPasteState(NotePadState* notePadState);
    void ModifySelectionErasedBeforeActionToPasteState(NotePadState* notePadState);
	void ModifyPasteStateToSelectionErasedBeforeActionState(NotePadState* notePadState);
	NotePadState* ModifyWriteStateToSelectionErasedBeforeActionState(NotePadState* notePadState);
private:
	NotePadHistory* notePadHistory;
	NotePadForm* notePadForm;
};
#endif // !_HISTORYMODIFIER_H

