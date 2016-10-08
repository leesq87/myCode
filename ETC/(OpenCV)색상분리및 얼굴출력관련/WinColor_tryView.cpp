
// WinColor_tryView.cpp : CWinColor_tryView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "WinColor_try.h"
#endif

#include "WinColor_tryDoc.h"
#include "WinColor_tryView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinColor_tryView

IMPLEMENT_DYNCREATE(CWinColor_tryView, CView)

BEGIN_MESSAGE_MAP(CWinColor_tryView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CWinColor_tryView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_RGBSPLIT_R, &CWinColor_tryView::OnRgbsplitR)
	ON_COMMAND(IDM_HSISPLIT_H, &CWinColor_tryView::OnHsisplitH)
	ON_COMMAND(IDM_RGBSPLIT_G, &CWinColor_tryView::OnRgbsplitG)
	ON_COMMAND(IDM_RGBSPLIT_B, &CWinColor_tryView::OnRgbsplitB)
	ON_COMMAND(IDM_HSISPLIT_S, &CWinColor_tryView::OnHsisplitS)
	ON_COMMAND(IDM_HSISPLIT_I, &CWinColor_tryView::OnHsisplitI)
	ON_COMMAND(IDM_HSISPLIT_B, &CWinColor_tryView::OnHsisplitB)
	ON_COMMAND(IDM_HSISPLIT_Face, &CWinColor_tryView::OnHsisplitFace)
END_MESSAGE_MAP()

// CWinColor_tryView ����/�Ҹ�

CWinColor_tryView::CWinColor_tryView()
	: BmInfo(NULL)
	, height(0)
	, width(0)
	, rwsize(0)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
		BmInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER)+256*sizeof(RGBQUAD));
	//�ʱ�ȭ
	for(int i=0; i<256; i++) 	{
		BmInfo->bmiColors[i].rgbRed= BmInfo-> bmiColors[i].rgbGreen = BmInfo->bmiColors[i].rgbBlue = i; 
		BmInfo->bmiColors[i].rgbReserved = 0;
	}	

}

CWinColor_tryView::~CWinColor_tryView()
{
		if(BmInfo) delete BmInfo;

}

BOOL CWinColor_tryView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CWinColor_tryView �׸���

void CWinColor_tryView::OnDraw(CDC* pDC)
{
	CWinColor_tryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	if(pDoc->m_InImg==NULL) return;
	height = pDoc->dibHi.biHeight;
	width = pDoc->dibHi.biWidth;
	rwsize = WIDTHBYTES(pDoc->dibHi.biBitCount*pDoc-> dibHi.biWidth);
	BmInfo->bmiHeader = pDoc->dibHi;
	SetDIBitsToDevice(pDC->GetSafeHdc(),0,0,width,height,
				0,0,0,height, pDoc->m_InImg, BmInfo, 				DIB_RGB_COLORS);
	SetDIBitsToDevice(pDC->GetSafeHdc(),300,0,width,height,
				0,0,0,height, pDoc->m_OutImg, BmInfo, 				DIB_RGB_COLORS);
	SetDIBitsToDevice(pDC->GetSafeHdc(),0,300,width,height,
				0,0,0,height, pDoc->m_OutImg2, BmInfo, 				DIB_RGB_COLORS);
	SetDIBitsToDevice(pDC->GetSafeHdc(),300,300,width,height,
				0,0,0,height, pDoc->m_OutImg3, BmInfo, 				DIB_RGB_COLORS);

}


// CWinColor_tryView �μ�


void CWinColor_tryView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CWinColor_tryView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CWinColor_tryView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CWinColor_tryView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CWinColor_tryView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CWinColor_tryView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CWinColor_tryView ����

#ifdef _DEBUG
void CWinColor_tryView::AssertValid() const
{
	CView::AssertValid();
}

void CWinColor_tryView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWinColor_tryDoc* CWinColor_tryView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinColor_tryDoc)));
	return (CWinColor_tryDoc*)m_pDocument;
}
#endif //_DEBUG


// CWinColor_tryView �޽��� ó����


void CWinColor_tryView::OnRgbsplitR()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CWinColor_tryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int index, i, j;
	int k=2;  //R���� B= 0, G=1
		for(i=0; i<height*rwsize; i++) pDoc->m_OutImg[i]=0;
		for(i=0; i<height; i++){
			index = (height-i-1)*rwsize;
			for(j=0; j<width; j++) pDoc->m_OutImg[index+3*j+k]= 
                                                      pDoc->m_InImg[index+3*j+k];

		}
	Invalidate(FALSE);

}



void CWinColor_tryView::OnRgbsplitG()
{	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CWinColor_tryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int index, i, j;
	int k=1;  //R���� B= 0, G=1
		for(i=0; i<height*rwsize; i++) pDoc->m_OutImg2[i]=0;
		for(i=0; i<height; i++){
			index = (height-i-1)*rwsize;
			for(j=0; j<width; j++) pDoc->m_OutImg2[index+3*j+k]= 
                                                      pDoc->m_InImg[index+3*j+k];

		}
	Invalidate(FALSE);
}


void CWinColor_tryView::OnRgbsplitB()
{	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CWinColor_tryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int index, i, j;
	int k=0;  //R���� B= 0, G=1
		for(i=0; i<height*rwsize; i++) pDoc->m_OutImg3[i]=0;
		for(i=0; i<height; i++){
			index = (height-i-1)*rwsize;
			for(j=0; j<width; j++) pDoc->m_OutImg3[index+3*j+k]= 
                                                      pDoc->m_InImg[index+3*j+k];

		}
	Invalidate(FALSE);
}



