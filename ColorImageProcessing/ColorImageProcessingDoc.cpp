
// ColorImageProcessingDoc.cpp: CColorImageProcessingDoc 클래스의 구현
//
////// 코드 시작은 190줄 부터입니다

//////
////// 해당 파일에 코드 다 있습니다 view에서 연결되는 것들 전부 있고 값 입력받는 애들은 dlg에서 MFC로 진행했습니다
//////

////// 재정의는 openDoc , closeDoc , save 쪽에 했습니다 코드



#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ColorImageProcessing.h"
#endif

#include "ColorImageProcessingDoc.h"

#include <propkey.h>
#include "ConstantDlg.h"
#include "DoubleDlg.h"
#include "HIGHLIGHT.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CColorImageProcessingDoc

IMPLEMENT_DYNCREATE(CColorImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CColorImageProcessingDoc, CDocument)
END_MESSAGE_MAP()


// CColorImageProcessingDoc 생성/소멸

CColorImageProcessingDoc::CColorImageProcessingDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CColorImageProcessingDoc::~CColorImageProcessingDoc()
{
}

BOOL CColorImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CColorImageProcessingDoc serialization

void CColorImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CColorImageProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CColorImageProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CColorImageProcessingDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CColorImageProcessingDoc 진단

#ifdef _DEBUG
void CColorImageProcessingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CColorImageProcessingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CColorImageProcessingDoc 명령


unsigned char** CColorImageProcessingDoc::OnMalloc2D(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	unsigned char** memory;
	memory = new unsigned char* [h];
	for (int i = 0; i < h; i++)
		memory[i] = new unsigned char[w];
	return memory;
}

double** CColorImageProcessingDoc::OnMalloc2D_Double(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	double** memory;
	memory = new double* [h];
	for (int i = 0; i < h; i++)
		memory[i] = new double[w];

	for (int i = 0; i < h; i++)
		for (int k = 0; k < w; k++)
			memory[i][k] = 127.0;

	return memory;
}

template <typename T>
void CColorImageProcessingDoc::OnFree2D(T memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		delete memory[i];
	delete[] memory;
}

///// 파일 여는것은 MFC 기능 사용했고 재정의 한 부분은 입력크기 알아내서 메모리 할당입니다. 이미지 파일들의 크기가 전부 다르기때문에 중요합니다.

BOOL CColorImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	if (m_inImageR != NULL) {
		OnFree2D(m_inImageR, m_inH);
		OnFree2D(m_inImageG, m_inH);
		OnFree2D(m_inImageB, m_inH);
		m_inImageR = m_inImageG = m_inImageB = NULL;
		m_inH = m_inW = 0;

		OnFree2D(m_outImageR, m_outH);
		OnFree2D(m_outImageG, m_outH);
		OnFree2D(m_outImageB, m_outH);
		m_outImageR = m_outImageG = m_outImageB = NULL;
		m_outH = m_outW = 0;
	}
		CImage image;
		image.Load(lpszPathName);
		// (중요!) 입력 영상 크기 알아내기~
		m_inH = image.GetHeight();
		m_inW = image.GetWidth();
		// 메모리 할당
		m_inImageR = OnMalloc2D(m_inH, m_inW);
		m_inImageG = OnMalloc2D(m_inH, m_inW);
		m_inImageB = OnMalloc2D(m_inH, m_inW);
		// CImage의 객체값 --> 메모리
		COLORREF  px;
		for (int i = 0; i < m_inH; i++)
			for (int k = 0; k < m_inW; k++) {
				px = image.GetPixel(k, i);
				m_inImageR[i][k] = GetRValue(px);
				m_inImageG[i][k] = GetGValue(px);
				m_inImageB[i][k] = GetBValue(px);
			}
	return TRUE;
}

//// 프로그램 끌때 메모리 해제 해주었습니다.

void CColorImageProcessingDoc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	OnFree2D(m_inImageR, m_inH);
	OnFree2D(m_inImageG, m_inH);
	OnFree2D(m_inImageB, m_inH);

	OnFree2D(m_outImageR, m_outH);
	OnFree2D(m_outImageG, m_outH);
	OnFree2D(m_outImageB, m_outH);
	
	CDocument::OnCloseDocument();
}

//// OutImage 메모리 해제를 자주 해주기 때문에 함수로 만들어서 쓰고있습니다. 영상처리 함수 들어갈때 한번씩 지우고 들어가줍니다.

void CColorImageProcessingDoc::OnFreeOutImage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_outImageR != NULL) {
		OnFree2D(m_outImageR, m_outH);
		OnFree2D(m_outImageG, m_outH);
		OnFree2D(m_outImageB, m_outH);
		m_outImageR = m_outImageG = m_outImageB = NULL;
		m_outH = m_outW = 0;
	}	
}

//// 에러나면 쓰려고 만들어둔 함수 입니다. OutImage가 unsigned char 형으로 메모리 할당 되어있는데 값 넘어가지 않게 캐스팅해서 에러 줄이려고 만들었습니다.

void CColorImageProcessingDoc::OutImageOK()
{
	// TODO: 여기에 구현 코드 추가.
	
	for(int i = 0; i< m_outH ; i++)
		for (int k = 0; k < m_outW; k++) {
			if (m_outImageR[i][k] > 255)
				m_outImageR[i][k] = 255;
			if (m_outImageR[i][k] < 0)
				m_outImageR[i][k] = 0;
			if (m_outImageG[i][k] > 255)
				m_outImageG[i][k] = 255;
			if (m_outImageG[i][k] < 0)
				m_outImageG[i][k] = 0;
			if (m_outImageB[i][k] > 255)
				m_outImageB[i][k] = 255;
			if (m_outImageB[i][k] < 0)
				m_outImageB[i][k] = 0;
			m_outImageR[i][k] = (unsigned char)m_outImageR[i][k];
			m_outImageG[i][k] = (unsigned char)m_outImageG[i][k];
			m_outImageB[i][k] = (unsigned char)m_outImageB[i][k];
		}
}

//// 모든 처리에 기본 . 원본 이미지 출력입니다다

void CColorImageProcessingDoc::OnEqaulImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = m_inH;
	m_outW = m_inW;

	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = m_inImageR[i][k];
			m_outImageG[i][k] = m_inImageG[i][k];
			m_outImageB[i][k] = m_inImageB[i][k];
		}
	}
}

//// 화소값 평균내서 동일하게 만들어 회색이미지에 명암만 있게 만들어줍니다

void CColorImageProcessingDoc::OnGrayScale()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	
	double avg;     //RGB = 평균값 각각 넣기
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
			m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (unsigned char)avg;
		}
	}
}

//// 밝기 조절절

void CColorImageProcessingDoc::OnAddImage()
{
	// TODO: 여기에 구현 코드 추가.
	
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK) {
		
		OnFreeOutImage();
		m_outH = m_inH;
		m_outW = m_inW;

		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		int val = dlg.m_constant;
		int sum;
		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				sum = m_inImageR[i][k] + val;
				if (sum > 255) {
					m_outImageR[i][k] = 255;
				}
				else if (sum < 0) {
					m_outImageR[i][k] = 0;
				}
				else {
					m_outImageR[i][k] = sum;
				}
			}
		}
		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				sum = m_inImageG[i][k] + val;
				if (sum > 255) {
					m_outImageG[i][k] = 255;
				}
				else if (sum < 0) {
					m_outImageG[i][k] = 0;
				}
				else {
					m_outImageG[i][k] = sum;
				}
			}
		}
		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				sum = m_inImageB[i][k] + val;
				if (sum > 255) {
					m_outImageB[i][k] = 255;
				}
				else	if (sum < 0) {
					m_outImageB[i][k] = 0;
				}
				else {
					m_outImageB[i][k] = sum;
				}
			}
		}
	}
}

//// HIS 모델로 명도값만 보정할때 쓰기 유용합니다.

void CColorImageProcessingDoc::OnChageSatur()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// HIS 모델 값
			// H(색상) 0~360
			// S(채도) 0.0~1.0
			// I(명도) 0~255
			//RGB --> HSI
			double H, S, I;
			double R, G, B;

			R = m_inImageR[i][k];
			G = m_inImageG[i][k];
			B = m_inImageB[i][k];

			double* hsi = RGB2HSI(R, G, B);
			H = hsi[0];
			S = hsi[1];
			I = hsi[2];

			S = S + 0.2;
			if (S < 0)
				S = 0.0;

			double* rgb = HSI2RGB2(H, S, I);
			R = rgb[0];
			G = rgb[1];
			B = rgb[2];

			if (R > 255)
				R = 255;
			else if (R < 0)
				R = 0;

			if (G > 255)
				G = 255;
			else if (G < 0)
				G = 0;

			if (B > 255)
				B = 255;
			else if (B < 0)
				B = 0;

			m_outImageR[i][k] =(unsigned char) R;
			m_outImageG[i][k] =(unsigned char) G;
			m_outImageB[i][k] =(unsigned char) B;
			
		}
	}


}

//// RGB에서 HSI로 변환해주는 함수입니다.

double* CColorImageProcessingDoc::RGB2HSI(int R, int G, int B)
{
	// TODO: 여기에 구현 코드 추가.
	double H, S, I;
	double* HSI = new double[3];
	double min_value, angle;
	I = (R + G + B) / 3.0; // 밝기
	if ((R == G) && (G == B)) { // 그레이
		S = 0.0;
		H = 0.0;
	}
	else {

		min_value = min(min(R, G), B); //최소값 추출
		angle = (R - 0.5 * G - 0.5 * B) / (double)sqrt((R - G) * (R - G) + (R - B) * (G - B));

		H = (double)acos(angle) * 57.29577951;
		S = 1.0f - (3.0 / (R + G + B)) * min_value;
	}
	if (B > G) H = 360. - H;

	HSI[0] = H;
	HSI[1] = S;
	HSI[2] = I;

	return HSI;
}

//// HSI 에서 다시 RGB로 변환환

unsigned char* CColorImageProcessingDoc::HSI2RGB(double H, double S, double I)
{
	// TODO: 여기에 구현 코드 추가.
	double R, G, B;
	unsigned char* RGB = new unsigned char[3];
	double angle1, angle2, scale;

	if (I == 0.0) { // Black
		RGB[0] = 0;
		RGB[1] = 0;
		RGB[2] = 0;
		return RGB;
	}

	if (H <= 0.0) H += 360.0f;

	scale = 3.0 * I;
	if (H <= 120.0)
	{
		angle1 = H * 0.017453293;
		angle2 = (60.0 - H) * 0.017453293;
		B = (1.0 - S) / 3.0f;
		R = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
		G = 1.0 - R - B;
		B *= scale;
		R *= scale;
		G *= scale;
	}


	else if ((H > 120.0) && (H <= 240.0)) {
		H -= 120.0;
		angle1 = H * 0.017453293;

		angle2 = (60.0 - H) * 0.017453293;
		R = (1.0 - S) / 3.0;
		G = (double)(1.0f + (S * cos(angle1) / cos(angle2))) / 3.0;
		B = 1.0 - R - G;
		R *= scale;
		G *= scale;
		B *= scale;
	}
	else {
		H -= 240.0;
		angle1 = H * 0.017453293;
		angle2 = (60.0 - H) * 0.017453293;
		G = (1.0f - S) / 3.0;
		B = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
		R = 1.0 - G - B;

		R *= scale;
		G *= scale;
		B *= scale;
	}

	RGB[0] = (unsigned char)R;
	RGB[1] = (unsigned char)G;
	RGB[2] = (unsigned char)B;
	return RGB;
}

