//NotePadState.h

#ifndef _NOTEPADSTATE_H
#define _NOTEPADSTATE_H

#include<string>
using namespace std;
typedef signed long int Long;

class Glyph;
class NotePadState {

public:
	NotePadState(bool isWritingAction,
				bool isRemoveAction,
				bool isBackSpaceRemoving,
				bool isPastegAction,
				bool isCutOutAction,
				bool isSelectionErasedBeforeAction,
				bool isReplaceAllContentsAction,
				bool isBeginOrEndPointOfReplaceAllContents,
				Glyph* glyph,
				string* contents,
				Long rowIndexRelatedWithAction,
				Long columnIndexRelatedWithAction);

	NotePadState(const NotePadState& source);
	~NotePadState();
	
	void SetIsWritingAction(bool isWritingAction);
	void SetIsRemoveAction(bool isRemoveAction);
	void SetIsBackSpaceRemoving(bool isBackSpaceRemoving);
	void SetIsPastegAction(bool isPastegAction);
	void SetIsCutOutAction(bool isCutOutAction);
	void SetIsSelectionErasedBeforeAction(bool isSelectionErasedBeforeAction);
	void SetIsReplaceAllContentsAction(bool isReplaceAllContentsAction);
	void SetIsBeginOrEndPointOfReplaceAllContents(bool isBeginOrEndPointOfReplaceAllContents);
	void SetGlyph(Glyph* glyph);
	void SetContents(string* contents);
	void SetRowIndexRelatedWithAction(Long rowIndexRelatedWithAction);
	void SetColumnIndexRelatedWithAction(Long columnIndexRelatedWithAction);
	//인라인함수
	bool GetIsWritingAction() const;
	bool GetIsRemoveAction() const;
	bool GetIsBackspaceRemoving() const;
	bool GetIsPasteAction() const;
	bool GetIsCutOutAction() const;
	bool GetIsSelectionErasedBeforeAction() const;
	bool GetIsReplaceAllContentsAction() const;
	bool GetIsBeginOrEndPointOfReplaceAllContents() const;
	Glyph* GetGlyph() const;
	string* GetContents() const;
	Long GetRowIndexRelatedWithAction() const;
	Long GetColumnIndexRelatedWithAction() const;
	
private:
	bool isWritingAction;
	bool isRemoveAction;
	bool isBackspaceRemoving;
	bool isPasteAction;
	bool isCutOutAction;
	bool isSelectionErasedBeforeAction;
	bool isReplaceAllContentsAction;
	bool isBeginOrEndPointOfReplaceAllContents;
	Glyph* glyph;
	string* contents;
	Long rowIndexRelatedWithAction;
	Long columnIndexRelatedWithAction;
};


inline bool NotePadState::GetIsWritingAction() const {
	return this->isWritingAction;
}
inline bool NotePadState::GetIsRemoveAction() const {
	return this->isRemoveAction;
}
inline bool NotePadState::GetIsBackspaceRemoving() const {
	return this->isBackspaceRemoving;
}
inline bool NotePadState::GetIsPasteAction() const {
	return this->isPasteAction;
}
inline bool NotePadState::GetIsCutOutAction() const {
	return this->isCutOutAction;
}
inline bool NotePadState::GetIsSelectionErasedBeforeAction() const {
	return this->isSelectionErasedBeforeAction;
}
inline bool NotePadState::GetIsReplaceAllContentsAction() const {
	return this->isReplaceAllContentsAction;
}
inline bool NotePadState::GetIsBeginOrEndPointOfReplaceAllContents() const {
	return this->isBeginOrEndPointOfReplaceAllContents;
}
inline Glyph* NotePadState::GetGlyph() const {
	return const_cast<Glyph*>(this->glyph);
}
inline string* NotePadState::GetContents() const {
	return const_cast<string*>(this->contents);
}
inline Long NotePadState::GetRowIndexRelatedWithAction() const {
	return this->rowIndexRelatedWithAction;
}
inline Long NotePadState::GetColumnIndexRelatedWithAction() const {
	return this->columnIndexRelatedWithAction;
}

#endif//!_NOTEPADSTATE_H
