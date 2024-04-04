#pragma once
#include "afxdialogex.h"


// CHIGHLIGHT 대화 상자

class CHIGHLIGHT : public CDialog
{
	DECLARE_DYNAMIC(CHIGHLIGHT)

public:
	CHIGHLIGHT(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CHIGHLIGHT();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HILIGHT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_highmin;
	int m_highmax;
};