//// 얘도 똑같이 HSI TO RGB 인데 DOUBLE로 해줘서 값이 소실되거나 OVERFLOW 되지 않아요 대신에 마지막에 Unsigned Char 형으로 꼭 캐스팅 해주세요요

double* CColorImageProcessingDoc::HSI2RGB2(double H, double S, double I)
{
	// TODO: 여기에 구현 코드 추가.
	double R, G, B;
	double* RGB = new double[3];
	double angle1, angle2, scale;

	if (I == 0.0) { // Black
		RGB[0] = 0;
		RGB[1] = 0;
		RGB[2] = 0;
		return RGB;
	}

	if (H <= 0.0) H += 360.0f;

	scale = 3.0 * I;
	if (H <= 120.0)
	{
		angle1 = H * 0.017453293;
		angle2 = (60.0 - H) * 0.017453293;
		B = (1.0 - S) / 3.0f;
		R = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
		G = 1.0 - R - B;
		B *= scale;
		R *= scale;
		G *= scale;
	}


	else if ((H > 120.0) && (H <= 240.0)) {
		H -= 120.0;
		angle1 = H * 0.017453293;

		angle2 = (60.0 - H) * 0.017453293;
		R = (1.0 - S) / 3.0;
		G = (double)(1.0f + (S * cos(angle1) / cos(angle2))) / 3.0;
		B = 1.0 - R - G;
		R *= scale;
		G *= scale;
		B *= scale;
	}
	else {
		H -= 240.0;
		angle1 = H * 0.017453293;
		angle2 = (60.0 - H) * 0.017453293;
		G = (1.0f - S) / 3.0;
		B = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
		R = 1.0 - G - B;

		R *= scale;
		G *= scale;
		B *= scale;
	}

	RGB[0] = R;
	RGB[1] = G;
	RGB[2] = B;
	return RGB;
}

//// 특정 색상범위만 표현 해주는 함수인데 지금은 오렌지색상에 맞춰져 있어요 다른 값 넣으면 다른 색상 뽑을 수 있습니다.

void CColorImageProcessingDoc::OnPickOrange()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = m_inH;
	m_outW = m_inW;

	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// HIS 모델 값
			// H(색상) 0~360
			// S(채도) 0.0~1.0
			// I(명도) 0~255

			//RGB --> HSI
			double H, S, I;
			unsigned char R, G, B;


			R = m_inImageR[i][k];
			G = m_inImageG[i][k];
			B = m_inImageB[i][k];

			double* hsi = RGB2HSI(R, G, B);
			H = hsi[0];
			S = hsi[1];
			I = hsi[2];

			// 오렌지 추출
			if (8 <= H && H <= 20) {
				m_outImageR[i][k] = m_inImageR[i][k];
				m_outImageG[i][k] = m_inImageG[i][k];
				m_outImageB[i][k] = m_inImageB[i][k];
			}
			else {
				double avg = (m_inImageR[i][k] + m_inImageG[i][k] + m_inImageB[i][k]) / 3.0;
				m_outImageR[i][k] = m_outImageG[i][k] = m_outImageB[i][k] = (unsigned char)avg;
			}
		
		}
	}
}

void CColorImageProcessingDoc::OnBWImage1()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = m_inH;
	m_outW = m_inW;

	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = 255 - m_inImageR[i][k];
			m_outImageG[i][k] = 255 - m_inImageG[i][k];
			m_outImageB[i][k] = 255 - m_inImageB[i][k];
		}
	}
}

void CColorImageProcessingDoc::OnBWImage2()
{
	// TODO: 여기에 구현 코드 추가.
	// 안씀
}

void CColorImageProcessingDoc::OnGamma()
{
	// TODO: 여기에 구현 코드 추가.
	CDoubleDlg dlg;
	if (dlg.DoModal() == IDOK) {

		OnFreeOutImage();
		m_outH = m_inH;
		m_outW = m_inW;

		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		double val = dlg.m_double;

		if (val <= 0)
			return;

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				float tmp = pow(m_inImageR[i][k], 1 / val);

				if (tmp > 255)
					m_outImageR[i][k] = 255;
				else if (tmp < 0)
					m_outImageR[i][k] = 0;
				else
					m_outImageR[i][k] = (int)tmp;
			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				float tmp = pow(m_inImageG[i][k], 1 / val);

				if (tmp > 255)
					m_outImageG[i][k] = 255;
				else if (tmp < 0)
					m_outImageG[i][k] = 0;
				else
					m_outImageG[i][k] = (int)tmp;
			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				float tmp = pow(m_inImageB[i][k], 1 / val);

				if (tmp > 255)
					m_outImageB[i][k] = 255;
				else if (tmp < 0)
					m_outImageB[i][k] = 0;
				else
					m_outImageB[i][k] = (int)tmp;
			}
		}
	}
}

void CColorImageProcessingDoc::OnPosterize()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK) {

		OnFreeOutImage();
		m_outH = m_inH;
		m_outW = m_inW;

		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		
		int level, border, interval;
		level = (int)dlg.m_constant;
		if (level < 1)
			return;
		if (level > 255)
			return;

		border = 256 / level;

		interval = 256 / (level - 1);
		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				int tmp = (int)(m_inImageR[i][k] / border) * interval;

				if (tmp > 255)
					m_outImageR[i][k] = 255;
				else if (tmp < 0)
					m_outImageR[i][k] = 0;
				else
					m_outImageR[i][k] = tmp;
			}
		}

		interval = 256 / (level - 1);
		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				int tmp = (int)(m_inImageG[i][k] / border) * interval;

				if (tmp > 255)
					m_outImageG[i][k] = 255;
				else if (tmp < 0)
					m_outImageG[i][k] = 0;
				else
					m_outImageG[i][k] = tmp;
			}
		}

		interval = 256 / (level - 1);
		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				int tmp = (int)(m_inImageB[i][k] / border) * interval;

				if (tmp > 255)
					m_outImageB[i][k] = 255;
				else if (tmp < 0)
					m_outImageB[i][k] = 0;
				else
					m_outImageB[i][k] = tmp;
			}
		}
	}
}

void CColorImageProcessingDoc::OnHighlight()
{
	// TODO: 여기에 구현 코드 추가.
	CHIGHLIGHT dlg;
	if (dlg.DoModal() == IDOK) {
		OnFreeOutImage();
		m_outH = m_inH;
		m_outW = m_inW;

		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		
		int start, end;
		start = dlg.m_highmin;
		end = dlg.m_highmax;

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				if (m_inImageR[i][k] <= start)
					m_outImageR[i][k] = 0;
				else if(m_inImageR[i][k] >= end)
					m_outImageR[i][k] = 255;
				else
					m_outImageR[i][k] = m_inImageR[i][k];

			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				if (m_inImageG[i][k] <= start)
					m_outImageG[i][k] = 0;
				else if (m_inImageG[i][k] >= end)
					m_outImageG[i][k] = 255;
				else
					m_outImageG[i][k] = m_inImageG[i][k];

			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				if (m_inImageB[i][k] <= start)
					m_outImageB[i][k] = 0;
				else if (m_inImageB[i][k] >= end)
					m_outImageB[i][k] = 255;
				else
					m_outImageB[i][k] = m_inImageB[i][k];
			}
		}
	}
}

void CColorImageProcessingDoc::OnHisto1()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = m_inH;
	m_outW = m_inW;

	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	
	int old;
	int new1;
	int high = m_inImageR[0][0], low = m_inImageR[0][0];
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImageR[i][k] < low)
				low = m_inImageR[i][k];
			if (m_inImageR[i][k] > high)
				high = m_inImageR[i][k];
		}
	}
	
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			old = m_inImageR[i][k];
			new1 = (int)((double)(old - low) / (high - low) * 255.0);
			if (new1 > 255)
				new1 = 255;
			if (new1 < 0)
				new1 = 0;
			m_outImageR[i][k] = new1;
		}
	}

	high = m_inImageG[0][0], low = m_inImageG[0][0];
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImageG[i][k] < low)
				low = m_inImageG[i][k];
			if (m_inImageG[i][k] > high)
				high = m_inImageG[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			old = m_inImageG[i][k];
			new1 = (int)((double)(old - low) / (high - low) * 255.0);
			if (new1 > 255)
				new1 = 255;
			if (new1 < 0)
				new1 = 0;
			m_outImageG[i][k] = new1;
		}
	}

	high = m_inImageB[0][0], low = m_inImageB[0][0];
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImageB[i][k] < low)
				low = m_inImageB[i][k];
			if (m_inImageB[i][k] > high)
				high = m_inImageB[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			old = m_inImageB[i][k];
			new1 = (int)((double)(old - low) / (high - low) * 255.0);
			if (new1 > 255)
				new1 = 255;
			if (new1 < 0)
				new1 = 0;
			m_outImageB[i][k] = new1;
		}
	}
}

void CColorImageProcessingDoc::OnHisto2()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = m_inH;
	m_outW = m_inW;

	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int histo[256] = { 0, };
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			histo[m_inImageR[i][k]]++;

	int sumHisto[256] = { 0, };
	sumHisto[0] = histo[0];

	for (int i = 1; i < 256; i++) {
		sumHisto[i] = sumHisto[i - 1] + histo[i];
	}

	double normalHisto[256] = { 1.0, };
	for (int i = 0; i < 256; i++) {
		normalHisto[i] = sumHisto[i] * (1.0 / (m_inH * m_inW) * 255.0);
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = (unsigned char)normalHisto[m_inImageR[i][k]];
		}
	}

	//
	for (int i = 0; i < 256; i++) {
		histo[i] = 0;
		sumHisto[i] = 0;
		normalHisto[i] = 0;
	}
	
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			histo[m_inImageG[i][k]]++;

	for (int i = 1; i < 256; i++) {
		sumHisto[i] = sumHisto[i - 1] + histo[i];
	}

	for (int i = 0; i < 256; i++) {
		normalHisto[i] = sumHisto[i] * (1.0 / (m_inH * m_inW) * 255.0);
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageG[i][k] = (unsigned char)normalHisto[m_inImageG[i][k]];
		}
	}

	//

	for (int i = 0; i < 256; i++) {
		histo[i] = 0;
		sumHisto[i] = 0;
		normalHisto[i] = 0;
	}

	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			histo[m_inImageB[i][k]]++;

	sumHisto[0] = histo[0];
	for (int i = 1; i < 256; i++) {
		sumHisto[i] = sumHisto[i - 1] + histo[i];
	}

	for (int i = 0; i < 256; i++) {
		normalHisto[i] = sumHisto[i] * (1.0 / (m_inH * m_inW) * 255.0);
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageB[i][k] = (unsigned char)normalHisto[m_inImageB[i][k]];
		}
	}
}

