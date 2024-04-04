
// ColorImageProcessingView.cpp: CColorImageProcessingView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ColorImageProcessing.h"
#endif

#include "ColorImageProcessingDoc.h"
#include "ColorImageProcessingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColorImageProcessingView

IMPLEMENT_DYNCREATE(CColorImageProcessingView, CView)

BEGIN_MESSAGE_MAP(CColorImageProcessingView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_EQAUL_IMAGE, &CColorImageProcessingView::OnEqaulImage)
	ON_COMMAND(IDM_GRAY_SCALE, &CColorImageProcessingView::OnGrayScale)
	ON_COMMAND(IDM_ADD_IMAGE, &CColorImageProcessingView::OnAddImage)
	ON_COMMAND(IDM_CHAGE_SATUR, &CColorImageProcessingView::OnChageSatur)
	ON_COMMAND(IDM_PICK_ORANGE, &CColorImageProcessingView::OnPickOrange)
	ON_COMMAND(IDM_B_W_IMAGE1, &CColorImageProcessingView::OnBWImage1)
	ON_COMMAND(IDM_B_W_IMAGE2, &CColorImageProcessingView::OnBWImage2)
	ON_COMMAND(IDM_GAMMA, &CColorImageProcessingView::OnGamma)
	ON_COMMAND(IDM_POSTERIZE, &CColorImageProcessingView::OnPosterize)
	ON_COMMAND(IDM_HIGHLIGHT, &CColorImageProcessingView::OnHighlight)
	ON_COMMAND(IDM_HISTO1, &CColorImageProcessingView::OnHisto1)
	ON_COMMAND(IDM_HISTO2, &CColorImageProcessingView::OnHisto2)
	ON_COMMAND(IDM_ENDIN, &CColorImageProcessingView::OnEndin)
	ON_COMMAND(IDM_ZOOMOUT, &CColorImageProcessingView::OnZoomout)
	ON_COMMAND(IDM_H_S_I_EMBOSS, &CColorImageProcessingView::OnHSIEmboss)
	ON_COMMAND(IDM_EMBOSS, &CColorImageProcessingView::OnEmboss)
	ON_COMMAND(IDM_ZOOMIN, &CColorImageProcessingView::OnZoomin)
	ON_COMMAND(IDM_ROTATE, &CColorImageProcessingView::OnRotate)
	ON_COMMAND(IDM_MOVE, &CColorImageProcessingView::OnMove)
	ON_COMMAND(IDM_LR, &CColorImageProcessingView::OnLr)
	ON_COMMAND(IDM_UD, &CColorImageProcessingView::OnUd)
	ON_COMMAND(IDM_LRUD, &CColorImageProcessingView::OnLrud)
	ON_COMMAND(IDM_BLR, &CColorImageProcessingView::OnBlr)
	ON_COMMAND(IDM_SHARP, &CColorImageProcessingView::OnSharp)
	ON_COMMAND(IDM_EDGE1, &CColorImageProcessingView::OnEdge1)
	ON_COMMAND(IDM_EDGE2, &CColorImageProcessingView::OnEdge2)
	ON_COMMAND(IDM_EDGE3, &CColorImageProcessingView::OnEdge3)
	ON_COMMAND(IDM_EDGE4, &CColorImageProcessingView::OnEdge4)
	ON_COMMAND(IDM_EDGE5, &CColorImageProcessingView::OnEdge5)
	ON_COMMAND(IDM_EDGE6, &CColorImageProcessingView::OnEdge6)
	ON_COMMAND(IDM_EDGE7, &CColorImageProcessingView::OnEdge7)
	ON_COMMAND(IDM_EDGE8, &CColorImageProcessingView::OnEdge8)
	ON_COMMAND(IDM_EDGE9, &CColorImageProcessingView::OnEdge9)
	ON_COMMAND(IDM_EDGE10, &CColorImageProcessingView::OnEdge10)
	ON_COMMAND(IDM_EDGE11, &CColorImageProcessingView::OnEdge11)
	ON_COMMAND(IDM_DOG1, &CColorImageProcessingView::OnDog1)
	ON_COMMAND(IDM_DOG2, &CColorImageProcessingView::OnDog2)
	ON_COMMAND(IDM_H_S_I_BLR, &CColorImageProcessingView::OnHSIBlr)
	ON_COMMAND(IDM_H_S_I_SHARP, &CColorImageProcessingView::OnHSISharp)
	ON_COMMAND(IDM_H_S_I_EDGE1, &CColorImageProcessingView::OnHSIEdge1)
	ON_COMMAND(IDM_H_S_I_EDGE2, &CColorImageProcessingView::OnHSIEdge2)
	ON_COMMAND(IDM_H_S_I_EDGE3, &CColorImageProcessingView::OnHSIEdge3)
	ON_COMMAND(IDM_H_S_I_EDGE4, &CColorImageProcessingView::OnHSIEdge4)
	ON_COMMAND(IDM_H_S_I_EDGE5, &CColorImageProcessingView::OnHSIEdge5)
	ON_COMMAND(IDM_H_S_I_EDGE6, &CColorImageProcessingView::OnHSIEdge6)
	ON_COMMAND(IDM_H_S_I_EDGE7, &CColorImageProcessingView::OnHSIEdge7)
	ON_COMMAND(IDM_H_S_I_EDGE8, &CColorImageProcessingView::OnHSIEdge8)
	ON_COMMAND(IDM_H_S_I_EDGE9, &CColorImageProcessingView::OnHSIEdge9)
	ON_COMMAND(IDM_H_S_I_EDGE10, &CColorImageProcessingView::OnHSIEdge10)
	ON_COMMAND(IDM_H_S_I_EDGE11, &CColorImageProcessingView::OnHSIEdge11)
	ON_COMMAND(IDM_H_S_I_DOG1, &CColorImageProcessingView::OnHSIDog1)
	ON_COMMAND(IDM_H_S_I_DOG2, &CColorImageProcessingView::OnHSIDog2)
	ON_COMMAND(IDM_MINI_SAVE, &CColorImageProcessingView::OnMiniSave)
