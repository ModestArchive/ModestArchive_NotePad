//CMyDialog.h

#ifndef _CMYDIALOG_H
#define _CMYDIALOG_H
#include "resource.h"
#include"NotePadForm.h"

#include <afxwin.h>

typedef signed long int Long;

class CMyDialog :public CDialog {
public:
	enum { IDD = IDD_SAVEDIALOG };
public:
	CMyDialog(NotePadForm* notePadForm=0,CWnd* parent = NULL);
	virtual BOOL OnInitDialog();
protected:
	afx_msg void OnSaveButtonClicked();
	afx_msg void OnNoSaveButtonClicked();
	afx_msg void OnCancelButtonClicked();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()

private:
	NotePadForm* notePadForm;
};
#endif // !_CMYDIALOG_H
