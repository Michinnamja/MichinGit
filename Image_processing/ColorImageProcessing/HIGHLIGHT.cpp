// HIGHLIGHT.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageProcessing.h"
#include "afxdialogex.h"
#include "HIGHLIGHT.h"


// CHIGHLIGHT 대화 상자

IMPLEMENT_DYNAMIC(CHIGHLIGHT, CDialog)

CHIGHLIGHT::CHIGHLIGHT(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_HILIGHT, pParent)
	, m_highmin(0)
	, m_highmax(0)
{

}

CHIGHLIGHT::~CHIGHLIGHT()
{
}

void CHIGHLIGHT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_HIGH_MIN, m_highmin);
	DDX_Text(pDX, IDC_EDIT_HIGH_MAX, m_highmax);
}


BEGIN_MESSAGE_MAP(CHIGHLIGHT, CDialog)
END_MESSAGE_MAP()


// CHIGHLIGHT 메시지 처리기