END_MESSAGE_MAP()

// CColorImageProcessingView 생성/소멸

CColorImageProcessingView::CColorImageProcessingView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CColorImageProcessingView::~CColorImageProcessingView()
{
}

BOOL CColorImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CColorImageProcessingView 그리기

void CColorImageProcessingView::OnDraw(CDC* pDC)
{
	///////////////
	///////////////
	// 화면 크기 조절
	/////////////
	///////////////

	///////////////////
	/// ** 더블 버퍼링 **
	///////////////////
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	/////////////////////
	/// 성능 개선을 위한 더블 버퍼링 
	////////////////////
	int i, k;
	unsigned char R, G, B;
	// 메모리 DC 선언
	CDC memDC;
	CBitmap* pOldBitmap, bitmap;

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_inW, pDoc->m_inH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_inW, pDoc->m_inH, WHITENESS); // 흰색으로 초기화


	// 출력 영상의 크기를 자동 조절
	double MAXSIZE = 800;  // 필요시 실 모니터 또는 화면의 해상도에 따라서 변경 가능!
	int inH = pDoc->m_inH;
	int inW = pDoc->m_inW;
	double hop = 1.0; // 기본

	if (inH > MAXSIZE || inW > MAXSIZE) {
		// hop을 새로 계산.
		if (inW > inH)
			hop = (inW / MAXSIZE);
		else
			hop = (inH / MAXSIZE);

		inW = (int)(inW / hop);
		inH = (int)(inH / hop);
	}

	// 메모리 DC에 그리기
	for (i = 0; i < inH; i++) {
		for (k = 0; k < inW; k++) {
			R = pDoc->m_inImageR[(int)(i * hop)][(int)(k * hop)];
			G = pDoc->m_inImageG[(int)(i * hop)][(int)(k * hop)];
			B = pDoc->m_inImageB[(int)(i * hop)][(int)(k * hop)];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}

	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(5, 5, pDoc->m_inW, pDoc->m_inH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();

	///////////////////

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_outW, pDoc->m_outH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_outW, pDoc->m_outH, WHITENESS); // 흰색으로 초기화

	int outH = pDoc->m_outH;
	int outW = pDoc->m_outW;
	hop = 1.0; // 기본

	if (outH > MAXSIZE || outW > MAXSIZE) {
		// hop을 새로 계산.
		if (outW > outH)
			hop = (outW / MAXSIZE);
		else
			hop = (outH / MAXSIZE);

		outW = (int)(outW / hop);
		outH = (int)(outH / hop);
	}

	// 메모리 DC에 그리기
	for (i = 0; i < outH; i++) {
		for (k = 0; k < outW; k++) {
			R = pDoc->m_outImageR[(int)(i * hop)][(int)(k * hop)];
			G = pDoc->m_outImageG[(int)(i * hop)][(int)(k * hop)];
			B = pDoc->m_outImageB[(int)(i * hop)][(int)(k * hop)];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}
	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(inW + 10, 5, pDoc->m_outW, pDoc->m_outH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();
}


// CColorImageProcessingView 인쇄

BOOL CColorImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CColorImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CColorImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CColorImageProcessingView 진단

#ifdef _DEBUG
void CColorImageProcessingView::AssertValid() const
{
	CView::AssertValid();
}

void CColorImageProcessingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CColorImageProcessingDoc* CColorImageProcessingView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CColorImageProcessingDoc)));
	return (CColorImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CColorImageProcessingView 메시지 처리기


void CColorImageProcessingView::OnEqaulImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEqaulImage();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnGrayScale()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGrayScale();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnAddImage()
{
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAddImage();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnChageSatur()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnChageSatur();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnPickOrange()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnPickOrange();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnBWImage1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBWImage1();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnBWImage2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBWImage2();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnGamma()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGamma();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnPosterize()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnPosterize();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnHighlight()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHighlight();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnHisto1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHisto1();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnHisto2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHisto2();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnEndin()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEndin();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnZoomout()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomout();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnEmboss()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEmboss();
	Invalidate(TRUE);
}

void CColorImageProcessingView::OnHSIEmboss()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHSIEmboss();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnZoomin()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomin();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnRotate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotate();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnMove()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMove();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnLr()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLr();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnUd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnUd();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnLrud()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLrud();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnBlr()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBlr();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharp();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnEdge1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge1();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnEdge2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge2();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnEdge3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge3();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnEdge4()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge4();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnEdge5()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge5();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnEdge6()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge6();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnEdge7()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge7();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnEdge8()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge8();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnEdge9()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge9();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnEdge10()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge10();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnEdge11()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge11();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnDog1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnDog1();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnDog2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnDog2();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnHSIBlr()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHSIBlr();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnHSISharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHSISharp();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnHSIEdge1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHSIEdge1();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnHSIEdge2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHSIEdge2();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnHSIEdge3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHSIEdge3();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnHSIEdge4()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHSIEdge4();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnHSIEdge5()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHSIEdge5();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnHSIEdge6()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHSIEdge6();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnHSIEdge7()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHSIEdge7();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnHSIEdge8()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHSIEdge8();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnHSIEdge9()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHSIEdge9();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnHSIEdge10()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHSIEdge10();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnHSIEdge11()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHSIEdge11();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnHSIDog1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHSIDog1();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnHSIDog2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHSIDog2();
	Invalidate(TRUE);
}


void CColorImageProcessingView::OnMiniSave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMiniSave();
	Invalidate(TRUE);
}
