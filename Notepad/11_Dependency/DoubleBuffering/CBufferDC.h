//CBufferDC.h

#ifndef _CBUFFERDC_H
#define _CBUFFERDC_H
#include"NotePadForm.h"

class CBufferDC : public CDC{
public:
    CBufferDC(CWnd* pParent);
    ~CBufferDC();
private:
   
   
    CBufferDC& operator=(const CBufferDC& src) {};

protected: 
    BOOL Attach(HDC hDC);
    HDC Detach();

private:
    
    CWnd* m_pParent;                        // 대상 윈도우에 대한 포인터 
    CDC* m_pTarget;                        // 대상 윈도우 DC에 대한 포인터 
    PAINTSTRUCT m_PaintStruct;                    // 화면을 그리기 위한 정보를 담는 구조체 
    CRect  m_RcClient, m_RcWindow;            // 대상 윈도우의 크기 정보 
    CDC  m_MemoryDC;                        // 메모리 DC(버퍼 DC) 
    CBitmap m_MemoryBmp, * m_pOldMemoryBmp;    // 버퍼링을 위한 비트맵 
};
#endif // !_CBUFFERDC_H