void CColorImageProcessingDoc::OnEndin()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = m_inH;
	m_outW = m_inW;

	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int high = m_inImageR[0][0], low = m_inImageR[0][0];
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImageR[i][k] < low)
				low = m_inImageR[i][k];
			if (m_inImageR[i][k] > high)
				high = m_inImageR[i][k];
		}
	}

	high -= 50;
	low += 50;

	int old, new1;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			old = m_inImageR[i][k];
			new1 = (int)((double)(old - low) / (high - low) * 255.0);
			if (new1 > 255)
				new1 = 255;
			if (new1 < 0)
				new1 = 0;
			m_outImageR[i][k] = new1;
		}
	}

	//

	high = m_inImageG[0][0], low = m_inImageG[0][0];
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImageG[i][k] < low)
				low = m_inImageG[i][k];
			if (m_inImageG[i][k] > high)
				high = m_inImageG[i][k];
		}
	}

	high -= 50;
	low += 50;

	old, new1;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			old = m_inImageG[i][k];
			new1 = (int)((double)(old - low) / (high - low) * 255.0);
			if (new1 > 255)
				new1 = 255;
			if (new1 < 0)
				new1 = 0;
			m_outImageG[i][k] = new1;
		}
	}

	//

	high = m_inImageB[0][0], low = m_inImageB[0][0];
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImageB[i][k] < low)
				low = m_inImageB[i][k];
			if (m_inImageB[i][k] > high)
				high = m_inImageB[i][k];
		}
	}

	high -= 50;
	low += 50;

	old, new1;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			old = m_inImageB[i][k];
			new1 = (int)((double)(old - low) / (high - low) * 255.0);
			if (new1 > 255)
				new1 = 255;
			if (new1 < 0)
				new1 = 0;
			m_outImageB[i][k] = new1;
		}
	}
}

void CColorImageProcessingDoc::OnZoomout()
{
	// TODO: 여기에 구현 코드 추가.

	CDoubleDlg dlg;

	if (dlg.DoModal() == IDOK) {
		double scale = dlg.m_double;
		OnFreeOutImage();
		m_outH =(int)m_inH/scale;
		m_outW =(int)m_inW/scale;
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		for (int i = 0; i < m_outH; i++)
			for (int k = 0; k < m_outW; k++)
				m_outImageR[i][k] = 0;
		for (int i = 0; i < m_inH; i++)
			for (int k = 0; k < m_inW; k++)
				m_outImageR[(int)(i / scale)][(int)(k / scale)] += m_inImageR[i][k] / (scale * scale);

		for (int i = 0; i < m_outH; i++)
			for (int k = 0; k < m_outW; k++)
				m_outImageG[i][k] = 0;
		for (int i = 0; i < m_inH; i++)
			for (int k = 0; k < m_inW; k++)
				m_outImageG[(int)(i / scale)][(int)(k / scale)] += m_inImageG[i][k] / (scale * scale);

		for (int i = 0; i < m_outH; i++)
			for (int k = 0; k < m_outW; k++)
				m_outImageB[i][k] = 0;
		for (int i = 0; i < m_inH; i++)
			for (int k = 0; k < m_inW; k++)
				m_outImageB[(int)(i / scale)][(int)(k / scale)] += m_inImageB[i][k] / (scale * scale);
	}
}

void CColorImageProcessingDoc::OnZoomin()
{
	// TODO: 여기에 구현 코드 추가.
	CDoubleDlg dlg;

	if (dlg.DoModal() == IDOK) {
		double scale = dlg.m_double;
		OnFreeOutImage();
		m_outH = (int)m_inH * scale;
		m_outW = (int)m_inW * scale;
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		for (int i = 0; i < m_outH; i++)
			for (int k = 0; k < m_outW; k++)
				m_outImageR[i][k] = m_inImageR[(int)(i / scale)][(int)(k / scale)];

		for (int i = 0; i < m_outH; i++)
			for (int k = 0; k < m_outW; k++)
				m_outImageG[i][k] = m_inImageG[(int)(i / scale)][(int)(k / scale)];

		for (int i = 0; i < m_outH; i++)
			for (int k = 0; k < m_outW; k++)
				m_outImageB[i][k] = m_inImageB[(int)(i / scale)][(int)(k / scale)];

	}
}

void CColorImageProcessingDoc::OnRotate()
{
	// TODO: 여기에 구현 코드 추가.
	CDoubleDlg dlg;

	if (dlg.DoModal() == IDOK) {

		double degree = dlg.m_double;
		double radian = -degree * 3.141592 / 180.0;
		int scale = 1;
		OnFreeOutImage();


		m_outH = (int)m_inH * scale;
		m_outW = (int)m_inW * scale;
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		int cx = (int)m_inH / 2;
		int cy = (int)m_inW / 2;
		for (int i = 0; i < m_outH; i++) {
			for (int k = 0; k < m_outW; k++) {
				int xd = i;
				int yd = k;

				int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
				int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));
				xs += cx;
				ys += cy;

				if ((0 <= xs && xs < m_outH) && (0 <= ys && ys < m_outW))
					m_outImageR[xd][yd] = m_inImageR[xs][ys];
			}
		}

		for (int i = 0; i < m_outH; i++) {
			for (int k = 0; k < m_outW; k++) {
				int xd = i;
				int yd = k;

				int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
				int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));
				xs += cx;
				ys += cy;

				if ((0 <= xs && xs < m_outH) && (0 <= ys && ys < m_outW))
					m_outImageG[xd][yd] = m_inImageG[xs][ys];
			}
		}

		for (int i = 0; i < m_outH; i++) {
			for (int k = 0; k < m_outW; k++) {
				int xd = i;
				int yd = k;

				int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
				int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));
				xs += cx;
				ys += cy;

				if ((0 <= xs && xs < m_outH) && (0 <= ys && ys < m_outW))
					m_outImageB[xd][yd] = m_inImageB[xs][ys];
			}
		}
	}
}

void CColorImageProcessingDoc::OnMove()
{
	// TODO: 여기에 구현 코드 추가.
	CHIGHLIGHT dlg;
	if (dlg.DoModal() == IDOK) {
		OnFreeOutImage();
		int scale = 1;
		m_outH = (int)m_inH * scale;
		m_outW = (int)m_inW * scale;
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		int val2 = dlg.m_highmin;
		int val1 = dlg.m_highmax;

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				if (((0 <= (i - val1)) && ((i - val1) < m_inH)) && ((0 <= (k + val2)) && ((k + val2) < m_inW)))
					m_outImageR[i - val1][k + val2] = m_inImageR[i][k];	
			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				if (((0 <= (i - val1)) && ((i - val1) < m_inH)) && ((0 <= (k + val2)) && ((k + val2) < m_inW)))
					m_outImageG[i - val1][k + val2] = m_inImageG[i][k];
			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				if (((0 <= (i - val1)) && ((i - val1) < m_inH)) && ((0 <= (k + val2)) && ((k + val2) < m_inW)))
					m_outImageB[i - val1][k + val2] = m_inImageB[i][k];
			}
		}
	}
}

void CColorImageProcessingDoc::OnLr()
{
	// TODO: 여기에 구현 코드 추가.
	int scale = 1;
	m_outH = (int)m_inH * scale;
	m_outW = (int)m_inW * scale;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = m_inImageR[i][m_inW - k - 1];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageG[i][k] = m_inImageG[i][m_inW - k - 1];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageB[i][k] = m_inImageB[i][m_inW - k - 1];
		}
	}
}

void CColorImageProcessingDoc::OnUd()
{
	// TODO: 여기에 구현 코드 추가.
	int scale = 1;
	m_outH = (int)m_inH * scale;
	m_outW = (int)m_inW * scale;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = m_inImageR[m_inH - i - 1][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageG[i][k] = m_inImageG[m_inH - i - 1][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageB[i][k] = m_inImageB[m_inH - i - 1][k];
		}
	}
}

void CColorImageProcessingDoc::OnLrud()
{
	// TODO: 여기에 구현 코드 추가.
	int scale = 1;
	m_outH = (int)m_inH * scale;
	m_outW = (int)m_inW * scale;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageR[i][k] = m_inImageR[m_inH - i - 1][m_inW - k - 1];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageG[i][k] = m_inImageG[m_inH - i - 1][m_inW - k - 1];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImageB[i][k] = m_inImageB[m_inH - i - 1][m_inW - k - 1];
		}
	}
}

void CColorImageProcessingDoc::OnEmboss()
{
	// TODO: 여기에 구현 코드 추가.

	CConstantDlg dlg;

	if (dlg.DoModal() == IDOK) {

		OnFreeOutImage();
		m_outH = (int)m_inH;
		m_outW = (int)m_inW;
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		int scale = (int)dlg.m_constant;
		int sc = scale - 1;
		//마스크 설정

		double** mask;
		mask = OnMalloc2D_Double(scale, scale);
		for (int i = 0; i < scale; i++) {
			for (int k = 0; k < scale; k++) {
				mask[i][k] = 0.;
			}
		}

		mask[0][0] = -1.;
		mask[sc][sc] = 1;

		//

		double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
		double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
		double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

		//R

		for (int i = sc / 2; i < m_inH + sc / 2; i++) {
			for (int k = sc / 2; k < m_inW + sc / 2; k++) {
				tmpInImageR[i][k] = 0;
			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
			}
		}

		double S;
		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				S = 0.0;

				for (int m = 0; m < scale; m++)
					for (int n = 0; n < scale; n++)
						S += tmpInImageR[i + m][k + n] * mask[m][n];

				tmpOutImageR[i][k] = S + 127;
			}
		}

		//G

		for (int i = sc / 2; i < m_inH + sc / 2; i++) {
			for (int k = sc / 2; k < m_inW + sc / 2; k++) {
				tmpInImageG[i][k] = 0;
			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				S = 0.0;

				for (int m = 0; m < scale; m++)
					for (int n = 0; n < scale; n++)
						S += tmpInImageG[i + m][k + n] * mask[m][n];

				tmpOutImageG[i][k] = S + 127;
			}
		}

		//B

		for (int i = sc / 2; i < m_inH + sc / 2; i++) {
			for (int k = sc / 2; k < m_inW + sc / 2; k++) {
				tmpInImageB[i][k] = 0;
			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				S = 0.0;

				for (int m = 0; m < scale; m++)
					for (int n = 0; n < scale; n++)
						S += tmpInImageB[i + m][k + n] * mask[m][n];

				tmpOutImageB[i][k] = S + 127;
			}
		}

		// 임시 출력 영상--> 출력 영상. 
		for (int i = 0; i < m_outH; i++) {
			for (int k = 0; k < m_outW; k++) {
				if (tmpOutImageR[i][k] < 0.0)
					m_outImageR[i][k] = 0;
				else if (tmpOutImageR[i][k] > 255.0)
					m_outImageR[i][k] = 255;
				else
					m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			}
		}

		for (int i = 0; i < m_outH; i++) {
			for (int k = 0; k < m_outW; k++) {
				if (tmpOutImageG[i][k] < 0.0)
					m_outImageG[i][k] = 0;
				else if (tmpOutImageG[i][k] > 255.0)
					m_outImageG[i][k] = 255;
				else
					m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			}
		}

		for (int i = 0; i < m_outH; i++) {
			for (int k = 0; k < m_outW; k++) {
				if (tmpOutImageB[i][k] < 0.0)
					m_outImageB[i][k] = 0;
				else if (tmpOutImageB[i][k] > 255.0)
					m_outImageB[i][k] = 255;
				else
					m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
			}
		}
		OnFree2D(tmpInImageR, m_inH + sc);
		OnFree2D(tmpInImageG, m_inH + sc);
		OnFree2D(tmpInImageB, m_inH + sc);
		OnFree2D(tmpOutImageR, m_inH);
		OnFree2D(tmpOutImageG, m_inH);
		OnFree2D(tmpOutImageB, m_inH);
	}
}

