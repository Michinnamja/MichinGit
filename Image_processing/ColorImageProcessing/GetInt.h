#pragma once
#include "afxdialogex.h"


// CGetInt 대화 상자

class CGetInt : public CDialogEx
{
	DECLARE_DYNAMIC(CGetInt)

public:
	CGetInt(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CGetInt();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GET_INT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
