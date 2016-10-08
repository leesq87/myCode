
// WinColor_tryView.h : CWinColor_tryView Ŭ������ �������̽�
//

#pragma once


class CWinColor_tryView : public CView
{
protected: // serialization������ ��������ϴ�.
	CWinColor_tryView();
	DECLARE_DYNCREATE(CWinColor_tryView)

// Ư���Դϴ�.
public:
	CWinColor_tryDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CWinColor_tryView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	BITMAPINFO *BmInfo;
	int height;
	int width;
	int rwsize;
	afx_msg void OnRgbsplitR();
	afx_msg void OnHsisplitH();
	afx_msg void OnRgbsplitG();
	afx_msg void OnRgbsplitB();
	afx_msg void OnHsisplitS();
	afx_msg void OnHsisplitI();
	afx_msg void OnHsisplitB();
	afx_msg void OnHsisplitFace();
};

#ifndef _DEBUG  // WinColor_tryView.cpp�� ����� ����
inline CWinColor_tryDoc* CWinColor_tryView::GetDocument() const
   { return reinterpret_cast<CWinColor_tryDoc*>(m_pDocument); }
#endif