void CWinColor_tryView::OnHsisplitH()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CWinColor_tryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_RGB2HSI(pDoc->m_InImg,pDoc->m_OutImg,height,width);
	int index, i, j;
	int grRWSIZE = WIDTHBYTES(8*width);
	unsigned char *GrayImg = new unsigned char [height*grRWSIZE];
	int k=0;//H ���� k=2 �� k=1 ä��
		for(i=0; i<height; i++){
		       index = (height-i-1)*rwsize;
		       for(j=0; j<width; j++) GrayImg[(height-i-1)*grRWSIZE+j]
                                                     = pDoc->m_OutImg[index+3*j+k];
		}
		for(k=0; k<3; k++)	{
		       for(i=0; i<height; i++) {
		              index = (height-i-1)*rwsize;
		              for(j=0; j<width; j++) pDoc-> m_OutImg[index+3*j+k]
                                                            = GrayImg[(height-i-1)*grRWSIZE+j];
			}	}
		Invalidate(FALSE);
	delete []GrayImg;	
}

void CWinColor_tryView::OnHsisplitS()
{
	
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CWinColor_tryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_RGB2HSI(pDoc->m_InImg,pDoc->m_OutImg2,height,width);
	int index, i, j;
	int grRWSIZE = WIDTHBYTES(8*width);
	unsigned char *GrayImg = new unsigned char [height*grRWSIZE];
	int k=1;//ä��=1
		for(i=0; i<height; i++){
		       index = (height-i-1)*rwsize;
		       for(j=0; j<width; j++) GrayImg[(height-i-1)*grRWSIZE+j]
                                                     = pDoc->m_OutImg2[index+3*j+k];
		}
		for(k=0; k<3; k++)	{
		       for(i=0; i<height; i++) {
		              index = (height-i-1)*rwsize;
		              for(j=0; j<width; j++) pDoc-> m_OutImg2[index+3*j+k]
                                                            = GrayImg[(height-i-1)*grRWSIZE+j];
			}	}
		Invalidate(FALSE);
	delete []GrayImg;	
}


void CWinColor_tryView::OnHsisplitI()
{
	
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CWinColor_tryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_RGB2HSI(pDoc->m_InImg,pDoc->m_OutImg3,height,width);
	int index, i, j;
	int grRWSIZE = WIDTHBYTES(8*width);
	unsigned char *GrayImg = new unsigned char [height*grRWSIZE];
	int k=2;//��=2
		for(i=0; i<height; i++){
		       index = (height-i-1)*rwsize;
		       for(j=0; j<width; j++) GrayImg[(height-i-1)*grRWSIZE+j]
                                                     = pDoc->m_OutImg3[index+3*j+k];
		}
		for(k=0; k<3; k++)	{
		       for(i=0; i<height; i++) {
		              index = (height-i-1)*rwsize;
		              for(j=0; j<width; j++) pDoc-> m_OutImg3[index+3*j+k]
                                                            = GrayImg[(height-i-1)*grRWSIZE+j];
			}	}
		Invalidate(FALSE);
	delete []GrayImg;	
}


void CWinColor_tryView::OnHsisplitB()
{
	CWinColor_tryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_RGB2HSI(pDoc->m_InImg,pDoc->m_OutImg,height,width);
	int index, i, j;
	int grRWSIZE = WIDTHBYTES(8*width);
	unsigned char *GrayImg = new unsigned char [height*grRWSIZE];
	int k=0;//H ����
		for(i=0; i<height; i++){
		       index = (height-i-1)*rwsize;
		       for(j=0; j<width; j++) if(pDoc->m_OutImg[index+3*j+k] > 150 && pDoc->m_OutImg[index+3*j+k] < 160) GrayImg[(height-i-1)*grRWSIZE+j] = pDoc->m_OutImg[index+3*j+k];
			   else GrayImg[(height-i-1)*grRWSIZE+j] = 255;
		}
		for(k=0; k<3; k++)	{
		       for(i=0; i<height; i++) {
		              index = (height-i-1)*rwsize;
		              for(j=0; j<width; j++) pDoc-> m_OutImg[index+3*j+k] =  GrayImg[(height-i-1)*grRWSIZE+j];
			}	}
		Invalidate(FALSE);
	delete []GrayImg;	
}


void CWinColor_tryView::OnHsisplitFace()
{
	CWinColor_tryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_RGB2HSI(pDoc->m_InImg,pDoc->m_OutImg,height,width);
	int index, i, j;
	int grRWSIZE = WIDTHBYTES(8*width);
	unsigned char *GrayImg = new unsigned char [height*grRWSIZE];
	int k=0;//H ����
		for(i=0; i<height; i++){
		       index = (height-i-1)*rwsize;
		       for(j=0; j<width; j++){
				   if(pDoc->m_OutImg[index+3*j+k] > 0 && pDoc->m_OutImg[index+3*j+k] < 80) 
					   GrayImg[(height-i-1)*grRWSIZE+j] = pDoc->m_OutImg[index+3*j+k];
			   }
		}
		for(k=0; k<3; k++)	{
		       for(i=0; i<height; i++) {
		              index = (height-i-1)*rwsize;
		              for(j=0; j<width; j++){
						  if(GrayImg[(height-i-1)*grRWSIZE+j] > 0 && GrayImg[(height-i-1)*grRWSIZE+j] < 80) pDoc-> m_OutImg[index+3*j+k] = pDoc->m_InImg[index+3*j+k];
						  else pDoc-> m_OutImg[index+3*j+k] = 255;
					  }							
			}	}
		Invalidate(FALSE);
	delete []GrayImg;	
}
