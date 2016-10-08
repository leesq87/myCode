
// WinColor_tryView.h : CWinColor_tryView 클래스의 인터페이스
//

#pragma once


class CWinColor_tryView : public CView
{
protected: // serialization에서만 만들어집니다.
	CWinColor_tryView();
	DECLARE_DYNCREATE(CWinColor_tryView)

// 특성입니다.
public:
	CWinColor_tryDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CWinColor_tryView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // WinColor_tryView.cpp의 디버그 버전
inline CWinColor_tryDoc* CWinColor_tryView::GetDocument() const
   { return reinterpret_cast<CWinColor_tryDoc*>(m_pDocument); }
#endif