void CColorImageProcessingDoc::OnHSIEmboss()
{
	CConstantDlg dlg;

	if (dlg.DoModal() == IDOK) {

		OnFreeOutImage();
		m_outH = (int)m_inH;
		m_outW = (int)m_inW;
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		int scale = (int)dlg.m_constant;
		int sc = scale - 1;
		//마스크 설정

		double** mask;
		mask = OnMalloc2D_Double(scale, scale);
		for (int i = 0; i < scale; i++) {
			for (int k = 0; k < scale; k++) {
				mask[i][k] = 0.;
			}
		}

		mask[0][0] = -1.;
		mask[sc][sc] = 1;

		//

		double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
		double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
		double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

		double** tmpInImageH = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpInImageS = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpInImageI = OnMalloc2D_Double(m_inH + sc, m_inW + sc);

		// 임시 메모리 초기화 (127)
		for (int i = 0; i < m_inH + 2; i++)
			for (int k = 0; k < m_inW + 2; k++)
				tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

		// 입력메모리 --> 임시입력메모리
		for (int i = 0; i < m_inH; i++)
			for (int k = 0; k < m_inW; k++) {
				tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
				tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
				tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
			}

		///////// RGB 모델 --> HSI 모델 ///////////////
		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				double* hsi;
				unsigned char R, G, B;
				R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
				hsi = RGB2HSI(R, G, B);

				double H, S, I;
				H = hsi[0]; S = hsi[1]; I = hsi[2];
				tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
			}
		}
		// *** 회선 연산 : 마스크로 긁어가면서 계산하기.	
		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				double S_VALUE = 0.0;
				for (int m = 0; m < scale; m++)
					for (int n = 0; n < scale; n++)
						S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
				tmpInImageI[i][k] = S_VALUE;
			}
		}

		// 후처리 (마스크의 합계에 따라서 127을 더할지 결정)
		for (int i = 0; i < m_inH; i++)
			for (int k = 0; k < m_inW; k++) {
				tmpInImageI[i][k] += 127;
			}

		////// HSI --> RGB ////////
		for (int i = 0; i < m_inH; i++)
			for (int k = 0; k < m_inW; k++) {
				double* rgb;
				double H, S, I;

				H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

				rgb = HSI2RGB2(H, S, I);
				tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
			}


		// 임시 출력 이미지 ---> 출력 이미지
		for (int i = 0; i < m_outH; i++)
			for (int k = 0; k < m_outW; k++) {
				if (tmpOutImageR[i][k] < 0.0)
					m_outImageR[i][k] = 0;
				else if (tmpOutImageR[i][k] > 255.0)
					m_outImageR[i][k] = 255;
				else
					m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

				if (tmpOutImageG[i][k] < 0.0)
					m_outImageG[i][k] = 0;
				else if (tmpOutImageG[i][k] > 255.0)
					m_outImageB[i][k] = 255;
				else
					m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

				if (tmpOutImageB[i][k] < 0.0)
					m_outImageB[i][k] = 0;
				else if (tmpOutImageB[i][k] > 255.0)
					m_outImageB[i][k] = 255;
				else
					m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

			}
		OnFree2D(tmpInImageR, m_inH + sc);
		OnFree2D(tmpInImageG, m_inH + sc);
		OnFree2D(tmpInImageB, m_inH + sc);
		OnFree2D(tmpOutImageR, m_inH);
		OnFree2D(tmpOutImageG, m_inH);
		OnFree2D(tmpOutImageB, m_inH);
		OnFree2D(tmpInImageH, m_inH + sc);
		OnFree2D(tmpInImageS, m_inH + sc);
		OnFree2D(tmpInImageI, m_inH + sc);
	}
}

void CColorImageProcessingDoc::OnBlr()
{
	CConstantDlg dlg;

	if (dlg.DoModal() == IDOK) {

		OnFreeOutImage();
		m_outH = (int)m_inH;
		m_outW = (int)m_inW;
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		int scale = (int)dlg.m_constant;
		int sc = scale - 1;
		//마스크 설정

		double** mask;
		mask = OnMalloc2D_Double(scale, scale);

		for (int i = 0; i < scale; i++) {
			for (int k = 0; k < scale; k++) {
				mask[i][k] = 0.;
			}
		}

		for (int i = 0; i < scale; i++)
			for (int k = 0; k < scale; k++)
				mask[i][k] = (double)1 / (scale * scale);
		//

		double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
		double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
		double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

		//R

		for (int i = sc / 2; i < m_inH + sc / 2; i++) {
			for (int k = sc / 2; k < m_inW + sc / 2; k++) {
				tmpInImageR[i][k] = 0;
			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
			}
		}

		double S;
		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				S = 0.0;

				for (int m = 0; m < scale; m++)
					for (int n = 0; n < scale; n++)
						S += tmpInImageR[i + m][k + n] * mask[m][n];

				tmpOutImageR[i][k] = S ;
			}
		}

		//G

		for (int i = sc / 2; i < m_inH + sc / 2; i++) {
			for (int k = sc / 2; k < m_inW + sc / 2; k++) {
				tmpInImageG[i][k] = 0;
			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				S = 0.0;

				for (int m = 0; m < scale; m++)
					for (int n = 0; n < scale; n++)
						S += tmpInImageG[i + m][k + n] * mask[m][n];

				tmpOutImageG[i][k] = S ;
			}
		}

		//B

		for (int i = sc / 2; i < m_inH + sc / 2; i++) {
			for (int k = sc / 2; k < m_inW + sc / 2; k++) {
				tmpInImageB[i][k] = 0;
			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				S = 0.0;

				for (int m = 0; m < scale; m++)
					for (int n = 0; n < scale; n++)
						S += tmpInImageB[i + m][k + n] * mask[m][n];

				tmpOutImageB[i][k] = S ;
			}
		}

		// 임시 출력 영상--> 출력 영상. 
		for (int i = 0; i < m_outH; i++) {
			for (int k = 0; k < m_outW; k++) {
				if (tmpOutImageR[i][k] < 0.0)
					m_outImageR[i][k] = 0;
				else if (tmpOutImageR[i][k] > 255.0)
					m_outImageR[i][k] = 255;
				else
					m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			}
		}

		for (int i = 0; i < m_outH; i++) {
			for (int k = 0; k < m_outW; k++) {
				if (tmpOutImageG[i][k] < 0.0)
					m_outImageG[i][k] = 0;
				else if (tmpOutImageG[i][k] > 255.0)
					m_outImageG[i][k] = 255;
				else
					m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			}
		}

		for (int i = 0; i < m_outH; i++) {
			for (int k = 0; k < m_outW; k++) {
				if (tmpOutImageB[i][k] < 0.0)
					m_outImageB[i][k] = 0;
				else if (tmpOutImageB[i][k] > 255.0)
					m_outImageB[i][k] = 255;
				else
					m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
			}
		}
		OnFree2D(tmpInImageR, m_inH + sc);
		OnFree2D(tmpInImageG, m_inH + sc);
		OnFree2D(tmpInImageB, m_inH + sc);
		OnFree2D(tmpOutImageR, m_inH);
		OnFree2D(tmpOutImageG, m_inH);
		OnFree2D(tmpOutImageB, m_inH);
	}
}

void CColorImageProcessingDoc::OnHSIBlr()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;

	if (dlg.DoModal() == IDOK) {

		OnFreeOutImage();
		m_outH = (int)m_inH;
		m_outW = (int)m_inW;
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		int scale = (int)dlg.m_constant;
		int sc = scale - 1;

		double** mask;

		mask = OnMalloc2D_Double(scale, scale);
		for (int i = 0; i < scale; i++) {
			for (int k = 0; k < scale; k++) {
				mask[i][k] = 0.;
			}
		}

		for (int i = 0; i < scale; i++)
			for (int k = 0; k < scale; k++)
				mask[i][k] = (double)1 / (scale * scale);

		double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
		double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
		double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

		double** tmpInImageH = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpInImageS = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpInImageI = OnMalloc2D_Double(m_inH + sc, m_inW + sc);

		for (int i = 0; i < m_inH + 2; i++)
			for (int k = 0; k < m_inW + 2; k++)
				tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

		for (int i = 0; i < m_inH; i++)
			for (int k = 0; k < m_inW; k++) {
				tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
				tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
				tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
			}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				double* hsi;
				double R, G, B;
				R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
				hsi = RGB2HSI(R, G, B);

				double H, S, I;
				H = hsi[0]; S = hsi[1]; I = hsi[2];
				tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				double S_VALUE = 0.0;
				for (int m = 0; m < scale; m++)
					for (int n = 0; n < scale; n++)
						S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
				tmpInImageI[i][k] = S_VALUE;
			}
		}

		for (int i = 0; i < m_inH; i++)
			for (int k = 0; k < m_inW; k++) {
				double* rgb;
				double H, S, I;

				H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

				rgb = HSI2RGB2(H, S, I);
				tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
			}

		for (int i = 0; i < m_outH; i++)
			for (int k = 0; k < m_outW; k++) {
				if (tmpOutImageR[i][k] < 0.0)
					m_outImageR[i][k] = 0;
				else if (tmpOutImageR[i][k] > 255.0)
					m_outImageR[i][k] = 255;
				else
					m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

				if (tmpOutImageG[i][k] < 0.0)
					m_outImageG[i][k] = 0;
				else if (tmpOutImageG[i][k] > 255.0)
					m_outImageB[i][k] = 255;
				else
					m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

				if (tmpOutImageB[i][k] < 0.0)
					m_outImageB[i][k] = 0;
				else if (tmpOutImageB[i][k] > 255.0)
					m_outImageB[i][k] = 255;
				else
					m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

			}
		OnFree2D(tmpInImageR, m_inH + sc);
		OnFree2D(tmpInImageG, m_inH + sc);
		OnFree2D(tmpInImageB, m_inH + sc);
		OnFree2D(tmpOutImageR, m_inH);
		OnFree2D(tmpOutImageG, m_inH);
		OnFree2D(tmpOutImageB, m_inH);
		OnFree2D(tmpInImageH, m_inH + sc);
		OnFree2D(tmpInImageS, m_inH + sc);
		OnFree2D(tmpInImageI, m_inH + sc);
	}
}

