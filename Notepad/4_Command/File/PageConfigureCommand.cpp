//PageConfigureCommand.cpp

#include"PageConfigureCommand.h"
#include"NotePadFormControlWnd.h"
#include<afxdlgs.h>

PageConfigureCommand::PageConfigureCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm) :Command(notePadForm){
	this->notePadFormControlWnd = notePadFormControlWnd;
	this->notePadForm = notePadForm;
}


PageConfigureCommand::~PageConfigureCommand() {

}

void PageConfigureCommand::Execute() {

    CPageSetupDialog psd(PSD_INHUNDREDTHSOFMILLIMETERS| PSD_MARGINS | PSD_ENABLEPAGEPAINTHOOK);
    // Initialize margins
    psd.m_psd.rtMargin.top = this->notePadFormControlWnd->GetPrinter()->GetPageSetupDlg()->rtMargin.top;
    psd.m_psd.rtMargin.left = this->notePadFormControlWnd->GetPrinter()->GetPageSetupDlg()->rtMargin.left;
    psd.m_psd.rtMargin.right = this->notePadFormControlWnd->GetPrinter()->GetPageSetupDlg()->rtMargin.right;
    psd.m_psd.rtMargin.bottom = this->notePadFormControlWnd->GetPrinter()->GetPageSetupDlg()->rtMargin.bottom;
   
    if (IDOK == psd.DoModal()) {
        this->notePadFormControlWnd->GetPrinter()->GetPageSetupDlg()->rtMargin.top = psd.m_psd.rtMargin.top;
        this->notePadFormControlWnd->GetPrinter()->GetPageSetupDlg()->rtMargin.left= psd.m_psd.rtMargin.left;
        this->notePadFormControlWnd->GetPrinter()->GetPageSetupDlg()->rtMargin.right = psd.m_psd.rtMargin.right;
        this->notePadFormControlWnd->GetPrinter()->GetPageSetupDlg()->rtMargin.bottom = psd.m_psd.rtMargin.bottom;
        // Propagate changes to the app
        AfxGetApp()->SelectPrinter(psd.m_psd.hDevNames, psd.m_psd.hDevMode);
    }
    this->notePadForm->GetNotePadFormControlWnd()->SetNoNeedToScroll(true);
}