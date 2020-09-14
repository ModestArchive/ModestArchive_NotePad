//MouseTrackTextMetric.h
#ifndef _MOUSETRACKTEXTMETRIC_H
#define _MOUSETRACKTEXTMETRIC_H

#include"NotePadForm.h"

class MouseTrackTextMetric {
public:
	MouseTrackTextMetric(NotePadForm* notePadForm);
	~MouseTrackTextMetric();
	//¸Þ¼Òµå
	void TransferMouseCoordinateToNotePadLocation(UINT nFlags, CPoint point);
	void TransferMouseCoordinateToNotePadLocaitonWhenMouseMove(UINT nFlags, CPoint point);
private:
	NotePadForm* notePadForm;
};
#endif // !_MOUSETRACKTEXTMETRIC_H

