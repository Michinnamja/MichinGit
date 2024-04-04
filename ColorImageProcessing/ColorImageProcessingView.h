
// ColorImageProcessingView.h: CColorImageProcessingView 클래스의 인터페이스
//

#pragma once


class CColorImageProcessingView : public CView
{
protected: // serialization에서만 만들어집니다.
	CColorImageProcessingView() noexcept;
	DECLARE_DYNCREATE(CColorImageProcessingView)

// 특성입니다.
public:
	CColorImageProcessingDoc* GetDocument() const;

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
	virtual ~CColorImageProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEqaulImage();
	afx_msg void OnGrayScale();
	afx_msg void OnAddImage();
	afx_msg void OnChageSatur();
	afx_msg void OnPickOrange();
	afx_msg void OnBWImage1();
	afx_msg void OnBWImage2();
	afx_msg void OnGamma();
	afx_msg void OnPosterize();
	afx_msg void OnHighlight();
	afx_msg void OnHisto1();
	afx_msg void OnHisto2();
	afx_msg void OnEndin();
	afx_msg void OnZoomout();
	afx_msg void OnHSIEmboss();
	afx_msg void OnEmboss();
	afx_msg void OnZoomin();
	afx_msg void OnRotate();
	afx_msg void OnMove();
	afx_msg void OnLr();
	afx_msg void OnUd();
	afx_msg void OnLrud();
	afx_msg void OnBlr();
	afx_msg void OnSharp();
	afx_msg void OnEdge1();
	afx_msg void OnEdge2();
	afx_msg void OnEdge3();
	afx_msg void OnEdge4();
	afx_msg void OnEdge5();
	afx_msg void OnEdge6();
	afx_msg void OnEdge7();
	afx_msg void OnEdge8();
	afx_msg void OnEdge9();
	afx_msg void OnEdge10();
	afx_msg void OnEdge11();
	afx_msg void OnDog1();
	afx_msg void OnDog2();
	afx_msg void OnHSIBlr();
	afx_msg void OnHSISharp();
	afx_msg void OnHSIEdge1();
	afx_msg void OnHSIEdge2();
	afx_msg void OnHSIEdge3();
	afx_msg void OnHSIEdge4();
	afx_msg void OnHSIEdge5();
	afx_msg void OnHSIEdge6();
	afx_msg void OnHSIEdge7();
	afx_msg void OnHSIEdge8();
	afx_msg void OnHSIEdge9();
	afx_msg void OnHSIEdge10();
	afx_msg void OnHSIEdge11();
	afx_msg void OnHSIDog1();
	afx_msg void OnHSIDog2();
	afx_msg void OnMiniSave();
};

#ifndef _DEBUG  // ColorImageProcessingView.cpp의 디버그 버전
inline CColorImageProcessingDoc* CColorImageProcessingView::GetDocument() const
   { return reinterpret_cast<CColorImageProcessingDoc*>(m_pDocument); }
#endif