void CColorImageProcessingDoc::OnSharp()
{
	// TODO: 여기에 구현 코드 추가.

	CConstantDlg dlg;

	if (dlg.DoModal() == IDOK) {

		OnFreeOutImage();
		m_outH = (int)m_inH;
		m_outW = (int)m_inW;
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		int scale = (int)dlg.m_constant;
		int sc = scale - 1;
		//마스크 설정

		double** mask;
		mask = OnMalloc2D_Double(scale, scale);

		for (int i = 0; i < scale; i++) {
			for (int k = 0; k < scale; k++) {
				mask[i][k] = -1;
			}
		}

		mask[(sc / 2) + 1][(sc / 2) + 1] = scale * scale;

		//

		double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
		double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
		double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

		//R

		for (int i = sc / 2; i < m_inH + sc / 2; i++) {
			for (int k = sc / 2; k < m_inW + sc / 2; k++) {
				tmpInImageR[i][k] = 0;
			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
			}
		}

		double S;
		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				S = 0.0;

				for (int m = 0; m < scale; m++)
					for (int n = 0; n < scale; n++)
						S += tmpInImageR[i + m][k + n] * mask[m][n];

				tmpOutImageR[i][k] = S ;
			}
		}

		//G

		for (int i = sc / 2; i < m_inH + sc / 2; i++) {
			for (int k = sc / 2; k < m_inW + sc / 2; k++) {
				tmpInImageG[i][k] = 0;
			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				S = 0.0;

				for (int m = 0; m < scale; m++)
					for (int n = 0; n < scale; n++)
						S += tmpInImageG[i + m][k + n] * mask[m][n];

				tmpOutImageG[i][k] = S ;
			}
		}

		//B

		for (int i = sc / 2; i < m_inH + sc / 2; i++) {
			for (int k = sc / 2; k < m_inW + sc / 2; k++) {
				tmpInImageB[i][k] = 0;
			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				S = 0.0;

				for (int m = 0; m < scale; m++)
					for (int n = 0; n < scale; n++)
						S += tmpInImageB[i + m][k + n] * mask[m][n];

				tmpOutImageB[i][k] = S ;
			}
		}

		// 임시 출력 영상--> 출력 영상. 
		for (int i = 0; i < m_outH; i++) {
			for (int k = 0; k < m_outW; k++) {
				if (tmpOutImageR[i][k] < 0.0)
					m_outImageR[i][k] = 0;
				else if (tmpOutImageR[i][k] > 255.0)
					m_outImageR[i][k] = 255;
				else
					m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
			}
		}

		for (int i = 0; i < m_outH; i++) {
			for (int k = 0; k < m_outW; k++) {
				if (tmpOutImageG[i][k] < 0.0)
					m_outImageG[i][k] = 0;
				else if (tmpOutImageG[i][k] > 255.0)
					m_outImageG[i][k] = 255;
				else
					m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
			}
		}

		for (int i = 0; i < m_outH; i++) {
			for (int k = 0; k < m_outW; k++) {
				if (tmpOutImageB[i][k] < 0.0)
					m_outImageB[i][k] = 0;
				else if (tmpOutImageB[i][k] > 255.0)
					m_outImageB[i][k] = 255;
				else
					m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
			}
		}
		OnFree2D(tmpInImageR, m_inH + sc);
		OnFree2D(tmpInImageG, m_inH + sc);
		OnFree2D(tmpInImageB, m_inH + sc);
		OnFree2D(tmpOutImageR, m_inH);
		OnFree2D(tmpOutImageG, m_inH);
		OnFree2D(tmpOutImageB, m_inH);
	}
}

void CColorImageProcessingDoc::OnHSISharp()
{
	CConstantDlg dlg;

	if (dlg.DoModal() == IDOK) {

		OnFreeOutImage();
		m_outH = (int)m_inH;
		m_outW = (int)m_inW;
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		int scale = (int)dlg.m_constant;
		int sc = scale - 1;

		double** mask;

		mask = OnMalloc2D_Double(scale, scale);

		for (int i = 0; i < scale; i++) {
			for (int k = 0; k < scale; k++) {
				mask[i][k] = -1;
			}
		}

		mask[(sc / 2) + 1][(sc / 2) + 1] = scale * scale;

		double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
		double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
		double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

		double** tmpInImageH = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpInImageS = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpInImageI = OnMalloc2D_Double(m_inH + sc, m_inW + sc);

		for (int i = 0; i < m_inH + 2; i++)
			for (int k = 0; k < m_inW + 2; k++)
				tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

		for (int i = 0; i < m_inH; i++)
			for (int k = 0; k < m_inW; k++) {
				tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
				tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
				tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
			}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				double* hsi;
				double R, G, B;
				R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
				hsi = RGB2HSI(R, G, B);

				double H, S, I;
				H = hsi[0]; S = hsi[1]; I = hsi[2];
				tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				double S_VALUE = 0.0;
				for (int m = 0; m < scale; m++)
					for (int n = 0; n < scale; n++)
						S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
				tmpInImageI[i][k] = S_VALUE;
			}
		}

		for (int i = 0; i < m_inH; i++)
			for (int k = 0; k < m_inW; k++) {
				double* rgb;
				double H, S, I;

				H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

				rgb = HSI2RGB2(H, S, I);
				tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
			}

		for (int i = 0; i < m_outH; i++)
			for (int k = 0; k < m_outW; k++) {
				if (tmpOutImageR[i][k] < 0.0)
					m_outImageR[i][k] = 0;
				else if (tmpOutImageR[i][k] > 255.0)
					m_outImageR[i][k] = 255;
				else
					m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

				if (tmpOutImageG[i][k] < 0.0)
					m_outImageG[i][k] = 0;
				else if (tmpOutImageG[i][k] > 255.0)
					m_outImageB[i][k] = 255;
				else
					m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

				if (tmpOutImageB[i][k] < 0.0)
					m_outImageB[i][k] = 0;
				else if (tmpOutImageB[i][k] > 255.0)
					m_outImageB[i][k] = 255;
				else
					m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

			}
		OnFree2D(tmpInImageR, m_inH + sc);
		OnFree2D(tmpInImageG, m_inH + sc);
		OnFree2D(tmpInImageB, m_inH + sc);
		OnFree2D(tmpOutImageR, m_inH);
		OnFree2D(tmpOutImageG, m_inH);
		OnFree2D(tmpOutImageB, m_inH);
		OnFree2D(tmpInImageH, m_inH + sc);
		OnFree2D(tmpInImageS, m_inH + sc);
		OnFree2D(tmpInImageI, m_inH + sc);
	}
}

void CColorImageProcessingDoc::OnEdge1()   //수직 엣지
{
	OnFreeOutImage();
	m_outH = (int)m_inH;
	m_outW = (int)m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int scale = 3;
	int sc = scale - 1;
	//마스크 설정

	double mask[3][3] = { { 0,-1, 0},          // 엣지 마스크
							  { 0, 1, 0},
							  { 0, 0, 0} };
	//

	double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageR[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
		}
	}

	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];

			tmpOutImageR[i][k] = S;
		}
	}

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageG[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];

			tmpOutImageG[i][k] = S;
		}
	}

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageB[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];

			tmpOutImageB[i][k] = S ;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}
	OnFree2D(tmpInImageR, m_inH + sc);
	OnFree2D(tmpInImageG, m_inH + sc);
	OnFree2D(tmpInImageB, m_inH + sc);
	OnFree2D(tmpOutImageR, m_inH);
	OnFree2D(tmpOutImageG, m_inH);
	OnFree2D(tmpOutImageB, m_inH);
}

void CColorImageProcessingDoc::OnEdge2()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = (int)m_inH;
	m_outW = (int)m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int scale = 3;
	int sc = scale - 1;
	//마스크 설정

	double mask[3][3] = { {0,0,0}, // 엣지 마스크
						 {-1,1,0},
						 {0,0,0} };
	//

	double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageR[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
		}
	}

	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];

			tmpOutImageR[i][k] = S;
		}
	}

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageG[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];

			tmpOutImageG[i][k] = S;
		}
	}

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageB[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];

			tmpOutImageB[i][k] = S;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}
	OnFree2D(tmpInImageR, m_inH + sc);
	OnFree2D(tmpInImageG, m_inH + sc);
	OnFree2D(tmpInImageB, m_inH + sc);
	OnFree2D(tmpOutImageR, m_inH);
	OnFree2D(tmpOutImageG, m_inH);
	OnFree2D(tmpOutImageB, m_inH);
}

void CColorImageProcessingDoc::OnEdge3()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = (int)m_inH;
	m_outW = (int)m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int scale = 3;
	int sc = scale - 1;
	//마스크 설정

	double mask[3][3] = { {-1,0,-1}, // 엣지 마스크
						 {0,2,0},
						 {0,0,0} };
	//

	double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageR[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
		}
	}

	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];

			tmpOutImageR[i][k] = S;
		}
	}

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageG[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];

			tmpOutImageG[i][k] = S;
		}
	}

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageB[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];

			tmpOutImageB[i][k] = S;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}
	OnFree2D(tmpInImageR, m_inH + sc);
	OnFree2D(tmpInImageG, m_inH + sc);
	OnFree2D(tmpInImageB, m_inH + sc);
	OnFree2D(tmpOutImageR, m_inH);
	OnFree2D(tmpOutImageG, m_inH);
	OnFree2D(tmpOutImageB, m_inH);
}

void CColorImageProcessingDoc::OnEdge4()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = (int)m_inH;
	m_outW = (int)m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int scale = 3;
	int sc = scale - 1;
	//마스크 설정

	double mask[3][3] = { {0,-1,-2}, // 엣지 마스크
						 {1,0,-1},
						 {2,1,0} };
	//

	double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageR[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
		}
	}

	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];

			tmpOutImageR[i][k] = S;
		}
	}

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageG[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];

			tmpOutImageG[i][k] = S;
		}
	}

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageB[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];

			tmpOutImageB[i][k] = S;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}
	OnFree2D(tmpInImageR, m_inH + sc);
	OnFree2D(tmpInImageG, m_inH + sc);
	OnFree2D(tmpInImageB, m_inH + sc);
	OnFree2D(tmpOutImageR, m_inH);
	OnFree2D(tmpOutImageG, m_inH);
	OnFree2D(tmpOutImageB, m_inH);
}

void CColorImageProcessingDoc::OnEdge5()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = (int)m_inH;
	m_outW = (int)m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int scale = 3;
	int sc = scale - 1;
	//마스크 설정

	double mask[3][3] = { {0,-2,-2}, // 엣지 마스크
							 {2,0,-2},
							 {2,2,0} };
	//

	double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageR[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
		}
	}

	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];

			tmpOutImageR[i][k] = S;
		}
	}

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageG[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];

			tmpOutImageG[i][k] = S;
		}
	}

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageB[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];

			tmpOutImageB[i][k] = S;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}
	OnFree2D(tmpInImageR, m_inH + sc);
	OnFree2D(tmpInImageG, m_inH + sc);
	OnFree2D(tmpInImageB, m_inH + sc);
	OnFree2D(tmpOutImageR, m_inH);
	OnFree2D(tmpOutImageG, m_inH);
	OnFree2D(tmpOutImageB, m_inH);
}

