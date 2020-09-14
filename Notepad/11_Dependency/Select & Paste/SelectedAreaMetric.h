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
	//rightdownward,leftupward�� ���� �ٲپ��ֱ�(���� �ٲ���� ��Ʈ�е��Ȳ�� �°� ���� ���̷� �񱳴��� �غ��°���.)
	//void ChangeRightDownwardSelectedAreaStartPointAfterOnSizingAutoLineBreak(Long lengthToSelectedArea);
	//void ChangeLeftUpwardSelectedAreaStartPointAfterOnSizingAutoLineBreak(Long lengthToSelectedArea);
	//void ChangeRightDownwardSelectedAreaEndPointAfterOnSizingAutoLineBreak(Long selectedAreaLength);
	//void ChangeLeftUpwardSelectedAreaEndPointAfterOnSizingAutoLineBreak(Long selectedAreaLength);

private:
	Selector* selector;

};
#endif // !_SELECTEDAREAMETRIC_H

