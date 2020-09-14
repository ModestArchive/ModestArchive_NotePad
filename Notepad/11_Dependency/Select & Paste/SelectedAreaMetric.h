//SelectedAreaMetric.h
#ifndef _SELECTEDAREAMETRIC_H
#define _SELECTEDAREAMETRIC_H

class Selector;
typedef signed long int Long;

class SelectedAreaMetric {

public:
	SelectedAreaMetric(Selector* selector);
	~SelectedAreaMetric();
	Long GetSelectedAreaLengthWhenRightDownwardSelected();
	Long GetSelectedAreaLengthWhenLeftUpwardSelected();
	Long GetLengthToSelectedAreaWhenRightDownwardSelected();
	Long GetLengthToSelectedAreaWhenLeftUpwardSelected();
	//rightdownward,leftupward에 따라서 바꾸어주기(현재 바뀌어진 노트패드상황에 맞게 이제 길이로 비교대조 해보는거임.)
	//void ChangeRightDownwardSelectedAreaStartPointAfterOnSizingAutoLineBreak(Long lengthToSelectedArea);
	//void ChangeLeftUpwardSelectedAreaStartPointAfterOnSizingAutoLineBreak(Long lengthToSelectedArea);
	//void ChangeRightDownwardSelectedAreaEndPointAfterOnSizingAutoLineBreak(Long selectedAreaLength);
	//void ChangeLeftUpwardSelectedAreaEndPointAfterOnSizingAutoLineBreak(Long selectedAreaLength);

private:
	Selector* selector;

};
#endif // !_SELECTEDAREAMETRIC_H

