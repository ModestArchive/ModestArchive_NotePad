//Selector.h

#ifndef _SELECTOR_H
#define _SELECTOR_H
#include"NotePadForm.h"

class Selector {
public:
	Selector(NotePadForm* notePadForm);
	~Selector();
	//////////순방향으로 누적해서 선택영역을 지정하는 기본연산
	//
	void SetRegionForHighLightNextCharWithinSingleRow();
	void SetRegionForHighLightNextCharBeyondSingleRow();
	void SetRegionForHighLightPreviousCharWithinSingleRow();
	void SetRegionForHighLightPreviousCharBeyondSingleRow();
	//
	void SetRegionForHighLightNextWordWithinSingleRow();
	void SetRegionForHighLightNextWordBeyondSingleRow();
	void SetRegionForHighLightPreviousWordWithinSingleRow();
	void SetRegionForHighLightPreviousWordBeyondSingleRow();
	//
	void SetRegionForHighLightFromCurrentColumnIndexToFirstColumnIndexInRow();
	void SetRegionForHighLightFromCurrentColumnIndexToLastColumnIndexInRow();
	//
	void SetRegionForHighLightFromCurrentIndexToNotePadFirst();
	void SetRegionForHighLightFromCurrentIndexToNotePadLast();
	//
	void SetRegionForHighLightFromCurrentIndexToDesignatedIndexOfPreviousRow();
	void SetRegionForHighLightFromCurrentIndexToDesignatedIndexOfNextRow();
	//구버전 마우스선택영역 정하기
	void SetRegionForHighLightMousetoRightTracedInSingleRow();
	void SetRegionForHighLightMousetoLeftTracedInSingleRow();
	void SetRegionForHighLightMouseUpwardTraced();
	void SetRegionForHightLightMouseDownwardTraced();
	//신버전 마우스선택영역 정하기
	void SetRegionForHighLightWithMouseRightDownard(bool isFoward_FacingDirection);
	void SetRegionForHighLightWithMouseLeftUpward(bool isFoward_FacingDirection);
	//자동개행에 맞게 선택영역을 잘라주는 연산.
	void ReHighLightRightDownwardSumRegionMatchToClientArea();
	void ReHighLightLeftUpwardSumRegionMatchToClientArea();
	//들어가기 전에 전에 선택되었던영역 삭제해주고 간다.
	void HighLightMatchContents();
	////////////역방향으로 선택영역을 지정해서 이미 선택된영역을 누적해서 지워나가는 응용연산. 
	//
	void SetRegionForUnHighLightNextCharWithinSingleRow();
	void SetRegionForUnHighLightNextCharBeyondSingleRow();
	void SetRegionForUnHighLightPreviousCharWithinSingleRow();
	void SetRegionForUnHighLightPreviousCharBeyondSingleRow();
	//
	void SetRegionForUnHighLightNextWordWithinSingleRow();
	void SetRegionForUnHighLightNextWordBeyondSingleRow();
	void SetRegionForUnHighLightPreviousWordWithinSingleRow();
	void SetRegionForUnHighLightPreviousWordBeyondSingleRow();
	//
	void SetRegionForUnHighLightFromCurrentColumnIndexToFirstColumnIndexInSingleRow();
	void SetRegionForUnHighLightFromCurrentColumnIndexToFirstColumnIndexBeyondSingleRow();
	void SetRegionForUnHighLightFromCurrentColumnIndexToLastColumnIndexInSingleRow();
	void SetRegionForUnHighLightFromCurrentColumnIndexToLastColumnIndexBeyondSingleRow();
	//
	void SetRegionForUnHighLightFromCurrentIndexToNotePadFirst();
	void SetRegionForUnHighLightFromCurrentIndexToNotePadLast();
	//
	void SetRegionForUnHighLightFromCurrentIndexToDesignatedIndexOfPreviousRow();
	void SetRegionForUnHighLightFromCurrentIndexToDesignatedIndexOfNextRow();
	//
	void SetRegionForUnHighLightMousetoRightTracedInSingleRow();
	void SetRegionForUnHighLightMousetoLeftTracedInSingleRow();
	void SetRegionForUnHighLightMouseUpwardTraced();
	void SetRegionForUnHighLightMouseDownwardTraced();
	//
	
