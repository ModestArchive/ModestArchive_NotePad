//Printer.cpp
#include<afxdlgs.h>
#include"Glyph.h"
#include"ScrollController.h"
#include"PrintCommand.h"
#include"Font.h"
#include"NotePadModifier.h"
#include"NotePadMetric.h"
#include"CoordinateCalculator.h"
#include"NotePadIndicator.h"
#include"TextMetric.h"
#include"Printer.h"

PrintCommand::PrintCommand(NotePadFormControlWnd* notePadFormControlWnd,NotePadForm* notePadForm) :Command(notePadForm){
	this->notePadFormControlWnd = notePadFormControlWnd;
	this->notePadForm = notePadForm;
}


PrintCommand::~PrintCommand() {

}


void PrintCommand::Execute() {
	NotePadModifier notePadModifier(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);
	CoordinateCalculator coordinateCalculator(this->notePadForm);
	NotePadIndicator notePadIndicator(this->notePadForm);
	TextMetric textMetric(this->notePadForm);

	CPrintDialog dlg(FALSE);

	if (dlg.DoModal()==IDOK) {
		Long rowCount = 0;
		Long totalLengthToCurrent = 0;
		CPoint cPoint = { 0, };
		
		TEXTMETRIC tm = { 0, };
		Font font(this->notePadForm);
		tm = font.CalculateFontMetric();

		CDC dc;
		dc.Attach(dlg.m_pd.hDC);
		if (dc != NULL) {
			DOCINFO docinfo;
			ZeroMemory(&docinfo, sizeof(docinfo));
			docinfo.cbSize = sizeof(docinfo);
			docinfo.lpszDocName = "�޸��� �μ��׽�Ʈ";

			//A4 size (210mm * 297mm)
			//�μ��� ���̸� �ȼ������� ��´�
			int nPageWidth = dc.GetDeviceCaps(HORZRES);
			//�μ��� ���̸� �ȼ������� ��´�
			int nPageHeight = dc.GetDeviceCaps(VERTRES);

			//SetViewportExtEx �Լ������ ����
			dc.SetMapMode(MM_ISOTROPIC);
			//A4������ ������ ���߱� ���ؼ�b
			dc.SetWindowExt(2100, 2970);
			//�۾������� �μ⿵���� �״�� ���εȴ�.
			dc.SetViewportExt(nPageWidth, nPageHeight);

			//����ڰ� ������ ��Ʈ�� dc�� �����Ų��.
			CFont newFont;
			newFont.CreateFontIndirect(&this->notePadForm->GetLogFont());
			CFont* oldFont = dc.SelectObject(&newFont);
			//a4����ũ��� ������ ���ο��鿡 �����ǰ� �޸��峻���� �߶��ش�.
			rowCount = notePadModifier.CountRowFromStartToCurrent();
			totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
			notePadModifier.Combine();
			notePadModifier.SplitForPrinter(this->notePadFormControlWnd->GetPrinter()->GetPageSetupDlg()->rtMargin.left / 10,
				                            2100- this->notePadFormControlWnd->GetPrinter()->GetPageSetupDlg()->rtMargin.right / 10);
			cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCount);
			notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);

			//a4����ũ��� ������ ���ο��鿡 �����ǰ� ������ ��µ��� ����Ѵ�.
			Long howManyPage = textMetric.GetY(this->notePadForm->notePad->GetLength()) / (2970- (this->notePadFormControlWnd->GetPrinter()->GetPageSetupDlg()->rtMargin.top / 10+
																						          this->notePadFormControlWnd->GetPrinter()->GetPageSetupDlg()->rtMargin.bottom / 10));
			if (howManyPage <= 0) {
				howManyPage++;
			}
			else {
				Long howManyPageRemainder = textMetric.GetY(this->notePadForm->notePad->GetLength()) % (2970 - (this->notePadFormControlWnd->GetPrinter()->GetPageSetupDlg()->rtMargin.top / 10 +
				                                                                                                this->notePadFormControlWnd->GetPrinter()->GetPageSetupDlg()->rtMargin.bottom / 10));
				if (howManyPageRemainder != 0) {
					howManyPage++;
				}
			}
			//���鼳���� a4������ ��ŭ�� ������ ������ ���Ѵ�.
			Long rowCountInPage = (2970 - (this->notePadFormControlWnd->GetPrinter()->GetPageSetupDlg()->rtMargin.top / 10 +
										   this->notePadFormControlWnd->GetPrinter()->GetPageSetupDlg()->rtMargin.bottom / 10)) / (tm.tmHeight + 5);
			Long firstRowPrintIndex = 0;	
			Long lastPrintedRowIndex = 0;
			Long i = 0;
			Long k = 0;
			//���� ��ü ���������� �°� �޸��峻���� ����Ѵ�.
			if (dc.StartDoc(&docinfo) > 0) {
				while (i < howManyPage) {
					if (dc.StartPage() > 0) {
						
						dc.SetBkMode(WHITENESS);
						k = 0;
						if (firstRowPrintIndex + rowCountInPage > this->notePadForm->notePad->GetLength()) {
							lastPrintedRowIndex = this->notePadForm->notePad->GetLength();
						}
						else {
							lastPrintedRowIndex = firstRowPrintIndex + rowCountInPage;
						}
						while (firstRowPrintIndex < lastPrintedRowIndex) {
							dc.TextOut(this->notePadFormControlWnd->GetPrinter()->GetPageSetupDlg()->rtMargin.left / 10,
										this->notePadFormControlWnd->GetPrinter()->GetPageSetupDlg()->rtMargin.top /10 +k * (tm.tmHeight + 5),
										this->notePadForm->notePad->GetAt(firstRowPrintIndex)->GetContents().c_str());
							k++;
							firstRowPrintIndex++;
						}
						dc.EndPage();
					}
					i++;
				}
				dc.EndDoc();
			}
			dc.SelectObject(oldFont);
			newFont.DeleteObject();
			dc.DeleteDC();
		}
		rowCount = notePadModifier.CountRowFromStartToCurrent();
		totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
		notePadModifier.Combine();
		cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCount);
		notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);
	}
}

