// GetInt.cpp: 구현 파일
//

#include "pch.h"
#include "ColorImageProcessing.h"
#include "afxdialogex.h"
#include "GetInt.h"


// CGetInt 대화 상자

IMPLEMENT_DYNAMIC(CGetInt, CDialogEx)

CGetInt::CGetInt(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GET_INT, pParent)
{

}

CGetInt::~CGetInt()
{
}

void CGetInt::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGetInt, CDialogEx)
END_MESSAGE_MAP()


// CGetInt 메시지 처리기