	bool IsRightDownWardSelectedArea();

	// 
	void SetStartRowIndex(Long startRowIndex);
	void SetStartColumnIndex(Long startColumnIndex);
	void SetEndRowIndex(Long endRowIndex);
	void SetEndColumnIndex(Long endColumnIndex);
	void SetOriginRowIndex(Long originRowIndex);
	void SetOriginColumnIndex(Long originColumnIndex);
	void SetOffsetedHPosition(Long offsetedHPosition);
	void SetOffsetedVPosition(Long offsetedVPosition);
	void SetSelectedAreaLength(Long selectedAreaLength);
	void SetLengthToSelectedArea(Long lengthToSelectedArea);
	void SetIsFirstContentTab(bool isFirstContentTab);
	NotePadForm* GetNotePadForm() const;
	CRgn* GetSumRegion() const;
	CRgn* GetCopyOfSumRegion() const;
	Long GetStartRowIndex() const;
	Long GetStartColumnIndex() const;
	Long GetEndRowIndex() const;
	Long GetEndColumnIndex() const;
	Long GetOriginRowIndex() const;
	Long GetOriginColumnIndex() const;
	Long GetOffsetedHPosition() const;
	Long GetOffsetedVPosition() const;
	Long GetSelectedAreaLength() const;
	Long GetLengthToSelectedArea() const;
	bool GetIsFirstContentTab() const;
	
private:
	NotePadForm* notePadForm;
	CRgn* sumRegion;
	CRgn* copyOfSumRegion;
	CRgn* combinedTwoRegions;
	CRgn* primaryCurrentActionProcessedRegion;
	CRgn* secondaryCurrentActionProcessedRegion;
	Long startRowIndex;
	Long startColumnIndex;
	Long endRowIndex;
	Long endColumnIndex;
	Long originRowIndex;
	Long originColumnIndex;
	Long offsetedHPosition;
	Long offsetedVPosition;
	Long selectedAreaLength;
	Long lengthToSelectedArea;
	bool isFirstContentTab;
};
inline NotePadForm* Selector::GetNotePadForm() const {
	return const_cast<NotePadForm*>(this->notePadForm);
}
inline CRgn* Selector::GetSumRegion() const {
	return const_cast<CRgn*>(this->sumRegion);
}
inline CRgn* Selector::GetCopyOfSumRegion() const {
	return const_cast<CRgn*>(this->copyOfSumRegion);
}
inline Long Selector::GetStartRowIndex() const {
	return this->startRowIndex;
}

inline Long Selector::GetStartColumnIndex() const {
	return this->startColumnIndex;
}

inline Long Selector::GetEndRowIndex() const {
	return this->endRowIndex;
}

inline Long Selector::GetEndColumnIndex() const {
	return this->endColumnIndex;
}

inline Long Selector::GetOriginRowIndex() const {
	return this->originRowIndex;
}

inline Long Selector::GetOriginColumnIndex() const {
	return this->originColumnIndex;
}

inline Long Selector::GetOffsetedHPosition() const {
	return this->offsetedHPosition;
}

inline Long Selector::GetOffsetedVPosition() const {
	return this->offsetedVPosition;
}

inline Long Selector::GetSelectedAreaLength() const{
	return this->selectedAreaLength;
}

inline Long Selector::GetLengthToSelectedArea() const {
	return this->lengthToSelectedArea;
}

inline bool Selector::GetIsFirstContentTab() const {
	return this->isFirstContentTab;
}
#endif // !_SELECTOR_H