void CColorImageProcessingDoc::OnEdge6()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	for (int i = 1; i < m_inH - 1; i++) {
		for (int k = 1; k < m_inW - 1; k++) {
			int max = 0;
			for (int m = -1; m < 2; m++)
				for (int n = -1; n < 2; n++)
					if ((m_inImageR[i][k] - m_inImageR[i + m][k + n]) >= max)
						max = m_inImageR[i][k] - m_inImageR[i + m][k + n];

			m_outImageR[i][k] = max;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_outImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (m_outImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
		}
	}

	for (int i = 1; i < m_inH - 1; i++) {
		for (int k = 1; k < m_inW - 1; k++) {
			int max = 0;
			for (int m = -1; m < 2; m++)
				for (int n = -1; n < 2; n++)
					if ((m_inImageG[i][k] - m_inImageG[i + m][k + n]) >= max)
						max = m_inImageG[i][k] - m_inImageG[i + m][k + n];

			m_outImageG[i][k] = max;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_outImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (m_outImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
		}
	}

	for (int i = 1; i < m_inH - 1; i++) {
		for (int k = 1; k < m_inW - 1; k++) {
			int max = 0;
			for (int m = -1; m < 2; m++)
				for (int n = -1; n < 2; n++)
					if ((m_inImageB[i][k] - m_inImageB[i + m][k + n]) >= max)
						max = m_inImageB[i][k] - m_inImageB[i + m][k + n];

			m_outImageB[i][k] = max;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_outImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (m_outImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
		}
	}

}

void CColorImageProcessingDoc::OnEdge7()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	for (int i = 1; i < m_inH - 1; i++) {
		for (int k = 1; k < m_inW - 1; k++) {
			int max = 0;
			if ((m_inImageR[i - 1][k - 1] - m_inImageR[i + 1][k + 1]) >= max)
				max = (m_inImageR[i - 1][k - 1] - m_inImageR[i + 1][k + 1]);
			if ((m_inImageR[i - 1][k] - m_inImageR[i + 1][k]) >= max)
				max = (m_inImageR[i - 1][k] - m_inImageR[i + 1][k]);
			if ((m_inImageR[i - 1][k + 1] - m_inImageR[i + 1][k - 1]) >= max)
				max = (m_inImageR[i - 1][k + 1] - m_inImageR[i + 1][k - 1]);
			if ((m_inImageR[i][k - 1] - m_inImageR[i][k + 1]) >= max)
				max = (m_inImageR[i][k - 1] - m_inImageR[i][k + 1]);

			m_outImageR[i][k] = max;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_outImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (m_outImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
		}
	}

	for (int i = 1; i < m_inH - 1; i++) {
		for (int k = 1; k < m_inW - 1; k++) {
			int max = 0;
			if ((m_inImageG[i - 1][k - 1] - m_inImageG[i + 1][k + 1]) >= max)
				max = (m_inImageG[i - 1][k - 1] - m_inImageG[i + 1][k + 1]);
			if ((m_inImageG[i - 1][k] - m_inImageG[i + 1][k]) >= max)
				max = (m_inImageG[i - 1][k] - m_inImageG[i + 1][k]);
			if ((m_inImageG[i - 1][k + 1] - m_inImageG[i + 1][k - 1]) >= max)
				max = (m_inImageG[i - 1][k + 1] - m_inImageG[i + 1][k - 1]);
			if ((m_inImageG[i][k - 1] - m_inImageG[i][k + 1]) >= max)
				max = (m_inImageG[i][k - 1] - m_inImageG[i][k + 1]);

			m_outImageG[i][k] = max;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_outImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (m_outImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
		}
	}

	for (int i = 1; i < m_inH - 1; i++) {
		for (int k = 1; k < m_inW - 1; k++) {
			int max = 0;
			if ((m_inImageB[i - 1][k - 1] - m_inImageB[i + 1][k + 1]) >= max)
				max = (m_inImageB[i - 1][k - 1] - m_inImageB[i + 1][k + 1]);
			if ((m_inImageB[i - 1][k] - m_inImageB[i + 1][k]) >= max)
				max = (m_inImageB[i - 1][k] - m_inImageB[i + 1][k]);
			if ((m_inImageB[i - 1][k + 1] - m_inImageB[i + 1][k - 1]) >= max)
				max = (m_inImageB[i - 1][k + 1] - m_inImageB[i + 1][k - 1]);
			if ((m_inImageB[i][k - 1] - m_inImageB[i][k + 1]) >= max)
				max = (m_inImageB[i][k - 1] - m_inImageB[i][k + 1]);

			m_outImageB[i][k] = max;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_outImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (m_outImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
		}
	}
}

void CColorImageProcessingDoc::OnEdge8()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int scale = 3;
	int sc = scale - 1;
	//마스크 설정

	double mask[3][3] = { {0,-1,0}, // 엣지 마스크
						 {-1,4,-1},
						 {0,-1,0} };
	//

	double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageR[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
		}
	}

	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];

			tmpOutImageR[i][k] = S;
		}
	}

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageG[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];

			tmpOutImageG[i][k] = S;
		}
	}

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageB[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];

			tmpOutImageB[i][k] = S;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}
	OnFree2D(tmpInImageR, m_inH + sc);
	OnFree2D(tmpInImageG, m_inH + sc);
	OnFree2D(tmpInImageB, m_inH + sc);
	OnFree2D(tmpOutImageR, m_inH);
	OnFree2D(tmpOutImageG, m_inH);
	OnFree2D(tmpOutImageB, m_inH);

}

void CColorImageProcessingDoc::OnEdge9()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int scale = 3;
	int sc = scale - 1;
	//마스크 설정

	double mask[3][3] = { {1,1,1}, // 엣지 마스크
						 {1,-8,1},
						 {1,1,1} };

	//

	double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageR[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
		}
	}

	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];

			tmpOutImageR[i][k] = S;
		}
	}

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageG[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];

			tmpOutImageG[i][k] = S;
		}
	}

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageB[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];

			tmpOutImageB[i][k] = S;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}
	OnFree2D(tmpInImageR, m_inH + sc);
	OnFree2D(tmpInImageG, m_inH + sc);
	OnFree2D(tmpInImageB, m_inH + sc);
	OnFree2D(tmpOutImageR, m_inH);
	OnFree2D(tmpOutImageG, m_inH);
	OnFree2D(tmpOutImageB, m_inH);
}

void CColorImageProcessingDoc::OnEdge10()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int scale = 3;
	int sc = scale - 1;
	//마스크 설정

	double mask[3][3] = { {-1,-1,-1}, // 엣지 마스크
						 {-1,8,-1},
						 {-1,-1,-1} };
	//

	double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageR[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
		}
	}

	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];

			tmpOutImageR[i][k] = S;
		}
	}

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageG[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];

			tmpOutImageG[i][k] = S;
		}
	}

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageB[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];

			tmpOutImageB[i][k] = S;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}
	OnFree2D(tmpInImageR, m_inH + sc);
	OnFree2D(tmpInImageG, m_inH + sc);
	OnFree2D(tmpInImageB, m_inH + sc);
	OnFree2D(tmpOutImageR, m_inH);
	OnFree2D(tmpOutImageG, m_inH);
	OnFree2D(tmpOutImageB, m_inH);
}

void CColorImageProcessingDoc::OnEdge11()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int scale = 5;
	int sc = scale - 1;
	//마스크 설정

	double mask[5][5] = { { 0, 0,-1, 0, 0}, // 엣지 마스크
						 { 0,-1,-2,-1, 0},
						 {-1,-2,16,-2,-1},
						 { 0,-1,-2,-1, 0},
						 { 0, 0,-1, 0, 0} };

	//

	double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageR[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
		}
	}

	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];

			tmpOutImageR[i][k] = S;
		}
	}

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageG[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];

			tmpOutImageG[i][k] = S;
		}
	}

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageB[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];

			tmpOutImageB[i][k] = S;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}
	OnFree2D(tmpInImageR, m_inH + sc);
	OnFree2D(tmpInImageG, m_inH + sc);
	OnFree2D(tmpInImageB, m_inH + sc);
	OnFree2D(tmpOutImageR, m_inH);
	OnFree2D(tmpOutImageG, m_inH);
	OnFree2D(tmpOutImageB, m_inH);
}

void CColorImageProcessingDoc::OnDog1()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int scale = 7;
	int sc = scale - 1;
	//마스크 설정

	double mask[7][7] = { { 0, 0,-1,-1,-1, 0, 0}, // 엣지 마스크
						 { 0,-2,-3,-3,-3,-2, 0},
						 {-1,-3, 5, 5, 5,-3,-1},
						 {-1,-3, 5,16, 5,-3,-1},
						 {-1,-3, 5, 5, 5,-3,-1},
						 { 0,-2,-3,-3,-3,-2, 0},
						 { 0, 0,-1,-1,-1, 0, 0} };
	//

	double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageR[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
		}
	}

	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];

			tmpOutImageR[i][k] = S;
		}
	}

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageG[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];

			tmpOutImageG[i][k] = S;
		}
	}

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageB[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];

			tmpOutImageB[i][k] = S;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}
	OnFree2D(tmpInImageR, m_inH + sc);
	OnFree2D(tmpInImageG, m_inH + sc);
	OnFree2D(tmpInImageB, m_inH + sc);
	OnFree2D(tmpOutImageR, m_inH);
	OnFree2D(tmpOutImageG, m_inH);
	OnFree2D(tmpOutImageB, m_inH);
}

void CColorImageProcessingDoc::OnDog2()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = m_inH;
	m_outW = m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int scale = 9;
	int sc = scale - 1;
	//마스크 설정

	double mask[9][9] = { { 0, 0, 0,-1,-1,-1, 0, 0, 0}, // 엣지 마스크
						 { 0,-2,-3,-3,-3,-3,-3,-2, 0},
						 { 0,-3,-2,-1,-1,-1,-2,-3, 0},
						 {-1,-3,-1, 9, 9, 9,-1,-3,-1},
						 {-1,-3,-1, 9, 19, 9,-1,-3,-1},
						 {-1,-3,-1, 9, 9, 9,-1,-3,-1},
						 { 0,-3,-2,-1,-1,-1,-2,-3, 0},
						 { 0,-2,-3,-3,-3,-3,-3,-2, 0},
						 { 0, 0, 0,-1,-1,-1, 0, 0, 0} };
	//

	double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageR[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
		}
	}

	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageR[i + m][k + n] * mask[m][n];

			tmpOutImageR[i][k] = S;
		}
	}

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageG[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageG[i + m][k + n] * mask[m][n];

			tmpOutImageG[i][k] = S;
		}
	}

	for (int i = sc / 2; i < m_inH + sc / 2; i++) {
		for (int k = sc / 2; k < m_inW + sc / 2; k++) {
			tmpInImageB[i][k] = 0;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			S = 0.0;

			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S += tmpInImageB[i + m][k + n] * mask[m][n];

			tmpOutImageB[i][k] = S;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageG[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];
		}
	}
	OnFree2D(tmpInImageR, m_inH + sc);
	OnFree2D(tmpInImageG, m_inH + sc);
	OnFree2D(tmpInImageB, m_inH + sc);
	OnFree2D(tmpOutImageR, m_inH);
	OnFree2D(tmpOutImageG, m_inH);
	OnFree2D(tmpOutImageB, m_inH);
}

