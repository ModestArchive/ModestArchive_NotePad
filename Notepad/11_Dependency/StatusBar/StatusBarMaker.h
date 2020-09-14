//StatusBarMaker.h

#ifndef _STATUSBARMAKER_H
#define _STATUSBARMAKER_H
#include"NotePadFormControlWnd.h"
class StatusBarMaker{
public:
	StatusBarMaker(NotePadFormControlWnd* notePadFormControlWnd);
	~StatusBarMaker();
	void SetStatusBar();
	void MoveStatusBarAndClientArea();
	void RemoveStatusBar();
	void RefreshPaneContents();
private:
	NotePadFormControlWnd* notePadFormControlWnd;
};
#endif // !_STATUSBARMAKER_H