#if 0;
// CPrintDialog�� �̿��� �������� ����Ʈ ������ �о�´�.
CPrintDialog dlg(FALSE, PD_ALLPAGES, this->notePadFormControlWnd);
// DoModal�� �����ϸ� ������ ���̾�αװ� ���ߵ����� ���ڷ� PD_RETURNDEFAULT��
// �־��� ������ ������ ������ �ٷ� �����Ѵ�.
if (dlg.DoModal() == IDOK) {

	// ���̸� ���� �������� ��� �ʹٵ��� ���� �Ÿ� ��� �ʹٸ� �Ʒ��� �ڵ带 �����Ͽ�
	// ����Ѵ�. DEVMODE ����ü�� �����غ��� �ٶ���. ���� ���� ���� �������� �����ϴ� ���̴�.
	DEVMODE* pDevMode = (DEVMODE*)(dlg.GetDevMode());
	if (pDevMode) {
		// �������� �μ� ���� ������ �����Ѵ�.
		pDevMode->dmOrientation = 1;
		// 3�Ÿ� �ﵵ�� �Ѵ�.
		pDevMode->dmCopies = 1;
	}

	CDC dc;
	// ������ ������ dc ������ �ݿ��Ѵ�.
	if (dc.Attach(dlg.CreatePrinterDC())) {
		TEXTMETRIC tm = { 0, };
		Font font(this->notePadForm);
		tm = font.CalculateFontMetric();

		//CFont newFont;
		//newFont.CreateFontIndirect(&this->notePadForm->GetLogFont());
		//CFont* oldFont = dc.SelectObject(&newFont);

		DOCINFO di;
		// ���� �����Ǵ� ����Ʈ ���� �̸��� �ش�.
		memset(&di, 0x00, sizeof(DOCINFO));
		di.cbSize = sizeof(DOCINFO);
		di.lpszDocName = "NotePad Output";

		// ����Ʈ ���� �ϳ� ����.
		dc.StartPage();
		dc.StartDoc(&di);

		// dc�� ���ϴ� ����� �����Ѵ�.

		Long i = 0;
		while (i < this->notePadForm->notePad->GetLength()) {
			dc.TextOut(0 + tm.tmAveCharWidth / 4 - (this->notePadForm->GetScrollController()->GetHPosition()),
				(i * (tm.tmHeight + 5)) - (this->notePadForm->GetScrollController()->GetVPosition()),
				this->notePadForm->notePad->GetAt(i)->GetContents().c_str());
			i++;
		}
		// ����� ����Ǿ����� ������ �۾��� �Ѵ�.
		dc.EndDoc();
		dc.EndPage();
		//dc.SelectObject(oldFont);
		//newFont.DeleteObject();
		dc.DeleteDC();

	}

}
#endif 0;
#if 0;
while (i < howManyPage) {
	Long lastPrintedRowIndex = 0;
	if (firstRowPrintIndex + rowCountInPage > this->notePadForm->notePad->GetLength()) {
		lastPrintedRowIndex = this->notePadForm->notePad->GetLength();
	}
	else {
		lastPrintedRowIndex = firstRowPrintIndex + rowCountInPage;
	}
	if (dc.StartDoc(&docinfo) > 0) {

		if (dc.StartPage() > 0) {

			while (firstRowPrintIndex < lastPrintedRowIndex) {
				Long k = 0;
				dc.TextOut(0 + tm.tmAveCharWidth / 4, k * (tm.tmHeight + 5),
					this->notePadForm->notePad->GetAt(firstRowPrintIndex)->GetContents().c_str());
				k++;
				firstRowPrintIndex++;
			}
			dc.EndPage();
		}
	}
	dc.EndDoc();
	i++;
}
#endif 0;