void CColorImageProcessingDoc::OnHSIEdge1()
{
		OnFreeOutImage();
		m_outH = (int)m_inH;
		m_outW = (int)m_inW;
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		int scale = 3;
		int sc = scale - 1;

		double mask[3][3] = { { 0,-1, 0},          // 엣지 마스크
								  { 0, 1, 0},
								  { 0, 0, 0} };

		double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
		double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
		double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

		double** tmpInImageH = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpInImageS = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
		double** tmpInImageI = OnMalloc2D_Double(m_inH + sc, m_inW + sc);

		for (int i = 0; i < m_inH + 2; i++)
			for (int k = 0; k < m_inW + 2; k++)
				tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

		for (int i = 0; i < m_inH; i++)
			for (int k = 0; k < m_inW; k++) {
				tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
				tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
				tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
			}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				double* hsi;
				double R, G, B;
				R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
				hsi = RGB2HSI(R, G, B);

				double H, S, I;
				H = hsi[0]; S = hsi[1]; I = hsi[2];
				tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
			}
		}

		for (int i = 0; i < m_inH; i++) {
			for (int k = 0; k < m_inW; k++) {
				double S_VALUE = 0.0;
				for (int m = 0; m < scale; m++)
					for (int n = 0; n < scale; n++)
						S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
				tmpInImageI[i][k] = S_VALUE;
			}
		}

		for (int i = 0; i < m_inH; i++)
			for (int k = 0; k < m_inW; k++) {
				double* rgb;
				double H, S, I;

				H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

				rgb = HSI2RGB2(H, S, I);
				tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
			}

		for (int i = 0; i < m_outH; i++)
			for (int k = 0; k < m_outW; k++) {
				if (tmpOutImageR[i][k] < 0.0)
					m_outImageR[i][k] = 0;
				else if (tmpOutImageR[i][k] > 255.0)
					m_outImageR[i][k] = 255;
				else
					m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

				if (tmpOutImageG[i][k] < 0.0)
					m_outImageG[i][k] = 0;
				else if (tmpOutImageG[i][k] > 255.0)
					m_outImageB[i][k] = 255;
				else
					m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

				if (tmpOutImageB[i][k] < 0.0)
					m_outImageB[i][k] = 0;
				else if (tmpOutImageB[i][k] > 255.0)
					m_outImageB[i][k] = 255;
				else
					m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

			}
		OnFree2D(tmpInImageR, m_inH + sc);
		OnFree2D(tmpInImageG, m_inH + sc);
		OnFree2D(tmpInImageB, m_inH + sc);
		OnFree2D(tmpOutImageR, m_inH);
		OnFree2D(tmpOutImageG, m_inH);
		OnFree2D(tmpOutImageB, m_inH);
		OnFree2D(tmpInImageH, m_inH + sc);
		OnFree2D(tmpInImageS, m_inH + sc);
		OnFree2D(tmpInImageI, m_inH + sc);
	
}

void CColorImageProcessingDoc::OnHSIEdge2()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = (int)m_inH;
	m_outW = (int)m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int scale = 3;
	int sc = scale - 1;

	double mask[3][3] = { {0,0,0}, // 엣지 마스크
						 {-1,1,0},
						 {0,0,0} };

	double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

	double** tmpInImageH = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageS = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageI = OnMalloc2D_Double(m_inH + sc, m_inW + sc);

	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
			tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
			tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
		}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			double R, G, B;
			R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			double* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB2(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}

	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}
	OnFree2D(tmpInImageR, m_inH + sc);
	OnFree2D(tmpInImageG, m_inH + sc);
	OnFree2D(tmpInImageB, m_inH + sc);
	OnFree2D(tmpOutImageR, m_inH);
	OnFree2D(tmpOutImageG, m_inH);
	OnFree2D(tmpOutImageB, m_inH);
	OnFree2D(tmpInImageH, m_inH + sc);
	OnFree2D(tmpInImageS, m_inH + sc);
	OnFree2D(tmpInImageI, m_inH + sc);

}

void CColorImageProcessingDoc::OnHSIEdge3()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = (int)m_inH;
	m_outW = (int)m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int scale = 3;
	int sc = scale - 1;

	double mask[3][3] = { {-1,0,-1}, // 엣지 마스크
					 {0,2,0},
					 {0,0,0} };

	double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

	double** tmpInImageH = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageS = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageI = OnMalloc2D_Double(m_inH + sc, m_inW + sc);

	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
			tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
			tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
		}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			double R, G, B;
			R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			double* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB2(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}

	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}
	OnFree2D(tmpInImageR, m_inH + sc);
	OnFree2D(tmpInImageG, m_inH + sc);
	OnFree2D(tmpInImageB, m_inH + sc);
	OnFree2D(tmpOutImageR, m_inH);
	OnFree2D(tmpOutImageG, m_inH);
	OnFree2D(tmpOutImageB, m_inH);
	OnFree2D(tmpInImageH, m_inH + sc);
	OnFree2D(tmpInImageS, m_inH + sc);
	OnFree2D(tmpInImageI, m_inH + sc);

}

void CColorImageProcessingDoc::OnHSIEdge4()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = (int)m_inH;
	m_outW = (int)m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int scale = 3;
	int sc = scale - 1;

	double mask[3][3] = { {0,-1,-2}, // 엣지 마스크
						 {1,0,-1},
						 {2,1,0} };

	double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

	double** tmpInImageH = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageS = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageI = OnMalloc2D_Double(m_inH + sc, m_inW + sc);

	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
			tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
			tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
		}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			double R, G, B;
			R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			double* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB2(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}

	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}
	OnFree2D(tmpInImageR, m_inH + sc);
	OnFree2D(tmpInImageG, m_inH + sc);
	OnFree2D(tmpInImageB, m_inH + sc);
	OnFree2D(tmpOutImageR, m_inH);
	OnFree2D(tmpOutImageG, m_inH);
	OnFree2D(tmpOutImageB, m_inH);
	OnFree2D(tmpInImageH, m_inH + sc);
	OnFree2D(tmpInImageS, m_inH + sc);
	OnFree2D(tmpInImageI, m_inH + sc);

}

void CColorImageProcessingDoc::OnHSIEdge5()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = (int)m_inH;
	m_outW = (int)m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int scale = 3;
	int sc = scale - 1;

	double mask[3][3] = { {0,-2,-2}, // 엣지 마스크
							 {2,0,-2},
							 {2,2,0} };

	double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

	double** tmpInImageH = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageS = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageI = OnMalloc2D_Double(m_inH + sc, m_inW + sc);

	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
			tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
			tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
		}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			double R, G, B;
			R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			double* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB2(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}

	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}
	OnFree2D(tmpInImageR, m_inH + sc);
	OnFree2D(tmpInImageG, m_inH + sc);
	OnFree2D(tmpInImageB, m_inH + sc);
	OnFree2D(tmpOutImageR, m_inH);
	OnFree2D(tmpOutImageG, m_inH);
	OnFree2D(tmpOutImageB, m_inH);
	OnFree2D(tmpInImageH, m_inH + sc);
	OnFree2D(tmpInImageS, m_inH + sc);
	OnFree2D(tmpInImageI, m_inH + sc);

}

void CColorImageProcessingDoc::OnHSIEdge6()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = (int)m_inH;
	m_outW = (int)m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int scale = 3;
	int sc = scale - 1;

	//

	double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

	double** tmpInImageH = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageS = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageI = OnMalloc2D_Double(m_inH + sc, m_inW + sc);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
			tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
			tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// *** 연산	
	
	for (int i = 1; i < m_inH - 1; i++) {
		for (int k = 1; k < m_inW - 1; k++) {
			int max = 0;
			for (int m = -1; m < 2; m++)
				for (int n = -1; n < 2; n++)
					if ((tmpInImageI[i][k] - tmpInImageI[i + m][k + n]) >= max)
						max = tmpInImageI[i][k] - tmpInImageI[i + m][k + n];

			tmpInImageI[i][k] = max;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpInImageI[i][k] < 0.0)
				tmpInImageI[i][k] = 0;
			else if (tmpInImageI[i][k] > 255.0)
				tmpInImageI[i][k] = 255;
		}
	}

	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			double* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB2(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}
	OnFree2D(tmpInImageR, m_inH + sc);
	OnFree2D(tmpInImageG, m_inH + sc);
	OnFree2D(tmpInImageB, m_inH + sc);
	OnFree2D(tmpOutImageR, m_inH);
	OnFree2D(tmpOutImageG, m_inH);
	OnFree2D(tmpOutImageB, m_inH);
	OnFree2D(tmpInImageH, m_inH + sc);
	OnFree2D(tmpInImageS, m_inH + sc);
	OnFree2D(tmpInImageI, m_inH + sc);
}

void CColorImageProcessingDoc::OnHSIEdge7()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = (int)m_inH;
	m_outW = (int)m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int scale = 3;
	int sc = scale - 1;

	//

	double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

	double** tmpInImageH = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageS = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageI = OnMalloc2D_Double(m_inH + sc, m_inW + sc);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	// 입력메모리 --> 임시입력메모리
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
			tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
			tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			unsigned char R, G, B;
			R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}
	// *** 연산	

	for (int i = 1; i < m_inH - 1; i++) {
		for (int k = 1; k < m_inW - 1; k++) {
			int max = 0;
			if ((tmpInImageI[i - 1][k - 1] - tmpInImageI[i + 1][k + 1]) >= max)
				max = (tmpInImageI[i - 1][k - 1] - tmpInImageI[i + 1][k + 1]);
			if ((tmpInImageI[i - 1][k] - tmpInImageI[i + 1][k]) >= max)
				max = (tmpInImageI[i - 1][k] - tmpInImageI[i + 1][k]);
			if ((tmpInImageI[i - 1][k + 1] - tmpInImageI[i + 1][k - 1]) >= max)
				max = (tmpInImageI[i - 1][k + 1] - tmpInImageI[i + 1][k - 1]);
			if ((tmpInImageI[i][k - 1] - tmpInImageI[i][k + 1]) >= max)
				max = (tmpInImageI[i][k - 1] - tmpInImageI[i][k + 1]);

			tmpInImageI[i][k] = max;
		}
	}

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpInImageI[i][k] < 0.0)
				tmpInImageI[i][k] = 0;
			else if (tmpInImageI[i][k] > 255.0)
				tmpInImageI[i][k] = 255;
		}
	}


	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			double* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB2(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}


	// 임시 출력 이미지 ---> 출력 이미지
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}
	OnFree2D(tmpInImageR, m_inH + sc);
	OnFree2D(tmpInImageG, m_inH + sc);
	OnFree2D(tmpInImageB, m_inH + sc);
	OnFree2D(tmpOutImageR, m_inH);
	OnFree2D(tmpOutImageG, m_inH);
	OnFree2D(tmpOutImageB, m_inH);
	OnFree2D(tmpInImageH, m_inH + sc);
	OnFree2D(tmpInImageS, m_inH + sc);
	OnFree2D(tmpInImageI, m_inH + sc);

}

