//Printer.h

#ifndef _PRINTER_H
#define _PRINTER_H

#include<afxwin.h>
class NotePadFormControlWnd;
class NotePadForm;

class Printer {
public:
	Printer(NotePadFormControlWnd* notePadFormControlWnd,NotePadForm* notePadForm);
	~Printer();
	void PrintContents();
	void SetUpPageconfiguration();
	//인라인함수
	PAGESETUPDLG* GetPageSetupDlg() const;
private:
	NotePadFormControlWnd* notePadFormControlWnd;
	NotePadForm* notePadForm;
	PAGESETUPDLG* pageSetUpdlg;
};
inline PAGESETUPDLG* Printer::GetPageSetupDlg() const {
	return const_cast<PAGESETUPDLG*>(this->pageSetUpdlg);
}
#endif // !_PRINTER_H
