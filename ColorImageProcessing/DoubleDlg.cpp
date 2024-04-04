// DoubleDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageProcessing.h"
#include "afxdialogex.h"
#include "DoubleDlg.h"


// CDoubleDlg 대화 상자

IMPLEMENT_DYNAMIC(CDoubleDlg, CDialog)

CDoubleDlg::CDoubleDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DOUBLE, pParent)
	, m_double(0)
{

}

CDoubleDlg::~CDoubleDlg()
{
}

void CDoubleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DOUBLE, m_double);
}


BEGIN_MESSAGE_MAP(CDoubleDlg, CDialog)
END_MESSAGE_MAP()


// CDoubleDlg 메시지 처리기
