
// ColorImageProcessingDoc.h: CColorImageProcessingDoc 클래스의 인터페이스
//


#pragma once
#include <iostream>

class CColorImageProcessingDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CColorImageProcessingDoc() noexcept;
	DECLARE_DYNCREATE(CColorImageProcessingDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CColorImageProcessingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	int m_inH = 0;
	int m_inW = 0;
	int m_outH = 0;
	int m_outW = 0;
	unsigned char** m_inImageR = NULL;
	unsigned char** m_inImageG = NULL;
	unsigned char** m_inImageB = NULL;
	unsigned char** m_outImageR = NULL;
	unsigned char** m_outImageG = NULL;
	unsigned char** m_outImageB = NULL;
	unsigned char** OnMalloc2D(int h, int w);
	template <typename T>
	void OnFree2D(T memory, int h);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	void OnFreeOutImage();
	void OnEqaulImage();
	void OnGrayScale();
	void OnAddImage();
	void OutImageOK();
	void OnChageSatur();
	double* RGB2HSI(int R, int G, int B);
	unsigned char* HSI2RGB(double H, double S, double I);
	void OnPickOrange();
	void OnBWImage1();
	void OnBWImage2();
	void OnGamma();
	void OnPosterize();
	void OnHighlight();
	void OnHisto1();
	void OnHisto2();
	void OnEndin();
	void OnZoomout();
	void OnHSIEmboss();
	double** OnMalloc2D_Double(int h, int w);
	void OnEmboss();
	void OnZoomin();
	void OnRotate();
	void OnMove();
	void OnLr();
	void OnUd();
	void OnLrud();
	void OnBlr();
	void OnSharp();
	void OnEdge1();
	void OnEdge2();
	void OnEdge3();
	void OnEdge4();
	void OnEdge5();
	void OnEdge6();
	void OnEdge7();
	void OnEdge8();
	void OnEdge9();
	void OnEdge10();
	void OnEdge11();
	void OnDog1();
	void OnDog2();
	double* HSI2RGB2(double H, double S, double I);
	void OnHSIBlr();
	void OnHSISharp();
	void OnHSIEdge1();
	void OnHSIEdge2();
	void OnHSIEdge3();
	void OnHSIEdge4();
	void OnHSIEdge5();
	void OnHSIEdge6();
	void OnHSIEdge7();
	void OnHSIEdge8();
	void OnHSIEdge9();
	void OnHSIEdge10();
	void OnHSIEdge11();
	void OnHSIDog1();
	void OnHSIDog2();
	void OnMiniSave();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
};
