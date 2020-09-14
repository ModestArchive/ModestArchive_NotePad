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
    
    CWnd* m_pParent;                        // ��� �����쿡 ���� ������ 
    CDC* m_pTarget;                        // ��� ������ DC�� ���� ������ 
    PAINTSTRUCT m_PaintStruct;                    // ȭ���� �׸��� ���� ������ ��� ����ü 
    CRect  m_RcClient, m_RcWindow;            // ��� �������� ũ�� ���� 
    CDC  m_MemoryDC;                        // �޸� DC(���� DC) 
    CBitmap m_MemoryBmp, * m_pOldMemoryBmp;    // ���۸��� ���� ��Ʈ�� 
};
#endif // !_CBUFFERDC_H