#if 0;
while (i < 2) {

	if (dc.StartDoc(&docinfo) > 0) {

		if (dc.StartPage() > 0) {
			Long p = 0;
			while (p < this->notePadForm->notePad->GetLength()) {

				dc.TextOut(0 + tm.tmAveCharWidth / 4, p * (tm.tmHeight + 5),
					this->notePadForm->notePad->GetAt(p)->GetContents().c_str());
				p++;
			}
			dc.EndPage();
		}
	}
	dc.EndDoc();
	i++;
}
#endif 0;


#if 0;
Long howManyPage = textMetric.GetY(this->notePadForm->notePad->GetLength()) / 2460;
Long howManyPageRemainder = textMetric.GetY(this->notePadForm->notePad->GetLength()) % 2460;
if (howManyPage <= 0) {
	howManyPage++;
}
else {
	if (howManyPageRemainder != 0) {
		howManyPage++;
	}
}
Long rowCountInPage = 2665 / (tm.tmHeight + 5);
Long firstRowPrintIndex = 0;
Long lastPrintedRowIndex = 0;
//bool isFirstDC = true;
Long i = 0;
Long k = 0;
while (i < howManyPage) {

	if (dc.StartDoc(&docinfo) > 0) {

		if (dc.StartPage() > 0) {
			dc.SetBkMode(WHITENESS);
			k = 0;
			if (firstRowPrintIndex + rowCountInPage > this->notePadForm->notePad->GetLength()) {
				lastPrintedRowIndex = this->notePadForm->notePad->GetLength();
			}
			else {
				lastPrintedRowIndex = firstRowPrintIndex + rowCountInPage;
			}

			while (firstRowPrintIndex < lastPrintedRowIndex) {
				dc.TextOut(0 + tm.tmAveCharWidth / 4, k * (tm.tmHeight + 5),
					this->notePadForm->notePad->GetAt(firstRowPrintIndex)->GetContents().c_str());
				k++;
				firstRowPrintIndex++;
			}
			dc.EndPage();
		}
	}
	dc.EndDoc();
	i++;

}
#endif 0;