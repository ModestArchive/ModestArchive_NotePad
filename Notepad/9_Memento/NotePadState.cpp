//NotePadState.cpp

#include"NotePadState.h"
#include"Glyph.h"

NotePadState::NotePadState(bool isWritingAction,
							bool isRemoveAction,
							bool isBackSpaceRemoving,
							bool isPasteAction,
							bool isCutOutAction,
							bool isSelectionErasedBeforeAction,
							bool isReplaceAllContents,
							bool isBeginOrEndPointOfReplaceAllContents,
							Glyph* glyph,
							string* contents,
							Long rowIndexRelatedWithAction,
							Long columnIndexRelatedWithAction){

	
	this->isWritingAction= isWritingAction;
	this->isRemoveAction= isRemoveAction;
	this->isBackspaceRemoving= isBackSpaceRemoving;
	this->isPasteAction= isPasteAction;
	this->isCutOutAction= isCutOutAction;
	this->isSelectionErasedBeforeAction = isSelectionErasedBeforeAction;
	this->isReplaceAllContentsAction = isReplaceAllContents;
	this->isBeginOrEndPointOfReplaceAllContents = isBeginOrEndPointOfReplaceAllContents;
	this->glyph = glyph;
	this->contents = contents;
	this->rowIndexRelatedWithAction=rowIndexRelatedWithAction;
	this->columnIndexRelatedWithAction= columnIndexRelatedWithAction;
}

NotePadState::NotePadState(const NotePadState& source) {//대체할때 사용하는거
	this->isWritingAction = source.isWritingAction;
	this->isRemoveAction= source.isRemoveAction;
	this->isBackspaceRemoving = source.isBackspaceRemoving;
	this->isPasteAction= source.isPasteAction;
	this->isCutOutAction= source.isCutOutAction;
	this->isSelectionErasedBeforeAction = source.isSelectionErasedBeforeAction;
	this->isReplaceAllContentsAction = source.isReplaceAllContentsAction;
	this->isBeginOrEndPointOfReplaceAllContents = source.isBeginOrEndPointOfReplaceAllContents;
	if (source.glyph!=0) {
		this->glyph = source.glyph->Clone();
	}
	else {
		this->glyph = 0;
	}
	if (source.contents!=0) {
		this->contents = new string(*source.GetContents());
	}
	else {
		this->contents = 0;
	}
	this->rowIndexRelatedWithAction= source.rowIndexRelatedWithAction;
	this->columnIndexRelatedWithAction = source.columnIndexRelatedWithAction;

}


NotePadState::~NotePadState() {
	if (this->glyph!=0) {
		delete glyph;
	}
	if (this->contents!=0) {
		delete contents;
	}
}


void NotePadState::SetIsWritingAction(bool isWritingAction) {
	this->isWritingAction = isWritingAction;
}
void NotePadState::SetIsRemoveAction(bool isRemoveAction) {
	this->isRemoveAction = isRemoveAction;
}
void NotePadState::SetIsBackSpaceRemoving(bool isBackSpaceRemoving) {
	this->isBackspaceRemoving = isBackSpaceRemoving;
}
void NotePadState::SetIsPastegAction(bool isPastegAction) {
	this->isPasteAction = isPastegAction;
}
void NotePadState::SetIsCutOutAction(bool isCutOutAction) {
	this->isCutOutAction = isCutOutAction;
}
void NotePadState::SetIsSelectionErasedBeforeAction(bool isSelectionErasedBeforeAction) {
	this->isSelectionErasedBeforeAction = isSelectionErasedBeforeAction;
}
void NotePadState::SetIsReplaceAllContentsAction(bool isReplaceAllContentsAction) {
	this->isReplaceAllContentsAction = isReplaceAllContentsAction;
}
void NotePadState::SetIsBeginOrEndPointOfReplaceAllContents(bool isBeginOrEndPointOfReplaceAllContents) {
	this->isBeginOrEndPointOfReplaceAllContents = isBeginOrEndPointOfReplaceAllContents;
}
void NotePadState::SetGlyph(Glyph* glyph) {
	this->glyph = glyph;
}
void NotePadState::SetContents(string* contents) {
	this->contents = contents;
}
void NotePadState::SetRowIndexRelatedWithAction(Long rowIndexRelatedWithAction) {
	this->rowIndexRelatedWithAction = rowIndexRelatedWithAction;
}
void NotePadState::SetColumnIndexRelatedWithAction(Long columnIndexRelatedWithAction) {
	this->columnIndexRelatedWithAction = columnIndexRelatedWithAction;
}