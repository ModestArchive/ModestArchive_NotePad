//selectModifier.h

#ifndef _SELECTMODIFIER_H
#define _SELECTMODIFIER_H
#include"Selector.h"

class SelectModifier {
public:
	SelectModifier(Selector* selector);
	~SelectModifier();
	void MoveSumRegionMatchToScrollPosition(Long hPosition, Long vPosition);
	void MoveCopyOfSumRegionMatchToScrollPosition(Long hPosition,Long vPosition);
	void ChangeRightDownwardSelectedAreaStartPointAfterAction(Long rowCountInFirstToSelectedAreaStartPoint);
	void ChangeRightDownwardSelectedAreaEndPointAfterAction(Long rowCountInSelectedArea);
	void ChangeLeftUpwardSelectedAreaStartPointAfterAction(Long rowCountInFirstToSelectedAreaStartPoint);
	void ChangeLeftUpwardSelectedAreaEndPointAfterAction(Long rowCountInSelectedArea);
	void SetAbsoluteSelectionInformation();
	Long CountRowInSelectedArea();
	Long CountRowInFirstToSelectedAreaStartPoint();
	bool isFirstLineInSelectedAreaDummyRow(Long index);
	

private:
	Selector* selector;
	Long offsetedHPosition;
	Long offsetedVPosition;

};
#endif // !_SELECTMODIFIER_H
