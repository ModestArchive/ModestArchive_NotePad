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
			docinfo.lpszDocName = "메모장 인쇄테스트";

			//A4 size (210mm * 297mm)
			//인쇄할 넓이를 픽셀값으로 얻는다
			int nPageWidth = dc.GetDeviceCaps(HORZRES);
			//인쇄할 높이를 픽셀값으로 얻는다
			int nPageHeight = dc.GetDeviceCaps(VERTRES);

			//SetViewportExtEx 함수사용을 위해
			dc.SetMapMode(MM_ISOTROPIC);
			//A4용지의 비율을 맞추기 위해서b
			dc.SetWindowExt(2100, 2970);
			//작업영역이 인쇄영역에 그대로 맵핑된다.
			dc.SetViewportExt(nPageWidth, nPageHeight);

			//사용자가 설정한 폰트를 dc에 적용시킨다.
			CFont newFont;
			newFont.CreateFontIndirect(&this->notePadForm->GetLogFont());
			CFont* oldFont = dc.SelectObject(&newFont);
			//a4용지크기와 설정한 가로여백에 대응되게 메모장내용을 잘라준다.
			rowCount = notePadModifier.CountRowFromStartToCurrent();
			totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
			notePadModifier.Combine();
			notePadModifier.SplitForPrinter(this->notePadFormControlWnd->GetPrinter()->GetPageSetupDlg()->rtMargin.left / 10,
				                            2100- this->notePadFormControlWnd->GetPrinter()->GetPageSetupDlg()->rtMargin.right / 10);
			cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCount);
			notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);

			//a4용지크기와 설정한 세로여백에 대응되게 몇장이 출력될지 계산한다.
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
			//여백설정된 a4용지에 얼만큼의 라인이 담기는지 구한다.
			Long rowCountInPage = (2970 - (this->notePadFormControlWnd->GetPrinter()->GetPageSetupDlg()->rtMargin.top / 10 +
										   this->notePadFormControlWnd->GetPrinter()->GetPageSetupDlg()->rtMargin.bottom / 10)) / (tm.tmHeight + 5);
			Long firstRowPrintIndex = 0;	
			Long lastPrintedRowIndex = 0;
			Long i = 0;
			Long k = 0;
			//구한 전체 페이지수에 맞게 메모장내용을 출력한다.
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
// CPrintDialog를 이용해 프린터의 디폴트 설정을 읽어온다.
CPrintDialog dlg(FALSE, PD_ALLPAGES, this->notePadFormControlWnd);
// DoModal을 실행하면 원래는 다이얼로그가 떠야되지만 인자로 PD_RETURNDEFAULT를
// 주었기 때문에 정보만 얻어오고 바로 리턴한다.
if (dlg.DoModal() == IDOK) {

	// 종이를 가로 방향으로 찍고 싶다든지 여러 매를 찍고 싶다면 아래의 코드를 수정하여
	// 사용한다. DEVMODE 구조체를 공부해보기 바란다. 다음 예는 가로 방향으로 설정하는 예이다.
	DEVMODE* pDevMode = (DEVMODE*)(dlg.GetDevMode());
	if (pDevMode) {
		// 프린터의 인쇄 방향 설정을 변경한다.
		pDevMode->dmOrientation = 1;
		// 3매를 찍도록 한다.
		pDevMode->dmCopies = 1;
	}

	CDC dc;
	// 프린터 설정을 dc 변수에 반영한다.
	if (dc.Attach(dlg.CreatePrinterDC())) {
		TEXTMETRIC tm = { 0, };
		Font font(this->notePadForm);
		tm = font.CalculateFontMetric();

		//CFont newFont;
		//newFont.CreateFontIndirect(&this->notePadForm->GetLogFont());
		//CFont* oldFont = dc.SelectObject(&newFont);

		DOCINFO di;
		// 새로 생성되는 프린트 잡의 이름을 준다.
		memset(&di, 0x00, sizeof(DOCINFO));
		di.cbSize = sizeof(DOCINFO);
		di.lpszDocName = "NotePad Output";

		// 프린트 잡을 하나 연다.
		dc.StartPage();
		dc.StartDoc(&di);

		// dc에 원하는 출력을 수행한다.

		Long i = 0;
		while (i < this->notePadForm->notePad->GetLength()) {
			dc.TextOut(0 + tm.tmAveCharWidth / 4 - (this->notePadForm->GetScrollController()->GetHPosition()),
				(i * (tm.tmHeight + 5)) - (this->notePadForm->GetScrollController()->GetVPosition()),
				this->notePadForm->notePad->GetAt(i)->GetContents().c_str());
			i++;
		}
		// 출력이 종료되었으면 마무리 작업을 한다.
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