void CColorImageProcessingDoc::OnHSIEdge8()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = (int)m_inH;
	m_outW = (int)m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int scale = 3;
	int sc = scale - 1;

	double mask[3][3] = { {0,-1,0}, // 엣지 마스크
						 {-1,4,-1},
						 {0,-1,0} };

	double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

	double** tmpInImageH = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageS = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageI = OnMalloc2D_Double(m_inH + sc, m_inW + sc);

	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
			tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
			tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
		}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			double R, G, B;
			R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			double* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB2(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}

	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}
	OnFree2D(tmpInImageR, m_inH + sc);
	OnFree2D(tmpInImageG, m_inH + sc);
	OnFree2D(tmpInImageB, m_inH + sc);
	OnFree2D(tmpOutImageR, m_inH);
	OnFree2D(tmpOutImageG, m_inH);
	OnFree2D(tmpOutImageB, m_inH);
	OnFree2D(tmpInImageH, m_inH + sc);
	OnFree2D(tmpInImageS, m_inH + sc);
	OnFree2D(tmpInImageI, m_inH + sc);

}

void CColorImageProcessingDoc::OnHSIEdge9()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = (int)m_inH;
	m_outW = (int)m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int scale = 3;
	int sc = scale - 1;

	double mask[3][3] = { {1,1,1}, // 엣지 마스크
						 {1,-8,1},
						 {1,1,1} };

	double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

	double** tmpInImageH = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageS = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageI = OnMalloc2D_Double(m_inH + sc, m_inW + sc);

	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
			tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
			tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
		}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			double R, G, B;
			R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			double* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB2(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}

	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}
	OnFree2D(tmpInImageR, m_inH + sc);
	OnFree2D(tmpInImageG, m_inH + sc);
	OnFree2D(tmpInImageB, m_inH + sc);
	OnFree2D(tmpOutImageR, m_inH);
	OnFree2D(tmpOutImageG, m_inH);
	OnFree2D(tmpOutImageB, m_inH);
	OnFree2D(tmpInImageH, m_inH + sc);
	OnFree2D(tmpInImageS, m_inH + sc);
	OnFree2D(tmpInImageI, m_inH + sc);

}

void CColorImageProcessingDoc::OnHSIEdge10()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = (int)m_inH;
	m_outW = (int)m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int scale = 3;
	int sc = scale - 1;

	double mask[3][3] = { {-1,-1,-1}, // 엣지 마스크
						 {-1,8,-1},
						 {-1,-1,-1} };

	double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

	double** tmpInImageH = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageS = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageI = OnMalloc2D_Double(m_inH + sc, m_inW + sc);

	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
			tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
			tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
		}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			double R, G, B;
			R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			double* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB2(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}

	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}
	OnFree2D(tmpInImageR, m_inH + sc);
	OnFree2D(tmpInImageG, m_inH + sc);
	OnFree2D(tmpInImageB, m_inH + sc);
	OnFree2D(tmpOutImageR, m_inH);
	OnFree2D(tmpOutImageG, m_inH);
	OnFree2D(tmpOutImageB, m_inH);
	OnFree2D(tmpInImageH, m_inH + sc);
	OnFree2D(tmpInImageS, m_inH + sc);
	OnFree2D(tmpInImageI, m_inH + sc);

}

void CColorImageProcessingDoc::OnHSIEdge11()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = (int)m_inH;
	m_outW = (int)m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int scale = 5;
	int sc = scale - 1;

	double mask[5][5] = { { 0, 0,-1, 0, 0}, // 엣지 마스크
						 { 0,-1,-2,-1, 0},
						 {-1,-2,16,-2,-1},
						 { 0,-1,-2,-1, 0},
						 { 0, 0,-1, 0, 0} };

	double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

	double** tmpInImageH = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageS = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageI = OnMalloc2D_Double(m_inH + sc, m_inW + sc);

	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
			tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
			tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
		}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			double R, G, B;
			R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			double* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB2(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}

	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}
	OnFree2D(tmpInImageR, m_inH + sc);
	OnFree2D(tmpInImageG, m_inH + sc);
	OnFree2D(tmpInImageB, m_inH + sc);
	OnFree2D(tmpOutImageR, m_inH);
	OnFree2D(tmpOutImageG, m_inH);
	OnFree2D(tmpOutImageB, m_inH);
	OnFree2D(tmpInImageH, m_inH + sc);
	OnFree2D(tmpInImageS, m_inH + sc);
	OnFree2D(tmpInImageI, m_inH + sc);

}

void CColorImageProcessingDoc::OnHSIDog1()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = (int)m_inH;
	m_outW = (int)m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int scale = 7;
	int sc = scale - 1;

	double mask[7][7] = { { 0, 0,-1,-1,-1, 0, 0}, // 엣지 마스크
						 { 0,-2,-3,-3,-3,-2, 0},
						 {-1,-3, 5, 5, 5,-3,-1},
						 {-1,-3, 5,16, 5,-3,-1},
						 {-1,-3, 5, 5, 5,-3,-1},
						 { 0,-2,-3,-3,-3,-2, 0},
						 { 0, 0,-1,-1,-1, 0, 0} };

	double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

	double** tmpInImageH = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageS = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageI = OnMalloc2D_Double(m_inH + sc, m_inW + sc);

	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
			tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
			tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
		}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			double R, G, B;
			R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			double* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB2(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}

	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}
	OnFree2D(tmpInImageR, m_inH + sc);
	OnFree2D(tmpInImageG, m_inH + sc);
	OnFree2D(tmpInImageB, m_inH + sc);
	OnFree2D(tmpOutImageR, m_inH);
	OnFree2D(tmpOutImageG, m_inH);
	OnFree2D(tmpOutImageB, m_inH);
	OnFree2D(tmpInImageH, m_inH + sc);
	OnFree2D(tmpInImageS, m_inH + sc);
	OnFree2D(tmpInImageI, m_inH + sc);

}

void CColorImageProcessingDoc::OnHSIDog2()
{
	// TODO: 여기에 구현 코드 추가.
	OnFreeOutImage();
	m_outH = (int)m_inH;
	m_outW = (int)m_inW;
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);

	int scale = 9;
	int sc = scale - 1;

	double mask[9][9] = { { 0, 0, 0,-1,-1,-1, 0, 0, 0}, // 엣지 마스크
							 { 0,-2,-3,-3,-3,-3,-3,-2, 0},
							 { 0,-3,-2,-1,-1,-1,-2,-3, 0},
							 {-1,-3,-1, 9, 9, 9,-1,-3,-1},
							 {-1,-3,-1, 9, 19, 9,-1,-3,-1},
							 {-1,-3,-1, 9, 9, 9,-1,-3,-1},
							 { 0,-3,-2,-1,-1,-1,-2,-3, 0},
							 { 0,-2,-3,-3,-3,-3,-3,-2, 0},
							 { 0, 0, 0,-1,-1,-1, 0, 0, 0} };

	double** tmpInImageR = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageR = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageG = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageG = OnMalloc2D_Double(m_inH, m_inW);
	double** tmpInImageB = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpOutImageB = OnMalloc2D_Double(m_inH, m_inW);

	double** tmpInImageH = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageS = OnMalloc2D_Double(m_inH + sc, m_inW + sc);
	double** tmpInImageI = OnMalloc2D_Double(m_inH + sc, m_inW + sc);

	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++)
			tmpInImageR[i][k] = tmpInImageG[i][k] = tmpInImageB[i][k] = 127.0;

	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			tmpInImageR[i + sc / 2][k + sc / 2] = m_inImageR[i][k];
			tmpInImageG[i + sc / 2][k + sc / 2] = m_inImageG[i][k];
			tmpInImageB[i + sc / 2][k + sc / 2] = m_inImageB[i][k];
		}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double* hsi;
			double R, G, B;
			R = tmpInImageR[i][k]; G = tmpInImageG[i][k]; B = tmpInImageB[i][k];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;
			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][k] = H; tmpInImageS[i][k] = S; tmpInImageI[i][k] = I;
		}
	}

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			double S_VALUE = 0.0;
			for (int m = 0; m < scale; m++)
				for (int n = 0; n < scale; n++)
					S_VALUE += tmpInImageI[i + m][k + n] * mask[m][n];
			tmpInImageI[i][k] = S_VALUE;
		}
	}

	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++) {
			double* rgb;
			double H, S, I;

			H = tmpInImageH[i][k]; S = tmpInImageS[i][k]; I = tmpInImageI[i][k];

			rgb = HSI2RGB2(H, S, I);
			tmpOutImageR[i][k] = rgb[0]; tmpOutImageG[i][k] = rgb[1]; tmpOutImageB[i][k] = rgb[2];
		}

	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImageR[i][k] < 0.0)
				m_outImageR[i][k] = 0;
			else if (tmpOutImageR[i][k] > 255.0)
				m_outImageR[i][k] = 255;
			else
				m_outImageR[i][k] = (unsigned char)tmpOutImageR[i][k];

			if (tmpOutImageG[i][k] < 0.0)
				m_outImageG[i][k] = 0;
			else if (tmpOutImageG[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageG[i][k] = (unsigned char)tmpOutImageG[i][k];

			if (tmpOutImageB[i][k] < 0.0)
				m_outImageB[i][k] = 0;
			else if (tmpOutImageB[i][k] > 255.0)
				m_outImageB[i][k] = 255;
			else
				m_outImageB[i][k] = (unsigned char)tmpOutImageB[i][k];

		}
	OnFree2D(tmpInImageR, m_inH + sc);
	OnFree2D(tmpInImageG, m_inH + sc);
	OnFree2D(tmpInImageB, m_inH + sc);
	OnFree2D(tmpOutImageR, m_inH);
	OnFree2D(tmpOutImageG, m_inH);
	OnFree2D(tmpOutImageB, m_inH);
	OnFree2D(tmpInImageH, m_inH + sc);
	OnFree2D(tmpInImageS, m_inH + sc);
	OnFree2D(tmpInImageI, m_inH + sc);
}

void CColorImageProcessingDoc::OnMiniSave()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_outImageR == NULL) {
		return;
	}
	OnFree2D(m_inImageR, m_inH);
	OnFree2D(m_inImageG, m_inH);
	OnFree2D(m_inImageB, m_inH);
	m_inImageR = m_inImageG = m_inImageB = NULL;
	m_inH = m_inW = 0;

	m_inH = m_outH;
	m_inW = m_outW;

	m_inImageR = OnMalloc2D(m_inH, m_inW);
	m_inImageG = OnMalloc2D(m_inH, m_inW);
	m_inImageB = OnMalloc2D(m_inH, m_inW);

	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_inImageR[i][k] = m_outImageR[i][k];
			m_inImageG[i][k] = m_outImageG[i][k];
			m_inImageB[i][k] = m_outImageB[i][k];
		}
	}
	OnFreeOutImage();
}

BOOL CColorImageProcessingDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if (m_outImageR == NULL)
		return FALSE;
	CImage image;
	image.Create(m_outW, m_outH, 32);
	unsigned char R, G, B;
	COLORREF px;
	for (int i = 0; i < m_outW; i++)
		for (int k = 0; k < m_outH; k++) {
			R = m_outImageR[k][i];
			G = m_outImageG[k][i];
			B = m_outImageB[k][i];
			px = RGB(R, G, B);
			image.SetPixel(i, k, px);
		}
	image.Save(lpszPathName, Gdiplus::ImageFormatPNG);
	MessageBox(NULL, L"저장", L"성공", NULL);
	return TRUE;
}
